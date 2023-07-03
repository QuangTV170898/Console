/**
 * @file console.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdbool.h>

typedef int (*QG_consoleCallbackFunc_t)(int argc, char **argv);

typedef struct console_t
{
    const char *command;
    const char *help;
    QG_consoleCallbackFunc_t callback;
} QG_consoleContext_t;

typedef struct cmd_item_
{
    QG_consoleContext_t ctx;
    struct cmd_item_ *next;
} QG_consoleItemCmd_t;

int QG_consoleInit();
void QG_consoleListCommand();
bool QG_consoleRegisterCommand(QG_consoleContext_t *cmd);
QG_consoleItemCmd_t* QG_consoleFindCmdByName(const char *name);
bool QG_consoleStart(char *cmdline);

#endif // __CONSOLE_H__