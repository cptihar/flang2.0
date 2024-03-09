#include "ResourceManager.h"
namespace ex {
	std::vector<int32_t> ResourceManager::m_programMemory; // Definition
	std::unordered_map<std::string, size_t> ResourceManager::m_variables;
}


ex::ResourceManager::~ResourceManager()
{
	#if DEBUG_STATE
		std::cout << "Total memory size: " << m_programMemory.size() << '\n';
		std::cout << "Number of variables: " << m_variables.size() << '\n';
	#endif

	#if GET_MEM_STATE
	for (auto k : m_programMemory) {
		std::cout << k << '\n';
	}
	#endif
}

///=============================
//
//  Deletes elements from memory
//  
//  Checks for invalid size
// 
//  Throws: std::logic_error
//  Return: void
// 
///=============================
void ex::ResourceManager::delete_memory(const size_t size)
{
	m_programMemory.erase(m_programMemory.end() - size, m_programMemory.end());
}


///================================================
//
//  Creates variable
//  Updates all of the necessary data structures
//  
//  If variable already exists, throws an exception
// 
//  Throws: std::logic_error
//  Return: void
//
///================================================
void ex::ResourceManager::c_create_variable(const std::string & variable_name, int32_t value)
{
	if (m_variables.count(variable_name)) {
		throw std::logic_error("Variable already exists");
	}

	m_variables[variable_name] = m_programMemory.size();
	m_programMemory.push_back(value);
	m_programStack.insertToScope(variable_name);
}


///===================================================================
//
//  Creates variable
//  Updates all of the necessary data structures
//  
//  If variable already exists OR the referenced variable doesnt exist
//		-> throws an exception
// 
//  Throws: std::logic_error
//  Return: void
//
///===================================================================
void ex::ResourceManager::v_create_variable(const std::string& variable_name, const std::string& value)
{
	if (m_variables.count(variable_name) || !m_variables.count(value)) {
		throw std::logic_error("Error while creating variable from another variable");
	}

	m_variables[variable_name] = m_programMemory.size();
	m_programMemory.push_back(m_programMemory[m_variables[value]]);
	m_programStack.insertToScope(variable_name);
}


///=======================================
//
//  Deletes variable from the map ONLY!!
//		-> Useful for variable promotion
// 
//  Updates the necessary containers
// 
//  If it doesnt exist throws an exception
// 
//  Throws: std::logic_error
//  Return: void
//
///=======================================
void ex::ResourceManager::deleteVariable(const std::string& variable_name)
{
	// Check whether variable exists
	if (!m_variables.count(variable_name)) {
		throw std::logic_error("Variable '" + variable_name + "' doesn't exist");
	}

	// Delete it from map
	m_variables.erase(variable_name);
}


///==========================================
// 
//  Updates the variable's value
//  Updates all the necessary data structures
//  
//  If it doesnt exist throws an exception
// 
//  Throws: std::logic_error
//  Return: void
// 
///==========================================
void ex::ResourceManager::v_update_value(const std::string& variable_name, int32_t new_value)
{
	if (!m_variables.count(variable_name)) {
		throw std::logic_error("Variable '" + variable_name + "' doesn't exist");
	}

	m_programMemory[m_variables[variable_name]] = new_value ;
}


///===========================================
// 
//  Updates the memory at position (parameter)
// 
//  Checks whether the index is out of bounds
//  If it is throws an exception
// 
//  Throws: std::out_of_range
//  Return: void
//
///===========================================
void ex::ResourceManager::c_update_value(const size_t position, int32_t new_value)
{
	if (position >= m_programMemory.size())
		throw std::out_of_range("Position of is out of bounds");

	m_programMemory[position] = new_value;
}


///===========================================
//
//  Returns the value stored by the variable
//  
//  If it doesn't exist it throws an exception
// 
//  Throws: std::logic_error
//  Return: int32_t (the value)
// 
///===========================================
const int32_t ex::ResourceManager::v_fetch_from_memory(const std::string& variable_name)
{
	if (!m_variables.count(variable_name))
		throw std::logic_error("Variable '" + variable_name + "'doesn't exist");

	return m_programMemory[m_variables[variable_name]];
}


