#include "ICompact.h"
#include "ICompactImpl.h"


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

		ICompactImpl* res = new ICompactImpl();


	}
}

ICompact* ICompact::intersection(ICompact const* const left, ICompact const* const right, ILogger * logger)
{}

//union
ICompact* ICompact::add(ICompact const* const left, ICompact const* const right, ILogger* logger)
{}

ICompact* ICompact::makeConvex(ICompact const* const left, ICompact const* const right, ILogger* logger)
{}