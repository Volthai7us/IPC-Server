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

long receive_id;
long send_id;
char clientName [100];
int msgid;
int registered = -1;

pthread_t thread_id;

void registerToServer();
void* listenMessage(void * args);
long hashing(unsigned char *str, int type);

int main(int argc, char *argv[])
{
    key_t key;
    key = ftok("server.c" , 302);
    msgid = msgget(key, IPC_CREAT);
    strcpy(clientName, argv[1]);

    registerToServer();
    while(1)
    {
        if(registered == 0)
        {
            struct mesg_buffer *send_buffer = malloc(sizeof *send_buffer);
            printf("----------------\n");
            printf("Write a message: ");
            fgets(send_buffer->mesg_text, 100, stdin);
            printf("Write a client id: ");
            fgets(send_buffer->device, 100, stdin);
            
            send_buffer->mesg_type = send_id;
            msgsnd(msgid, send_buffer, sizeof(*send_buffer), 0);
        }
    }
}

void registerToServer()
{
    struct mesg_buffer *register_buffer = malloc(sizeof *register_buffer);

    strcpy(register_buffer->mesg_text, clientName);

    register_buffer->mesg_type = 1;
    strcpy(register_buffer->device, "Register");
    int result = msgsnd(msgid, register_buffer, sizeof(*register_buffer), 0);

    receive_id = hashing(register_buffer->mesg_text, 0);
    send_id = hashing(register_buffer->mesg_text, 1);

    free(register_buffer);

    pthread_create(&thread_id, NULL, listenMessage, NULL);
}

void* listenMessage(void * args)
{
    struct mesg_buffer *receive_buffer = malloc(sizeof *receive_buffer);
    printf("Waiting server to accept registration...\n");
    while(1)
    {
        msgrcv(msgid, receive_buffer, sizeof(*receive_buffer), receive_id, 0);

        if(registered == 0)
        {
            printf("\n----------------\n");
            printf("%s ----> %s", receive_buffer->device, receive_buffer->mesg_text);
            printf("----------------\n");
            printf("Write a message: ");
            fflush(stdout);
        }
        else
        {
            if(strcmp(receive_buffer->mesg_text, "Success") == 0)
            {
                printf("You succesfully connected to server.\n");
                registered = 0;
            }
            else
            {
                struct mesg_buffer *register_buffer = malloc(sizeof *register_buffer);

                strcpy(register_buffer->mesg_text, clientName);

                register_buffer->mesg_type = 1;
                strcpy(register_buffer->device, "Register");
                int result = msgsnd(msgid, register_buffer, sizeof(*register_buffer), 0);
            }
        }
    }
    free(receive_buffer);

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