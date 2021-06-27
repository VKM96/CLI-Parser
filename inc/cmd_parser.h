/**
 * @file cmd_parser.h
 * @author vishalk
 * @brief Command parser interface file that contains all the structures used by the parser 
 * @date 2020-12-19
 * 
 */
#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <stdint.h>

#define CMD_MAX_BUF_SIZE 128
#define CMD_MAX_CMD_SIZE 32
#define CMD_MAX_PARAMS 32

/**
 * @brief CLI status enums
 * 
 */
typedef enum
{
    E_SUCCESS,
    E_CMD_NOT_FOUND,
    E_BUF_FULL,
    E_FAIL

}eCLIStatus_t;

/**
 * @brief Function pointer with the signature of user functions
 * @note All user functions must adhere to this signature , The functions should defined in \ref Cli_Interface.c
 * 
 */
typedef eCLIStatus_t (*pfCmd)(uint8_t argc,char** argv) ;

/**
 * @brief Function pointer with the signature of print function
 * @note The function pointer is initialized at initialisation \see cmdParserInit
 * 
 */
typedef void (*pfUserprint)(const char* usr_string, uint8_t len);

/**
 * @brief Structure that holds command name and function pointer to execute command
 * 
 */
typedef struct 
{
    char* cmdName;
    pfCmd pFuncExec;

}sCmd_t;

/**
 * @brief Main CLI structure used throughout the application
 * 
 */
typedef struct 
{
    pfUserprint pUserprintFunc;     /**< Function pointer to print function , to be obtained from end application and armed during init */
    const sCmd_t* pCmdTbl;                /**< Pointer to command table, Initialized at init */
    uint8_t numCmd;                 /**< Number of commands in command table pointed by pCmdTbl*/

    char Buf[CMD_MAX_BUF_SIZE];     /**< Buffer for incoming data, filled by cmdParserInput*/
    char CmdBuf[CMD_MAX_CMD_SIZE];  /**< Buffer for holding the current command, exctracted from Buf*/

    char* pBuf;                     /**< Pointer to Buf*/
    char* PCmdBuf;                  /**< Pointer to CmdBUf*/

}sCLI_t;

eCLIStatus_t cmdParserInit(sCLI_t*  pCLIHandle , pfUserprint pUserPrint);
eCLIStatus_t cmdParserProcess(sCLI_t* pCLIHandle);
eCLIStatus_t cmdParserInput(sCLI_t* pCLIHandle,const char inputChar);

#endif