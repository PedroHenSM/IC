#include "ServiceContainer.h"

namespace Library
{
	ServiceContainer::ServiceContainer() : mServices()
	{}

	void ServiceContainer::AddService(unsigned int typeID, void* service)
	{
		mServices.insert(std::pair<unsigned int, void*>(typeID, service));
	}

	void ServiceContainer::RemoveService(unsigned int typeID)
	{
		mServices.erase(typeID);
	}

	void* ServiceContainer::GetService(unsigned int typeID) const
	{
		std::map<unsigned int, void*>::const_iterator it = mServices.find(typeID);
		return (it != mServices.end() ? it->second : nullptr);
	}
}