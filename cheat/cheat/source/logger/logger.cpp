#include "logger.h"
#include <ctime>
#include <filesystem>
#include <print>
#include <KnownFolders.h>
#include <shlobj_core.h>

using namespace Asthmaphobia;

constexpr std::string_view Logger::LevelToString(const Level level)
{
	switch (level)
	{
	case Level::Call:
		return "[Call]";
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
	case Level::Call:
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

bool Logger::InitializeLogDirectory()
{
	try
	{
		Helper::CreateAsthmaphobiaDirectory();

		const std::string logDir = Helper::GetAsthmaphobiaDirectory() + "\\logs";
		if (!std::filesystem::exists(logDir))
			std::filesystem::create_directories(logDir);

		const auto now = std::time(nullptr);
		std::tm timeinfo;
		localtime_s(&timeinfo, &now);

		char timestamp[32];
		std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", &timeinfo);

		LogFilePath = logDir + "\\log_" + timestamp + ".txt";
		FileOut.open(LogFilePath, std::ios_base::out | std::ios_base::app);

		FileOut.rdbuf()->pubsetbuf(nullptr, 0);

		return FileOut.is_open();
	}
	catch (const std::exception&)
	{
		return false;
	}
}

Logger::Logger(Level minLevel) : MinLevel(minLevel)
#ifdef _DEBUG
                                 , ConsoleExists(false), HConsole(nullptr)
#endif


{
	if (!InitializeLogDirectory())
		throw std::runtime_error("Failed to initialize log directory");

#ifdef _DEBUG
	ConsoleExists = AttachConsole(GetCurrentProcessId());
	if (!ConsoleExists)
		ConsoleExists = AllocConsole();

	FILE* dummy;
	freopen_s(&dummy, "CONOUT$", "w", stdout);
	HConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (HConsole && HConsole != INVALID_HANDLE_VALUE)
	{
		DWORD consoleMode;
		if (GetConsoleMode(HConsole, &consoleMode))
		{
			SetConsoleMode(HConsole, consoleMode & ~ENABLE_QUICK_EDIT_MODE);
			SetConsoleTitleA("[Debug] Asthmaphobia");
			SetConsoleOutputCP(CP_UTF8);
		}
	}
#endif

	logger = this;
}

Logger::~Logger()
{
	if (FileOut.is_open())
		FileOut.close();


#ifdef _DEBUG
	if (ConsoleExists)
		FreeConsole();
#endif

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

void Logger::ActualLog(const Level level, const std::string_view message)
{
	if (level < MinLevel)
		return;

	std::lock_guard lock(LogMutex);
	const auto timestamp = GetTimestamp();
	const auto levelStr = LevelToString(level);

#ifdef _DEBUG
	if (HConsole && HConsole != INVALID_HANDLE_VALUE)
	{
		SetConsoleTextAttribute(HConsole, LevelToColor(level));
		std::println("{} {}", levelStr.data(), message.data());
		fflush(stdout);
	}
#endif

	if (level > Level::Call && FileOut.is_open() && FileOut.good())
	{
		FileOut << '[' << timestamp << "] " << levelStr << ' ' << message << "\n";
		FileOut.flush();
	}
}
