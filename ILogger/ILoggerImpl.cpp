#include "ILoggerImpl.h"
#include <fstream>

RESULT_CODE ILoggerImpl::setLogFile(const char* pLogFile)
{
	logStream.open(pLogFile);
	if (logStream.fail())
	{
		return RESULT_CODE::NOT_FOUND;
	}
	
	else
	{
		return RESULT_CODE::SUCCESS;
	}
}

void ILoggerImpl::log(char const* pMsg, RESULT_CODE err)
{
	logStream << resultCodeToStr(err) << " : " << pMsg << std::endl;
}

void ILoggerImpl::destroyLogger(void* pClient)
{
	if (pClient != nullptr)
	{
		// some implementation
	}

	else
	{
		logStream.close();
	}
}

ILoggerImpl::~ILoggerImpl()
{
	logStream.close();
}

const char* ILoggerImpl::resultCodeToStr(RESULT_CODE res)
{
	switch (res)
	{
		case RESULT_CODE::SUCCESS:
			return "SUCCESS";
		
		case RESULT_CODE::OUT_OF_MEMORY:
			return "OUT_OF_MEMORY";

		case RESULT_CODE::BAD_REFERENCE:
			return "BAD_REFERENCE";
			
		case RESULT_CODE::WRONG_DIM:
			return "WRONG_DIM";

		case RESULT_CODE::DIVISION_BY_ZERO:
			return "DIVISION_BY_ZERO";

		case RESULT_CODE::NAN_VALUE:
			return "NAN_VALUE";

		case RESULT_CODE::OUT_OF_BOUNDS:
			return "OUT_OF_BOUNDS";

		case RESULT_CODE::NOT_FOUND:
			return "NOT_FOUND";

		case RESULT_CODE::WRONG_ARGUMENT:
			return "WRONG_ARGUMENT";

		case RESULT_CODE::CALCULATION_ERROR:
			return "CALCULATION_ERROR";

		case RESULT_CODE::MULTIPLE_DEFINITION:
			return "MULTIPLE_DEFINITION";

		default:
			return "UNKNOWN_RESULT_CODE";

	}
}
