#include "ISet.h"
#include "ISetImpl.h"

ISet* ISet::createSet(ILogger* pLogger)
{
	ISet* res = new ISetImpl();
	if (!res && pLogger)
	{
		pLogger->log("Error in ISet createSet", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	return res;
}

ISet* ISet::add(ISet const* pOperand1,
	ISet const* pOperand2,
	IVector::NORM norm,
	double tolerance,
	ILogger* pLogger)
{
	if (pOperand1 == nullptr || pOperand2 == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet add, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet add, dim mismatch", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	if (tolerance < 0.)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet add, negative tolerance", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	ISet* res = pOperand1->clone();

	IVector* elemHolder = nullptr;

	for (int i = 0; i < pOperand2->getSize(); ++i)
	{
		RESULT_CODE getRc = pOperand2->get(elemHolder, i);
		if (getRc != RESULT_CODE::SUCCESS)
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet add", getRc);
			}
			return nullptr;
		}

		RESULT_CODE insertionRc = res->insert(elemHolder, norm, tolerance);
		if (insertionRc != RESULT_CODE::SUCCESS)
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet add", insertionRc);
			}
			return nullptr;
		}
	}
	return res;
}

ISet* ISet::intersect(ISet const* pOperand1,
	ISet const* pOperand2,
	IVector::NORM norm,
	double tolerance,
	ILogger* pLogger)
{
	if (pOperand1 == nullptr || pOperand2 == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet intersect, nullptr provided",
				RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet intersect, dim mismatch", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	if (tolerance < 0.)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet intersect, negative tolerance",
				RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	ISet* res = ISetImpl::add(pOperand1, pOperand2, norm, tolerance, pLogger);
	ISet* unionTmp = res->clone();

	IVector* set1ElemHolder = nullptr;
	IVector* set2ElemHolder = nullptr;
	IVector* unionTmpElemHolder = nullptr;

	for (int i = 0; i < unionTmp->getSize(); ++i)
	{

		RESULT_CODE unionTmpGetRC = unionTmp->get(unionTmpElemHolder, i);
		//
		if (unionTmpGetRC != RESULT_CODE::SUCCESS)
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet intersect", unionTmpGetRC);
			}
			return nullptr;
		}
		RESULT_CODE set1GetRC = pOperand1->get(set1ElemHolder,
			unionTmpElemHolder,
			norm,
			tolerance);
		//
		if ((set1GetRC != RESULT_CODE::SUCCESS) && (set1GetRC != RESULT_CODE::NOT_FOUND))
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet intersect", set1GetRC);
			}
			return nullptr;
		}
		RESULT_CODE set2GetRC = pOperand2->get(set2ElemHolder,
			unionTmpElemHolder,
			norm,
			tolerance);
		//
		if ((set2GetRC != RESULT_CODE::SUCCESS) && (set2GetRC != RESULT_CODE::NOT_FOUND))
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet intersect", set2GetRC);
			}
			return nullptr;
		}

		if (set1GetRC == RESULT_CODE::NOT_FOUND || set2GetRC == RESULT_CODE::NOT_FOUND)
		{
			RESULT_CODE resEraseRC = res->erase(unionTmpElemHolder, norm, tolerance);

			if (resEraseRC == RESULT_CODE::NOT_FOUND)
			{
				if (pLogger)
				{
					pLogger->log("Unexpected behaivor!!!", resEraseRC);
				}
			}

			if ((resEraseRC != RESULT_CODE::SUCCESS) && (resEraseRC != RESULT_CODE::NOT_FOUND))
			{
				if (pLogger)
				{
					pLogger->log("Error in ISet intersect", resEraseRC);
				}
				return nullptr;
			}
		}
	}
	return res;
}

ISet* ISet::sub(ISet const* pOperand1,
	ISet const* pOperand2,
	IVector::NORM norm,
	double tolerance,
	ILogger* pLogger)
{
	if (pOperand1 == nullptr || pOperand2 == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, dim mismatch", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	if (tolerance < 0.)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, negative tolerance", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}


	ISet* res = pOperand1->clone();
	IVector* set2ElemHolder = nullptr;

	for (int i = 0; i < pOperand2->getSize(); ++i)
	{
		RESULT_CODE set2GetRc = pOperand2->get(set2ElemHolder, i);
		//
		if (set2GetRc != RESULT_CODE::SUCCESS)
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet sub", set2GetRc);
			}
			return nullptr;
		}
		RESULT_CODE set1EraseRc = res->erase(set2ElemHolder, norm, tolerance);

		if ((set1EraseRc != RESULT_CODE::NOT_FOUND) && (set1EraseRc != RESULT_CODE::SUCCESS))
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet sub", set1EraseRc);
			}
			return nullptr;
		}

	}

	return res;
}

ISet* ISet::symSub(ISet const* pOperand1,
	ISet const* pOperand2,
	IVector::NORM norm,
	double tolerance,
	ILogger* pLogger)
{
	if (pOperand1 == nullptr || pOperand2 == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, dim mismatch", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	if (tolerance < 0.)
	{
		if (pLogger)
		{
			pLogger->log("Error in ISet sub, negative tolerance", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	// symSub(A, B) = sub(A, B) U sub(B, A)
	ISet* res = add(sub(pOperand1, pOperand2, norm, tolerance, pLogger),
		sub(pOperand2, pOperand1, norm, tolerance, pLogger),
		norm,
		tolerance,
		pLogger);

	return res;
}
