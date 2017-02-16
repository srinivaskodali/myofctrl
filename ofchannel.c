#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <error.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define OF_DEFAULT_PORT 6653

void *newSwitch (void *arg) {
	printf("child thread %d with pid %d created.\n", (int)pthread_self(), getpid());
	int sock = (int) arg;
	char buffer[4096] = {0};
   /* If connection is established then start communicating */
   bzero(buffer,4096);
   if (read( sock,buffer, 4096 ) < 0) {
      perror("ERROR reading from socket");
      return NULL;
   }
   
   printf("\n Here is the message: %s\n", buffer);

	sleep(5);
	close(sock);
	printf("child thread %d with pid %d finished.\n", (int)pthread_self(), getpid());
	
}

int main(int argc, char *argv[]) {
	int ofPort = OF_DEFAULT_PORT;
	int ofSock, clientSock, clientLen, clntSock;
	struct sockaddr_in ofServAddr,clientAddr;
	pthread_t switchThread;

	if((ofSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ) {
		perror("Error : could not create socket");
		return 1;
	}

	/* construct local address structure */
	memset(&ofServAddr, 0, sizeof(ofServAddr));

	ofServAddr.sin_family = AF_INET;
	ofServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ofServAddr.sin_port = htons(ofPort);

	/*Bind to local address*/
	if(bind(ofSock, (struct sockaddr *) &ofServAddr, sizeof(ofServAddr)) < 0) {
		perror("Error : could not bind socket");
		return 1;
	}

	/*Listen for incoming connections*/
	if(listen(ofSock, 5) < 0) {
		perror("Error: could not listen in socket");
		return 1;
	}

while(1) {
	if((clntSock = accept(ofSock, NULL, NULL)) < 0) {
		perror("Error: Accept failed");
		return 1;
	}

	if(pthread_create(&switchThread, NULL, newSwitch, (void *)clntSock )) {
      printf("Could not create thread.\n");
      return 1;
	}

//    pthread_detach(switchThread);
//    sched_yield();
}
	return 0;
}

