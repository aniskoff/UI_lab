#pragma once
#include "ICompact.h"
#include <vector>

class ICompactImpl : public ICompact
{
public:

    /* returns a step, end, begin with which you can iterate over all domains of compact*/
    ICompactImpl(IVector const* const begin, IVector const* const end, ILogger* pLogger);
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
    ~ICompactImpl() override;

    class iteratorImpl : iterator
    {
    public:
        //adds step to current value in iterator
        //+step
        iteratorImpl(ICompact const *const domain,
                     const IVector* stepSize,
                     const IVector* initPoint);
        RESULT_CODE doStep() override;

        IVector* getPoint() const override;

        //change order of step
        RESULT_CODE setDirection(IVector const* const dir) override ;

        /*dtor*/
        ~iteratorImpl() override = default;

    private:
        ICompact const* domain_;
        IVector const* stepSize_;
        std::vector<int> iterOrder_;
        IVector* initPoint_;
        IVector* currPoint_;
        int currDimIdx_;


        friend class ICompactImpl;
    };
private:
    /*non default copyable*/
    // ICompactImpl(const ICompact& other) = delete;
    // void operator=(const ICompact& other) = delete;
    IVector const* begin_;
    IVector const* end_;
    size_t dim_;
    static ILogger* pLogger_;
};