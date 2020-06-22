#include <iostream>
#include <tests/SimpleTests.h>
#include <tests/ICompact_tests.h>
#include "tests/ISet_tests.h"
#include "tests/IVector_tests.h"
#include "ICompact/ICompact.h"
#include "ISet/ISet.h"


int main()
{


	const char* logFilePath = "TestingLog.txt";
	ILogger* pLogger = ILogger::createLogger(nullptr);
	RESULT_CODE logRc = pLogger->setLogFile(logFilePath);
	
	std::cout << "Logger created with RESULT_CODE: " << resultCodeToStr(logRc) << std::endl;

	std::cout << "------------------- IVector Tests -------------------" << std::endl;
    IVectorTests::runAllTests(pLogger);

    std::cout << "------------------- ISet Tests -------------------" << std::endl;
    ISetTests::runAllTests(pLogger);

    std::cout << "------------------- ICompact Tests -------------------" << std::endl;
    ICompactTests::runAllTests(pLogger);

}