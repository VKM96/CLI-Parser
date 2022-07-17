/**
 * @file Version.h
 * @author https://github.com/VKM96
 * @brief Version details and change logs maintained here
 * @date 2020-12-20
 * 
 * 
 */
#ifndef VERSION_H
#define VERSION_H

#include <stdint.h>
#include <stddef.h>

#define VERSION_MAJOR 00 ///> Major version 
#define VERSION_MINOR 01 ///> Minor version 

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__ 

void Version_GetVersion(char* const pVersion, size_t bufSize);

#endif