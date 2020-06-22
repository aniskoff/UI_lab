#include "ICompactImpl.h"
#include <set>
ILogger* ICompactImpl::pLogger_;

ICompactImpl::ICompactImpl(IVector const * begin, IVector const * end, ILogger* pLogger)
    :begin_(begin)
    ,end_(end)
    ,dim_(begin->getDim())
{
    if (pLogger_ == nullptr)
    {
        pLogger_ = pLogger;
    }
}

IVector* ICompactImpl::getBegin() const
{
    return begin_->clone();
}
IVector* ICompactImpl::getEnd() const
{
    return end_->clone();
}

ICompact::iterator* ICompactImpl::end(IVector const* const step)
{
    if (step == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact end, step=nullptr", RESULT_CODE::WRONG_ARGUMENT);
        }
        return nullptr;
    }

    for (int i = 0; i < dim_; ++i)
    {
        if (step->getCoord(i) >= 0)
        {
            if (pLogger_)
            {
                pLogger_->log("Error in ICompact end, all steps should be < 0", RESULT_CODE::WRONG_ARGUMENT);
            }
            return nullptr;
        }
    }

    return new iteratorImpl(this, step, getEnd());
}

ICompact::iterator* ICompactImpl::begin(IVector const* const step)
{
    if (step == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact begin, step=nullptr", RESULT_CODE::WRONG_ARGUMENT);
        }
        return nullptr;
    }

    for (int i = 0; i < dim_; ++i)
    {
        if (step->getCoord(i) <= 0)
        {
            if (pLogger_)
            {
                pLogger_->log("Error in ICompact begin, all steps should be > 0", RESULT_CODE::WRONG_ARGUMENT);
            }
            return nullptr;
        }
    }
    return new iteratorImpl(this, step, getBegin());
}


RESULT_CODE ICompactImpl::isContains(IVector const* const vec, bool& result) const
{
    if (vec == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isContains", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    if (vec->getDim() != dim_)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isContains", RESULT_CODE::WRONG_DIM);
        }
        return RESULT_CODE::WRONG_DIM;
    }

    for (int i = 0; i < vec->getDim(); ++i)
    {
        if ((vec->getCoord(i) < begin_->getCoord(i)) || (vec->getCoord(i) > end_->getCoord(i)))
        {
            result = false;
            return RESULT_CODE::SUCCESS;
        }
    }

    result = true;
    return RESULT_CODE::SUCCESS;
}

RESULT_CODE ICompactImpl::isSubSet(ICompact const* const other, bool& result) const
{
    if (other == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isSubSet", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    if (other->getDim() != dim_)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isSubSet", RESULT_CODE::WRONG_DIM);
        }
        return RESULT_CODE::WRONG_DIM;
    }

    if (other->getBegin() == nullptr || other->getEnd() == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isSubSet", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    bool otherBegInside, otherEndInside;
    IVector* otherBeg = other->getBegin();
    IVector* otherEnd = other->getEnd();

    RESULT_CODE containsOtherBegRC = isContains(otherBeg, otherBegInside);
    if (containsOtherBegRC != RESULT_CODE::SUCCESS)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isSubSet", containsOtherBegRC);
        }
        return containsOtherBegRC;
    }

    RESULT_CODE containsOtherEndRC = isContains(otherEnd, otherEndInside);
    if (containsOtherEndRC != RESULT_CODE::SUCCESS)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isSubSet", containsOtherEndRC);
        }
        return containsOtherEndRC;
    }

    if (otherBegInside && otherEndInside)
    {
        result = true;
        return RESULT_CODE::SUCCESS;
    }

    result = false;
    return RESULT_CODE::SUCCESS;
}

RESULT_CODE ICompactImpl::isIntersects(ICompact const* const other, bool& result) const
{
    if (other == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isIntersects", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    if (other->getDim() != dim_)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isIntersects", RESULT_CODE::WRONG_DIM);
        }
        return RESULT_CODE::WRONG_DIM;
    }

    if (other->getBegin() == nullptr || other->getEnd() == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in ICompact isIntersects", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    for (int i = 0; i < other->getDim(); ++i)
    {
        if ((end_->getCoord(i) < other->getBegin()->getCoord(i)) || (begin_->getCoord(i) > other->getEnd()->getCoord(i)))
        {
            result = false;
            return RESULT_CODE::SUCCESS;
        }
    }

    result = true;
    return RESULT_CODE::SUCCESS;
}

