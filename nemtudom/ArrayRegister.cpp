#include "ArrayRegister.h"

ex::ArrayRegister::ArrayRegister(const hlp::Token& token)
	:m_resourceManager(), 
	 m_currentToken(token), 
	 m_registerHandler()
{
}

ex::ArrayRegister::~ArrayRegister()
{}


///=======================================================
//
//  Moves the register's position to the array's beginning
// 
//  Addressing mode: variable
// 
//  Return: void
//
///=======================================================
void ex::ArrayRegister::move_register_to_array()
{
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);
	m_registerHandler.setRegisterStartIndex(m_resourceManager.getPositionInMemory(buffer));

}


///=========================================================
//
//  Updates the registers current index
// 
//  Addressing mode: variable (uri -> Update register index)
// 
//  Return: void
//
///=========================================================
void ex::ArrayRegister::update_array_register_index()
{
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

	// Get index value

	uint32_t index = m_resourceManager.v_fetch_from_memory(buffer);

	m_registerHandler.setRegisterIndex(index);
}


///==========================================
//
//  Sets the registers value to a variables
//
//  Addressing mode: variable (srv variable;)
// 
//  Return: void
// 
///==========================================
void ex::ArrayRegister::set_register_value()
{
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);
	uint32_t stored_value = m_resourceManager.v_fetch_from_memory(buffer);
	m_registerHandler.setRegisterValue(stored_value);
}


///===========================================
//
//  Fetches the value that the index points to
// 
//  It is stored in the register
// 
//  Addressing mode: variable (fvi index;)
// 
//  Return: void
// 
///===========================================
void ex::ArrayRegister::fetch_value_from_index()
{
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

	// Get index value

	uint32_t index = m_resourceManager.v_fetch_from_memory(buffer);
	size_t array_start = m_registerHandler.getRegisterStartIndex();

	uint32_t element_value = m_resourceManager.c_fetch_from_memory(index + array_start);
	m_registerHandler.setRegisterValue(element_value);
}


///=======================================================
//
//  Pushes the value stored in the register into the array
//
//  Addressing mode: register (pvr^)
// 
//  Return: void
//
///=======================================================
void ex::ArrayRegister::push_value_from_register()
{
	uint32_t value_in_register = m_registerHandler.getRegisterValue();

	size_t push_pos = m_registerHandler.getRegisterStartIndex() + m_registerHandler.getCurrentIndex();

	m_resourceManager.c_update_value(push_pos, value_in_register);
}


///========================================
//
//  Prints the value stored in the register
// 
//  Adressing mode: register (prv^)
//
//  Return: void
// 
///========================================
void ex::ArrayRegister::print_value_at_index()
{
	size_t mem_index = m_registerHandler.getCurrentIndex() + m_registerHandler.getRegisterStartIndex();
	uint32_t value = m_resourceManager.c_fetch_from_memory(mem_index);
	std::cout << value;
}


///
//
//
//
///
void ex::ArrayRegister::export_to_variable()
{
	auto variable_name = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

	uint32_t value_in_index = m_registerHandler.getRegisterValue();
	m_resourceManager.v_update_value(variable_name, value_in_index);
}