#ifndef VECTOR_ISET_TESTS_H
#define VECTOR_ISET_TESTS_H

#include "../ILogger/ILogger.h"

namespace ISetTests
{
    bool testInsert(ILogger* logger);
    bool testClone(ILogger* logger);
    bool testGet(ILogger* logger);
    bool testClear(ILogger* logger);
    bool testErase(ILogger* logger);
    bool testAdd(ILogger* logger);
    bool testIntersect(ILogger* logger);
    void runAllTests(ILogger* logger);
}

#endif //VECTOR_ISET_TESTS_H
