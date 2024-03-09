#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

#include "Instructions.h"

// def = default

namespace hlp
{
	struct Token 
	{
		char		 instruction[4]; // The instruction itself, 4th byte is for null character (\0)
		uint8_t      addressing_mode; // Defines the way that the instruction should be addressed (e.g. constant)
		std::string  value_buffer; // Rest of the string containing data. If it is a label it contains its name

		Token() 
			:instruction("def"),
			 addressing_mode(99),
			 value_buffer("def")
		{}
	};

	class Tokenizer
	{
		public:
			Tokenizer(const std::vector<std::string>& raw);
			~Tokenizer();

			std::vector<Token> tokenized_code();

		private:
			const std::vector<std::string>&  m_rawCode;

		private:
			Token m_instructionToken(const std::string& line);
	};
}
#endif