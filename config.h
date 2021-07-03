#ifndef NDEBUG
    #define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)
    #define log_info_detected(M, ...) fprintf(stderr, "[DETECTED_THREATS] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define log_info(M, ...)
    #define log_info_detected(M, ...)
#endif