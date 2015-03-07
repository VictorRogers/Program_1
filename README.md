**Programmer:** Victor Rogers

**Course:** CS360

**Assignment:** Program 1

**Description:**  This is a server and client that implement and follow
the Knock Knock Protocol as described in the assignment instruction
documentation for the CS360 Program 1 homework.

**Make instructions**
* make all - builds the server and client binaries
* make server - builds the server binary
* make client - builds the client binary
* make clean - removes binary files

**Testing instruction**

The client and server may be tested by running the server and running the client
with the server's address as its second argument.

The client was simulated by using netcat with the following commands:
* `echo -n "000Tell me a joke" | nc localhost 2983` _(Server Response: 100knock knock)_
* `echo -n "200who's there" | nc localhost 2983` _(Server Response: 300(joke name))_
* `echo -n "400(joke name) who" | nc localhost 2983` _(Server Response: 500(joke) and close connection)_

