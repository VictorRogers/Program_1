#CS 360
#Victor Rogers
#Lab_1

make server - builds the server
make client - builds the client
make clean - clears the executables from the directory

Note: Running the server starts a daemon process. I still do not have sigint figured
			out for that process so you have to use "pkill server" to kill it. I tested the
			client by starting the server and then running client with "localhost" as its 
			argument.
