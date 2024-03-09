#ifndef PROGRAM_STACK_H
#define PROGRAM_STACK_H

#include <stack>
#include <string>
#include <vector>
#include <iostream>

namespace ex
{
	class ProgramStack
	{
		public:
			ProgramStack() = default;
			~ProgramStack();

			const std::vector<std::string>&  getTop() const
			{	return m_currentScope; }

			void insertToScope(const std::string& variable_name);
			void addScope();

			void popStack()
			{	m_variableStack.pop();	}

		private:
			static std::stack<std::vector<std::string>>  m_variableStack;
			static std::vector<std::string>			     m_currentScope;
	};
}
#endif