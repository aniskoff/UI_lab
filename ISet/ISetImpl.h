#pragma once
#include "ISet.h"
#include <vector>

class ISetImpl : public ISet 
{
public:
	ISetImpl() = default;
	~ISetImpl() = default;
	RESULT_CODE insert(const IVector* pVector, IVector::NORM norm, double tolerance) override;
	RESULT_CODE get(IVector*& pVector, size_t index) const override;
	RESULT_CODE get(IVector*& pVector, IVector const* pSample, IVector::NORM norm, double tolerance) const override;
	size_t getDim() const override; //space dimension
	size_t getSize() const override; //num elements in set
	void clear() override; // delete all
	RESULT_CODE erase(size_t index) override;
	RESULT_CODE erase(IVector const* pSample, IVector::NORM norm, double tolerance) override;
	ISet* clone()const override;
	
private:
	std::vector<IVector*> storage_;
	size_t set_dim_;
};
