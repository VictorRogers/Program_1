**Programmer:** Victor Rogers

**Course:** CS360

**Assignment:** Program 1

**Note:** Client is incomplete at this point in time

**Description:**  This is a server that implements the "Knock Knock Protocol" as
described in the instruction document for the CS360 Program 1
assignment. The client is incomplete at this point in time.

**Make instructions**
* make all - builds the server and client binaries
* make server - builds the server binary
* make client - builds the client binary
* make clean - removes binary files

**Testing instruction**
I have tested the client using the following netcat commands
* `echo -n "000Tell me a joke" | nc localhost 2983` _(Server Response: 100knock knock)_
* `echo -n "200who's there" | nc localhost 2983` _(Server Response: 300(joke name))_
* `echo -n "400(joke name) who" | nc localhost 2983` _(Server Response: 500(joke) and close connection)_

