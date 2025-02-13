#include "Log.hpp"
#include <iostream>
#include <cstdarg>
#include <sstream>

void Log(const char file[], int line, const char* format, ...)
{
    char tmpString[4096];
    va_list variableArguments;

    // Construct the formatted string
    va_start(variableArguments, format);
    vsnprintf(tmpString, sizeof(tmpString), format, variableArguments);
    va_end(variableArguments);

    // Efficiently build the final log message
    std::ostringstream logMessage;
    logMessage << "\n" << file << "(" << line << ") : " << tmpString;

    // Output to standard error for unbuffered messages - they will appear immediately even if the program crashes.
    // This makes it less efficient but has immediate output.
    std::cerr << logMessage.str() << std::endl;
}
