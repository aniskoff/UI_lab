#include <iostream>
#include "ICompact_tests.h"
#include "../ICompact/ICompact.h"
#include "../ISet/ISet.h"
#define EPS 1E-7

using namespace ICompactTests;

bool ICompactTests::testCreate(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {1, 5};
    double arr3[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    ICompact *comp1 = ICompact::createCompact(vec3, vec1, logger);
    bool test1, test2, test3, test4;
    test1 = comp1 == nullptr;
    delete comp1;
    comp1 = ICompact::createCompact(vec1, vec2, logger);
    test2 = comp1 != nullptr;
    delete comp1;
    comp1 = ICompact::createCompact(vec1, vec1, logger);
    test3 = comp1 != nullptr;
    delete comp1;
    comp1 = ICompact::createCompact(vec1, vec3, logger);
    test4 = comp1 != nullptr;
    delete vec1;
    delete vec2;
    delete vec3;
    delete comp1;
    return test1 && test2 && test3 && test4;
}

bool ICompactTests::testClone(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);
    ICompact *comp2 = comp1->clone();
    bool test1 = comp1->getDim() == comp2->getDim();
    IVector* vec3, *vec4, *vec5, *vec6;
    vec3 = comp1->getBegin();
    vec4 = comp1->getEnd();
    vec5 = comp2->getBegin();
    vec6 = comp2->getEnd();
    bool test2, test3;
    IVector::equals(vec3, vec5, IVector::NORM::NORM_1, 0.001, &test2, logger);
    IVector::equals(vec4, vec6, IVector::NORM::NORM_1, 0.001, &test3, logger);
    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete vec5;
    delete vec6;
    delete comp1;
    delete comp2;
    return test1 && test2 && test3;
}

bool ICompactTests::testIsContains(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {2, 4};
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    bool test1, test2, test3;
    comp1->isContains(vec1, test1);
    comp1->isContains(vec2, test2);
    comp1->isContains(vec3, test3);
    delete vec1;
    delete vec2;
    delete vec3;
    delete comp1;
    return test1 && test2 && test3;
}

bool ICompactTests::testIsSubset(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {1.5, 3};
    double arr4[2] = {2.5, 4};
    IVector *vec4 = IVector::createVector(2, arr3, logger);
    IVector *vec5 = IVector::createVector(2, arr4, logger);
    ICompact *comp2 = ICompact::createCompact(vec4, vec5, logger);

    ICompact *comp3 = comp1->clone();

    double arr5[2] = {1.5, 3};
    double arr6[2] = {2.5, 6};
    IVector *vec6 = IVector::createVector(2, arr5, logger);
    IVector *vec7 = IVector::createVector(2, arr6, logger);
    ICompact *comp4 = ICompact::createCompact(vec6, vec7, logger);

    bool test1, test2, test3, test4;

    comp1->isSubSet(comp2, test1);
    comp1->isSubSet(comp3, test2);
    comp1->isSubSet(comp1, test3);
    comp1->isSubSet(comp4, test4);

    delete vec1;
    delete vec2;
    delete vec4;
    delete vec5;
    delete vec6;
    delete vec7;
    delete comp1;
    delete comp2;
    delete comp3;
    delete comp4;

    return test1 && test2 && test3 && !test4;
}


bool ICompactTests::testIsIntersects(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {1.5, 3};
    double arr4[2] = {2.5, 4};
    IVector *vec4 = IVector::createVector(2, arr3, logger);
    IVector *vec5 = IVector::createVector(2, arr4, logger);
    ICompact *comp2 = ICompact::createCompact(vec4, vec5, logger);

    ICompact *comp3 = comp1->clone();

    double arr5[2] = {1.5, 3};
    double arr6[2] = {2.5, 6};
    IVector *vec6 = IVector::createVector(2, arr5, logger);
    IVector *vec7 = IVector::createVector(2, arr6, logger);
    ICompact *comp4 = ICompact::createCompact(vec6, vec7, logger);

    double arr7[2] = {3, 5};
    double arr8[2] = {5, 7};
    IVector *vec8 = IVector::createVector(2, arr7, logger);
    IVector *vec9 = IVector::createVector(2, arr8, logger);
    ICompact *comp5 = ICompact::createCompact(vec8, vec9, logger);

    double arr9[2] = {4, 5};
    double arr10[2] = {7, 10};
    IVector *vec10 = IVector::createVector(2, arr9, logger);
    IVector *vec11 = IVector::createVector(2, arr10, logger);
    ICompact *comp6 = ICompact::createCompact(vec10, vec11, logger);

    bool test1, test2, test3, test4, test5, test6;

    comp1->isIntersects(comp2, test1);
    comp1->isIntersects(comp3, test2);
    comp1->isIntersects(comp1, test3);
    comp1->isIntersects(comp4, test4);
    comp1->isIntersects(comp5, test5);
    comp1->isIntersects(comp6, test6);

    delete vec1;
    delete vec2;
    delete vec4;
    delete vec5;
    delete vec6;
    delete vec7;
    delete vec8;
    delete vec9;
    delete vec10;
    delete vec11;

    delete comp1;
    delete comp2;
    delete comp3;
    delete comp4;
    delete comp5;
    delete comp6;

    return test1 && test2 && test3 && test4 && test5 && !test6;
}

