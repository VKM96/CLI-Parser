/**
 * @file cmd_parser.c
 * @author vishalK
 * @brief Core logic of Command parsing and initializing occurs in this file
 * @date 2020-12-19
 * 
 */

#include <stddef.h>
#include <string.h>
#include "cmd_parser.h"


static const char* const DELIM = "#" ;                             /**< Delimiter used in application, change according to need */
static const char CLI_CR = '\n';                                   /**< Terminate char set to '\n' , change according to need */

static const char* CLI_INIT_PROMPT = "-- CLI Init complete, type help for list of commands --\n" ;  /**< CLI init prompt text*/
static const char* CLI_CMD_NOT_Found = "-- CMD not found --\n" ;                                    /**< CLI Not found text*/
static const char* CLI_PROMPT = "\n-- Enter next cmd --\n<< " ;                                     /**< CLI prompt text*/         
static const char* CLI_TERMINAL = ">> " ;                                                           /**< CLI terminal text*/                     
                       

/**
 * @brief Helper function to reset main buffer pointer
 * 
 * @param pCLIHandle Handle to CLI structure whose buf will be reset to head
 */
static void CmdBufReset(sCLI_t* pCLIHandle )
{
    pCLIHandle->pBuf = pCLIHandle->Buf ;
}

/**
 * @brief Helper function to reset cmd buffer pointer
 * 
 * @param pCLIHandle Handle to CLI structure whose cmdbuf will be reset to head
 */
static void CmdCmdBufReset(sCLI_t*  pCLIHandle )
{
    pCLIHandle->PCmdBuf = pCLIHandle->CmdBuf;
}

/**
 * @brief helper function to flush command buffer
 * 
 * @param pCLIHandle 
 */
static void CmdFlushCmdBuf(sCLI_t*  pCLIHandle )
{
    memset(pCLIHandle->CmdBuf,'\0',CMD_MAX_CMD_SIZE);
}

/**
 * @brief helper function to flush main buffer
 * 
 * @param pCLIHandle 
 */
static void CmdFlushBuf(sCLI_t*  pCLIHandle )
{
    memset(pCLIHandle->Buf,'\0',CMD_MAX_BUF_SIZE);
}

/**
 * @brief wrapper function around the print method of CLI
 * 
 * @param pCLIHandle Handle to CLI structure
 * @param str 
 * @param len 
 */
static void CmdOut(sCLI_t*  pCLIHandle , const char* str , uint8_t len )
{
    pCLIHandle->pUserprintFunc(str,len);
}

/**
 * @brief Init function for the command parser
 * 
 * @param pCLIHandle handle to the CLI structure that needs to be insitalised
 * @param pUserPrint Print function to be used by CLI
 * @return eCLIStatus_t status of init : E_SUCCESS on success \see eCLIStatus_t
 */
eCLIStatus_t cmdParserInit(sCLI_t*  pCLIHandle , pfUserprint pUserPrint)
{
    CmdBufReset(pCLIHandle);

    CmdCmdBufReset(pCLIHandle);
   
    pCLIHandle->pUserprintFunc = pUserPrint ;

    CmdOut(pCLIHandle,CLI_INIT_PROMPT,strlen(CLI_INIT_PROMPT));

    return E_SUCCESS;

}

/**
 * @brief Function to parse commands inside buffer
 * 
 * @param pCLIHandle Handle to CLI structure whose buffer will be parsed by this function
 * @return eCLIStatus_t status : return E_SUCCESS on success
 */
eCLIStatus_t cmdParserProcess(sCLI_t* pCLIHandle)
{
    eCLIStatus_t status;

    uint8_t argc = 0;
    char *argv[CMD_MAX_PARAMS] ;

    argv[argc] = strtok(pCLIHandle->CmdBuf, DELIM);

    while((NULL != argv[argc] ) && (argc < CMD_MAX_PARAMS))
    {
        argv[++argc] = strtok(NULL,DELIM);
    }


    for(uint8_t i = 0 ; i < pCLIHandle->numCmd ; i++)
    {
        if( strcmp(argv[0], pCLIHandle->pCmdTbl[i].cmdName) == 0) 
        {
            CmdOut(pCLIHandle,CLI_TERMINAL,strlen(CLI_TERMINAL));

            status = pCLIHandle->pCmdTbl[i].pFuncExec(argc,argv);
            break;
        }
        else
        {
            status = E_CMD_NOT_FOUND; 
        }
        
    }
    if(status == E_CMD_NOT_FOUND)
    {
        CmdOut(pCLIHandle,CLI_CMD_NOT_Found,strlen(CLI_CMD_NOT_Found));
    }

    CmdOut(pCLIHandle,CLI_PROMPT,strlen(CLI_PROMPT));

    CmdFlushCmdBuf(pCLIHandle);
    return status;
}

/**
 * @brief Function that fills up the buffer of the CLI
 * 
 * @param pCLIHandle Handle to CLI structure whose nufer needs to be filled
 * @param inputChar character to be filled inside buffer of pCLIHandle
 * @return eCLIStatus_t status : return E_SUCCESS on success
 * @note This function is to be called from the function that recives input from the user
 * scanf is used for demonstration purposes, it will be called by an interrupt in e,bedded applications
 * 
 */
eCLIStatus_t cmdParserInput(sCLI_t* pCLIHandle,const char inputChar)
{
    eCLIStatus_t status = E_FAIL;

    if(CLI_CR == inputChar)
    {

        *(pCLIHandle->PCmdBuf) = '\0' ;

        strcpy(pCLIHandle->CmdBuf, pCLIHandle->Buf); 

        CmdFlushBuf(pCLIHandle);
        CmdBufReset(pCLIHandle);

    }

    else
    {
        if( (pCLIHandle->pBuf - pCLIHandle->Buf) < CMD_MAX_BUF_SIZE )
        {
            *(pCLIHandle->pBuf++) = inputChar ;
            status = E_SUCCESS ;
        }
        else
        {
            status = E_BUF_FULL ;
        }
        
    }    

    return status;
}
