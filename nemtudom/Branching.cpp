#include "Branching.h"

ex::Branching::Branching(const hlp::Token& curr_token, LABEL_MAP& mp, size_t& it)
	:m_currentToken(curr_token), 
	 m_compareFlags(DEFAULT_VALUE),
	 m_labelMap(mp),
	 m_instructionPointer(it)
{}

ex::Branching::~Branching()
{}


///====================================================
//
//  Handles comparisons between variables and constants
// 
//  Return: void
//
///====================================================
void ex::Branching::c_compare_values()
{
	auto str_buffer = m_resourceManager.bufferSplitConstant(m_currentToken.value_buffer);

	// Get values
	int32_t variable_value = m_resourceManager.v_fetch_from_memory(str_buffer[0]);
	int32_t constant_value = std::stoi(str_buffer[1]);

	m_makeComparison(variable_value, constant_value);
}


///======================================
//
//  Handles comparisons between variables
// 
//  Return: void
//
///======================================
void ex::Branching::v_compare_values()
{
	auto str_buffer = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

	// Fetch values
	int32_t variable1 = m_resourceManager.v_fetch_from_memory(str_buffer[0]);
	int32_t variable2 = m_resourceManager.v_fetch_from_memory(str_buffer[1]);

	m_makeComparison(variable1, variable2);
}


///=============================
// 
//  Executes unconditional jumps
// 
//  Return: void
// 
///=============================
void ex::Branching::l_jump()
{
	m_executeLabelJump(m_compareFlags);
}

void ex::Branching::c_jump()
{
	m_executeConstantJump(m_compareFlags);
}


///===============================================
// 
//  Manipulates the IP if the comparison was equal
//  
//  Return: void
// 
///===============================================
void ex::Branching::l_jump_equal()
{
	m_executeLabelJump(JUMP_EQUAL);
}

void ex::Branching::c_jump_equal()
{
	m_executeConstantJump(JUMP_EQUAL);
}


///=======================================================
// 
//  Manipulates the IP if the was not comparison was equal
//  
//  Return: void
// 
///=======================================================
void ex::Branching::l_jump_not_equal()
{
	m_executeLabelJump(JUMP_NOT_EQUAL);
}

void ex::Branching::c_jump_not_equal()
{
	m_executeConstantJump(JUMP_NOT_EQUAL);
}


///============================
// 
//  Handles greater (jgr) jumps
// 
//  Return: void
// 
///============================
void ex::Branching::l_jump_greater()
{
	m_executeLabelJump(JUMP_GREATER);
}

void ex::Branching::c_jump_greater()
{
	m_executeConstantJump(JUMP_GREATER);
}


///============================
// 
//  Handles smaller (jsm) jumps
// 
//  Return: void
// 
///============================
void ex::Branching::l_jump_smaller()
{
	m_executeLabelJump(JUMP_SMALLER);
}

void ex::Branching::c_jump_smaller()
{
	m_executeConstantJump(JUMP_SMALLER);
}


///===============================================
//
//  Handles branching smaller or equal flag is set
//  
//  Return: void
// 
///===============================================
void ex::Branching::l_jump_smaller_or_equal()
{
	m_executeLabelJump(JUMP_SMALLER_EQUAL);
}

void ex::Branching::c_jump_smaller_or_equal()
{
	m_executeConstantJump(JUMP_SMALLER_EQUAL);
}


///===============================================
//
//  Handles branching greater or equal flag is set
//  
//  Return: void
// 
///===============================================
void ex::Branching::l_jump_greater_or_equal()
{
	m_executeLabelJump(JUMP_GREATER_EQUAL);
}

void ex::Branching::c_jump_greater_or_equal()
{
	m_executeConstantJump(JUMP_GREATER_EQUAL);
}


///==================================
//
//  Handles return instruction
// 
//  Deletes memory that was allocated
// 
//  Return: void
//
///==================================
void ex::Branching::r_return_instruction()
{
	// Extract values
	size_t return_position = m_iteratorStack.top().return_position;
	size_t delete_size = m_resourceManager.getMemorySize() - m_iteratorStack.top().mem_size_before;

	// Handle jump back
	m_instructionPointer = return_position;
	m_resourceManager.delete_memory(delete_size);

	// Pop
	m_iteratorStack.pop();
}


///========================================
//
//  Pushes data related to jumps
//  Could be useful for memory optimization 
//  (when jumps happen)
//
//  Return: void
// 
///========================================
void ex::Branching::r_push_stack()
{
	// Push to the stack
	m_iteratorStack.push({ m_instructionPointer, m_resourceManager.getMemorySize() });
}


///====================================================================
//
//  It will pops the stack
//  Does not delete memory!!! (ret does it)
// 
//  Does not check for errors
//  (If the stack is empty program will crash anyways (should be fine))
//
//  Return: void
//
///====================================================================
void ex::Branching::r_pop_stack()
{
	m_iteratorStack.pop();
}


///=====================================
//
//  Makes the comparisons between values
// 
//  Sets the appropriate flags
//
//  Return: void
//
///=====================================
void ex::Branching::m_makeComparison(const int32_t var1, const int32_t var2)
{
	m_compareFlags = 0; // Reset flags
	// Equality
	m_compareFlags |= JUMP_EQUAL * (var1 == var2);
	m_compareFlags |= JUMP_NOT_EQUAL * (var1 != var2);

	// Greater and smaller
	m_compareFlags |= JUMP_GREATER * (var1 > var2);
	m_compareFlags |= JUMP_SMALLER * (var1 < var2);

	// Greater and smaller + equality
	m_compareFlags |= JUMP_GREATER_EQUAL * (var1 >= var2);
	m_compareFlags |= JUMP_SMALLER_EQUAL * (var1 <= var2);
}


///=========================================
// 
//  Function template for constant branching
//
//  Calculates the IP's new position
// 
//  Return: void
// 
///=========================================
void ex::Branching::m_executeConstantJump(uint8_t flag)
{
	std::string buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

	int64_t jump_value = std::stoi(buffer.substr(1, buffer.size()));

	m_instructionPointer += jump_value * ((m_compareFlags & flag) == flag);
}


///======================================
// 
//  Function template for label branching
//
//  Calculates the IP's new position
// 
//  Return: void
// 
///======================================
inline void ex::Branching::m_executeLabelJump(uint8_t flag)
{
	// Convert buffer
	auto buffer = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

	// Fetch data
	std::string label_name = buffer.substr(1, buffer.size());

	size_t label_position = m_labelMap[label_name];
	int64_t jump_factor = label_position - m_instructionPointer;

	m_instructionPointer += jump_factor * ((m_compareFlags & flag) == flag);
}