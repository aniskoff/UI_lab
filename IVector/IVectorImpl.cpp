#include "IVectorImpl.h"
#include <algorithm>
#include <cmath>


IVectorImpl::IVectorImpl(size_t dim, double* pData)
{
	dim_ = dim;
	pData_ = pData;
}

IVectorImpl::~IVectorImpl()
{
	delete pData_;
}
IVector* IVectorImpl::clone() const
{
	IVectorImpl* res = new IVectorImpl();
	res->dim_ = dim_;
	res->pData_ = new double[res->dim_];
	std::copy(pData_, pData_ + dim_, res->pData_);

	return res;
}





double IVectorImpl::getCoord(size_t index) const
{
	if (index >= dim_)
	{
		return NAN;
	}
	return pData_[index];
}
RESULT_CODE IVectorImpl::setCoord(size_t index, double value)
{
	if (index >= dim_)
	{
		return RESULT_CODE::OUT_OF_BOUNDS;
	}

	pData_[index] = value;
	return RESULT_CODE::SUCCESS;
}
double IVectorImpl::norm(NORM norm) const
{
	double res = 0.;

	switch (norm)
	{
	case IVector::NORM::NORM_1:
		for (int i = 0; i < dim_; ++i)
		{
			res += std::abs(getCoord(i));
		}
		return res;
		

	case IVector::NORM::NORM_2:
		for (int i = 0; i < dim_; ++i)
		{
			res += std::pow(getCoord(i), 2);
		}
		return res;

	case IVector::NORM::NORM_INF:
		res = *std::max_element(pData_, pData_ + dim_);
		return res;

	default:
		return NAN;
	}
}
size_t IVectorImpl::getDim() const 
{
	return dim_;
}