#include <iostream>
#include "ISet_tests.h"
#include "../ISet/ISet.h"

using namespace ISetTests;

bool ISetTests::testInsert(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {1.00001,2.00001};
    double arr3[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::add(vec1, vec3, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec2, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec3, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec4, IVector::NORM::NORM_1, 0.001);
    
    bool res = set1->getSize() == 3;
    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete set1;
    return res;
}

bool ISetTests::testClone(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::add(vec1, vec2, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec2, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec3, IVector::NORM::NORM_1, 0.001);

    
    ISet *set2 = set1->clone();
    if (set1->getSize() != set2->getSize()){
        return false;
    }
    
    bool res = true;
    IVector* vec4 = nullptr, *vec5 = nullptr;
    for (int i = 0; res && i < 3; ++i) {
        set1->get(vec4, i);
        res = set2->get(vec5, vec4, IVector::NORM::NORM_1, 0.00001) == RESULT_CODE::SUCCESS;
        delete vec4;
        delete vec5;
    }

    delete vec1;
    delete vec2;
    delete vec3;
    delete set1;
    delete set2;
    return res;
}

bool ISetTests::testGet(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {1.00001,2.00001};
    double arr3[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::add(vec1, vec3, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec3, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec4, IVector::NORM::NORM_1, 0.001);

    bool test1, test2;
    IVector* vec5 = nullptr;
    test1 = set1->get(vec5, vec2, IVector::NORM::NORM_1, 0.001) == RESULT_CODE::SUCCESS;
    delete vec5;
    test2 = set1->get(vec5, vec2, IVector::NORM::NORM_1, 0.000001) == RESULT_CODE::NOT_FOUND;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete set1;
    return test1 && test2;
}

bool ISetTests::testClear(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::add(vec1, vec2, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec2, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec3, IVector::NORM::NORM_1, 0.001);

    set1->clear();

    bool test1, test2;
    test1 = set1->getSize() == 0;
    test2 = set1->getDim() == 0;

    delete vec1;
    delete vec2;
    delete vec3;
    delete set1;
    return test1 && test2;
}

bool ISetTests::testErase(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {1.00001,2.00001};
    double arr3[2] = {3,2};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::add(vec1, vec3, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec3, IVector::NORM::NORM_1, 0.001);
    set1->insert(vec4, IVector::NORM::NORM_1, 0.001);

    bool test1, test2;
    set1->erase(2);
    IVector* vec5 = nullptr;
    test1 = set1->get(vec5, vec4, IVector::NORM::NORM_1, 0.001) == RESULT_CODE::NOT_FOUND;
    delete vec5;
    test2 = set1->erase(vec2, IVector::NORM::NORM_1, 0.001) == RESULT_CODE::SUCCESS;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete set1;
    return test1 && test2;
}

bool ISetTests::testAdd(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    double arr3[2] = {1.00001,2.00001};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::add(vec1, vec2, logger);
    IVector *vec5 = IVector::mul(vec1, 2.0, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.01);
    set1->insert(vec2, IVector::NORM::NORM_1, 0.01);

    ISet *set2 = ISet::createSet(logger);
    set2->insert(vec5,IVector::NORM::NORM_1, 0.01);
    set2->insert(vec4,IVector::NORM::NORM_1, 0.01);
    set2->insert(vec3, IVector::NORM::NORM_1, 0.01);

    bool test1, test2, test3, test4;
    ISet *unionSet = ISet::add(set1, set2, IVector::NORM::NORM_1, 0.001, logger);
    if (unionSet->getSize() != 4){
        return false;
    };
    IVector* vec6 = nullptr;
    test1 = unionSet->get(vec6, vec1, IVector::NORM::NORM_1, 0.01) == RESULT_CODE::SUCCESS;
    delete vec6;
    test2 = unionSet->get(vec6, vec2, IVector::NORM::NORM_1, 0.01) == RESULT_CODE::SUCCESS;
    delete vec6;
    test3 = unionSet->get(vec6, vec4, IVector::NORM::NORM_1, 0.01) == RESULT_CODE::SUCCESS;
    delete vec6;
    test4 = unionSet->get(vec6, vec5, IVector::NORM::NORM_1, 0.01) == RESULT_CODE::SUCCESS;
    delete vec6;
    delete vec1;
    delete vec2;
    delete vec3;
    delete vec5;
    delete set1;
    delete set2;
    delete unionSet;
    return test1 && test2 && test3 && test4;
}

bool ISetTests::testIntersect(ILogger* logger){
    double arr1[2] = {1,2};
    double arr2[2] = {3,2};
    double arr3[2] = {1.00001,2.00001};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::add(vec1, vec2, logger);
    IVector *vec5 = IVector::mul(vec1, 2.0, logger);
    ISet *set1 = ISet::createSet(logger);

    set1->insert(vec1, IVector::NORM::NORM_1, 0.01);
    set1->insert(vec2, IVector::NORM::NORM_1, 0.01);

    ISet *set2 = ISet::createSet(logger);
    set2->insert(vec5,IVector::NORM::NORM_1, 0.01);
    set2->insert(vec4,IVector::NORM::NORM_1, 0.01);
    set2->insert(vec3, IVector::NORM::NORM_1, 0.01);

    bool test1, test2;
    ISet *intersectSet = ISet::intersect(set1, set2, IVector::NORM::NORM_1, 0.001, logger);
    test1 = intersectSet->getSize() == 1;
    delete intersectSet;
    intersectSet = ISet::intersect(set1, set2, IVector::NORM::NORM_1, 0.000001, logger);
    test2 = intersectSet->getSize() == 0;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec5;
    delete set1;
    delete set2;
    delete intersectSet;
    return test1 && test2;
}

void ISetTests::runAllTests(ILogger* logger){
   std::cout << "INSERT IN SET TESTS | ";
    if (testInsert(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "CLONE SET TESTS | ";
    if (testClone(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "GET FROM SET TESTS | ";
    if (testGet(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "CLEAR SET TEST | ";
    if (testClear(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "ERASE FROM SET TESTS | ";
    if (testErase(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "ADD SETS TESTS | ";
    if (testAdd(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "INTERSECT SETS TESTS | ";
    if (testIntersect(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
}
