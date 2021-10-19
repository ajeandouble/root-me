#include "global.h"

void sigsegv_handle(int n)
{
	PRINT_LINE();
	// DEBUG("%x(%d)<-\n", n_handlers, n_handlers);
	// DEBUG("Hander_List addr:%x\tn_handler:%x.val=%d", ptrH, ptrN, *ptrN);
	printf("\n####### CRASHED ##########\n");
	creat("reboot.txt", 0666);
	exit(0);
}

int main(int argc, char **argv)
{
	int fd;
	struct sigaction sig;
	
	memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = sigsegv_handle;
	sigaction(SIGSEGV, &sig, NULL);
	
	
	init_handlers();
	fd = connect_to_server(SERVER, PORT);
	write_msg(fd, "NICK %s\r\n", NICK);
	write_msg(fd, "USER %s %s %s :%s\r\n", USER, USER, USER, USER);
	
	recv_loop(fd);
	close(fd);
	return 0;
}

