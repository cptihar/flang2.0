#include "Arrays.h"

ex::Arrays::Arrays(const hlp::Token& curr_token)
	:m_currentToken(curr_token)
{}

ex::Arrays::~Arrays()
{}


///===================================
//
//  Creates a variable with a constant
// 
//  Its size cannot change
// 
//  Initializes it in resource manager
// 
//  Return: void
// 
///===================================
void ex::Arrays::c_create_array()
{
	auto buffer = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);
	size_t mem_size = std::stoul(buffer[1]);
	

	m_createHelper(buffer[0], mem_size);
}


///==========================================
// 
//  Creates array with a size stored in a var
// 
//  Size is fixed, cannot grow
// 
//  Return: void
// 
///==========================================
void ex::Arrays::v_create_array()
{
	auto buffer = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);
	size_t mem_size = m_resourceManager.v_fetch_from_memory(buffer[1]);
	m_createHelper(buffer[0], mem_size);
}


///===========================
//
//  Get value at a given index
// 
//  Return: void
//
///===========================
void ex::Arrays::c_get_value()
{
	auto buffer = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	size_t index = std::stoul(buffer[1]);
	m_fetchHelper(buffer[0], index);
}

///
// 
// 
// 
///
void ex::Arrays::v_get_value()
{
	auto buffer = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);
	int32_t fetched_value = m_resourceManager.v_fetch_from_memory(buffer[1]);
	m_fetchHelper(buffer[1], fetched_value);
}


///======================
// 
//  Array creation helper
//  
//  Return: void
//
///======================
void ex::Arrays::m_createHelper(const std::string& name, size_t mem_size)
{
	if (mem_size == 0)
		throw std::logic_error("Cannot create array with size 0");

	if (m_arrayMap.count(name))
		throw std::logic_error("Array already exists");

	ex::ArrStruct array_structure = ex::ArrStruct(m_resourceManager.getMemorySize(), mem_size);

	// Insert into hash map
	m_arrayMap[name] = array_structure;

	// Create variable for it
	m_resourceManager.c_create_variable(name, 0);

	// Dump memory
	m_resourceManager.dumpAdditionalMemory(mem_size - 1);
}


//
//
//
//
void ex::Arrays::m_fetchHelper(const std::string& name, size_t index)
{
	ex::ArrStruct current_array = m_arrayMap[name];

	if (current_array._memStart + index >= current_array._memStart + current_array._size)
		throw std::out_of_range("Out of range");

	int32_t value = m_resourceManager.c_fetch_from_memory(current_array._memStart + index);

	m_resourceManager.v_update_value(name, value);
}