#include "logger.h"

using namespace Asthmaphobia;

Logger::Logger()
{
	if (!((ConsoleExists = AttachConsole(GetCurrentProcessId()))))
		AllocConsole();

	if ((HConsole = GetStdHandle(STD_OUTPUT_HANDLE)) != nullptr)
	{
		SetConsoleTitleA("[Debug] Asthmaphobia");
		SetConsoleOutputCP(CP_UTF8);

		ConsoleOut.open("CONOUT$", std::ios_base::out | std::ios_base::app);
		logger = this;
	}
}

Logger::~Logger()
{
	if (!ConsoleExists)
		FreeConsole();

	logger = nullptr;
}

void Logger::Log(const LogType type, const std::string& message)
{
	switch (type)
	{
	case Debug:
		SetConsoleTextAttribute(HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		ConsoleOut << "[Debug] " << message << std::endl;
		break;
	case Info:
		SetConsoleTextAttribute(HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		ConsoleOut << "[Info] " << message << std::endl;
		break;
	case Warning:
		SetConsoleTextAttribute(HConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		ConsoleOut << "[Warning] " << message << std::endl;
		break;
	case Error:
		SetConsoleTextAttribute(HConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
		ConsoleOut << "[Error] " << message << std::endl;
		break;
	}
}
