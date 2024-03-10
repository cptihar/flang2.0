#include "Interpreter.h"

ex::Interpreter::Interpreter(const std::vector<hlp::Token>& tokenized)
	: m_tokenizedCode(tokenized),
	  m_instructionPointer(0),
	  m_variableHandler(m_currentToken),
	  m_containsWanderingCode(false),
	  m_branchingHandler(m_currentToken, m_labelPositions, m_instructionPointer),
	  m_arrayHandler(m_currentToken),
	  m_stringHandler(m_currentToken),
	  m_arrayRegisterHandler(m_currentToken)
{

	// Bind the necessary things
	m_bindHashFunctions();
	m_setupLabelPositions();
}

ex::Interpreter::~Interpreter()
{}


///=============================================
//
//  Iterates through the tokens
//  Extracts their hashable values
//  Looks up table, calls corresponding function
// 
//  If there is an error during execution:
//     -> Sets program failure flag
//	   -> Returns early
// 
//  Return: void
//
///=============================================
void ex::Interpreter::interpretProgram()
{
	m_instructionPointer++; // Move IP from the main label, straight into exectuion position

	while (m_instructionPointer < m_tokenizedCode.size()) {

		m_currentToken = m_tokenizedCode[m_instructionPointer];

		// Check whether a label would be executed (bad af)
		if (m_currentToken.addressing_mode == ADDR_LABEL) {
			m_containsWanderingCode = true;
			return;
		}

		// Execute
		std::string lookupValue = m_extractInstruction(m_currentToken);

		auto func = m_hashedFunctions.find(lookupValue); 
		func->second(); // Should be ok to call it like that, other functions checks whether the instruction is valid


		// Increase instruction pointer
		m_instructionPointer++;
	}
}


///============================================
// 
//  Inserts the label's positions into hash map
// 
//  Looks for entry point:
//     -> Sets IP to that position
// 
//  If entry point is not found:
// 	  -> Updates appropriate flags
// 
//  Return: void
// 
///============================================
void ex::Interpreter::m_setupLabelPositions()
{
	size_t counter = 0;
	for (auto& tk : m_tokenizedCode) {

		// It is a label
		if (tk.addressing_mode == ADDR_LABEL) {
			m_labelPositions[tk.value_buffer] = counter;
			if (tk.value_buffer == ENTR_POINT_NAME) {
				m_instructionPointer = counter;
			}
		}
		++counter;
	}
}


///====================================
// 
//  Extracts the instruction from token
//		-> Instruction name
//		-> Addressing mode  
// 
//  Return: const std::string
// 
///====================================
const std::string ex::Interpreter::m_extractInstruction(const hlp::Token& t)
{
	return std::string(t.instruction, 3) + char(t.addressing_mode + '0');
}


