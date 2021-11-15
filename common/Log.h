//
// Created by developer on 2021/7/23.
//

#ifndef JSON_LOG_H_
#define JSON_LOG_H_

#define __FILENAME__ (strrchr(__FILE__, '/') + 1)


	#ifndef DEBUG

		#ifdef __APPLE__
		#define LOGD(format, ...) printf("[%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,\
									__LINE__, ##__VA_ARGS__)
		#endif 

		#ifdef WIN32

		#define LOGD(format, ...) fprintf(stderr, "[%s|%s@%s,%d] " format "\n", "DEBUG", __func__, __FILE__, __LINE__, ##__VA_ARGS__);
		
		#endif

		#ifdef __ANDROID__

		#else

		#endif


	#else 
		#define LOGD(format, ...)
	#endif


#endif