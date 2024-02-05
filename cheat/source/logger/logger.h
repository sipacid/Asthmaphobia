#pragma once
#include "source/common.h"

#ifdef _DEBUG
#define DEBUG_LOG(message) \
    if (Asthmaphobia::logger) { \
        Asthmaphobia::logger->Log(Logger::LogType::Debug, message); \
    }
#else
#define DEBUG_LOG(message)
#endif

namespace Asthmaphobia
{
	class Logger
	{
	public:
		enum LogType : uint8_t
		{
			Debug,
			Info,
			Warning,
			Error
		};

		explicit Logger();
		~Logger();
		void Log(LogType type, const std::string& message);

	private:
		bool ConsoleExists{};
		HANDLE HConsole{};
		std::ofstream ConsoleOut{};
	};

	inline Logger* logger{};
}