///=============================================
//  
//  Initializes the execution hash map
//  
//  Binds external functions to the instructions
//  (for speed)
//
//  Haborus bun
// 
//  Return: void 
//
///=============================================
void ex::Interpreter::m_bindHashFunctions()
{
	// Variables
	m_hashedFunctions[PVA_V] = std::bind(&ex::Variables::v_print_as_number, &m_variableHandler);
	m_hashedFunctions[VAR_C] = std::bind(&ex::Variables::c_create_variable, &m_variableHandler);
	m_hashedFunctions[VAR_V] = std::bind(&ex::Variables::v_create_variable, &m_variableHandler);

	// Additions
	m_hashedFunctions[ADD_C] = std::bind(&ex::Variables::c_add_value, &m_variableHandler);
	m_hashedFunctions[ADD_V] = std::bind(&ex::Variables::v_add_value, &m_variableHandler);

	// Subtractions
	m_hashedFunctions[SUB_C] = std::bind(&ex::Variables::c_sub_value, &m_variableHandler);
	m_hashedFunctions[SUB_V] = std::bind(&ex::Variables::v_sub_value, &m_variableHandler);

	// Multiplications
	m_hashedFunctions[MUL_C] = std::bind(&ex::Variables::c_mul_value, &m_variableHandler);
	m_hashedFunctions[MUL_V] = std::bind(&ex::Variables::v_mul_value, &m_variableHandler);

	// Division
	m_hashedFunctions[DIV_C] = std::bind(&ex::Variables::c_div_value, &m_variableHandler);
	m_hashedFunctions[DIV_V] = std::bind(&ex::Variables::v_div_value, &m_variableHandler);

	// Modulo
	m_hashedFunctions[MOD_C] = std::bind(&ex::Variables::c_mod_value, &m_variableHandler);
	m_hashedFunctions[MOD_V] = std::bind(&ex::Variables::v_mod_value, &m_variableHandler);

	// Equ
	m_hashedFunctions[EQU_C] = std::bind(&ex::Variables::c_equ_value, &m_variableHandler);
	m_hashedFunctions[EQU_V] = std::bind(&ex::Variables::v_equ_value, &m_variableHandler);

	// cmp
	m_hashedFunctions[CMP_C] = std::bind(&ex::Branching::c_compare_values, &m_branchingHandler);
	m_hashedFunctions[CMP_V] = std::bind(&ex::Branching::v_compare_values, &m_branchingHandler);
	m_hashedFunctions[CCF_R] = std::bind(&ex::Branching::clear_comparison_flags, &m_branchingHandler);

	// jumps
	m_hashedFunctions[JEQ_L] = std::bind(&ex::Branching::l_jump_equal, &m_branchingHandler);
	m_hashedFunctions[JEQ_C] = std::bind(&ex::Branching::c_jump_equal, &m_branchingHandler);
	m_hashedFunctions[JNE_C] = std::bind(&ex::Branching::c_jump_not_equal, &m_branchingHandler);
	m_hashedFunctions[JNE_L] = std::bind(&ex::Branching::l_jump_not_equal, &m_branchingHandler);
	m_hashedFunctions[JSM_C] = std::bind(&ex::Branching::c_jump_smaller, &m_branchingHandler);
	m_hashedFunctions[JSM_L] = std::bind(&ex::Branching::l_jump_smaller, &m_branchingHandler);
	m_hashedFunctions[JSE_C] = std::bind(&ex::Branching::c_jump_smaller_or_equal, &m_branchingHandler);
	m_hashedFunctions[JSE_L] = std::bind(&ex::Branching::l_jump_smaller_or_equal, &m_branchingHandler);
	m_hashedFunctions[JGE_C] = std::bind(&ex::Branching::c_jump_greater_or_equal, &m_branchingHandler);
	m_hashedFunctions[JGE_L] = std::bind(&ex::Branching::l_jump_greater_or_equal, &m_branchingHandler);
	m_hashedFunctions[JGR_C] = std::bind(&ex::Branching::c_jump_greater, &m_branchingHandler);
	m_hashedFunctions[JGR_L] = std::bind(&ex::Branching::l_jump_greater, &m_branchingHandler);
	m_hashedFunctions[JMP_C] = std::bind(&ex::Branching::c_jump, &m_branchingHandler);
	m_hashedFunctions[JMP_L] = std::bind(&ex::Branching::l_jump, &m_branchingHandler);
	
	m_hashedFunctions[CST_R] = std::bind(&ex::Branching::r_clear_stack_instruction, &m_branchingHandler);
	m_hashedFunctions[PSH_R] = std::bind(&ex::Branching::r_push_stack, &m_branchingHandler);

	// Arrays
	m_hashedFunctions[ARR_C] = std::bind(&ex::Arrays::c_create_array, &m_arrayHandler);
	m_hashedFunctions[ARR_V] = std::bind(&ex::Arrays::v_create_array, &m_arrayHandler);
	m_hashedFunctions[STR_V] = std::bind(&ex::Strings::create_string, &m_stringHandler);
	m_hashedFunctions[PRS_C] = std::bind(&ex::Strings::print_string, &m_stringHandler);
	m_hashedFunctions[PSN_C] = std::bind(&ex::Strings::print_string_with_newline, &m_stringHandler);

	// Registers
	m_hashedFunctions[MAR_V] = std::bind(&ex::ArrayRegister::move_register_to_array, &m_arrayRegisterHandler);
	m_hashedFunctions[URI_V] = std::bind(&ex::ArrayRegister::update_array_register_index, &m_arrayRegisterHandler);
	m_hashedFunctions[FVR_V] = std::bind(&ex::ArrayRegister::fetch_value_from_index, &m_arrayRegisterHandler);
	m_hashedFunctions[PVR_R] = std::bind(&ex::ArrayRegister::push_value_from_register, &m_arrayRegisterHandler);
	m_hashedFunctions[PRV_R] = std::bind(&ex::ArrayRegister::print_value_at_index, &m_arrayRegisterHandler);
	m_hashedFunctions[EXP_V] = std::bind(&ex::ArrayRegister::export_to_variable, &m_arrayRegisterHandler);
	m_hashedFunctions[SRV_V] = std::bind(&ex::ArrayRegister::set_register_value, &m_arrayRegisterHandler);
} // Xd