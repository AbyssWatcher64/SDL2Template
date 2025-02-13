#ifndef __LOG_H__
#define __LOG_H__

//#define LOG(format, ...) Log(__FILE__, __LINE__, format, ##__VA_ARGS__)

// Consider making Preprocessor directive for this so that it doesn't try to LOG without debug mode
// Otherwise make an if else. Meaning:
//#ifdef DEBUG_MODE
//#define LOG(format, ...) Log(__FILE__, __LINE__, format, ##__VA_ARGS__)
//#else
//#define LOG(format, ...)  // Expands to nothing when debug mode is off
//#endif
// OR
#define LOG(format, ...) \
    if (Engine::Singleton().GetIsDebugModeActive()) Log(__FILE__, __LINE__, format, ##__VA_ARGS__)

void Log(const char file[], int line, const char* format, ...);

#endif  // __LOG_H__