///==========================================
//
//  Returns the value at index
// 
//  If it is out of range throws an exception
// 
//  Throws: std::out_of_range
//  Return: void
// 
///==========================================
const int32_t ex::ResourceManager::c_fetch_from_memory(const size_t index)
{
	if (index >= m_programMemory.size())
		throw std::out_of_range("Index is out of range");

	return m_programMemory[index];
}

const size_t ex::ResourceManager::getPositionInMemory(const std::string& variable_name)
{
	if (!m_variables.count(variable_name))
		throw std::logic_error("Variable not found");

	return m_variables[variable_name];
}

//
//
//
void ex::ResourceManager::dumpFixedMemoryToPosition(size_t start_position, const std::vector<int32_t>& mem)
{
	if (start_position > m_programMemory.size())
		throw std::out_of_range("Start position is too big");
	m_programMemory.insert(m_programMemory.begin() + start_position, mem.begin(), mem.end());
}

///==========================
// 
//  Inserts additional memory
// 
//  Return: void
// 
///==========================
void ex::ResourceManager::dumpFixedMemory(std::vector<int32_t> mem)
{
	m_programMemory.insert(m_programMemory.end(), mem.begin(), mem.end());
}


///======================================
// 
//  Dumps additional elements to the back
// 
//  Useful for array creation
//
//  Return: void
//
///======================================
void ex::ResourceManager::dumpAdditionalMemory(size_t elements)
{
	m_programMemory.insert(m_programMemory.end(), elements, 0);
}


///========================================
//
//  Deletes elements from memory in a range
// 
//  Return: void
// 
///========================================
void ex::ResourceManager::deleteMemoryInRange(size_t start, size_t size)
{
	m_programMemory.erase(m_programMemory.begin() + start, m_programMemory.begin() + size);
}


///====================================================
// 
//  Handles the deletion of variables when a scope ends
// 
//  Doesnt check for errors, previous functions do it
// 
//  Return: void
//
///====================================================
void ex::ResourceManager::deleteScopedVariables()
{
	for (auto& s : m_programStack.getTop())
		m_variables.erase(s);
}


///==========================================
// 
//  Removes all of the spaces from the string
//  Makes a copy of the parameter!
// 
//  Return: const std::string
//
///==========================================
const std::string ex::ResourceManager::getSpacelessBuffer(const std::string& str) const
{
	std::string ret_data = str;
	ret_data.erase(std::remove(ret_data.begin(), ret_data.end(), ' '), ret_data.end());
	return ret_data;
}


///=======================================
//
//  Splits the string buffer up
//  
//  Checks for invalid syntax
// 
//  First element: variable's name
//  Second element: constant value
//  Useful for constant addressing
// 
//  Return: const std::vector<std::string>
// 
///=======================================
const std::vector<std::string> ex::ResourceManager::bufferSplitConstant(const std::string& str) const
{
	std::string copy_str = getSpacelessBuffer(str);

	std::vector<std::string> ret_value;
	ret_value.reserve(2);

	auto colon_position = copy_str.find(',');

	if (colon_position == std::string::npos)
		throw std::logic_error("No ',' was found");

	ret_value.emplace_back(copy_str.substr(0, colon_position));
	ret_value.emplace_back(copy_str.substr(colon_position + 2, copy_str.size()));
	return ret_value;
}


///========================================
//
//  Splits the string buffer up
//  
//  Checks for invalid syntax
// 
//  First element: first variable's name
//  Second element: second variable's value
// 
//  Useful for variable addressing
// 
//  Return: const std::vector<std::string>
// 
///========================================
const std::vector<std::string> ex::ResourceManager::bufferSplitVariable(const std::string& str) const
{
	std::string copy_str = getSpacelessBuffer(str);

	std::vector<std::string> ret_value;
	ret_value.reserve(2);

	auto colon_position = copy_str.find(',');

	if (colon_position == std::string::npos)
		throw std::logic_error("No ',' was found");

	ret_value.emplace_back(copy_str.substr(0, colon_position));
	ret_value.emplace_back(copy_str.substr(colon_position + 1, copy_str.size()));
	return ret_value;
}