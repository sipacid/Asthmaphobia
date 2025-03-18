use rand::distr::Alphanumeric;
use rand::{rng, Rng};
use reqwest;
use serde::{Deserialize, Serialize};
use std::ffi::CString;
use std::fs;
use std::io::{Error as IoError, Result as IoResult};
use std::path::Path;
use std::ptr;
use std::sync::atomic::{AtomicBool, Ordering};
use std::thread;
use std::time::Duration;
use sysinfo::System;
use winapi::shared::minwindef::{DWORD, FALSE};
use winapi::um::handleapi::{CloseHandle, INVALID_HANDLE_VALUE};
use winapi::um::libloaderapi::{GetModuleHandleA, GetProcAddress};
use winapi::um::memoryapi::{VirtualAllocEx, WriteProcessMemory};
use winapi::um::processthreadsapi::{CreateRemoteThread, OpenProcess};
use winapi::um::tlhelp32::{
    CreateToolhelp32Snapshot, Module32First, Module32Next, Process32First, Process32Next,
    MODULEENTRY32, PROCESSENTRY32, TH32CS_SNAPMODULE, TH32CS_SNAPMODULE32, TH32CS_SNAPPROCESS,
};
use winapi::um::winnt::PROCESS_ALL_ACCESS;

// Update NewsItem struct and add NewsResponse wrapper
#[derive(Debug, Serialize, Deserialize)]
struct NewsResponse {
    items: Vec<NewsItem>,
}

#[derive(Debug, Serialize, Deserialize)]
struct NewsItem {
    id: i32,
    title: String,
    date: String,
    category: String,
    #[serde(default)]
    version: String,
    content: Vec<String>,
}

#[derive(Debug, Serialize, Deserialize)]
struct VersionInfo {
    latest_version: String,
    release_date: String,
    changelog: Vec<String>,
}

// Static flag to track if cheat is already injected
static CHEAT_INJECTED: AtomicBool = AtomicBool::new(false);

// Get process ID by name
fn get_process_id_by_name(process_name: &str) -> Option<DWORD> {
    unsafe {
        let h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if h_snapshot == INVALID_HANDLE_VALUE {
            return None;
        }

        let mut process_entry = PROCESSENTRY32 {
            dwSize: std::mem::size_of::<PROCESSENTRY32>() as u32,
            cntUsage: 0,
            th32ProcessID: 0,
            th32DefaultHeapID: 0,
            th32ModuleID: 0,
            cntThreads: 0,
            th32ParentProcessID: 0,
            pcPriClassBase: 0,
            dwFlags: 0,
            szExeFile: [0; 260],
        };

        let target_name = process_name.to_lowercase();

        if Process32First(h_snapshot, &mut process_entry) != 0 {
            loop {
                // Convert i8 array to u8 slice for from_utf8_lossy
                let current_name = std::string::String::from_utf8_lossy(
                    &process_entry
                        .szExeFile
                        .iter()
                        .take_while(|&&c| c != 0) // Stop at null terminator
                        .map(|&c| c as u8)
                        .collect::<Vec<u8>>(),
                )
                .to_string()
                .to_lowercase();

                // Check if this process name contains our target name or vice versa
                if current_name.contains(&target_name) || target_name.contains(&current_name) {
                    CloseHandle(h_snapshot);
                    return Some(process_entry.th32ProcessID);
                }

                if Process32Next(h_snapshot, &mut process_entry) == 0 {
                    break;
                }
            }
        }

        CloseHandle(h_snapshot);
        None
    }
}

// Generate a random string for temporary DLL name
fn generate_random_string(length: usize) -> String {
    rng()
        .sample_iter(&Alphanumeric)
        .take(length)
        .map(char::from)
        .collect()
}