size_t ICompactImpl::getDim() const
{
    return dim_;
}
ICompact* ICompactImpl::clone() const
{
    return ICompactImpl::createCompact(begin_, end_, pLogger_);
}

/*dtor*/
ICompactImpl::~ICompactImpl()
{
    delete begin_;
    delete end_;
}


//adds step to current value in iterator
//+step

ICompactImpl::iteratorImpl::iteratorImpl(ICompact const *const domain,
                                         const IVector* stepSize,
                                         const IVector* initPoint)
    :domain_(domain)
    ,stepSize_(stepSize->clone())
    ,initPoint_(initPoint->clone())
    ,currPoint_(initPoint->clone())
    ,currDimIdx_(0)
{
    size_t dim = domain->getDim();
    iterOrder_.reserve(dim);
    for (int i = 0; i < dim; ++i)
    {
        iterOrder_.push_back(i);
    }
}

RESULT_CODE ICompactImpl::iteratorImpl::doStep()
{
    if (currDimIdx_ >= domain_->getDim())
    {
        return RESULT_CODE::OUT_OF_BOUNDS; //Iteration complete. Maybe another STOP_ITERATION signal.
    }

    size_t currDim = iterOrder_[currDimIdx_];
    double nextDimVal = currPoint_->getCoord(currDim) + stepSize_->getCoord(currDim);

    if ((nextDimVal >= domain_->getBegin()->getCoord(currDim)) && //valid step
        (nextDimVal <= domain_->getEnd()->getCoord(currDim)))
    {
        currPoint_->setCoord(currDim, nextDimVal);
        currDimIdx_ = 0;
        return RESULT_CODE::SUCCESS;
    }

    if (stepSize_->getCoord(currDim) > 0) //iterating forward
    {
        currPoint_->setCoord(currDim, domain_->getBegin()->getCoord(currDim)); // restarting this dim from beg
    }
    else
    {
        currPoint_->setCoord(currDim, domain_->getEnd()->getCoord(currDim)); // restarting this dim from end
    }

    ++currDimIdx_;
    return doStep();

}

IVector* ICompactImpl::iteratorImpl::getPoint() const
{
    return currPoint_->clone();
}

//change order of step
RESULT_CODE ICompactImpl::iteratorImpl::setDirection(IVector const* const dir) //iter order
{
    if (dir == nullptr)
    {
        if (pLogger_)
        {
            pLogger_->log("Error in iterator setDirection", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    if (dir->getDim() != domain_->getDim())
    {
        if (pLogger_)
        {
            pLogger_->log("Error in iterator setDirection", RESULT_CODE::WRONG_DIM);
        }
        return RESULT_CODE::WRONG_DIM;
    }

    std::set<int> checkSet;
    for (int i = 0; i < domain_->getDim(); ++i)
    {
        checkSet.insert(int(dir->getCoord(i)));
    }

    if (*checkSet.begin() < 0 || *checkSet.rbegin() >= domain_->getDim())
    {
        if (pLogger_)
        {
            pLogger_->log("Error in iterator setDirection, numbers should be from 0 to DIMENSION-1", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;
    }

    if (checkSet.size() != domain_->getDim())
    {
        if (pLogger_)
        {
            pLogger_->log("Error in iterator setDirection, numbers should be distinct", RESULT_CODE::WRONG_ARGUMENT);
        }
        return RESULT_CODE::WRONG_ARGUMENT;

    }

    delete currPoint_;
    currPoint_ = initPoint_->clone();
    currDimIdx_ = 0;
    for (int i = 0; i < domain_->getDim(); ++i)
    {
        iterOrder_[i] = int(dir->getCoord(i));
    }
    return RESULT_CODE::SUCCESS;
}
