#pragma once

#include "ILogger.h"
#include <fstream>

class ILoggerImpl : public ILogger
{
public:

	RESULT_CODE setLogFile(const char* pLogFile) override;
	void log(char const* pMsg, RESULT_CODE err) override;
	void destroyLogger(void* pClient) override;
	~ILoggerImpl();

private:
	std::ofstream logStream;
	const char* resultCodeToStr(RESULT_CODE res);
};
