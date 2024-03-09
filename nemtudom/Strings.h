#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <iostream>
#include <unordered_map>

#include "ResourceManager.h"
#include "Tokenizer.h"
#include "Arrays.h" // Get ArrStruct

#define CHAR_SIZE_IN_BITS 8

namespace ex
{
	class Strings
	{
		public:
			Strings(const hlp::Token& curr_token);
			~Strings();

			void create_string();

			void print_string();
			void print_string_with_newline();

		private: // Private variables
			ex::ResourceManager  m_resourceManager;
			const hlp::Token&    m_currentToken;

		private: // Helpers
			std::vector<std::string>  m_stringCreationHelper();
			std::vector<int32_t>	  m_createIntRepresentation(const std::string& str);
			inline void			      m_printString();
	};
}
#endif // !_STRINGS_H_