#include "ILoggerImpl.h"
#include "IVectorImpl.h"
#include "ISetImpl.h"
#include <iostream>
#include "KozlovTests/ISet_tests.h"

const char* resultCodeToStr(RESULT_CODE res)
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

void iVectorImplSimpleTest(ILogger* pLogger)
{
	size_t dim = 5;
	double* pData1 = new double[dim];
	pData1[0] = 1.;
	pData1[1] = 2.;
	pData1[2] = 3.;
	pData1[3] = 4.;
	pData1[4] = 5.;

	double* pData2 = new double[dim];
	pData2[0] = 5.;
	pData2[1] = 4.;
	pData2[2] = 3.;
	pData2[3] = 2.;
	pData2[4] = 1.;

	IVector* v1 = IVector::createVector(dim, pData1, pLogger);
	IVector* v2 = IVector::createVector(dim, pData2, pLogger);

	bool* eq_res = new bool;
	RESULT_CODE eq_rc = IVector::equals(v1, v2, IVector::NORM::NORM_2, 1e-5, eq_res, pLogger);
	std::cout << "eq_res value is " << *eq_res << std::endl;
	std::cout << "eq_rc is : " << resultCodeToStr(eq_rc) << std::endl;

}

void iSetImplSimpleTest(ILogger* pLogger)
{
	IVector::NORM norm = IVector::NORM::NORM_2;
	double tol = 1e-5;
	size_t dim = 5;
	double* pData1 = new double[dim];
	pData1[0] = 1.;
	pData1[1] = 2.;
	pData1[2] = 3.;
	pData1[3] = 4.;
	pData1[4] = 5.;

	double* pData2 = new double[dim];
	pData2[0] = 5.;
	pData2[1] = 4.;
	pData2[2] = 3.;
	pData2[3] = 2.;
	pData2[4] = 1.;

	IVector* v1 = IVector::createVector(dim, pData1, pLogger);
	IVector* v2 = IVector::createVector(dim, pData2, pLogger);

	// Check create set
	ISet* s1 = ISet::createSet(pLogger);
	ISet* s2 = ISet::createSet(pLogger);

	std::cout << "s1 dim before insert : " << s1->getDim() << std::endl;
	std::cout << "s2 dim before insert : " << s2->getDim() << std::endl;

	std::cout << "s1 size before insert : " << s1->getSize() << std::endl;
	std::cout << "s2 size before insert : " << s2->getSize() << std::endl;

	RESULT_CODE s1InsRc = s1->insert(v1, norm, tol);
	RESULT_CODE s2InsRc = s2->insert(v2, norm, tol);

	//Check insertion
	std::cout << "s1InsRc : " << resultCodeToStr(s1InsRc) << std::endl;
	std::cout << "s2InsRc : " << resultCodeToStr(s2InsRc) << std::endl;

	std::cout << "s1 dim after insert : " << s1->getDim() << std::endl;
	std::cout << "s2 dim after insert : " << s2->getDim() << std::endl;

	std::cout << "s1 size after insert : " << s1->getSize() << std::endl;
	std::cout << "s2 size after insert : " << s2->getSize() << std::endl;

	//Check Union(add)
	ISet* s1Us2 = ISet::add(s1, s2, norm, tol, pLogger);
	
	std::cout << "union(s1, s2) dim is " << s1Us2->getDim() << std::endl;
	std::cout << "union(s1, s2) size is " << s1Us2->getSize() << std::endl;

	//Check Intersect
	ISet* s1ands2 = ISet::intersect(s1, s2, norm, tol, pLogger);

	std::cout << "intersect(s1, s2) dim is " << s1ands2->getDim() << std::endl;
	std::cout << "intersect(s1, s2) size is " << s1ands2->getSize() << std::endl;

	//Check subtraction
	ISet* s1subs2 = ISet::sub(s1, s2, norm, tol, pLogger);

	std::cout << "sub(s1, s2) dim is " << s1subs2->getDim() << std::endl;
	std::cout << "sub(s1, s2) size is " << s1subs2->getSize() << std::endl;

	ISet* s2subs1 = ISet::sub(s2, s1, norm, tol, pLogger);

	std::cout << "sub(s2, s1) dim is " << s2subs1->getDim() << std::endl;
	std::cout << "sub(s2, s1) size is " << s2subs1->getSize() << std::endl;

	//Check sym subtraction
	ISet* s1symSubs2 = ISet::symSub(s1, s2, norm, tol, pLogger);

	std::cout << "symSub(s1, s2) dim is " << s1symSubs2->getDim() << std::endl;
	std::cout << "symSub(s1, s2) size is " << s1symSubs2->getSize() << std::endl;

	ISet* s2symSubs1 = ISet::symSub(s2, s1, norm, tol, pLogger);

	std::cout << "symSub(s2, s1) dim is " << s2symSubs1->getDim() << std::endl;
	std::cout << "symSub(s2, s1) size is " << s2symSubs1->getSize() << std::endl;

	// Check clear
	s1Us2->clear();
	std::cout << "s1Us2->clear() dim is " << s1Us2->getDim() << std::endl;
	std::cout << "s1Us2->clear() size is " << s1Us2->getSize() << std::endl;

}

