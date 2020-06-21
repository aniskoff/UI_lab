#pragma once
#include "ICompact.h"

class ICompactImpl : public ICompact
{
public:

    /* returns a step, end, begin with which you can iterate over all domains of compact*/
    ICompactImpl() = default;
    IVector* getBegin() const override;
    IVector* getEnd() const override;

    iterator* end(IVector const* const step = 0) override;
    iterator* begin(IVector const* const step = 0) override;

    RESULT_CODE isContains(IVector const* const vec, bool& result) const override;
    RESULT_CODE isSubSet(ICompact const* const other, bool& result) const override;
    RESULT_CODE isIntersects(ICompact const* const other, bool& result) const override;

    size_t getDim() const override;
    ICompact* clone() const override;

    /*dtor*/
    ~ICompactImpl();

    class iteratorImpl : iterator
    {
    public:
        //adds step to current value in iterator
        //+step
        RESULT_CODE doStep() override;

        IVector* getPoint() const override;

        //change order of step
        RESULT_CODE setDirection(IVector const* const dir) = 0;

        /*dtor*/
        ~iteratorImpl() = default;
    };
private:
    /*non default copyable*/
    // ICompactImpl(const ICompact& other) = delete;
    // void operator=(const ICompact& other) = delete;
    IVector const* const begin_;
    IVector const* const end_;
    size_t dim_;
};