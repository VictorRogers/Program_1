#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define SERVER_PORT 2983 
#define MAX_PENDING 1
#define BUFSIZE 256

//Programmer: Victor Rogers ====================================================
//Class: CS 360
//Assignment: Program 1 (SERVER)
//==============================================================================
//Description: This is a server that implements the "Knock Knock Protocol" as
//		described in the instruction document for the CS360 Program 1
//		assignment.
//		
//		NOTE: Please view the README for instruction on testing the
//		server without a client.
//==============================================================================


int main() {
  struct sockaddr_in sin;
  unsigned int s, new_s, len;
  int bytes_recv, bytes_sent;
  char buf[BUFSIZE];

	//--Status Validation Initialization--
	//CStrings Status' are used for client request validation and server responses

	//Client Request = Status 000 Validation =====================================
	char status000[] = "000Tell me a joke";
	//============================================================================

	//Server Response - Status 100 Init ==========================================
	char status100[] = "100knock knock"; 
	//============================================================================
	
	//Client Request - Status 200 Validation ====================================
	char status200[] = "200who's there";
	//============================================================================

	//Server Response - Status 300 Init ==========================================
	const char *jokeName[4] = {"doughnut", "little old lady", "who", "Dewey"};
	srand(time(NULL));
	int jokeNumber = rand() % 4;	
	char status300[50];
	snprintf(status300, 50, "300%s", jokeName[jokeNumber]);
	//============================================================================

	//Client Request - Status 400 Validation =====================================
	char status400[50];
	snprintf(status400, 50, "400%s %s", jokeName[jokeNumber], "who");
	//============================================================================

	//Server Response - Status 500 Init ==========================================
	const char *jokeCompleteResponse[4] = {"Doughnut ask, it is a secret",
					"I didn't know you could yodel", 
					"Are you an owl", 
					"Dewey have to keep telling silly jokes"};
	char status500[50];
	snprintf(status500, 50, "500%s", jokeCompleteResponse[jokeNumber]);
	//============================================================================

	//Server Response - Status 600 Init ==========================================
	char status600[] = "600Errors aren't funny";
	//============================================================================


	//Address Data Structure =====================================================
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);
	//============================================================================

	//Open Socket ================================================================
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
	perror("Error while creating socket");
	exit(1);	
	}
	//============================================================================

	//Bind socket to address =====================================================
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("Error while binding the port");
		exit(1);	
	}
	//============================================================================

	//Listen for connections======================================================
	listen(s, MAX_PENDING);
	//============================================================================

	while(1) {
		len = sizeof(sin);

		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Error while accepting the connection");
			exit(1);	
		}

		//NOTE: Ignore warning - This assignment is on purpose 
		while (bytes_recv = recv(new_s, buf, sizeof(buf), 0)) {
			buf[bytes_recv] = '\0';	
			printf("Received: %s \n", buf);
			
			//Validate that the client request is equivalent to Status 000
			if (strcmp(buf, status000) == 0) { 
				//Respond with Status 100
				if ((bytes_sent = send(new_s, status100, strlen(status100), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
				} else {
					printf("Sent: %s \n", status100);	
				}
			}

			//Validate that the client request is equivalent to Status 200
			else if (strcmp(buf, status200) == 0) {
				//Respond with Status 300
				if ((bytes_sent = send(new_s, status300, strlen(status300), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
			        } else {
					printf("Sent: %s \n", status300);
				}
			}

			//Validate that the client request is equivalent to Status 400
			else if (strcmp(buf, status400) == 0) {
				//Respond with Status 500
				if ((bytes_sent = send(new_s, status500, strlen(status500), 0)) == -1) {
					perror("Error while sending data");
					exit(1);
				} else { //Close Socket and Shut down server
					printf("Sent: %s \n", status500);
					close(new_s);
					exit(0);
				}
			}
			
			//Invalid client request - Send Status 600 (ERROR)
			else {
				if ((bytes_sent = send(new_s, status600, strlen(status600), 0)) == -1) {
					perror("Error while sending error message");
					exit(1);
				} else {
					printf("Sent: %s \n", status600);
				}
			}
		}
	}
	if ((bytes_sent = send(new_s, status600, strlen(status600), 0)) = -1) {
		perror("Error occurred while sending error message to client");
		exit(1);
	} else {
		printf("Sent: %s \n", status600);
	}
}
