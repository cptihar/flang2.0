#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "ArrayRegister.h"
#include "Tokenizer.h" // Include token struct
#include "Variables.h"
#include "Branching.h"
#include "Arrays.h"
#include "Strings.h"

#define ERR_MSG_WANDER_CODE  "Program contains wandering code\n"

namespace ex 
{
	class Interpreter
	{
		public:
			Interpreter(const std::vector<hlp::Token>& tokenized);
			~Interpreter();


			std::unordered_map<std::string, std::function<void()>>& getInstructionMap()
			{  return m_hashedFunctions;  }

			const bool hasWanderingCode() const
			{  return m_containsWanderingCode;  }

			void interpretProgram();

		private: // References, execution related variables, objects
			hlp::Token						m_currentToken;
			const std::vector<hlp::Token>&	m_tokenizedCode;
			size_t							m_instructionPointer;
			ex::Variables					m_variableHandler;
			bool							m_containsWanderingCode;
			ex::Branching					m_branchingHandler;
			ex::Arrays						m_arrayHandler;
			ex::Strings						m_stringHandler;
			ex::ArrayRegister				m_arrayRegisterHandler;

		private: // Important hash maps
			std::unordered_map<std::string, std::function<void()>>  m_hashedFunctions;
			std::unordered_map<std::string, size_t>				    m_labelPositions;


		private: // Helper functions
			const std::string  m_extractInstruction(const hlp::Token& t);
			void			   m_bindHashFunctions();
			void			   m_setupLabelPositions();
	};
}
#endif // ! INTERPRETER_H