/**
 * @file version.c
 * @author https://github.com/VKM96
 * @brief Version control source file 
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Version.h"
#include <stdint.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief utility function to get version information 
 * 
 * @param pVersion 
 * @param bufSize 
 */
void Version_GetVersion(char* const pVersion, size_t bufSize)
{
    snprintf(pVersion, bufSize, "%d.%d | %s | %s", VERSION_MAJOR, VERSION_MINOR, (COMPILE_DATE), (COMPILE_TIME));
}