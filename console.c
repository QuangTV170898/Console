/**
 * @file console.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/queue.h>

#include "console.h"


typedef struct cmd_list_
{
    QG_consoleItemCmd_t *head;
    QG_consoleItemCmd_t *tail;
} QG_consoleListCmd_t;

QG_consoleListCmd_t listCmd;

static const QG_consoleListCmd_t *__findCmdByName(const char *name)
{
    const QG_consoleListCmd_t *cmd = NULL;
    return cmd;
}
int QG_consoleInit()
{
    listCmd.head == NULL;
    listCmd.tail == NULL;
    printf("\033[1;34m[console@quangtv98]\033[0m$ ");
    return 0;
}

static QG_consoleItemCmd_t *__createCommand(QG_consoleContext_t *cmd)
{
    QG_consoleItemCmd_t *item = (QG_consoleItemCmd_t *)malloc(sizeof(QG_consoleItemCmd_t));
    if (item == NULL)
        return NULL;
    item->ctx.command = cmd->command;
    item->ctx.help = cmd->help;
    item->ctx.callback = cmd->callback;

    item->next = NULL;
    return item;
}

static void __insertHead(QG_consoleListCmd_t *list, QG_consoleListCmd_t *cmd);
static void __insertAfter(QG_consoleListCmd_t *list, QG_consoleListCmd_t *cmd);

/**
 * @brief 
 * 
 * @param name 
 * @return QG_consoleItemCmd_t* 
 */
static QG_consoleItemCmd_t* __consoleFindCmdByName(const char *name){
    QG_consoleItemCmd_t *item;
    size_t len =  strlen(name);
    for (item = listCmd.head; item != NULL; item = item->next){
        if (strlen(item->ctx.command) == len && strcmp(name, item->ctx.command) == 0){
            return item;
        }
    }
    return NULL;
}

/**
 * @brief 
 * 
 */
void QG_consoleListCommand(){
    QG_consoleItemCmd_t *item;
    for (item = listCmd.head; item != NULL; item = item->next){
        printf("%s\n", item->ctx.command);
    }
}

/**
 * @brief 
 * 
 * @param cmd 
 * @return true 
 * @return false 
 */
bool QG_consoleRegisterCommand(QG_consoleContext_t *cmd)
{
    QG_consoleItemCmd_t *item;
    item = __createCommand(cmd);
    if (item == NULL)
        return false;

    if (listCmd.head == NULL){
        listCmd.head = listCmd.tail = item;
    }
    else{
        listCmd.tail->next = item;
        listCmd.tail = item;
    }
    return true;
}

/**
 * @brief 
 * 
 * @param input 
 * @param argv 
 * @return true 
 * @return false 
 */
int QG_consleSplitArgv(char *input, char **argv){
    int argc = 0;
    const char *SPACE = " ";
    char *token = NULL;
    if (input == NULL)
        return -1;

    token = strtok(input, SPACE); 
    
    do{
        argv[argc] = (char*)calloc(strlen(token), sizeof(char*));
        strcpy(argv[argc], token);
        argc ++;    
    }  while ((token = strtok(NULL, SPACE)));

    return argc;
}

/**
 * @brief 
 * 
 * @param cmdline 
 * @return true 
 * @return false 
 */
bool QG_consoleStart(char *cmdline){
    if (*cmdline == '\0'){
        return false;
    }
    char **argv =  (char**)calloc(10, sizeof(char*));
    if (argv == NULL)
        return false;

    char cmd[128];
    memset(cmd, 0, sizeof(cmd));
    strcpy(&cmd[0], cmdline);
    int argc = QG_consleSplitArgv(cmd, argv);
    if (argc == 0){
        free(argv);
        return false;
    }

    QG_consoleItemCmd_t *item = __consoleFindCmdByName(argv[0]);   
    if (item == NULL){
        free(argv);
        return false;
    }

    item->ctx.callback(argc, argv);

    free(argv);
    return true;
}

