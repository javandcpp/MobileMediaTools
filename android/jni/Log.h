//
// Created by developer on 2021/7/23.
//

#ifndef JSON_LOG_H_
#define JSON_LOG_H_

#define __FILENAME__ (strrchr(__FILE__, '/') + 1)


#ifdef DEBUG
#define LOGD(format, ...) printf("[%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,\
                            __LINE__, ##__VA_ARGS__)
#else
#define LOGD(format, ...)
#endif

#endif //JSON_LOG_H_
