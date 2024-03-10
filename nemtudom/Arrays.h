#ifndef ARRAYS_H
#define ARRAYS_H

#include <cstdint>

#include "ResourceManager.h"
#include "Tokenizer.h"
#include "TRegister.h"

namespace ex
{
	class Arrays
	{
		public:
			Arrays(const hlp::Token& curr_token);
			~Arrays();

			void c_create_array();
			void v_create_array();

		private: // Variables
			ex::ResourceManager	 m_resourceManager;
			const hlp::Token&	 m_currentToken;
			ex::TRegister		 m_registerHandler;

		private: // Helpers
			void m_createHelper(const std::string& name, size_t mem_size);
	};
}
#endif