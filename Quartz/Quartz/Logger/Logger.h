#ifndef QUARTZ_LOGGER_H
#define QUARTZ_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef QUARTZ_DEBUG
#define LOG_INFO(...)  spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#else

#define LOG_INFO(...) 
#define LOG_WARN(...) 
#define LOG_ERROR(...) 
#define LOG_CRITICAL(...) 

#endif // DEBUG_BUILD


#ifdef QUARTZ_DEBUG

#define LOG_ASSERT(CONDITION, ...)   if(!CONDITION){ LOG_ERROR("Assert failure at line {0} in file {1}: {2} ",__LINE__, __FILE__, __VA_ARGS__) __debugbreak();}
#define LOG_FAILURE(...) LOG_CRITICAL("Exception occured at line {0} in file {1}: {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak()
#else

#define LOG_ASSERT(CONDITION, ...)  
#define LOG_FAILURE(...) 
#endif // DEBUG_BUILD

#endif