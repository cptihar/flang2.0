#include "Tokenizer.h"

hlp::Tokenizer::Tokenizer(const std::vector<std::string>& raw)
	:m_rawCode(raw)
{}

hlp::Tokenizer::~Tokenizer()
{}


///========================================
// 
//  Creates tokens from the raw source code
//  Handles:
//     -> Instructions
//     -> Labels
// 
//  Doesn't check for unknown instructions
// 
//  Return: std::vector<Token>
// 
///========================================
std::vector<hlp::Token> hlp::Tokenizer::tokenized_code()
{
	auto dummy = std::vector<hlp::Token>();
	dummy.reserve(m_rawCode.size());

	for (auto& line : m_rawCode) {

		// It is a label
		if (line[0] == '_') {
			Token t;
			t.addressing_mode = ADDR_LABEL;
			t.value_buffer = line;
			dummy.emplace_back(t);
		}

		// it is not a label
		else {
			dummy.emplace_back(m_instructionToken(line));
		}
	}
	return dummy;
}


///=============================
// 
//  Creates an instruction token
//  Intializes:
//     -> Addressing mode
//     -> Instruction
//     -> Value buffer
// 
//  Return: Token
//
///=============================
hlp::Token hlp::Tokenizer::m_instructionToken(const std::string& line)
{
	Token t;

	// Determine addressing mode
	if (line.find(ADDR_CONSTANT_SYMBOL) != std::string::npos) 
		t.addressing_mode = ADDR_CONSTANT;

	else if (line.find(ADDR_IP_SYMBOL) != std::string::npos) 
		t.addressing_mode = ADDR_IP;

	else if (line.find(ADDR_REGISTER_SYMBOL) != std::string::npos) 
		t.addressing_mode = ADDR_REGISTER;

	else if (line.find(ADDR_LBL_JUMP) != std::string::npos) 
		t.addressing_mode = ADDR_JMP;

	else 
		t.addressing_mode = ADDR_VARIABLE;

	// Insert instruction
	for (uint8_t i = 0; i < 4; ++i) 
		t.instruction[i] = line[i];

	// Insert value_buffer
	t.value_buffer = (line.substr(3, line.size()));

	return t;
}