// Inject DLL into a process
fn inject_dll(process_id: DWORD, dll_path: &Path) -> IoResult<bool> {
    unsafe {
        // Open the target process
        let h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
        if h_process.is_null() {
            return Err(IoError::last_os_error());
        }

        // Convert DLL path to C string
        let dll_path_str = dll_path.to_string_lossy().to_string();
        let c_dll_path = match CString::new(dll_path_str.clone()) {
            Ok(path) => path,
            Err(_) => {
                CloseHandle(h_process);
                return Err(IoError::new(
                    std::io::ErrorKind::InvalidInput,
                    "Invalid DLL path",
                ));
            }
        };

        // Allocate memory in the target process
        let path_len = dll_path_str.len() + 1; // +1 for null terminator
        let remote_buffer = VirtualAllocEx(
            h_process,
            ptr::null_mut(),
            path_len,
            winapi::um::winnt::MEM_COMMIT | winapi::um::winnt::MEM_RESERVE,
            winapi::um::winnt::PAGE_READWRITE,
        );

        if remote_buffer.is_null() {
            CloseHandle(h_process);
            return Err(IoError::last_os_error());
        }

        // Write the DLL path to the allocated memory
        // Fix: Use proper c_void type from winapi
        let bytes_written: usize = 0;
        let write_result = WriteProcessMemory(
            h_process,
            remote_buffer,
            c_dll_path.as_ptr() as *const winapi::ctypes::c_void,
            path_len,
            &bytes_written as *const usize as *mut usize,
        );

        if write_result == 0 {
            CloseHandle(h_process);
            return Err(IoError::last_os_error());
        }

        // Get address of LoadLibraryA
        let kernel32 = GetModuleHandleA(b"kernel32.dll\0".as_ptr() as *const i8);
        let load_library_addr = GetProcAddress(kernel32, b"LoadLibraryA\0".as_ptr() as *const i8);

        if load_library_addr.is_null() {
            CloseHandle(h_process);
            return Err(IoError::last_os_error());
        }

        // Create a remote thread to call LoadLibraryA
        let h_thread = CreateRemoteThread(
            h_process,
            ptr::null_mut(),
            0,
            Some(std::mem::transmute(load_library_addr)),
            remote_buffer,
            0,
            ptr::null_mut(),
        );

        if h_thread.is_null() {
            CloseHandle(h_process);
            return Err(IoError::last_os_error());
        }

        // Wait for the thread to complete
        winapi::um::synchapi::WaitForSingleObject(h_thread, winapi::um::winbase::INFINITE);

        // Cleanup
        CloseHandle(h_thread);
        CloseHandle(h_process);

        Ok(true)
    }
}

// Get remote module handle by module name
fn get_remote_module_handle(
    process_id: DWORD,
    module_name: &str,
) -> Option<winapi::shared::minwindef::HMODULE> {
    unsafe {
        let snapshot =
            CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);

        if snapshot == INVALID_HANDLE_VALUE {
            return None;
        }

        let mut module_entry = MODULEENTRY32 {
            dwSize: std::mem::size_of::<MODULEENTRY32>() as u32,
            th32ModuleID: 0,
            th32ProcessID: 0,
            GlblcntUsage: 0,
            ProccntUsage: 0,
            modBaseAddr: ptr::null_mut(),
            modBaseSize: 0,
            hModule: ptr::null_mut(),
            szModule: [0; 256],
            szExePath: [0; 260],
        };

        if Module32First(snapshot, &mut module_entry) != 0 {
            loop {
                // Convert i8 array to u8 slice properly handling null terminators
                let current_name = std::string::String::from_utf8_lossy(
                    &module_entry
                        .szModule
                        .iter()
                        .take_while(|&&c| c != 0) // Stop at null terminator
                        .map(|&c| c as u8)
                        .collect::<Vec<u8>>(),
                )
                .to_string()
                .to_lowercase();

                let target_name = module_name.to_lowercase();

                // Try various matching strategies
                if current_name == target_name
                    || current_name.contains(&target_name)
                    || target_name.contains(&current_name)
                {
                    CloseHandle(snapshot);
                    return Some(module_entry.hModule);
                }

                if Module32Next(snapshot, &mut module_entry) == 0 {
                    break;
                }
            }
        }

        CloseHandle(snapshot);
        None
    }
}

