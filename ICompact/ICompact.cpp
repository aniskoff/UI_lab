#include "ICompact.h"
#include "ICompactImpl.h"
#include "IVector/IVector.h"
#include <algorithm>


ICompact::~ICompact() = default;

ICompact* ICompact::createCompact(IVector const* const begin, IVector const* const end, ILogger* pLogger)
{
	{
		if (begin == nullptr || end == nullptr)
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet add, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
			}
			return nullptr;
		}

		if (begin->getDim() != end->getDim())
		{
			if (pLogger)
			{
				pLogger->log("Error in ISet add, dim mismatch", RESULT_CODE::WRONG_DIM);
			}
			return nullptr;
		}


		//check begin <= end coordinate-wise
		for (int i = 0; i < begin->getDim(); ++i)
        {
		    if (begin->getCoord(i) > end->getCoord(i))
            {
                if (pLogger)
                {
                    pLogger->log("Error in ICompact create, ineq (begin <= end) violated",
                                 RESULT_CODE::WRONG_ARGUMENT);
                    return nullptr;
                }
            }
        }


        IVector* beginClone = begin->clone();
		IVector* endClone = end->clone();
        return new ICompactImpl(beginClone, endClone, pLogger);

	}
}

ICompact* ICompact::intersection(ICompact const* const left, ICompact const* const right, ILogger * pLogger)
{
    if (left == nullptr || right == nullptr)
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact intersect, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
        }
        return nullptr;
    }

    if (left->getDim() != right->getDim())
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact intersect, dim mismatch", RESULT_CODE::WRONG_DIM);
        }
        return nullptr;
    }

    size_t dim = left->getDim();
    IVector* resBeg = IVector::createVector(dim, new double[dim], pLogger);
    IVector* resEnd = IVector::createVector(dim, new double[dim], pLogger);

    for (int i = 0; i < dim; ++i)
    {
        double begI = std::max(left->getBegin()->getCoord(i), right->getBegin()->getCoord(i));
        double endI = std::min(left->getEnd()->getCoord(i), right->getEnd()->getCoord(i));

        if (begI > endI)
        {
            delete resBeg;
            delete resEnd;
            return nullptr;
        }
        resBeg->setCoord(i, begI);
        resEnd->setCoord(i, endI);
    }
    return new ICompactImpl(resBeg, resEnd, pLogger);
}

//union
ICompact* ICompact::add(ICompact const* const left, ICompact const* const right, ILogger* pLogger)
{
    if (left == nullptr || right == nullptr)
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact add, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
        }
        return nullptr;
    }

    if (left->getDim() != right->getDim())
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact add, dim mismatch", RESULT_CODE::WRONG_DIM);
        }
        return nullptr;
    }

    size_t dim = left->getDim();

    size_t concatAxis = 0;
    bool concatAxisFound = false;

    for (int i = 0; i < dim; ++i)
    {
        if (left->getBegin()->getCoord(i) != right->getBegin()->getCoord(i) || // candidate to concatAxis
            left->getEnd()->getCoord(i) != right->getEnd()->getCoord(i))
        {
            if (concatAxisFound)
            {

                return nullptr;
            }
            concatAxisFound = true;
            concatAxis = i;
        }
    }

    if (!concatAxisFound) // concatAxis not found means that provided compacts are the same, so returning left one for definiteness
    {
        return left->clone();
    }

    double begConcatAxisIntersection = std::max(left->getBegin()->getCoord(concatAxis),
                                                right->getBegin()->getCoord(concatAxis));
    double endConcatAxisIntersection = std::min(left->getEnd()->getCoord(concatAxis),
                                                right->getEnd()->getCoord(concatAxis));
    if (begConcatAxisIntersection > endConcatAxisIntersection) // provided compacts don't intersect
    {
        return nullptr;
    }

    IVector* resBeg =  (left->getBegin()->getCoord(concatAxis) < right->getBegin()->getCoord(concatAxis))
                      ? left->getBegin()->clone()
                      : right->getBegin()->clone();

    IVector* resEnd = (left->getEnd()->getCoord(concatAxis) < right->getEnd()->getCoord(concatAxis))
                      ? right->getEnd()->clone()
                      : left->getEnd()->clone();

    return ICompactImpl::createCompact(resBeg, resEnd, pLogger);
}

ICompact* ICompact::makeConvex(ICompact const* const left, ICompact const* const right, ILogger* pLogger)
{
    if (left == nullptr || right == nullptr)
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact add, nullptr provided", RESULT_CODE::WRONG_ARGUMENT);
        }
        return nullptr;
    }

    if (left->getDim() != right->getDim())
    {
        if (pLogger)
        {
            pLogger->log("Error in ICompact add, dim mismatch", RESULT_CODE::WRONG_DIM);
        }
        return nullptr;
    }

    size_t dim = left->getDim();
    IVector* resBeg = IVector::createVector(dim, new double[dim], pLogger);
    IVector* resEnd = IVector::createVector(dim, new double[dim], pLogger);

    for (int i = 0; i < dim; ++i)
    {
        resBeg->setCoord(i, std::min(left->getBegin()->getCoord(i),
                                     right->getBegin()->getCoord(i)));

        resEnd->setCoord(i, std::max(left->getEnd()->getCoord(i),
                                     right->getEnd()->getCoord(i)));
    }

    return ICompactImpl::createCompact(resBeg, resEnd, pLogger);
}