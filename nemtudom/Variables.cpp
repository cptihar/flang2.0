#include "Variables.h"

ex::Variables::Variables(const hlp::Token& curr_token)
	:m_currentToken(curr_token)
{}

ex::Variables::~Variables()
{}


///=================================================
//
//  Handles variable creation
//  Sets its value to a number (constant addressing)
// 
//  Achieved via ResourceManager
// 
//  Doesn't check for errors
// 
//  Return: void
//
///=================================================
void ex::Variables::c_create_variable()
{
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Create
	m_resourceManager.c_create_variable(value[0], std::stoi(value[1]));
}


///===================================
//
//  Handles variable creation
//  Sets its value to another variable
// 
//  Doesn't check for errors
// 
//  Return: void
//
///===================================
void ex::Variables::v_create_variable()
{
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Create
	m_resourceManager.v_create_variable(value[0], value[1]);
}


///=====================================
//
//  Handles addition between:
//		-> Variables and constant values
// 
//  Doesn't check for errors
// 
//  Return: void
//
///=====================================
void ex::Variables::c_add_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);


	// Update values
	int32_t current_value = m_resourceManager.v_fetch_from_memory(value[0]);
	current_value += std::stoi(value[1]);

	// Update in "memory"
	m_resourceManager.v_update_value(value[0], current_value);
}


///==========================
//
//  Handles addition between:
//		-> Variables values
// 
//  Doesn't check for errors
// 
//  Return: void
//
///==========================
void ex::Variables::v_add_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Values
	int32_t first = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t second = m_resourceManager.v_fetch_from_memory(value[1]);

	first += second;

	// Update 
	m_resourceManager.v_update_value(value[0], first);
}


///=====================================
//
//  Handles subtraction between:
//		-> Variables and constant values
// 
//  Doesn't check for errors
// 
//  Return: void
//
///=====================================
void ex::Variables::c_sub_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Update values
	int32_t current_value = m_resourceManager.v_fetch_from_memory(value[0]);
	current_value -= std::stoi(value[1]);

	// Update in "memory"
	m_resourceManager.v_update_value(value[0], current_value);
}


///=============================
//
//  Handles subtraction between:
//		-> Variables
// 
//  Doesn't check for errors
// 
//  Return: void
//
///=============================
void ex::Variables::v_sub_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Values
	int32_t first = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t second = m_resourceManager.v_fetch_from_memory(value[1]);

	first -= second;

	// Update 
	m_resourceManager.v_update_value(value[0], first);
}


///================================
//
//  Handles multiplication between:
//		-> Variables and constants
// 
//  Doesn't check for errors
// 
//  Return: void
//
///================================
void ex::Variables::c_mul_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Update values
	int32_t current_value = m_resourceManager.v_fetch_from_memory(value[0]);
	current_value *= std::stoi(value[1]);

	// Update in "memory"
	m_resourceManager.v_update_value(value[0], current_value);
}


///================================
//
//  Handles multiplication between:
//		-> Variables
// 
//  Doesn't check for errors
// 
//  Return: void
//
///================================
void ex::Variables::v_mul_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Values
	int32_t first = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t second = m_resourceManager.v_fetch_from_memory(value[1]);

	first *= second;

	// Update 
	m_resourceManager.v_update_value(value[0], first);
}


///================================
//
//  Handles division between:
//		-> Variables and constants
// 
//  Doesn't check for errors
// 
//  Return: void
//
///================================
void ex::Variables::c_div_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Update values
	int32_t current_value = m_resourceManager.v_fetch_from_memory(value[0]);
	float   divisor = std::stof(value[1]);

	if (divisor == 0.0f || current_value == 0) 
		throw std::logic_error("Zero division");

	current_value /= divisor;

	// Update in "memory"
	m_resourceManager.v_update_value(value[0], current_value);
}


///==========================
//
//  Handles division between:
//		-> Variables
// 
//  Doesn't check for errors
// 
//  Return: void
//
///==========================
void ex::Variables::v_div_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Values
	int32_t first = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t second = m_resourceManager.v_fetch_from_memory(value[1]);

	if (first == 0 || second == 0) 
		throw std::logic_error("Zero division");

	first /= second;

	// Update 
	m_resourceManager.v_update_value(value[0], first);
}


///==================================
//
//  Handles modulo operation between:
//		-> Variables and constants
// 
//  Doesn't check for errors
// 
//  Return: void
//
///==================================
void ex::Variables::c_mod_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Update values
	int32_t current_value = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t divisor = std::stoi(value[1]);

	if (divisor == 0 && current_value == 0) 
		throw std::logic_error("Zero division");

	current_value %= divisor;

	// Update in "memory"
	m_resourceManager.v_update_value(value[0], current_value);
}


///==================================
//
//  Handles modulo operation between:
//		-> Variables
// 
//  Doesn't check for errors
// 
//  Return: void
//
///==================================
void ex::Variables::v_mod_value()
{
	// Format value_buffer
	auto value = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Values
	int32_t first = m_resourceManager.v_fetch_from_memory(value[0]);
	int32_t second = m_resourceManager.v_fetch_from_memory(value[1]);

	if (first == 0 || second == 0)
		throw std::logic_error("Zero division");
	
	first %= second;

	// Update 
	m_resourceManager.v_update_value(value[0], first);
}


///=====================================
// 
//  Sets a variables value to a constant
//  
//  Does not check for errors!
//  Does not create the variable!
// 
//  Return: void
//
///=====================================
void ex::Variables::c_equ_value()
{
	auto buffer = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);
	int32_t value = std::stoi(buffer[1]);
	m_resourceManager.v_update_value(buffer[0], value);
}


///=============================================
// 
//  Sets a variables value to another variable's
//  
//  Does not check for errors!
//  Does not create the variable!
// 
//  Return: void
//
///=============================================
void ex::Variables::v_equ_value()
{
	auto buffer = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);
	int32_t second_value = m_resourceManager.v_fetch_from_memory(buffer[1]);
	m_resourceManager.v_update_value(buffer[0], second_value);
}


///====================================================================
//
//  Handles variable printing
// 
//  Whether the variable exists or not is checked by external functions
// 
//  Return: void
//
///====================================================================
void ex::Variables::v_print_as_number()
{
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);
	std::cout << m_resourceManager.v_fetch_from_memory(buffer);
}