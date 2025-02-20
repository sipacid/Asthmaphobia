#include "logger.h"
#include <ctime>
#include <filesystem>
#include <KnownFolders.h>
#include <shlobj_core.h>

using namespace Asthmaphobia;

constexpr std::string_view Logger::LevelToString(const Level level)
{
	switch (level)
	{
	case Level::Debug:
		return "[Debug]";
	case Level::Info:
		return "[Info]";
	case Level::Warning:
		return "[Warning]";
	case Level::Error:
		return "[Error]";
	default:
		return "[Unknown]";
	}
}

constexpr WORD Logger::LevelToColor(const Level level)
{
	switch (level)
	{
	case Level::Debug:
		return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	case Level::Info:
		return FOREGROUND_GREEN | FOREGROUND_BLUE;
	case Level::Warning:
		return FOREGROUND_RED | FOREGROUND_GREEN;
	case Level::Error:
		return FOREGROUND_RED;
	default:
		return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
}

std::string Logger::GetAppDataPath()
{
	PWSTR path = nullptr;
	std::string result;

	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path)))
	{
		std::wstring widePath(path);
		result = std::string(widePath.begin(), widePath.end()) + "\\Asthmaphobia";
		CoTaskMemFree(path);
	}

	return result;
}

bool Logger::InitializeLogDirectory()
{
	try
	{
		if (!std::filesystem::exists(GetAppDataPath()))
		{
			std::filesystem::create_directories(GetAppDataPath());
		}

		const std::string logDir = GetAppDataPath() + "\\logs";
		std::filesystem::create_directories(logDir);

		const auto now = std::time(nullptr);
		std::tm timeinfo;
		localtime_s(&timeinfo, &now);

		char timestamp[32];
		std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", &timeinfo);

		LogFilePath = logDir + "\\log_" + timestamp + ".txt";
		FileOut.open(LogFilePath, std::ios_base::out | std::ios_base::app);

		return FileOut.is_open();
	}
	catch (const std::exception&)
	{
		return false;
	}
}

Logger::Logger(Level minLevel) : minLevel(minLevel), ConsoleExists(false), HConsole(nullptr)
{
	if (!InitializeLogDirectory())
	{
		throw std::runtime_error("Failed to initialize log directory");
	}

	ConsoleExists = AttachConsole(GetCurrentProcessId());
	if (!ConsoleExists)
	{
		AllocConsole();
	}

	FILE* dummy;
	freopen_s(&dummy, "CONOUT$", "w", stdout);

	HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (HConsole)
	{
		DWORD consoleMode;
		GetConsoleMode(HConsole, &consoleMode);
		SetConsoleMode(HConsole, consoleMode & ~ENABLE_QUICK_EDIT_MODE);

		SetConsoleTitleA("[Debug] Asthmaphobia");
		SetConsoleOutputCP(CP_UTF8);
	}

	logger = this;
}

Logger::~Logger()
{
	if (FileOut.is_open())
		FileOut.close();

	if (!ConsoleExists)
		FreeConsole();

	logger = nullptr;
}

std::string Logger::GetTimestamp()
{
	char timestamp[32];
	const auto now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);
	std::strftime(timestamp, sizeof(timestamp), "%H:%M:%S", &timeinfo);
	return timestamp;
}

void Logger::Log(const Level level, const std::string_view message)
{
	if (level < minLevel)
		return;

	std::lock_guard lock(logMutex);

	const auto timestamp = GetTimestamp();
	const auto levelStr = LevelToString(level);

	if (HConsole)
	{
		SetConsoleTextAttribute(HConsole, LevelToColor(level));
		std::cout << levelStr << ' ' << message << "\n";
	}

	FileOut << '[' << timestamp << "] " << levelStr << ' ' << message << "\n";
	FileOut.flush();
}
