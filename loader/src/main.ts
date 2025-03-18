import { invoke } from "@tauri-apps/api/core";

document.addEventListener("DOMContentLoaded", () => {
  // Get references to DOM elements
  const injectForm = document.getElementById("inject-form") as HTMLFormElement;
  const isLoadedInput = document.getElementById(
    "is-loaded-input"
  ) as HTMLInputElement;
  const injectBtn = document.querySelector(".inject-btn") as HTMLButtonElement;
  const injectStatus = document.getElementById(
    "inject-status"
  ) as HTMLDivElement;
  const gameStatusDot = document.getElementById(
    "game-status-dot"
  ) as HTMLDivElement;
  const gameStatusText = document.getElementById(
    "game-status"
  ) as HTMLSpanElement;
  const cheatVersionElement = document.getElementById(
    "cheat-version"
  ) as HTMLSpanElement;
  const newsList = document.getElementById("news-list") as HTMLUListElement;

  // Create a new status indicator for cheat status
  const statusIndicators = document.querySelector(
    ".status-indicators"
  ) as HTMLDivElement;
  const cheatStatusIndicator = document.createElement("div");
  cheatStatusIndicator.className = "status-pill";

  const cheatStatusDot = document.createElement("div");
  cheatStatusDot.className = "indicator-dot";
  cheatStatusDot.id = "cheat-status-dot";

  const cheatStatusText = document.createElement("span");
  cheatStatusText.id = "cheat-status";
  cheatStatusText.textContent = "Not Injected";

  cheatStatusIndicator.appendChild(cheatStatusDot);
  cheatStatusIndicator.appendChild(cheatStatusText);
  statusIndicators.appendChild(cheatStatusIndicator);

  // Function to update game status indicator
  async function updateGameStatus() {
    const gameRunning = await invoke<boolean>("check_game_status");

    if (gameRunning) {
      gameStatusDot.classList.add("active");
      gameStatusText.textContent = "Running";
    } else {
      gameStatusDot.classList.remove("active");
      gameStatusText.textContent = "Not Detected";
    }
  }

  // Function to update cheat status indicator
  async function updateCheatStatus() {
    const isInjected = await invoke<boolean>("is_cheat_injected");

    if (isInjected) {
      cheatStatusDot.classList.add("active");
      cheatStatusText.textContent = "Injected";
      injectBtn.disabled = true;
      injectBtn.textContent = "CHEAT INJECTED";
      injectBtn.classList.remove("pulse");
    } else {
      cheatStatusDot.classList.remove("active");
      cheatStatusText.textContent = "Not Injected";
      injectBtn.disabled = false;
      injectBtn.textContent = "INJECT CHEAT";
      injectBtn.classList.add("pulse");
    }
  }

  // Fetch latest cheat version
  async function fetchLatestVersion() {
    try {
      // Get the latest version from API
      const versionInfo = await invoke<{
        latest_version: string;
        release_date: string;
        changelog: string[];
      }>("fetch_latest_version");

      // Display the version
      cheatVersionElement.textContent = versionInfo.latest_version;

      // Add tooltip with changelog and release date
      const tooltipText = `Released: ${versionInfo.release_date}\n${versionInfo.changelog}`;
      cheatVersionElement.title = tooltipText;
      cheatVersionElement.classList.add("with-tooltip");
    } catch (error) {
      console.error("Error fetching latest version:", error);
      // Set a placeholder if API fails
      cheatVersionElement.textContent = "Unknown";
    }
  }

  // Fetch news from API
  async function fetchNews() {
    try {
      newsList.innerHTML = '<li class="news-item loading">Loading news...</li>';

      const news = await invoke<
        {
          id: number;
          title: string;
          date: string;
          category: string;
          version: string;
          content: string[];
        }[]
      >("fetch_news");

      if (news.length === 0) {
        newsList.innerHTML = '<li class="news-item">No news available</li>';
        return;
      }

      newsList.innerHTML = "";
      news.forEach((item) => {
        const newsItem = document.createElement("li");
        newsItem.className = "news-item";

        const newsHeader = document.createElement("div");
        newsHeader.className = "news-header";

        const titleSpan = document.createElement("span");
        titleSpan.className = "news-title";
        titleSpan.textContent = item.title;

        const newsInfo = document.createElement("div");
        newsInfo.className = "news-info";

        const dateSpan = document.createElement("span");
        dateSpan.className = "news-date";
        dateSpan.textContent = item.date;

        const categoryBadge = document.createElement("span");
        categoryBadge.className = `news-category ${item.category.toLowerCase()}`;
        categoryBadge.textContent = item.category;

        newsInfo.appendChild(dateSpan);
        newsInfo.appendChild(categoryBadge);

        // Only add version badge if version exists and is not empty
        if (item.version && item.version.trim() !== "") {
          const versionBadge = document.createElement("span");
          versionBadge.className = "news-version";
          versionBadge.textContent = item.version;
          newsInfo.appendChild(versionBadge);
        }

        newsHeader.appendChild(titleSpan);
        newsHeader.appendChild(newsInfo);

        const contentDiv = document.createElement("div");
        contentDiv.className = "news-content";

        item.content.forEach((paragraph) => {
          const p = document.createElement("p");
          p.textContent = paragraph;
          contentDiv.appendChild(p);
        });

        newsItem.appendChild(newsHeader);
        newsItem.appendChild(contentDiv);
        newsList.appendChild(newsItem);
      });

      // Set the last news date
      const lastNewsDate = document.getElementById("last-news-date");
      if (lastNewsDate && news.length > 0) {
        lastNewsDate.textContent = `Last updated: ${news[0].date}`;
      }
    } catch (error) {
      newsList.innerHTML = `<li class="news-item error">Failed to load news: ${error}</li>`;
      console.error("News fetch error:", error);
    }
  }

  // Handle form submission for injection
  injectForm.addEventListener("submit", async (e) => {
    e.preventDefault();

    if (!isLoadedInput.checked) {
      injectStatus.textContent =
        "Please confirm you're in the Phasmophobia lobby";
      injectStatus.classList.add("error");
      return;
    }

    try {
      injectBtn.disabled = true;
      injectBtn.textContent = "INJECTING...";
      injectStatus.textContent = "Injecting cheat, please wait...";
      injectStatus.classList.remove("error");

      const result = await invoke<string>("inject");

      if (result.includes("successfully")) {
        injectStatus.textContent = "Cheat successfully injected!";
        // Update the cheat injected status immediately
        await updateCheatStatus();
      } else if (result.includes("already injected")) {
        injectStatus.textContent = "Cheat is already injected";
        await updateCheatStatus();
      } else {
        injectStatus.textContent = result;
        injectStatus.classList.add("error");
        injectBtn.disabled = false;
        injectBtn.textContent = "INJECT CHEAT";
      }
    } catch (error) {
      injectStatus.textContent = `Error: ${error}`;
      injectStatus.classList.add("error");
      injectBtn.disabled = false;
      injectBtn.textContent = "INJECT CHEAT";
    }
  });

  // Initialize the app
  async function initApp() {
    await Promise.all([
      updateGameStatus(),
      updateCheatStatus(),
      fetchLatestVersion(),
      fetchNews(),
    ]);

    // Set up interval to check game and cheat status
    setInterval(updateGameStatus, 5000);
    setInterval(updateCheatStatus, 5000);
  }

  // Start the app
  initApp();
});
