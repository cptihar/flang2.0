#ifndef _LOADER_H
#define _LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define LD_ERROR_NOT_FOUND   "File not found\n"
#define LD_ERROR_NO_SEMICOL  "Missing semicolon on line "

namespace hlp 
{
	class Loader
	{
		public:
			Loader(const char* path_to_file);
			~Loader();

			std::vector<std::string> rawCode();

			std::string	 getErrorMessage() const 
			{ return m_errorMessage; }

			const bool	 hasError() const 
			{ return m_fileNotFound || m_missingSemicolon; }

		private: // Variables
			std::ifstream  m_fileStream;
			std::string	   m_errorMessage;
			bool		   m_fileNotFound;
			bool		   m_missingSemicolon;
	};
}
#endif