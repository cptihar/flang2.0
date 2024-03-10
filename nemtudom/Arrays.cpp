#include "Arrays.h"

ex::Arrays::Arrays(const hlp::Token& curr_token)
	:m_currentToken(curr_token), m_resourceManager(), m_registerHandler()
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

	// Create variable for it
	m_resourceManager.c_create_variable(name, 0);

	// Dump memory
	m_resourceManager.dumpAdditionalMemory(mem_size - 1);
}