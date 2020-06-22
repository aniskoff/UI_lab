#pragma once
#include "RC.h"
#include "../ILogger/ILogger.h"

const char* resultCodeToStr(RESULT_CODE res);

void iVectorImplSimpleTest(ILogger* pLogger);

void iSetImplSimpleTest(ILogger* pLogger);