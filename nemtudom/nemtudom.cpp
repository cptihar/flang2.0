#include <iostream>
#include "Loader.h"
#include "Tokenizer.h"
#include "Interpreter.h"
#include "ErrorHandler.h"


#define LOG(message) std::cout << "[ERROR] " << message << std::endl;

int main(int argc, char** argv)
{
   // const std::string code = "code.txt"; // later use commandline args

    if (argc < 2) {
        LOG("Please provide a file");
        return EXIT_FAILURE;
    }

    hlp::Loader ld(argv[1]); // File loader, transformer
    

    auto raw_code = ld.rawCode(); // Extract raw code

    if (ld.hasError()) {
        LOG(ld.getErrorMessage());
        return EXIT_FAILURE;
    }


    hlp::Tokenizer tokenizer(raw_code); // Tokenize raw code
    auto tokenized = tokenizer.tokenized_code(); // Tokenized code

    raw_code.clear();

    // Interpret tokenized code
    ex::Interpreter interpreter(tokenized);

    hlp::ErrorHandler error_handler(tokenized, interpreter.getInstructionMap());
    error_handler.checkCode();

    if (error_handler.hasError()) {
        LOG(error_handler.getErrorMessage());
        return EXIT_FAILURE;
    }


    interpreter.interpretProgram();

    if (interpreter.hasWanderingCode()) {
        LOG(ERR_MSG_WANDER_CODE);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}