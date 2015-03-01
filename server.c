#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SERVER_PORT 2983 
#define MAX_PENDING 1
#define BUFSIZE 256

int main() {
	struct sockaddr_in sin;
  unsigned int s, new_s, len;
	int bytes_recv, bytes_sent;
	char buf[BUFSIZE];
	
	char status000[] = "000Tell me a joke.";
	char status100[] = "100Knock Knock."; 
	char status200[] = "200Who's there?";
	char status300[] = "300Doughnut.";
	char status400[] = "400Doughnut who?";
	char status500[] = "500Doughnut ask, it is a secret.";

	//Address Data Structure
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	//Open Socket
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error while creating socket");
		exit(1);	
	}

	//Bind socket to address	
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("Error while binding the port");
		exit(1);	
	}

	listen(s, MAX_PENDING);

	while(1) {
		len = sizeof(sin);

		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Error while accepting the connection");
			exit(1);	
		}

		while(bytes_recv = recv(new_s, buf, BUFSIZE-1, 0)) {
			buf[bytes_recv] = '\0';	
			
			printf("User sent: %s \n", buf);

			if (strcmp(buf, status000) == 0) { 
				if ((bytes_sent = send(new_s, status100, strlen(status100), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
				}
			}	

			else if (strcmp(buf, status200) == 0) {
				if ((bytes_sent = send(new_s, status300, strlen(status300), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
				}
			}

			else if (strcmp(buf, status400) ==0) {
				if ((bytes_sent = send(new_s, status500, strlen(status500), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
				} else {
					close(new_s);
				}
			}
		}
	}
}
