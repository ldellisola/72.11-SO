CC = gcc
CFLAGS = -Wall -Wextra -g


CLIENT_EXEC = Client.exec
CLIENT_OBJ = Client.o 
CLIENT_SRC = client.c

SERVER_EXEC = Server.exec
SERVER_OBJ = Server.o 
SERVER_SRC = server.c

TESTS_OBJ = AudioTest.o GDBTest.o FDTest.o
TESTS_SRC = AudioTest.c GDBTest.c FDTest.c
TESTS_HDR = AudioTest.h GDBTest.h FDTest.h

ASM_OBJ = ASMTest.o
ASM_SRC = ASMTest.asm


EXEC = $(CLIENT_EXEC) $(SERVER_EXEC)


all: $(EXEC) 

$(CLIENT_EXEC): $(CLIENT_OBJ) 
	$(CC) $(CFLAGS) $(CLIENT_OBJ)  -o $(CLIENT_EXEC)  

$(SERVER_EXEC): $(SERVER_OBJ)  $(TESTS_OBJ) $(TESTS_HDR) $(ASM_OBJ)
	$(CC) $(CFLAGS) $(TESTS_OBJ) $(ASM_OBJ) $(SERVER_OBJ) -o $(SERVER_EXEC) $(TESTS_HDR)


$(CLIENT_OBJ): $(CLIENT_SRC)  
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ) 

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC)  -o $(SERVER_OBJ) 

$(TESTS_OBJ): $(TESTS_SRC) 
	$(CC) $(CFLAGS) -c $(TESTS_SRC)  

$(ASM_OBJ): $(ASM_SRC)
	nasm -f elf64 $(ASM_SRC) -o $(ASM_OBJ)

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(TESTS_OBJ) $(EXEC) $(ASM_OBJ)


.PHONY: all
