#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>

namespace Library
{
	class RTTI
	{
	public:
		virtual const size_t& TypeIdInstance() const = 0;

		virtual RTTI* QueryInterface(const unsigned int id) const
		{
			return nullptr;
		}

		virtual bool Is(const unsigned int id) const
		{
			return false;
		}

		virtual bool Is(const std::string& name) const
		{
			return false;
		}

		template <typename T>
		T* As() const
		{
			if(Is(T::TypeIdClass()))
			{
				return (T*)this;
			}

			return nullptr;
		}
	};

#define RTTI_DECLARATIONS(Type, ParentType)                                                              \
        public:                                                                                              \
            typedef ParentType Parent;                                                                       \
            static std::string TypeName() { return std::string(#Type); }                                     \
            virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }               \
            static  const size_t& TypeIdClass() { return sRunTimeTypeId; }                             \
            virtual Library::RTTI* QueryInterface( const size_t id ) const                             \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return (RTTI*)this; }                                                                  \
                else                                                                                         \
                    { return Parent::QueryInterface(id); }                                                   \
            }                                                                                                \
            virtual bool Is(const size_t id) const                                                     \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return Parent::Is(id); }                                                               \
            }                                                                                                \
            virtual bool Is(const std::string& name) const                                                   \
            {                                                                                                \
                if (name == TypeName())                                                                      \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return Parent::Is(name); }                                                             \
            }                                                                                                \
	   private:                                                                                              \
            static size_t sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type)	size_t Type::sRunTimeTypeId = (typeid(Type::sRunTimeTypeId).hash_code());

}










/*

#define RTTI_DECLARATIONS(Type, ParentType)                                                              \
        public:                                                                                              \
            typedef ParentType Parent;                                                                       \
            static std::string TypeName() { return std::string(#Type); }                                     \
            virtual const unsigned int& TypeIdInstance() const { return Type::TypeIdClass(); }               \
            static  const unsigned int& TypeIdClass() { return sRunTimeTypeId; }                             \
            virtual Library::RTTI* QueryInterface( const unsigned int id ) const                             \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return (RTTI*)this; }                                                                  \
                else                                                                                         \
                    { return Parent::QueryInterface(id); }                                                   \
            }                                                                                                \
            virtual bool Is(const unsigned int id) const                                                     \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return Parent::Is(id); }                                                               \
            }                                                                                                \
            virtual bool Is(const std::string& name) const                                                   \
            {                                                                                                \
                if (name == TypeName())                                                                      \
                    { return true; }                                                                         \
                else                                                                                         \
                    { return Parent::Is(name); }                                                             \
            }                                                                                                \
	   private:                                                                                              \
            static unsigned int sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type)	unsigned int Type::sRunTimeTypeId = (unsigned int) Type::sRunTimeTypeId;


*/
