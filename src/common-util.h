#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

#ifdef LOG_DEBUG_MESSAGES
    #include <SDL_log.h>
    #include <thread>
    #include <string>
    #include <iostream>
    #include <sstream>
#endif // LOG_DEBUG_MESSAGES

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef LOG_DEBUG_MESSAGES
#define LOG(message) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s:%i: %s", __FILENAME__, __LINE__, message)
#define LOG_THREAD(message) {\
    std::thread::id this_id = std::this_thread::get_id();\
    std::stringstream os;\
    os << this_id;\
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s:%i: %s=>%s", __FILENAME__, __LINE__, os.str().c_str(), message);\
    } while(0)
#else
#define LOG(message)
#endif // LOG_DEBUG_MESSAGES

#endif // __COMMON_UTIL_H__