#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SERVER_PORT 2983 
#define MAX_PENDING 5

int main() {
	struct sockaddr_in sin;
  unsigned int s, new_s, len;

	//Address Data Structure
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	//Open Socket
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error while creating socket");
		exit(EXIT_FAILURE);	
	}

	//Bind socket to address	
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("Error while binding the port");
		exit(EXIT_FAILURE);	
	}

	listen(s, MAX_PENDING);

	while(1) {
		len = sizeof(sin);

		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Error while accepting the connection");
			exit(EXIT_FAILURE);	
		}
		
		//Intercept Sigterm Here
		}
	}
}