// Get remote export address
fn get_remote_export_address(
    dll_path: &str,
    export_name: &str,
    remote_base: winapi::shared::minwindef::HMODULE,
) -> Option<winapi::shared::minwindef::FARPROC> {
    unsafe {
        let c_dll_path = match CString::new(dll_path) {
            Ok(path) => path,
            Err(_) => return None,
        };

        let c_export_name = match CString::new(export_name) {
            Ok(name) => name,
            Err(_) => return None,
        };

        let local_module = winapi::um::libloaderapi::LoadLibraryExA(
            c_dll_path.as_ptr(),
            ptr::null_mut(),
            winapi::um::libloaderapi::DONT_RESOLVE_DLL_REFERENCES,
        );

        if local_module.is_null() {
            return None;
        }

        let local_export =
            winapi::um::libloaderapi::GetProcAddress(local_module, c_export_name.as_ptr());

        if local_export.is_null() {
            winapi::um::libloaderapi::FreeLibrary(local_module);
            return None;
        }

        let offset = local_export as usize - local_module as usize;
        winapi::um::libloaderapi::FreeLibrary(local_module);

        Some(std::mem::transmute(remote_base as usize + offset))
    }
}

// Download a file from URL
async fn download_file(url: &str, file_path: &Path) -> Result<(), String> {
    let response = match reqwest::get(url).await {
        Ok(resp) => {
            if !resp.status().is_success() {
                return Err(format!(
                    "Failed to download file: HTTP status {}",
                    resp.status()
                ));
            }
            resp
        }
        Err(e) => return Err(format!("Failed to download file: {}", e)),
    };

    let bytes = match response.bytes().await {
        Ok(b) => b,
        Err(e) => return Err(format!("Failed to read response body: {}", e)),
    };

    match fs::write(file_path, bytes) {
        Ok(_) => Ok(()),
        Err(e) => Err(format!("Failed to write file: {}", e)),
    }
}

