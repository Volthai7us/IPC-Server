#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    char device[100];
};

struct clientData
{
    long msgid;
    char device[100];
};

pthread_t thread_ids [100]; 

void* listenMessage(void * args);
long hashing(unsigned char *str, int type);

void* listenMessage(void * args)
{
    struct clientData *actual_args = args;
    long receive_id = hashing(actual_args->device, 0);
    long send_id = hashing(actual_args->device, 1);

    printf("%s is connected\n", actual_args->device);
    fflush(stdout);

    while(1)
    {
        struct mesg_buffer *receive_buffer = malloc(sizeof *receive_buffer);

        msgrcv(actual_args->msgid, receive_buffer, sizeof(*receive_buffer), send_id, 0);
        
        struct mesg_buffer *send_buffer = malloc(sizeof *send_buffer);
        receive_buffer->device[strcspn(receive_buffer->device, "\r\n")] = 0;

        send_buffer->mesg_type = hashing(receive_buffer->device, 0);
        strcpy(send_buffer->mesg_text, receive_buffer->mesg_text);
        strcpy(send_buffer->device, actual_args->device);

        msgsnd(actual_args->msgid, send_buffer, sizeof(*send_buffer), 0);

    }
    free(actual_args);
}

int main() {
    key_t key = ftok("server.c", 302);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Server is running. Waiting for users to connect...\n");
    struct mesg_buffer *listener_buffer = malloc(sizeof *listener_buffer);

    listener_buffer->mesg_type = 1;
    int totalClient = -1;
    while(1)
    {
        msgrcv(msgid, listener_buffer, sizeof(*listener_buffer), 1, 0);
        struct clientData *data = malloc(sizeof *data);

        strcpy(data->device, listener_buffer->mesg_text);
        data->msgid = msgid;

        if(strcmp(listener_buffer->device, "Register") == 0)
        {
            totalClient++;
            struct mesg_buffer *send_buffer = malloc(sizeof *listener_buffer);
            send_buffer->mesg_type = hashing(listener_buffer->mesg_text, 0);
            strcpy(send_buffer->mesg_text, "Success");
            msgsnd(msgid, send_buffer, sizeof(*send_buffer), 0);
            pthread_create(&thread_ids[totalClient], NULL, listenMessage, data);
        }
    }
}

long hashing(unsigned char *str, int type)
{
    char * copy = (unsigned char *) malloc(100);
    strcpy(copy, str);
    long hash = 5381;
    int c;
    if(type == 0)
    {
        strcat(copy, "receive");
    }
    if(type == 1)
    {
        strcat(copy, "send");
    }

    while (c = *copy++)
        hash = ((hash << 5) + hash) + c;

    return hash < 0 ? hash * -1 : hash;
}