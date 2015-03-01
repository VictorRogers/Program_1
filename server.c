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

	const char *jokeName[4] = {"doughnut", "little old lady", "who",
														"Dewey"};
	char jokeStatus[] = "300";	
	int jokeNumber = rand() % 4;	
	strncat(jokeStatus, jokeName[jokeNumber], 20);

  char status000[] = "000Tell me a joke";
  char status100[] = "100knock knock"; 
  char status200[] = "200who's there";
  char status300[20];
	strncat(status300, jokeStatus, 20);
  char status400[] = "400doughnut who";
  char status500[] = "500doughnut ask, it is a secret";
  char status600[] = "600Errors aren't funny";


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
		
    //This is supposed to be an assignment - Ignore warning
    while (bytes_recv = recv(new_s, buf, sizeof(buf), 0)) {
			
      buf[bytes_recv] = '\0';	
			
      printf("Received: %s \n", buf);

      if (strcmp(buf, status000) == 0) { 
        if ((bytes_sent = send(new_s, status100, strlen(status100), 0)) == -1) {
          perror("Error while sending data");
          exit(1);
        } else {
            printf("Sent: %s \n", status100);	
        }
      }	

      else if (strcmp(buf, status200) == 0) {
        if ((bytes_sent = send(new_s, status300, strlen(status300), 0)) == -1) {          perror("Error while sending data");
          exit(1);
        } else {
            printf("Sent: %s \n", status300);
        }
      }

      else if (strcmp(buf, status400) == 0) {
        if ((bytes_sent = send(new_s, status500, strlen(status500), 0)) == -1) {          perror("Error while sending data");
          exit(1);
        } else {
          printf("Sent: %s \n", status500);
          close(new_s);
          exit(0);
        }
      }

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
