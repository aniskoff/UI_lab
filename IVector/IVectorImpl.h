#pragma once
#include "IVector.h"

class IVectorImpl : public IVector
{
public:

    IVectorImpl() = default;
    IVectorImpl(size_t dim, double* pData);
	~IVectorImpl();
	IVector* clone() const override;
    double getCoord(size_t index) const override;
    RESULT_CODE setCoord(size_t index, double value) override;
    double norm(NORM norm) const override;
    size_t getDim() const override;

private:
    double* pData_;
    size_t dim_;
};