bool ICompactTests::testIntersection(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {1.5, 3};
    double arr4[2] = {2.5, 6};
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::createVector(2, arr4, logger);
    ICompact *comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact *comp3 = ICompact::intersection(comp1, comp2, logger);
    if (comp3 != nullptr){
        bool checkBegin, checkEnd;
        IVector *vec5 = comp3->getBegin();
        IVector::equals(vec3, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        double arr[2] = {2.5, 5};
        IVector *vec = IVector::createVector(2, arr, logger);
        IVector::equals(vec, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        delete vec;
        test1 = checkBegin && checkEnd;
    } else{
        test1 = false;
    }

    bool test2;
    double arr5[2] = {4, 5};
    double arr6[2] = {7, 10};
    IVector *vec6 = IVector::createVector(2, arr5, logger);
    IVector *vec7 = IVector::createVector(2, arr6, logger);
    ICompact *comp4 = ICompact::createCompact(vec6, vec7, logger);
    ICompact* comp5 = ICompact::intersection(comp1, comp4, logger);
    test2 = comp5 == nullptr;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete vec6;
    delete vec7;

    delete comp1;
    delete comp2;
    delete comp3;
    delete comp4;
    delete comp5;

    return test1 && test2;
}

bool ICompactTests::testAdd(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {1.5, 3};
    double arr4[2] = {2.5, 4};
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::createVector(2, arr4, logger);
    ICompact *comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact *comp3 = ICompact::add(comp2, comp1, logger);
    IVector *vec5 = nullptr;
    if (comp3 != nullptr){
        bool checkBegin, checkEnd;
        vec5 = comp3->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        IVector::equals(vec2, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test1 = checkBegin && checkEnd;
    } else{
        test1 = false;
    }

    double arr5[2] = {2, 2};
    double arr6[2] = {4, 5};
    IVector *vec6 = IVector::createVector(2, arr5, logger);
    IVector *vec7 = IVector::createVector(2, arr6, logger);
    ICompact *comp4 = ICompact::createCompact(vec6, vec7, logger);

    bool test2;
    ICompact *comp5 = ICompact::add(comp4, comp1, logger);
    if (comp5 != nullptr){
        bool checkBegin, checkEnd;
        vec5 = comp5->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp5->getEnd();
        IVector::equals(vec7, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test2 = checkBegin && checkEnd;
    } else{
        test2 = false;
    }

    double arr7[2] = {2, 2};
    double arr8[2] = {3, 6};
    IVector *vec8 = IVector::createVector(2, arr7, logger);
    IVector *vec9 = IVector::createVector(2, arr8, logger);
    ICompact *comp6 = ICompact::createCompact(vec8, vec9, logger);

    bool test3;
    ICompact *comp7 = ICompact::add(comp6, comp1, logger);
    test3 = comp7 == nullptr;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete vec6;
    delete vec7;
    delete vec8;
    delete vec9;

    delete comp1;
    delete comp2;
    delete comp3;
    delete comp4;
    delete comp5;
    delete comp6;
    delete comp7;

    return test1 && test2 && test3;

}

bool ICompactTests::testMakeConvex(ILogger* logger){

    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {4, 5};
    double arr4[2] = {7, 10};
    IVector *vec3 = IVector::createVector(2, arr3, logger);
    IVector *vec4 = IVector::createVector(2, arr4, logger);
    ICompact *comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact *comp3 = ICompact::makeConvex(comp2, comp1, logger);
    IVector *vec5 = nullptr;
    if (comp3 != nullptr){
        bool checkBegin, checkEnd;
        vec5 = comp3->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        IVector::equals(vec4, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test1 = checkBegin && checkEnd;
    } else{
        test1 = false;
    }

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;
    delete comp1;
    delete comp2;
    delete comp3;

    return test1;
}

bool ICompactTests::testCreateIterator(ILogger* logger){

    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {0.5, 0.5};
    IVector *step1 = IVector::createVector(2, arr3, logger);
    double arr4[2] = {-0.5, -0.5};
    IVector *step2 = IVector::createVector(2, arr4, logger);

    ICompact::iterator* it1 = comp1->begin(step1);
    ICompact::iterator* it2 = comp1->end(step2);

    IVector *vec3, *vec4;
    vec3 = it1->getPoint();
    vec4 = it2->getPoint();
    bool test1, checkBegin, checkEnd;
    IVector::equals(vec1, vec3, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
    IVector::equals(vec2,vec4, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
    test1 = checkBegin && checkEnd;

    bool test2;
    double arr5[2] = {0, 0.5};
    IVector *step3 = IVector::createVector(2, arr5, logger);
    ICompact::iterator* it3 = comp1->begin(step3);
    test2 = it3 == nullptr;

    bool test3;
    ICompact::iterator* it4 = comp1->end(step1);
    test3 = it4 == nullptr;

    delete vec1;
    delete vec2;
    delete vec3;
    delete vec4;

    delete step1;
    delete step2;
    delete step3;

    delete comp1;

    delete it1;
    delete it2;
    delete it3;
    delete it4;

    return test1 && test2 && test3;
}

bool ICompactTests::testIterator(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    bool test1;
    double arr3[2] = {0.5, 0.5};
    IVector *step1 = IVector::createVector(2, arr3, logger);
    IVector *curPoint;
    ICompact::iterator* it1 = comp1->begin(step1);
    int count = 0;
    bool contain;
    do{
        curPoint = it1->getPoint();
        comp1->isContains(curPoint, contain);
        ++count;
        delete curPoint;
    }while (contain && it1->doStep() == RESULT_CODE::SUCCESS);
    test1 = count == 35;

    bool test2;
    double arr4[2] = {-0.5, -0.501};
    IVector *step2 = IVector::createVector(2, arr4, logger);
    ICompact::iterator* it2 = comp1->end(step2);
    count = 0;
    do{
        curPoint = it2->getPoint();
        comp1->isContains(curPoint, contain);
        ++count;
        delete curPoint;
    }while (contain && it2->doStep() == RESULT_CODE::SUCCESS);
    test2 = count >= 30;

    delete vec1;
    delete vec2;

    delete step1;
    delete step2;

    delete comp1;
    delete it1;
    delete it2;

    return test1 && test2;
}

bool ICompactTests::testSetDirection(ILogger* logger){
    double arr1[2] = {1, 2};
    double arr2[2] = {3, 5};
    IVector *vec1 = IVector::createVector(2, arr1, logger);
    IVector *vec2 = IVector::createVector(2, arr2, logger);
    ICompact *comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = {0.5, 0.5};
    IVector *step1 = IVector::createVector(2, arr3, logger);
    IVector *curPoint;
    ICompact::iterator* it1 = comp1->begin(step1);

    bool test1;
    double arr4[2] = {1, 0};
    IVector *dir = IVector::createVector(2, arr4, logger);
    test1 = it1->setDirection(dir) == RESULT_CODE::SUCCESS;
    if (test1){
        ISet* set = ISet::createSet(logger);
        do{
            curPoint = it1->getPoint();
            set->insert(curPoint, IVector::NORM::NORM_1, 0.0001);
            delete curPoint;
        }while (it1->doStep() == RESULT_CODE::SUCCESS);

        delete it1;
        it1 = comp1->begin(step1);
        IVector* vec3;
        do{
            curPoint = it1->getPoint();
            test1 = set->get(vec3, curPoint, IVector::NORM::NORM_1, 0.0001) == RESULT_CODE::SUCCESS;
            delete curPoint;
            delete vec3;
        }while (test1 && it1->doStep() == RESULT_CODE::SUCCESS);

        delete set;
    }

    bool test2;
    double arr5[3] = {1, 2, 2};
    double arr6[3] = {3, 5, 7};
    IVector *vec4 = IVector::createVector(3, arr5, logger);
    IVector *vec5 = IVector::createVector(3, arr6, logger);
    ICompact *comp2 = ICompact::createCompact(vec4, vec5, logger);

    double arr7[3] = {0.5, 0.5, 0.5};
    IVector *step2 = IVector::createVector(3, arr7, logger);

    ICompact::iterator* it2 = comp2->begin(step2);

    double arr8[3] = {3, 0, 0};
    IVector *dir2 = IVector::createVector(3, arr8, logger);
    test2 = it2->setDirection(dir2) != RESULT_CODE::SUCCESS;

    delete vec1;
    delete vec2;
    delete vec4;
    delete vec5;

    delete dir;
    delete dir2;

    delete step1;
    delete step2;

    delete it1;
    delete it2;

    delete comp1;
    delete comp2;

    return test1 && test2;
}

void ICompactTests::runAllTests(ILogger* logger){
   std::cout << "CREATE COMPACT TESTS | ";
    if (testCreate(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "CLONE COMPACT TESTS | ";
    if (testClone(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "IS_CONTAIN COMPACT TESTS | ";
    if (testIsContains(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "IS_SUBSET COMPACT TESTS | ";
    if (testIsSubset(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "IS_INTERSECTS COMPACT TESTS | ";
    if (testIsIntersects(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "INTERSECT COMPACTS TESTS | ";
    if (testIntersection(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "ADD COMPACTS TESTS | ";
    if (testAdd(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "MAKE_CONVEX COMPACT TESTS | ";
    if (testMakeConvex(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "CREATE ITERATOR TESTS | ";
    if (testCreateIterator(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "ITERATE ALONG COMPACT TESTS | ";
    if (testIterator(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
   std::cout << "SET ITERATOR'S DIRECTION TESTS | ";
    if (testSetDirection(logger)){
       std::cout << "OK" << std::endl;
    }else {
       std::cout << "FAILED" << std::endl;
    }
}
