#include "SimpleTests.h"
#include "ILogger/ILoggerImpl.h"
#include "IVector/IVectorImpl.h"
#include "ISet/ISetImpl.h"
#include <iostream>


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
