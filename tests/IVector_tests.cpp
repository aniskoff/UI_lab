#include <cmath>
#include <iostream>
#include "../IVector/IVector.h"
#include "IVector_tests.h"

#define EPS 1E-7


using namespace IVectorTests;

bool IVectorTests::testClone(ILogger* logger){
    double arr[2] = {1,2};
    IVector *vec = IVector::createVector(2, arr, logger);
    bool res = true;
    IVector *vecClone = vec->clone();
    for (int i = 0; res && i < 2; ++i) {
        res = vec->getCoord(i) == vecClone->getCoord(i);
    }
    delete vec;
    delete vecClone;
    return res;
}

bool IVectorTests::testAdd(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::add(vec1, vec2, logger);
    bool res = true;
    for (int i = 0; res && i < 2; ++i) {
        res = fabs(vec3->getCoord(i) - (vec1->getCoord(i) + vec2->getCoord(i))) < EPS;
    }
    delete vec1;
    delete vec2;
    delete vec3;
    return res;
}

bool IVectorTests::testSub(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::sub(vec1, vec2, logger);
    bool res = true;
    for (int i = 0; res && i < 2; ++i) {
        res = fabs(vec3->getCoord(i) - (vec1->getCoord(i) - vec2->getCoord(i))) < EPS;
    }
    delete vec1;
    delete vec2;
    delete vec3;
    return res;
}

bool IVectorTests::testScaleMul(ILogger* logger){
    double arr1[2] = {1,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::mul(vec1, 2.0, logger);
    bool res = true;
    for (int i = 0; res && i < 2; ++i) {
        res = fabs(vec2->getCoord(i) - vec1->getCoord(i) * 2.0) < EPS;
    }
    delete vec1;
    delete vec2;
    return res;
}

bool IVectorTests::testMul(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    double ans = IVector::mul(vec1, vec2, logger);
    double realAns = 0;
    for (int i = 0; i < 2; ++i) {
        realAns += vec1->getCoord(i) * vec2->getCoord(i);
    }
    delete vec1;
    delete vec2;
    return fabs(ans - realAns) < EPS;
}

bool IVectorTests::testEquals(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {1.0001,2.0001};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    bool test1, test2;
    IVector::equals(vec1, vec2, IVector::NORM::NORM_1, 0.001, &test1, logger);
    IVector::equals(vec1, vec2, IVector::NORM::NORM_1, 0.00001, &test2, logger);
    delete vec1;
    delete vec2;
    return test1 && !test2;
}

bool IVectorTests::testSetAndGetCoord(ILogger* logger){
    double arr1[2] = {1,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    vec1->setCoord(1, 3);
    bool res = fabs(vec1->getCoord(1) - 3.0) < EPS;
    delete vec1;
    return res;
}

bool IVectorTests::testNanValue(ILogger* logger){
    double arr1[2] = {1,NAN};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    return vec1 == nullptr;
}

void IVectorTests::runAllTests(ILogger* logger){
   std::cout << "ADD VECTORS TESTS | ";
    if (testAdd(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "CLONE VECTOR TESTS | ";
    if (testClone(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "SCALAR MUL VECTORS TESTS | ";
    if (testMul(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "SCALE MUL VECTOR TESTS | ";
    if (testScaleMul(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "SUB VECTORS TESTS | ";
    if (testSub(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "EQUALS VECTORS TESTS | ";
    if (testEquals(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "SET AND GET VECTORS COORD TESTS | ";
    if (testSetAndGetCoord(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "NAN VALUE VECTOR TESTS | ";
    if (testNanValue(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
}
