#include "ILogger.h"
#include "ILoggerImpl.h"

ILogger* ILogger::createLogger(void* pClient)
{
	if (pClient != nullptr)
	{
        return nullptr; // some implementation
	}
	else
	{
		return new ILoggerImpl();
	}
}