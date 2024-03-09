#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "Tokenizer.h"


#define ERR_MISSING_START_LBL_IDX    0
#define ERR_UNKNOWN_INSTRUCTION      1
#define ERR_FLAGS_SIZE				 2 // Error vector size

#define ERR_MSG_UNKNOWN_INST   "Unknown instruction.";
#define ERR_MSG_MAIN_MISS      "Missing entry point. Add '_MAIN' label.\n"

namespace hlp
{
	class ErrorHandler
	{
		public:
			ErrorHandler(const std::vector<Token>& tksrc,
						 std::unordered_map<std::string, std::function<void()>>& a);

			void			   checkCode();
			const bool         hasError() const;
			const std::string  getErrorMessage() const
			{ return m_errorMessage; }

		private:
			const std::unordered_map<std::string, std::function<void()>>& m_exFunctions; // Xd

		private:
			const std::vector<hlp::Token>&  m_tokenizedSourceCode;
			std::string			            m_errorMessage;
			bool						    m_errorFlags[ERR_FLAGS_SIZE];
	};
}
#endif // !ERROR_HANDLER_H