#include <iostream>
#include "ICompact.h"
#include "ISet.h"
#define EPS 1E-7

using namespace  std;

bool testCreate(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 1, 5 };
    double arr3[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    IVector* vec3 = IVector::createVector(2, arr3, logger);
    ICompact* comp1 = ICompact::createCompact(vec3, vec1, logger);
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

bool testClone(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);
    ICompact* comp2 = comp1->clone();
    bool test1 = comp1->getDim() == comp2->getDim();
    IVector* vec3, * vec4, * vec5, * vec6;
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

bool testIsContains(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 2, 4 };
    IVector* vec3 = IVector::createVector(2, arr3, logger);
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

bool testIsSubset(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 1.5, 3 };
    double arr4[2] = { 2.5, 4 };
    IVector* vec4 = IVector::createVector(2, arr3, logger);
    IVector* vec5 = IVector::createVector(2, arr4, logger);
    ICompact* comp2 = ICompact::createCompact(vec4, vec5, logger);

    ICompact* comp3 = comp1->clone();

    double arr5[2] = { 1.5, 3 };
    double arr6[2] = { 2.5, 6 };
    IVector* vec6 = IVector::createVector(2, arr5, logger);
    IVector* vec7 = IVector::createVector(2, arr6, logger);
    ICompact* comp4 = ICompact::createCompact(vec6, vec7, logger);

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


bool testIsIntersects(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 1.5, 3 };
    double arr4[2] = { 2.5, 4 };
    IVector* vec4 = IVector::createVector(2, arr3, logger);
    IVector* vec5 = IVector::createVector(2, arr4, logger);
    ICompact* comp2 = ICompact::createCompact(vec4, vec5, logger);

    ICompact* comp3 = comp1->clone();

    double arr5[2] = { 1.5, 3 };
    double arr6[2] = { 2.5, 6 };
    IVector* vec6 = IVector::createVector(2, arr5, logger);
    IVector* vec7 = IVector::createVector(2, arr6, logger);
    ICompact* comp4 = ICompact::createCompact(vec6, vec7, logger);

    double arr7[2] = { 3, 5 };
    double arr8[2] = { 5, 7 };
    IVector* vec8 = IVector::createVector(2, arr7, logger);
    IVector* vec9 = IVector::createVector(2, arr8, logger);
    ICompact* comp5 = ICompact::createCompact(vec8, vec9, logger);

    double arr9[2] = { 4, 5 };
    double arr10[2] = { 7, 10 };
    IVector* vec10 = IVector::createVector(2, arr9, logger);
    IVector* vec11 = IVector::createVector(2, arr10, logger);
    ICompact* comp6 = ICompact::createCompact(vec10, vec11, logger);

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

bool testIntersection(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 1.5, 3 };
    double arr4[2] = { 2.5, 6 };
    IVector* vec3 = IVector::createVector(2, arr3, logger);
    IVector* vec4 = IVector::createVector(2, arr4, logger);
    ICompact* comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact* comp3 = ICompact::intersection(comp1, comp2, logger);
    if (comp3 != nullptr) {
        bool checkBegin, checkEnd;
        IVector* vec5 = comp3->getBegin();
        IVector::equals(vec3, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        double arr[2] = { 2.5, 5 };
        IVector* vec = IVector::createVector(2, arr, logger);
        IVector::equals(vec, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        delete vec;
        test1 = checkBegin && checkEnd;
    }
    else {
        test1 = false;
    }

    bool test2;
    double arr5[2] = { 4, 5 };
    double arr6[2] = { 7, 10 };
    IVector* vec6 = IVector::createVector(2, arr5, logger);
    IVector* vec7 = IVector::createVector(2, arr6, logger);
    ICompact* comp4 = ICompact::createCompact(vec6, vec7, logger);
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

bool testAdd(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 1.5, 3 };
    double arr4[2] = { 2.5, 4 };
    IVector* vec3 = IVector::createVector(2, arr3, logger);
    IVector* vec4 = IVector::createVector(2, arr4, logger);
    ICompact* comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact* comp3 = ICompact::add(comp2, comp1, logger);
    IVector* vec5 = nullptr;
    if (comp3 != nullptr) {
        bool checkBegin, checkEnd;
        vec5 = comp3->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        IVector::equals(vec2, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test1 = checkBegin && checkEnd;
    }
    else {
        test1 = false;
    }

    double arr5[2] = { 2, 2 };
    double arr6[2] = { 4, 5 };
    IVector* vec6 = IVector::createVector(2, arr5, logger);
    IVector* vec7 = IVector::createVector(2, arr6, logger);
    ICompact* comp4 = ICompact::createCompact(vec6, vec7, logger);

    bool test2;
    ICompact* comp5 = ICompact::add(comp4, comp1, logger);
    if (comp5 != nullptr) {
        bool checkBegin, checkEnd;
        vec5 = comp5->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp5->getEnd();
        IVector::equals(vec7, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test2 = checkBegin && checkEnd;
    }
    else {
        test2 = false;
    }

    double arr7[2] = { 2, 2 };
    double arr8[2] = { 3, 6 };
    IVector* vec8 = IVector::createVector(2, arr7, logger);
    IVector* vec9 = IVector::createVector(2, arr8, logger);
    ICompact* comp6 = ICompact::createCompact(vec8, vec9, logger);

    bool test3;
    ICompact* comp7 = ICompact::add(comp6, comp1, logger);
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

bool testMakeConvex(ILogger* logger) {

    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 4, 5 };
    double arr4[2] = { 7, 10 };
    IVector* vec3 = IVector::createVector(2, arr3, logger);
    IVector* vec4 = IVector::createVector(2, arr4, logger);
    ICompact* comp2 = ICompact::createCompact(vec3, vec4, logger);

    bool test1;
    ICompact* comp3 = ICompact::makeConvex(comp2, comp1, logger);
    IVector* vec5 = nullptr;
    if (comp3 != nullptr) {
        bool checkBegin, checkEnd;
        vec5 = comp3->getBegin();
        IVector::equals(vec1, vec5, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
        delete vec5;
        vec5 = comp3->getEnd();
        IVector::equals(vec4, vec5, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
        delete vec5;
        test1 = checkBegin && checkEnd;
    }
    else {
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

bool testCreateIterator(ILogger* logger) {

    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 0.5, 0.5 };
    IVector* step1 = IVector::createVector(2, arr3, logger);
    double arr4[2] = { -0.5, -0.5 };
    IVector* step2 = IVector::createVector(2, arr4, logger);

    ICompact::iterator* it1 = comp1->begin(step1);
    ICompact::iterator* it2 = comp1->end(step2);

    IVector* vec3, * vec4;
    vec3 = it1->getPoint(); 
    vec4 = it2->getPoint();
    bool test1, checkBegin, checkEnd;
    IVector::equals(vec1, vec3, IVector::NORM::NORM_1, 0.0001, &checkBegin, logger);
    IVector::equals(vec2, vec4, IVector::NORM::NORM_1, 0.0001, &checkEnd, logger);
    test1 = checkBegin && checkEnd;

    bool test2;
    double arr5[2] = { 0, 0.5 };
    IVector* step3 = IVector::createVector(2, arr5, logger);
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

bool testIterator(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    bool test1;
    double arr3[2] = { 0.5, 0.5 };
    IVector* step1 = IVector::createVector(2, arr3, logger);
    IVector* curPoint;
    ICompact::iterator* it1 = comp1->begin(step1);
    int count = 0;
    bool contain;
    do {
        curPoint = it1->getPoint();
        comp1->isContains(curPoint, contain);
        ++count;
        delete curPoint;
    } while (contain && it1->doStep() == RESULT_CODE::SUCCESS);
    test1 = count == 35;

    bool test2;
    double arr4[2] = { -0.5, -0.501 };
    IVector* step2 = IVector::createVector(2, arr4, logger);
    ICompact::iterator* it2 = comp1->end(step2);
    count = 0;
    do {
        curPoint = it2->getPoint();
        comp1->isContains(curPoint, contain);
        ++count;
        delete curPoint;
    } while (contain && it2->doStep() == RESULT_CODE::SUCCESS);
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

bool testSetDirection(ILogger* logger) {
    double arr1[2] = { 1, 2 };
    double arr2[2] = { 3, 5 };
    IVector* vec1 = IVector::createVector(2, arr1, logger);
    IVector* vec2 = IVector::createVector(2, arr2, logger);
    ICompact* comp1 = ICompact::createCompact(vec1, vec2, logger);

    double arr3[2] = { 0.5, 0.5 };
    IVector* step1 = IVector::createVector(2, arr3, logger);
    IVector* curPoint;
    ICompact::iterator* it1 = comp1->begin(step1);

    bool test1;
    double arr4[2] = { 1, 0 };
    IVector* dir = IVector::createVector(2, arr4, logger);
    test1 = it1->setDirection(dir) == RESULT_CODE::SUCCESS;
    if (test1) {
        ISet* set = ISet::createSet(logger);
        do {
            curPoint = it1->getPoint();
            set->insert(curPoint, IVector::NORM::NORM_1, 0.0001);
            delete curPoint;
        } while (it1->doStep() == RESULT_CODE::SUCCESS);

        delete it1;
        it1 = comp1->begin(step1);
        IVector* vec3;
        do {
            curPoint = it1->getPoint();
            test1 = set->get(vec3, curPoint, IVector::NORM::NORM_1, 0.0001) == RESULT_CODE::SUCCESS;
            delete curPoint;
            delete vec3;
        } while (test1 && it1->doStep() == RESULT_CODE::SUCCESS);

        delete set;
    }

    bool test2;
    double arr5[3] = { 1, 2, 2 };
    double arr6[3] = { 3, 5, 7 };
    IVector* vec4 = IVector::createVector(3, arr5, logger);
    IVector* vec5 = IVector::createVector(3, arr6, logger);
    ICompact* comp2 = ICompact::createCompact(vec4, vec5, logger);

    double arr7[3] = { 0.5, 0.5, 0.5 };
    IVector* step2 = IVector::createVector(3, arr7, logger);

    ICompact::iterator* it2 = comp2->begin(step2);

    double arr8[3] = { 3, 0, 0 };
    IVector* dir2 = IVector::createVector(3, arr8, logger);
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

void runAllTests(ILogger* logger) {
    cout << "CREATE COMPACT TESTS | ";
    if (testCreate(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "CLONE COMPACT TESTS | ";
    if (testClone(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "IS_CONTAIN COMPACT TESTS | ";
    if (testIsContains(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "IS_SUBSET COMPACT TESTS | ";
    if (testIsSubset(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "IS_INTERSECTS COMPACT TESTS | ";
    if (testIsIntersects(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "INTERSECT COMPACTS TESTS | ";
    if (testIntersection(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "ADD COMPACTS TESTS | ";
    if (testAdd(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "MAKE_CONVEX COMPACT TESTS | ";
    if (testMakeConvex(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "CREATE ITERATOR TESTS | ";
    if (testCreateIterator(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "ITERATE ALONG COMPACT TESTS | ";
    if (testIterator(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
    cout << "SET ITERATOR'S DIRECTION TESTS | ";
    if (testSetDirection(logger)) {
        cout << "OK" << std::endl;
    }
    else {
        cout << "FAILED" << std::endl;
    }
}


int main()
{
	/*const char* logFilePath = "SimpleTestingLog.txt";
	ILogger* pLogger = ILoggerImpl::createLogger(nullptr);
	RESULT_CODE res = pLogger->setLogFile(logFilePath);
	
	if (res == RESULT_CODE::SUCCESS)
	{
		std::cout << "setLogFile SUCCESS" << std::endl;
	}

	else
	{
		std::cout << "setLogFile failed" << std::endl;
	}

	iVectorImplSimpleTest(pLogger);
	iSetImplSimpleTest(pLogger);*/

	const char* logFilePath = "KozlovTestingLog.txt";
	ILogger* pLogger = ILoggerImpl::createLogger(nullptr);
	RESULT_CODE logRc = pLogger->setLogFile(logFilePath);
	
	std::cout << "Logger created with RC: " << resultCodeToStr(logRc) << std::endl;

	runAllTests(pLogger);
}