#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SERVER_PORT 1113
#define MAX_PENDING 5

int main() {
	struct sockaddr_in sin;
  unsigned int s, new_s, len;
	time_t t;
	struct tm *tm;
	FILE *timef;

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

	switch (fork()) {
		case -1:
			perror("Error while starting a child process");
			return 3;
			break;
		//Close top socket and end parent process
		default:
			close(s);
			return 0;
			break;
		//Daemon listens and enters loop to accept connections
		case 0:
			break;
	}

	listen(s, MAX_PENDING);

	while(1) {
		len = sizeof(sin);

		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Error while accepting the connection");
			exit(EXIT_FAILURE);	
		}
		
		//Intercept Sigterm Here

		if ((timef = fdopen(new_s, "w")) == NULL) {
			perror("fdopen error");
			exit(EXIT_FAILURE);	
		}

		if((t = time(NULL)) < 0) {
			perror("time error");
			exit(EXIT_FAILURE);	
		}
		
		tm = gmtime(&t);
		fprintf(timef, "%.4i-%.2i-%.2iT%.2i:%.2i:%.2iZ\n",
				tm->tm_year + 1900,
				tm->tm_mon + 1,
				tm->tm_mday,
				tm->tm_hour,
				tm->tm_min,
				tm->tm_sec);
			
		fclose(timef);
	}
}
