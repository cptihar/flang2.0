#ifndef ARRAYS_H
#define ARRAYS_H

#include <cstdint>
#include <unordered_map>

#include "ResourceManager.h"
#include "Tokenizer.h"

namespace ex
{
	struct ArrStruct 
	{
		size_t      _memStart;
		size_t      _size;

		ArrStruct() 
			:_memStart(0), _size(0)
		{};

		ArrStruct(size_t memstart, size_t size)
			:_memStart(memstart), _size(size)
		{};
	};

	class Arrays
	{
		public:
			Arrays(const hlp::Token& curr_token);
			~Arrays();

			void c_create_array();
			void v_create_array();

			void c_get_value();
			void v_get_value();

			std::unordered_map<std::string, ArrStruct>& getArrayMap()
			{	return m_arrayMap;	}

		private: // Variables
			std::unordered_map<std::string, ArrStruct>  m_arrayMap;
			ex::ResourceManager							m_resourceManager;
			const hlp::Token&						    m_currentToken;

		private: // Helpers
			void m_createHelper(const std::string& name, size_t mem_size);
			void m_fetchHelper(const std::string& name, size_t index);
	};
}
#endif