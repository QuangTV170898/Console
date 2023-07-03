#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "console.h"

#define CMD_BUFFER_SIZE 100
int i_get_command(unsigned char *cmd_buf);

static int helpme(int argc, char **argv)
{
    QG_consoleListCommand();
}

void register_help()
{
    QG_consoleContext_t help = {
        .command = "help",
        .help = "press help and enter",
        .callback = &helpme,
    };
    QG_consoleRegisterCommand(&help);
}

static int byebye(int argc, char **argv)
{
    printf("Bye\n");
}

void register_bye()
{
    QG_consoleContext_t bye = {
        .command = "bye",
        .help = "press bye and enter",
        .callback = &byebye,
    };
    QG_consoleRegisterCommand(&bye);
}

static int restart()
{
    printf("restart pc\n");
}

void register_restart()
{
    QG_consoleContext_t rst = {
        .command = "restart",
        .help = "press restart and enter",
        .callback = &restart,
    };
    QG_consoleRegisterCommand(&rst);
}

int main()
{
    static unsigned char cmd_buf[CMD_BUFFER_SIZE];
    QG_consoleInit();

    register_help();
    register_bye();
    register_restart();

    while(1){
        if (i_get_command(cmd_buf) == 0){
            QG_consoleStart(cmd_buf);
            memset(cmd_buf, 0, CMD_BUFFER_SIZE);
            printf("\033[1;34m[console@quangtv98]\033[0m$ ");
        }
        usleep(1000);
    }

    return 0;
}

int i_get_command(unsigned char *cmd_buf)
{
    unsigned char c = 0;
    unsigned char index = 0;

    do
    {
        c = getchar();
        if (c >= 0x20 && c < 0x7F)
        {
            cmd_buf[index] = c;
            index++;
        }
        if (index > CMD_BUFFER_SIZE)
        {
            index = 0;
            printf("ERROR: buffer overload !\n");
            return (-1);
        }

        /* sleep 100us */
        usleep(1000);

    } while (c != '\n');

    cmd_buf[index] = 0;
    return 0;
}