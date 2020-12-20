CLI Interface                        {#mainpage}
============
    This is a simple CLI interface developed for resource constrained environments.
    The code is best suited for usage in embedded environments

**Code Structure**

1. Source files are present in @ref Src
2. Interface files are present in @ref inc
3. PLease refer doxygen generated HTML documentaion in the Doc/html subfolder for implementation details
4. The function entry point @ref Main.c

**Usage**

1. Initialization of the CLI is achieved through @ref CliInit in @ref cli_Interface.h
2. At initialization the function for outputting to the console needs to be passed to @ref CliInit.
3. @ref UserPrint is to be implemented based on the platform, as an example @ref printf is used.

**Input**
 
1. Function @ref cmdParserInput needs to be invoked by the serial input to the system by the user.
2. In the demo program here @ref cmdParserInput  is invoked by @ref CliMockStream.
3. The CLI process is handled by @ref CliProcess in @ref cli_Interface.h

**Modification**

1. Update command table @ref gCmdTble in @ref Cli_Interface.c with command name and function.
2. To change the buffer sizes update Macros in @ref cmd_parser.h , the delimiter is changed my modifying variable @ref DELIM in @ref cmd_parser.c


**Permissions**

1. PLease refer to the LICENSE file 