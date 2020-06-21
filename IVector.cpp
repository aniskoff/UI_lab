#include "IVector.h"
#include "IVectorImpl.h"
#include <cmath>
#include <stddef.h>
#include <algorithm>

IVector* IVector::createVector(size_t dim, double* pData, ILogger* pLogger)
{
	if (pData == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector createVector, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}
	if (dim == 0)
	{
		if (pLogger)
		{
			pLogger->log("Error in createVector, dim=0", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	for (int i = 0; i < dim; ++i)
	{
		if (pData[i] != pData[i])
		{
			if (pLogger)
			{
				pLogger->log("Error in createVector, init data contains NAN", RESULT_CODE::WRONG_ARGUMENT);
			}
			return nullptr;
		}
	}

	double* pDataCopy = new double[dim];

	if (pDataCopy == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in createVector", RESULT_CODE::OUT_OF_MEMORY);
		}
		return nullptr;
	}
	std::copy(pData, pData + dim, pDataCopy);
	return new IVectorImpl(dim, pDataCopy);
}

IVector* IVector::add(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	if (!pOperand1 || !pOperand2)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector add, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		pLogger->log("Error in IVector add", RESULT_CODE::WRONG_DIM);
		return nullptr;
	}

	IVector* res = pOperand1->clone();
	for (int i = 0; i < pOperand1->getDim(); ++i)
	{
		res->setCoord(i, pOperand1->getCoord(i) + pOperand2->getCoord(i));
	}

	return res;

}

IVector* IVector::sub(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	if (!pOperand1 || !pOperand2)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector sub, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in IVector sub", RESULT_CODE::WRONG_DIM);
		}
		return nullptr;
	}

	IVector* res = pOperand1->clone();
	for (int i = 0; i < pOperand1->getDim(); ++i)
	{
		res->setCoord(i, pOperand1->getCoord(i) - pOperand2->getCoord(i));
	}

	return res;
}

IVector* IVector::mul(IVector const* pOperand1, double scaleParam, ILogger* pLogger)
{
	if (pOperand1 == nullptr)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector mul, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return nullptr;
	}

	IVector* res = pOperand1->clone();
	for (int i = 0; i < pOperand1->getDim(); ++i)
	{
		res->setCoord(i, scaleParam * pOperand1->getCoord(i));
	}

	return res;

}

double IVector::mul(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	if (!pOperand1 || !pOperand2)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector mul, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return NAN;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in IVector mul", RESULT_CODE::WRONG_DIM);
		}
		return NAN;
	}


	double res = 0.;
	for (int i = 0; i < pOperand1->getDim(); ++i)
	{
		res += pOperand1->getCoord(i) * pOperand2->getCoord(i);
	}
	return res;
}

RESULT_CODE IVector::equals(IVector const* pOperand1, IVector const* pOperand2, NORM norm, double tolerance, bool* result, ILogger* pLogger)
{
	if (!pOperand1 || !pOperand2)
	{
		if (pLogger)
		{
			pLogger->log("Error in Ivector equals, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger)
		{
			pLogger->log("Error in IVector equals", RESULT_CODE::WRONG_DIM);
		}
		return RESULT_CODE::WRONG_DIM;
	}

	if (tolerance < 0.)
	{
		if (pLogger)
		{
			pLogger->log("Error in IVector equals, tolerance shoud be nonnegative", RESULT_CODE::WRONG_ARGUMENT);
		}
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	if (!result)
	{
		if (pLogger)
		{
			pLogger->log("Error in IVector equals, nullptr result argument provided", RESULT_CODE::WRONG_ARGUMENT);
		}
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	double diff = sub(pOperand1, pOperand2, pLogger)->norm(norm);
	*result = diff <= tolerance ? true : false;
	return RESULT_CODE::SUCCESS;
}
