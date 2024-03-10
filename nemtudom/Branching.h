#ifndef BRANCHING_H
#define BRANCHING_H

#include <stack>
#include <cstdint>
#include <unordered_map>

#include "Tokenizer.h" // Token struct definition
#include "ProgramStack.h"
#include "ResourceManager.h"

#define DEFAULT_VALUE		0b00000000

#define JUMP_EQUAL          0b10000000
#define JUMP_NOT_EQUAL      0b01000000

#define JUMP_GREATER        0b00100000
#define JUMP_SMALLER        0b00010000

#define JUMP_GREATER_EQUAL  0b00001000
#define JUMP_SMALLER_EQUAL  0b00000100

#define LABEL_MAP  std::unordered_map<std::string, size_t>

namespace ex
{

	class Branching
	{
		public:
			Branching(const hlp::Token& curr_token, LABEL_MAP& mp, size_t& it);
			~Branching();

			// Reset flags
			void clear_comparison_flags() 
			{ m_comparisonFlags = DEFAULT_VALUE; }

			// Comparisons

			void c_compare_values();
			void v_compare_values();


			// Jumps

			void l_jump();
			void c_jump();

			void l_jump_equal();
			void c_jump_equal();

			void l_jump_not_equal();
			void c_jump_not_equal();

			void l_jump_greater();
			void c_jump_greater();

			void l_jump_smaller();
			void c_jump_smaller();


			void l_jump_smaller_or_equal();
			void c_jump_smaller_or_equal();

			void l_jump_greater_or_equal();
			void c_jump_greater_or_equal();

			void r_clear_stack_instruction();
			void r_push_stack();

		private: // Variables
			ex::ResourceManager  m_resourceManager;
			std::stack<size_t>   m_iteratorStack;
			const hlp::Token&    m_currentToken;
			uint8_t              m_comparisonFlags;
			ex::ProgramStack     m_programStack;

		private: // References
			LABEL_MAP&  m_labelMap;
			size_t&		m_instructionPointer;

		private: // Functions
			void         m_makeComparison(const int32_t var1, const int32_t var2);
			inline void  m_executeConstantJump(uint8_t flag);
			inline void  m_executeLabelJump(uint8_t flag);
	};
}
#endif // !BRANCHING_H