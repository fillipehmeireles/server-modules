/***
    File Monitor

        - fileMonitor.c

    ToDo:
        - Persistent Event Watcher
        - Browser/Mobile notifier

    Author: Fillipe Meireles
    Organization: Luspew

    https://github.com/fillipehmeireles/server-modules
    
***/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_BUFF_SIZE (sizeof(struct inotify_event))
#define BUFFER_SIZE (1024 * (EVENT_BUFF_SIZE + 16))

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("[!]Please, provide the directory path.\n");
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
    buff_read = read(fd, buffer, BUFFER_SIZE);
    if (buff_read == -1)
    {
        perror("Could not read in buffer");
        return -1;
    }

    int i = 0;

    while (i < buff_read)
    {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];

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

        i += EVENT_BUFF_SIZE + event->len;
    }

    inotify_rm_watch(fd, dir_watcher);
    close(fd);
}