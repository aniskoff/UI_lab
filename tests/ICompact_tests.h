#ifndef VECTOR_ICOMPACT_TESTS_H
#define VECTOR_ICOMPACT_TESTS_H

#include "../ILogger/ILogger.h"
namespace ICompactTests
{
    bool testCreate(ILogger* logger);
    bool testClone(ILogger* logger);
    bool testIsContains(ILogger* logger);
    bool testIsSubset(ILogger* logger);
    bool testIsIntersects(ILogger* logger);
    bool testIntersection(ILogger* logger);
    bool testAdd(ILogger* logger);
    bool testMakeConvex(ILogger* logger);
    bool testCreateIterator(ILogger* logger);
    bool testIterator(ILogger* logger);
    bool testSetDirection(ILogger* logger);
    void runAllTests(ILogger* logger);
}


#endif //VECTOR_ICOMPACT_TESTS_H
