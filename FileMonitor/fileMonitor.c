/***
    File Monitor

        - fileMonitor.c

    ToDo:
        - Browser/Mobile notifier

    Author: Fillipe Meireles
    Organization: Luspew

    https://github.com/fillipehmeireles/server-modules

***/

/* 

    void logger(LOGGER_MSG);

    log_type = [
        'w', 
        'e',
        'i'
    ]

    -> WARNING, ERROR, INFO

 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_BUFF_SIZE (sizeof(struct inotify_event))
#define BUFFER_SIZE (1024 * (EVENT_BUFF_SIZE + 16))

typedef struct
{
    char *type;
    char *msg;

} LOGGER_MSG;

void logger(LOGGER_MSG log);

int main(int argc, char *argv[])
{
    LOGGER_MSG log;

    if (argc < 2)
    {

        char *msg_type = "e";
        char *msg = "Please, provide the directory path.";

        log.msg = msg;
        log.type = msg_type;

        logger(log);
        return -1;
    }

    printf("[*]EVENT_BUFF_SIZE: %lu\n", EVENT_BUFF_SIZE);
    printf("[*]BUFFER_SIZE: %lu\n", BUFFER_SIZE);

    char buffer[BUFFER_SIZE];
    int fd, dir_watcher;
    fd = inotify_init();
    if (fd == -1)
    {
        perror("[!]Could not initialize inotify_event");
        return -1;
    }

    int buff_read = 0;
    dir_watcher = inotify_add_watch(fd, argv[1], IN_MODIFY | IN_CREATE | IN_DELETE);

    while (1)
    {
        struct inotify_event *event, *end;
        buff_read = read(fd, buffer, BUFFER_SIZE);

        if (buff_read < 0)
        {
            perror("read");
            break;
        }

        event = (struct inotify_event *)&buffer[0];

        end = (struct inotify_event *)&buffer[buff_read];

        while (event < end)
        {
            if (event->mask & IN_CREATE)
            {
                if (event->mask & IN_ISDIR)
                {

                    printf("Directory %s was created\n", event->name);
                }
                else
                {
                    printf("[+] File %s was created.\n", event->name);
                }
            }
            if (event->mask & IN_MODIFY)
            {
                printf("[+-] File %s was modified.\n", event->name);
            }
            if (event->mask & IN_DELETE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("Directory %s was deleted\n", event->name);
                }
                else
                {

                    printf("[-] File %s was deleted.\n", event->name);
                }
            }
            event = (struct inotify_event *)((char *)event) + sizeof(*event) + event->len;
        }
    }
}

void logger(LOGGER_MSG log)
{
    if (*log.type == 'w')
        printf("[!] %s\n", log.msg);
    if (*log.type == 'e')
        printf("[X] %s\n", log.msg);
    if (*log.type == 'i')
        printf("[*] %s\n", log.msg);
}