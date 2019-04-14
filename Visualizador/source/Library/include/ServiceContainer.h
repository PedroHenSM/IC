#pragma once

#include "Common.h"

namespace Library
{
	class ServiceContainer
	{
	public:
		ServiceContainer();

		void AddService(unsigned int typeID, void* service);
		void RemoveService(unsigned int typeID);
		void* GetService(unsigned int typeID) const;

	private:
		ServiceContainer(const ServiceContainer& rhs);
		ServiceContainer& operator=(const ServiceContainer& rhs);

		std::map<unsigned int, void*> mServices;
	};
}