#[tauri::command]
async fn inject() -> String {
    // Check if the cheat is already injected
    if CHEAT_INJECTED.load(Ordering::SeqCst) {
        return "Cheat is already injected".to_string();
    }

    // Find the Phasmophobia process - try multiple possible names
    let mut process_id = get_process_id_by_name("Phasmophobia.exe");

    if process_id.is_none() {
        process_id = get_process_id_by_name("Phasmophobia");
    }

    if process_id.is_none() {
        // One last attempt with just "phasmo" in case the executable name is different
        process_id = get_process_id_by_name("phasmo");
    }

    let process_id = match process_id {
        Some(pid) => pid,
        None => {
            return "Error: Phasmophobia process not found. Make sure the game is running."
                .to_string()
        }
    };

    // Generate a random name for the DLL
    let random_name = format!("{}.dll", generate_random_string(12));
    let temp_dir = std::env::temp_dir();
    let temp_dll_path = temp_dir.join(&random_name);

    // Download the DLL from our server
    let download_url = "https://asthmaphobia.xyz/cheat.dll";
    match download_file(download_url, &temp_dll_path).await {
        Ok(_) => {}
        Err(e) => return format!("Error downloading DLL: {}", e),
    }

    // Inject the DLL
    match inject_dll(process_id, &temp_dll_path) {
        Ok(_) => {
            // Wait longer for module to load
            thread::sleep(Duration::from_millis(2000));

            // First try with the exact random name
            let mut module_handle = get_remote_module_handle(process_id, &random_name);

            // If that fails, try with just the base name (without path)
            if module_handle.is_none() {
                let base_name = Path::new(&random_name)
                    .file_name()
                    .and_then(|n| n.to_str())
                    .unwrap_or(&random_name);

                module_handle = get_remote_module_handle(process_id, base_name);

                // If still not found, try again after waiting a bit longer
                if module_handle.is_none() {
                    thread::sleep(Duration::from_millis(3000));
                    module_handle = get_remote_module_handle(process_id, base_name);
                }
            }

            let module_handle = match module_handle {
                Some(handle) => handle,
                None => {
                    // Mark the file for deletion when the process exits
                    unsafe {
                        let c_path = match CString::new(temp_dll_path.to_string_lossy().to_string()) {
                            Ok(p) => p,
                            Err(_) => return "DLL injected but failed to get module handle and couldn't mark for deletion".to_string(),
                        };
                        winapi::um::winbase::MoveFileExA(
                            c_path.as_ptr(),
                            ptr::null(),
                            winapi::um::winbase::MOVEFILE_DELAY_UNTIL_REBOOT,
                        );
                    }

                    // Even if we couldn't get the module handle, we'll consider it injected
                    // because the DLL may still be working
                    CHEAT_INJECTED.store(true, Ordering::SeqCst);
                    return "DLL injected but couldn't verify module handle. Cheat should still work.".to_string();
                }
            };

            // Create the custom thread
            let dll_path_str = temp_dll_path.to_string_lossy().to_string();
            unsafe {
                let h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
                if h_process.is_null() {
                    // Mark the file for deletion when the process exits
                    let c_path = match CString::new(temp_dll_path.to_string_lossy().to_string()) {
                        Ok(p) => p,
                        Err(_) => return "Failed to open process for thread creation and couldn't mark DLL for deletion".to_string(),
                    };
                    winapi::um::winbase::MoveFileExA(
                        c_path.as_ptr(),
                        ptr::null(),
                        winapi::um::winbase::MOVEFILE_DELAY_UNTIL_REBOOT,
                    );
                    return "Failed to open process for thread creation".to_string();
                }

                // Get the address of our custom thread function
                if let Some(thread_proc) =
                    get_remote_export_address(&dll_path_str, "AsthmaphobiaThread", module_handle)
                {
                    let h_thread = CreateRemoteThread(
                        h_process,
                        ptr::null_mut(),
                        0,
                        Some(std::mem::transmute(thread_proc)),
                        ptr::null_mut(),
                        0,
                        ptr::null_mut(),
                    );

                    if h_thread.is_null() {
                        CloseHandle(h_process);
                        // Mark the file for deletion when the process exits
                        let c_path = match CString::new(temp_dll_path.to_string_lossy().to_string()) {
                            Ok(p) => p,
                            Err(_) => return "Failed to create custom thread and couldn't mark DLL for deletion".to_string(),
                        };
                        winapi::um::winbase::MoveFileExA(
                            c_path.as_ptr(),
                            ptr::null(),
                            winapi::um::winbase::MOVEFILE_DELAY_UNTIL_REBOOT,
                        );
                        return "Failed to create custom thread".to_string();
                    }

                    CloseHandle(h_thread);
                    CloseHandle(h_process);
                } else {
                    CloseHandle(h_process);
                    // Mark the file for deletion when the process exits
                    let c_path = match CString::new(temp_dll_path.to_string_lossy().to_string()) {
                        Ok(p) => p,
                        Err(_) => return "Failed to get thread procedure address and couldn't mark DLL for deletion".to_string(),
                    };
                    winapi::um::winbase::MoveFileExA(
                        c_path.as_ptr(),
                        ptr::null(),
                        winapi::um::winbase::MOVEFILE_DELAY_UNTIL_REBOOT,
                    );
                    return "Failed to get thread procedure address".to_string();
                }
            }

            // Mark the file for deletion when the process exits
            // Windows allows this operation even when the file is currently in use
            unsafe {
                let c_path = CString::new(temp_dll_path.to_string_lossy().to_string()).unwrap();
                winapi::um::winbase::MoveFileExA(
                    c_path.as_ptr(),
                    ptr::null(),
                    winapi::um::winbase::MOVEFILE_DELAY_UNTIL_REBOOT,
                );
            }

            // Set injected flag to true
            CHEAT_INJECTED.store(true, Ordering::SeqCst);

            "DLL successfully injected and custom thread created".to_string()
        }
        Err(e) => {
            // In this case, the DLL wasn't successfully injected, so we can delete it
            let _ = fs::remove_file(&temp_dll_path);
            format!("Failed to inject DLL: {}", e)
        }
    }
}

