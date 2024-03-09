#ifndef VARIABLES_H
#define VARIABLES_H

#include <algorithm>

#include "ResourceManager.h"
#include "ProgramStack.h"
#include "Tokenizer.h"

namespace ex
{
	class Variables
	{
		public:
			Variables(const hlp::Token& curr_token);
			~Variables();

			void c_create_variable();
			void v_create_variable();

			void c_add_value();
			void v_add_value();

			void c_sub_value();
			void v_sub_value();

			void c_mul_value();
			void v_mul_value();

			void c_div_value();
			void v_div_value();

			void c_mod_value();
			void v_mod_value();

			void c_equ_value();
			void v_equ_value();

			void v_print_as_number(); // PVA (print var)

		private:
			ex::ResourceManager  m_resourceManager;
			const hlp::Token&	 m_currentToken;
			ex::ProgramStack	 m_programStack;
	};
}
#endif // !VARIABLES_H