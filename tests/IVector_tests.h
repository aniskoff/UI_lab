#ifndef VECTOR_IVECTOR_TESTS_H
#define VECTOR_IVECTOR_TESTS_H

#include "../ILogger/ILogger.h"

namespace IVectorTests
{
    bool testClone(ILogger* logger);
    bool testAdd(ILogger* logger);
    bool testSub(ILogger* logger);
    bool testScaleMul(ILogger* logger);
    bool testMul(ILogger* logger);
    bool testEquals(ILogger* logger);
    bool testSetAndGetCoord(ILogger* logger);
    bool testNanValue(ILogger* logger);
    void runAllTests(ILogger* logger);
}


#endif //VECTOR_IVECTOR_TESTS_H
