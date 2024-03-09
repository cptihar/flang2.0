#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <iostream>

#include "ProgramStack.h"
#include "Instructions.h"

namespace ex
{
	class ResourceManager
	{
		public:

			ResourceManager() = default;
			~ResourceManager();

			// Variables

			void  delete_memory(const size_t size);
			void  c_create_variable(const std::string& variable_name, int32_t value);
			void  v_create_variable(const std::string& variable_name, const std::string& value);
			void  deleteVariable(const std::string& variable_name);
			void  v_update_value(const std::string& variable_name, int32_t new_value);
			void  c_update_value(const size_t position, int32_t new_value);


			const int32_t v_fetch_from_memory(const std::string& variable_name);
			const int32_t c_fetch_from_memory(const size_t index);
			const size_t  getPositionInMemory(const std::string& variable_name);

			void  dumpFixedMemoryToPosition(size_t start_position, const std::vector<int32_t>& mem);
			void  dumpFixedMemory(std::vector<int32_t> mem);
			void  dumpAdditionalMemory(size_t elements);
			void  deleteMemoryInRange(size_t start, size_t size);
			void  deleteScopedVariables();

			const size_t  getMemorySize() const
			{  return m_programMemory.size();  }
			
			const std::string  getSpacelessBuffer(const std::string& str) const;

			const std::vector<std::string>  bufferSplitConstant(const std::string& str) const;
			const std::vector<std::string>  bufferSplitVariable(const std::string& str) const;

		private:

			static std::unordered_map<std::string, size_t>  m_variables;
			static std::vector<int32_t>						m_programMemory;
			ex::ProgramStack								m_programStack;
	};
}
#endif // ! RESOURCE_MANAGER_H