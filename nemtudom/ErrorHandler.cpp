#include "ErrorHandler.h"

hlp::ErrorHandler::ErrorHandler(const std::vector<Token>& tksrc, std::unordered_map<std::string, std::function<void()>>& a)
	:m_tokenizedSourceCode(tksrc),
	 m_exFunctions(a)
{
	for (uint8_t i = 0; i < ERR_FLAGS_SIZE; ++i)
		m_errorFlags[i] = false;

	m_errorFlags[ERR_MISSING_START_LBL_IDX] = true;
}


void hlp::ErrorHandler::checkCode()
{
	// Iterate through tokens
	for (auto& t : m_tokenizedSourceCode) {

		// Check for unknown instructions
		std::string extracted = std::string(t.instruction, 3) + char(t.addressing_mode + '0');
		if (!m_exFunctions.count(extracted) && t.addressing_mode != ADDR_LABEL) {
			m_errorFlags[ERR_UNKNOWN_INSTRUCTION] = true;
			m_errorMessage += ERR_MSG_UNKNOWN_INST;
			return;
		}

		// it is a label
		if (m_errorFlags[ERR_MISSING_START_LBL_IDX] == true) {

			// Check whether it is main
			if (t.addressing_mode == ADDR_LABEL && t.value_buffer == ENTR_POINT_NAME)
				m_errorFlags[ERR_MISSING_START_LBL_IDX] = false;

		}
	}
}


///===================================================
//
//  Checks whether error array contains any true flags
// 
//  If yes:
//	   -> Returns true
//     -> Doesn't update error message
//
//  Return: const bool
//
///===================================================
const bool hlp::ErrorHandler::hasError() const
{
	for (uint8_t i = 0; i < ERR_FLAGS_SIZE; ++i) {
		if (m_errorFlags[i] == true) return true;
	}
	return false;
}