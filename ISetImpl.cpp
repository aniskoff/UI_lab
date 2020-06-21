#include "ISetImpl.h"
#include "IVectorImpl.h"




RESULT_CODE ISetImpl::insert(const IVector* pVector, IVector::NORM norm, double tolerance)
{
	if (pVector == nullptr || tolerance < 0.)
	{
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	if (storage_.size() == 0)
	{
		set_dim_ = pVector->getDim();
	}

	if (pVector->getDim() != set_dim_)
	{
		return RESULT_CODE::WRONG_DIM;
	}

	bool elemAlreadyExists = false;

	for (const IVector* elem : storage_)
	{
		RESULT_CODE eqRc = IVectorImpl::equals(pVector,
										       elem,
										       norm, 
										       tolerance,
										       &elemAlreadyExists,
										       nullptr);
		if (eqRc != RESULT_CODE::SUCCESS)
		{
			return eqRc;
		}

		if (elemAlreadyExists)
		{
			return RESULT_CODE::SUCCESS;
		}
	}
	
	IVector* newElem = pVector->clone();
	try
	{
		storage_.push_back(newElem);
	}
	catch (...)
	{
		return RESULT_CODE::OUT_OF_MEMORY;
	}

	return RESULT_CODE::SUCCESS; 
}

RESULT_CODE ISetImpl::get(IVector*& pVector, size_t index) const
{
	if (index >= storage_.size())
	{
		return RESULT_CODE::OUT_OF_BOUNDS;
	}

	// if (!pVector) // may not check
	// {
	//	return RESULT_CODE::WRONG_ARGUMENT;
	// }

	pVector = storage_[index]->clone();
	return RESULT_CODE::SUCCESS;
}

RESULT_CODE ISetImpl::get(IVector*& pVector,
						  IVector const* pSample,
						  IVector::NORM norm,
						  double tolerance) const
{
	if (pSample == nullptr || tolerance < 0.) // not checking pVector on nullptr
	{
		return RESULT_CODE::WRONG_ARGUMENT;
	}
	
	bool elemExists = false;

	for (const IVector* elem : storage_)
	{
		RESULT_CODE eqRc = IVectorImpl::equals(pSample,
											   elem,
											   norm,
											   tolerance,
											   &elemExists,
											   nullptr);
		if (eqRc != RESULT_CODE::SUCCESS)
		{
			return eqRc;
		}

		if (elemExists)
		{
			pVector = elem->clone();
			return RESULT_CODE::SUCCESS;
		}
	}

	return RESULT_CODE::NOT_FOUND;
}

size_t ISetImpl::getDim() const //space dimension
{
	return set_dim_;
}

size_t ISetImpl::getSize() const //num elements in set
{
	return storage_.size();
}

void ISetImpl::clear()// delete all
{
	for (IVector* elem : storage_)
	{
		delete elem;
	}

	set_dim_ = 0;
	storage_.clear();
}

RESULT_CODE ISetImpl::erase(size_t index) 
{
	if (index >= storage_.size())
	{
		return RESULT_CODE::OUT_OF_BOUNDS;
	}

	delete storage_[index];
	storage_.erase(storage_.begin() + index);
	return RESULT_CODE::SUCCESS;
}

RESULT_CODE ISetImpl::erase(IVector const* pSample, IVector::NORM norm, double tolerance) 
{
	if (pSample == nullptr || tolerance < 0.)
	{
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	bool elemExists = false;

	for (int i = 0; i < storage_.size(); ++i)
	{
		RESULT_CODE eqRc = IVectorImpl::equals(pSample,
											   storage_[i],
											   norm, 
											   tolerance, 
											   &elemExists,
											   nullptr);
		if (eqRc != RESULT_CODE::SUCCESS)
		{
			return eqRc;
		}

		if (elemExists)
		{	
			return erase(i);
		}
	}

	return RESULT_CODE::NOT_FOUND; 
}

ISet* ISetImpl::clone()const
{
	ISetImpl* res = new ISetImpl();
	res->set_dim_ = set_dim_;
	
	for (const IVector* elem : storage_)
	{
		res->storage_.push_back(elem->clone());
	}

	return res;
}

