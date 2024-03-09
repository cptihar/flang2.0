#include "Loader.h"

hlp::Loader::Loader(const char* path_to_file)
	:m_fileStream(path_to_file, std::ios::in),
	 m_errorMessage(""),
	 m_fileNotFound(false),
	 m_missingSemicolon(false)
{}

hlp::Loader::~Loader()
{
	if (m_fileStream.is_open()) {
		m_fileStream.close();
	}
}


///====================================================
// 
//  Reads in the raw code, formats it for the tokenizer
// 
//  Checks whether the file was opened:
//     -> If not: sets FileNotFound flag, returns
// 
//  Handles resource cleanup
// 
//  Return: std::vector<std::string>
// 
///===================================================
std::vector<std::string> hlp::Loader::rawCode()
{
	auto raw_ret = std::vector<std::string>();

	// Check whether the file was opened
	if (!m_fileStream.is_open()) {
		m_errorMessage += LD_ERROR_NOT_FOUND;
		m_fileNotFound = true;
		return raw_ret;
	}

	// Go through the file
	std::string current_line;
	size_t iterator = 1;
	while (std::getline(m_fileStream, current_line)) {

		// Check whether a semicolon is missing
		auto semi_colon_position = current_line.find(';');
		if (semi_colon_position == std::string::npos && !current_line.empty()) {
			m_missingSemicolon = true;
			m_errorMessage += LD_ERROR_NO_SEMICOL + std::to_string(iterator) + '\n';
			return raw_ret;
		}

		// First non space character
		auto first_not_space = current_line.find_first_not_of('\t');
		if (first_not_space != std::string::npos) {
			std::string dummy = current_line.substr(first_not_space, semi_colon_position - first_not_space);

			if (first_not_space != semi_colon_position && dummy.size() >= 3)
				raw_ret.push_back(dummy);

		}
		iterator++;
	}

	// Close stream
	m_fileStream.close();

	return raw_ret;
}