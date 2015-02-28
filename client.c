#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in sin;
	int s, bytes;
	char buf[BUFSIZ + 1];
	struct hostent *hent;
	char * host;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error while creating socket");
		exit(EXIT_FAILURE);	
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(1113);
	
	if (argc > 1) {
		host = argv[1];
	} else {
		perror("Error: Please enter a hostname as the second argument");
		exit(EXIT_FAILURE);
	}

	if ((hent = gethostbyname(host)) == NULL) {
			herror(host);
			exit(EXIT_FAILURE);
	}

	bcopy(hent->h_addr_list[0], &sin.sin_addr, hent->h_length);

	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Error while attempting to connect");
		exit(EXIT_FAILURE);
	}

	while ((bytes = read(s, buf, BUFSIZ)) > 0)
		write(1, buf, bytes);

	close(s);
	return 0;
}