#[tauri::command]
fn check_game_status() -> bool {
    // Try the process ID method first for consistency with injection
    if get_process_id_by_name("Phasmophobia.exe").is_some()
        || get_process_id_by_name("Phasmophobia").is_some()
        || get_process_id_by_name("phasmo").is_some()
    {
        return true;
    }

    // Fall back to the sysinfo method as a secondary check
    let system = System::new_all();
    for (_pid, process) in system.processes() {
        // Convert OsStr to a regular string before converting to lowercase
        let process_name = process.name().to_string_lossy().to_string().to_lowercase();
        if process_name.contains("phasmophobia") || process_name.contains("phasmo") {
            return true;
        }
    }

    false
}

#[tauri::command]
fn is_cheat_injected() -> bool {
    CHEAT_INJECTED.load(Ordering::SeqCst)
}

#[tauri::command]
async fn fetch_news() -> Result<Vec<NewsItem>, String> {
    let response = match reqwest::get("https://asthmaphobia.xyz/api/news.json").await {
        Ok(resp) => {
            if !resp.status().is_success() {
                return Err(format!("API returned error status: {}", resp.status()));
            }
            resp
        }
        Err(e) => return Err(format!("Failed to fetch news: {}", e)),
    };

    // Get the raw response text for debugging if needed
    let text = match response.text().await {
        Ok(t) => t,
        Err(e) => return Err(format!("Failed to get response text: {}", e)),
    };

    // Try to parse the JSON as a NewsResponse (object with items array)
    let news_response: NewsResponse = match serde_json::from_str(&text) {
        Ok(data) => data,
        Err(e) => {
            return Err(format!(
                "Failed to parse news data: {} - Raw response: {}",
                e,
                if text.len() > 100 {
                    format!("{}...", &text[..100])
                } else {
                    text.clone()
                }
            ))
        }
    };

    Ok(news_response.items)
}

#[tauri::command]
async fn fetch_latest_version() -> Result<VersionInfo, String> {
    let response = match reqwest::get("https://asthmaphobia.xyz/api/version.json").await {
        Ok(resp) => {
            if !resp.status().is_success() {
                return Err(format!("API returned error status: {}", resp.status()));
            }
            resp
        }
        Err(e) => return Err(format!("Failed to fetch version: {}", e)),
    };

    // Get the raw response text for debugging if needed
    let text = match response.text().await {
        Ok(t) => t,
        Err(e) => return Err(format!("Failed to get response text: {}", e)),
    };

    // Try to parse the JSON
    let version_info: VersionInfo = match serde_json::from_str(&text) {
        Ok(data) => data,
        Err(e) => {
            return Err(format!(
                "Failed to parse version data: {} - Raw response: {}",
                e,
                if text.len() > 100 {
                    format!("{}...", &text[..100])
                } else {
                    text.clone()
                }
            ))
        }
    };

    Ok(version_info)
}

#[tauri::command]
fn minimize_window(window: tauri::Window) {
    window.minimize().unwrap();
}

#[tauri::command]
fn close_window(window: tauri::Window) {
    window.close().unwrap();
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .invoke_handler(tauri::generate_handler![
            inject,
            check_game_status,
            is_cheat_injected,
            fetch_news,
            fetch_latest_version,
            minimize_window,
            close_window
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
