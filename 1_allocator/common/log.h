#include "stdio.h"
#include <thread>
#include <unistd.h> //for getpid()

static const bool LOG_DEBUG_ENABLE   = false;
static const bool LOG_INFO_ENABLE    = true;
static const bool LOG_WARNING_ENABLE = true;
static const bool LOG_ERROR_ENABLE   = true;

// #define ZLOGI(format, ...) printf("[INFO]    %s  %.20s<%d>: " format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
// #define ZLOGW(format, ...) printf("[WARNING] %s  %.20s<%d>: " format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
// #define ZLOGE(format, ...) printf("[ERROR]   %s  %.20s<%d>: " format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define ZLOGI(format, ...) if (LOG_INFO_ENABLE) \
    { \
        char t_id[6]; \
        uint32_t t_id_ori = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));\
        snprintf(t_id, 6, "%u", t_id_ori); \
        printf("[INFO]    %5d %.5s  %s  %.20s<%d>: " format "\n", getpid(), \
        t_id, \
        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }; \

#define ZLOGW(format, ...) if (LOG_WARNING_ENABLE) \
    { \
        char t_id[6]; \
        uint32_t t_id_ori = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));\
        snprintf(t_id, 6, "%u", t_id_ori); \
        printf("[WARNING] %5d %.5s  %s  %.20s<%d>: " format "\n", getpid(), \
        t_id, \
        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }; \

#define ZLOGE(format, ...) if (LOG_ERROR_ENABLE) \
    { \
        char t_id[6]; \
        uint32_t t_id_ori = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));\
        snprintf(t_id, 6, "%u", t_id_ori); \
        printf("[ERROR]   %5d %.5s  %s  %.20s<%d>: " format "\n", getpid(), \
        t_id, \
        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }; \

#define ZLOGD(format, ...) if (LOG_DEBUG_ENABLE) \
    { \
        char t_id[6]; \
        uint32_t t_id_ori = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));\
        snprintf(t_id, 6, "%u", t_id_ori); \
        printf("[DEBUG]   %5d %.5s  %s  %.20s<%d>: " format "\n", getpid(), \
        t_id, \
        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }; \


