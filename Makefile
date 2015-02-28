all: server client

server: server.c
	g++ -Wall -g -o server server.c

client: client.c
	g++ -Wall -g -o client client.c

clean:
	rm -f *core server client *o
