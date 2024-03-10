#ifndef ARRAY_REGISTER_H
#define	ARRAY_REGISTER_H

#include "ResourceManager.h"
#include "Tokenizer.h"
#include "TRegister.h"

namespace ex
{
	class ArrayRegister
	{
		public:
			ArrayRegister(const hlp::Token& token);
			~ArrayRegister();

			void move_register_to_array();
			void update_array_register_index();


			void set_register_value();
			void fetch_value_from_index();
			void push_value_from_register();
			void print_value_at_index();
			void export_to_variable();

		private:
			ex::ResourceManager  m_resourceManager;
			const hlp::Token&    m_currentToken;
			ex::TRegister		 m_registerHandler;
	};
}
#endif // !ARRAY_REGISTER_H