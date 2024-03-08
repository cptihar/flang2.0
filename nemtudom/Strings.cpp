#include "Strings.h"

ex::Strings::Strings(const hlp::Token& curr_token)
	:m_currentToken(curr_token)
{}

ex::Strings::~Strings()
{}


///======================================
//
//  Creates string
// 
//  Updates the necessary data structures
// 
//  Checks for:
//      -> Invalid size
//      -> Used name
// 
//  Return: void
// 
///======================================
void ex::Strings::create_string()
{
    std::vector<std::string> data = m_stringCreationHelper();

    // Convert string into int representation
    auto represented = m_createIntRepresentation(data[1]);

    // Setup memory info
    ex::ArrStruct mem_info = ex::ArrStruct(m_resourceManager.getMemorySize(), represented.size());

    // Store
    m_stringMap[data[0]] = mem_info;
    m_resourceManager.dumpFixedMemory(represented);
}


///====================================
//
//  Prints string and a new line
//
//  Validates whether the string exists
// 
//  Return: void
//
///====================================
void ex::Strings::print_string()
{
    m_printString();
}


///====================================
//
//  Prints string and a new line
//
//  Validates whether the string exists
// 
//  Return: void
//
///====================================
void ex::Strings::print_string_with_newline()
{
    m_printString();
    std::cout << std::endl; // Also calls std::flush
}


///====================================================
//
//  Helper for string creation
//  Fetches necessary data
//  
//  Checks for possible edge cases (e.g:missing quotes)
// 
//  Throws: std::logic_error
//  Return: std::vector<std::string>
//              -> First element: string's name
//              -> Second element: string's value
//
///====================================================
std::vector<std::string> ex::Strings::m_stringCreationHelper()
{
    std::vector<std::string> ret;
    ret.reserve(2);

    // Extract string data
    auto quote_start_pos = m_currentToken.value_buffer.find_first_of('"');
    auto quote_end_pos = m_currentToken.value_buffer.find_last_of('"');

    // Check whether one of the  quotes dont exist
    if (quote_start_pos == std::string::npos || quote_end_pos == std::string::npos)
        throw std::logic_error("Missing qoutes");

    std::string push_str = m_currentToken.value_buffer.substr(quote_start_pos + 1, quote_end_pos - quote_start_pos - 1);

    // Get variable name (it will be the first element)
    auto buffer = m_resourceManager.bufferSplitVariable(m_currentToken.value_buffer);

    // Check whether the string already exists or for invalid initialization value

    if (m_stringMap.count(buffer[0]) || push_str.size() == 0)
        throw std::logic_error("Error point");

    ret.emplace_back(buffer[0]);
    ret.emplace_back(push_str);

    return ret;
}


///=========================================================
//
//  Converts characters into int
// 
//  Uses bit manipulation to build up an int32 array from it
// 
//  Return: std::vector<int32_t> (converted string)
//
///=========================================================
std::vector<int32_t> ex::Strings::m_createIntRepresentation(const std::string & str)
{
    // Create return value
    std::vector<int32_t> ret;
    
    int32_t pdata = 0; // Data that is pushed into ret
    int32_t counter = 0; // Counter (for indexing)
    int8_t shift_size = 0; // Amount of bits to shift it by

    while (counter < str.size()) {

        char current = str[counter]; // Get current character

        // Check for reset
        if (shift_size >= sizeof(int32_t)) {
            shift_size = 0;
            ret.push_back(pdata);
            pdata = 0;
        }

        // bit stuff
        int32_t maskable = current;

        pdata |= ( maskable << (shift_size * CHAR_SIZE_IN_BITS) ); // Manipulate pdata

        // increase counters
        ++shift_size;
        ++counter;
    }

    if (pdata != 0) 
        ret.push_back(pdata);

    return ret;
}


///==================================================
//
//  Prints individual int representations of a string
// 
//  Return: void
//
///==================================================
inline void ex::Strings::m_printCharacter(int32_t int_representation)
{
    for (int8_t shift_value = 0; shift_value < 4; ++shift_value) {
        char value = (int_representation >> (shift_value * CHAR_SIZE_IN_BITS));

        if (value == 0)
            break;

        std::cout << value;
    }
}


///==============================================
//
//  Fetches important data related to the string
// 
//  Validates the string (whether it exists etc.)
// 
//  Throws: std::logic_error
//  Return: ex::ArrStruct
//
///==============================================
ex::ArrStruct ex::Strings::m_fetchStringData(const std::string& str)
{
    // Check whether the string exists
    if (!m_stringMap.count(str))
        throw std::logic_error("String with this name doesn't exist");

    return m_stringMap[str];
}


///===========================================
//
//  Prints out the int representation by bytes
//
//  Doesn't add new line to the end
//  Doesn't do error checking
//  (Has to be made before calling)
// 
//  Return: void
//
///===========================================
inline void ex::Strings::m_printString()
{
    auto data = m_resourceManager.getSpacelessBuffer(m_currentToken.value_buffer);

    ex::ArrStruct printable_str = m_fetchStringData(data.substr(1, data.size()));
    size_t interation_end = printable_str._memStart + printable_str._size;

    for (size_t j = printable_str._memStart; j < interation_end; ++j)
        m_printCharacter(m_resourceManager.c_fetch_from_memory(j));
}