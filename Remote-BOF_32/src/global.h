#ifndef DEF_GLOBAL_H
#define DEF_GLOBAL_H

#include <types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>


#define SERVER  "irc.root-me.org"
#define NICK    "ytb"
#define USER    "Bot"
#define CHANNEL "#root-me_challenge"
#define PORT    "6667"

#define MAX_CMD_LEN  32
#define MAX_FROM_LEN 64
#define MAX_TO_LEN   64
#define MAX_DATA_LEN 512
#define MAX_NICK_LEN 32
#define MAX_PAQUET_LEN 512

#define DEBUG(fmt, ...) do { fprintf(stderr, "%s:%d\t", __FUNCTION__, __LINE__); if (__VA_ARGS__) fprintf(stderr, fmt, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#define PRINT_LINE() do { fprintf(stderr, "%s:%d\n", __FUNCTION__, __LINE__); } while (0);


struct Msg
{
	char cmd[MAX_CMD_LEN+1];
	char from[MAX_FROM_LEN+1];
	char to[MAX_TO_LEN+1];
	char data[MAX_DATA_LEN+1];
};

struct Handler
{
	char cmd[MAX_CMD_LEN+1];
	void (*handler)(int, struct Msg*);	
};

int *ptrN;
int *ptrH;

void write_msg(int fd, const char *format, ...);
int connect_to_server (char *server, char *port);
void recv_loop(int fd);
void add_handler(const char *name, void (*handle)(int,struct Msg*));
void handle_data(int fd, char *data, int len);
void init_handlers(void);
void dump_data(char *data, int len);

#endif

