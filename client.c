#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 2983
#define BUFSIZE 256

//Programmer: Victor Rogers ===================================================
//Class: CS 360
//Assignment: Program 1 (Client)
//=============================================================================
//Description: This is a client that communicates with a server using the
//		"Knock Knock Protocol" as described in the instruction document
//		for the CS360 Program 1 assignment
//=============================================================================

int main(int argc, char *argv[]) {
	struct sockaddr_in sin;
	int s, bytes_recv, bytes_sent;
	char buf[BUFSIZE];
	struct hostent *hent;
	char * host;

	//--Status Validation Initialization--
	//CStrings Status' are used for client request validation and server responses
	
	//Client Request - Status 000 Init ===========================================
	const char status000[] = "000Tell me a joke";
	//============================================================================
	
	//Server Response - Status 100 ===============================================
	const char status100[] = "100knock knock";
	//============================================================================
	
	//Client Request - Status 200 Init ===========================================
	const char status200[] = "200who's there";
	//============================================================================	
	//Client Request - Status 400 Init ===========================================
	char status400[50];
	//============================================================================
	
	//Opening socket
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error while creating socket");
		exit(EXIT_FAILURE);	
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	
	if (argc > 1) {
		host = argv[1];
	} else {
		perror("Please enter a hostname as the second argument");
		exit(1);
	}

	if ((hent = gethostbyname(host)) == NULL) {
			herror(host);
			exit(1);
	}

	bcopy(hent->h_addr_list[0], &sin.sin_addr, hent->h_length);
	
	//Connecting to host
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Error while attempting to connect");
		exit(EXIT_FAILURE);
	}	else
			printf("Connected to %s\n", host);
	
	//Sending joke request
	if ((bytes_sent = send(s, status000, strlen(status000), 0)) == -1) {
		perror("Error while sending data");
		exit(1);
	} else {
		printf("Sent: %.3s %.*s\n", status000, 50, status000 + 3);
	}
	
	//Note: Ignore warning - This assignment is on purpose
	while (bytes_recv = recv(s, buf, sizeof(buf), 0)) {
		buf[bytes_recv] = '\0';
		printf("Received: %.3s %.*s\n", buf, 50, buf + 3);
		
		//Validate that the server response is equivalent to Status 100
		if (strcmp(buf, status100) == 0) {
			//Respond with Status 200
			if ((bytes_sent = send(s, status200, strlen(status200), 0)) == -1) {
				perror("Error while sending data");
				exit(1);
			} else {
				printf("Sent: %.3s %.*s\n", status200, 50, status200 + 3);
			}
		}
		
		//Validate that the server response code is equivalent to Status 300
		if (strncmp(buf, "300", 3) == 0) {
			//Respond with status 400
			snprintf(status400, 50, "400%s who", buf + 3);
			if ((bytes_sent = send(s, status400, strlen(status400), 0)) == -1) {
				perror("Error while sending data");
				exit(1);
			} else {
				printf("Sent: %.3s %.*s\n", status400, 50, status400 + 3);
			}
		}
	}
		
	close(s);
	return 0;
}
