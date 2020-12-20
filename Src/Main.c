/**
 * @file Main.c
 * @author vishalk
 * @brief Simple program to demonstrate the CLI parser
 * @version 1.0
 * @date 2020-12-19
 * @bug No known bugs at this time
 * 
 * 
 */

#include <stdio.h>
#include <stddef.h>
#include "Cli_Interface.h"

/**
 * @brief Function entry point
 * 
 * The function intializes the CLI and calls the CLI process in a superloop
 * 
 * @return int 
 */
int main()
{
    /// > Initialize CLI through @ref cmdParserInit
    CliInit();

    while(1)
    {
        /// > Mock input for CLI, calls @ref cmdParserInput
        CliMockStream();

        /// > CLI process through @ref CliProcess
        CliProcess();
    }
    return 0;

}