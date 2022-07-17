/**
 * @file Cli_Interface.c
 * @author Vishalk
 * @brief The user will use this file to add the commands required for the command parser by updating the command table
 * @date 2020-12-19
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Cli_Interface.h"
#include "cmd_parser.h"

static sCLI_t gCLIHandler;               /**< The global CLI struct that is used in the application*/
static sCLI_t* pgCLIHandler = &gCLIHandler ;    /**< Pointer to global cli struct */

static const char* HELPMSG =  "Comand <list> lists out all functions \r\n  \
The format for commands is <cmd><delim><args>...\r\n \
ex send add#5#6 to add 5 and 6, (assuming the delim is set to #) \r\n"; /**< Help msg string for demonstration */


/**
 * @brief Addition function for demonstration
 * 
 * @param argc Number of arguments
 * @param argv array of pointers to arguments
 * @return eCLIStatus_t return E_SUCCESS on success
 * @note User will have to retain the same function signature of arc,**argv
 */
eCLIStatus_t func_add(uint8_t argc,char** argv)
{
    int16_t res = 0;
    for(int i = 1 ; i< argc ; i++)
    {
        res += atoi(argv[i]);
    }
    printf("%d",res);
    return E_SUCCESS;
}

/**
 * @brief subtraction function for demonstration
 * 
 * @param argc Number of arguments
 * @param argv array of pointers to arguments
 * @return eCLIStatus_t return E_SUCCESS on success
 * @note User will have to retain the same function signature of arc,**argv
 */
eCLIStatus_t func_sub(uint8_t argc,char** argv)
{
    int16_t res = 0;

    res = atoi(argv[1]);

    for(int i = 2 ; i< argc ; i++)
    {
        res -= atoi(argv[i]);
    }
    printf("%d",res);
    return E_SUCCESS;
    
}

/**
 * @brief Multiplication function for demonstration
 * 
 * @param argc Number of arguments
 * @param argv array of pointers to arguments
 * @return eCLIStatus_t return E_SUCCESS on success
 * @note User will have to retain the same function signature of arc,**argv
 */
eCLIStatus_t func_mul(uint8_t argc,char** argv)
{
    int16_t res = 1;
    for(int i = 1 ; i< argc ; i++)
    {
        res *= atoi(argv[i]);
    }
    printf("%d",res);
    return E_SUCCESS;
    
}

/**
 * @brief List all commands
 * 
 * @param argc Number of arguments
 * @param argv array of pointers to arguments
 * @return eCLIStatus_t 
 */
eCLIStatus_t func_list(uint8_t argc,char** argv)
{
    printf("%s\n","List of commands are as follows");
    for(int i = 0 ; i< pgCLIHandler->numCmd ; i++)
    {
        printf("%s\n",pgCLIHandler->pCmdTbl[i].cmdName);
    }
    return E_SUCCESS;
    
}

/**
 * @brief Terminate program
 * 
 * @param argc 
 * @param argv 
 * @return eCLIStatus_t 
 */
eCLIStatus_t func_exit(uint8_t argc,char** argv)
{
    printf("%s\n","Program will terminate now");
    exit(0);
    return E_SUCCESS;
    
}

eCLIStatus_t func_help(uint8_t argc,char** argv)
{
    printf("%s\n",HELPMSG);
    return E_SUCCESS;
    
}

/**
 * @brief gCmdTble is an array of \ref sCmd_t structs that will contain commands and function pointers
 * 
 * @note: This table will be updated by the user with pairs of function names and function pointers
 */
static const sCmd_t gCmdTble[] = 
{
    {
        .cmdName = (char*)"list" ,
        .pFuncExec = func_list
    },

    {
        .cmdName = (char*)"help" ,
        .pFuncExec = func_help
    },

    {
        .cmdName = (char*)"add" ,
        .pFuncExec = func_add
    },

    {
        .cmdName = (char*)"sub" ,
        .pFuncExec = func_sub
    },

    {
        .cmdName = (char*)"mul" ,
        .pFuncExec = func_mul
    },

    {
        .cmdName = (char*)"quit" ,
        .pFuncExec = func_exit
    }

};

/**
 * @brief Needs to be implemented by the user to print to the target screen
 * 
 * @param str input string
 * @param len Length of the string
 */
void UserPrint(const char* str , uint8_t len)
{
    fwrite(str, sizeof(char), len, stdout);
}

/**
 * @brief Init function to be called by the end application
 * @todo Add error handling
 * 
 */
void CliInit()
{
    eCLIStatus_t status;

    pgCLIHandler->pCmdTbl = gCmdTble;

    pgCLIHandler->numCmd = sizeof(gCmdTble)/sizeof(sCmd_t);

    status = cmdParserInit(pgCLIHandler , UserPrint);

    if(status != E_SUCCESS)
    {

    }

}

/**
 * @brief Process function to be called repeatedly by the end application
 * @todo Add error handling
 */
void CliProcess()
{
    eCLIStatus_t status;

    status = cmdParserProcess(pgCLIHandler);

    if(status != E_SUCCESS)
    {
        /*TODO : Add error handling*/

    }

}
/**
 * @brief This is a dummy function to mimic input into the CLI
 * @todo Add error handling
 * @note \ref cmdParserInput is called here, IN a real application it will called by the input routine
 */
void CliMockStream()
{
    eCLIStatus_t status;
    char temp[50] ;
    uint8_t i = 0;

    scanf("%49s",temp);

    while('\0' != temp[i])
    {
        status = cmdParserInput(pgCLIHandler,temp[i++]);
    }
    cmdParserInput(pgCLIHandler,'\n') ; 

    if(status != E_SUCCESS)
    {
        /*TODO : Add error handling*/

    }

}