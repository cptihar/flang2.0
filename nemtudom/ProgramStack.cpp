#include "ProgramStack.h"

namespace ex {
	std::stack<std::vector<std::string>>  ProgramStack::m_variableStack;
	std::vector<std::string>			  ProgramStack::m_currentScope;
}

ex::ProgramStack::~ProgramStack()
{}

void ex::ProgramStack::insertToScope(const std::string& variable_name)
{
	m_currentScope.push_back(variable_name);
}

void ex::ProgramStack::addScope()
{
	m_variableStack.push(std::vector<std::string>());
	m_currentScope = {};
}