CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -D_XOPEN_SOURCE=700 -g
LDFLAGS =  -lrt  -pthread -fsanitize=address
EXEC = SatSolver SatSlave SatView 

LIB_OBJ = shmHelper.o semaphoreHelper.o
LIB_HDR = shmHelper.h semaphoreHelper.h
LIB_SRC = shmHelper.c semaphoreHelper.c

SOLVE_OBJ = aplication.o
SOLVE_SRC = aplication.c
 
SLAVE_OBJ = slave.o
SLAVE_SRC = slave.c

VIEW_OBJ = view.o
VIEW_SRC = view.c


all: $(EXEC)

SatSlave: $(SLAVE_OBJ) $(LIB_OBJ) $(LIB_HDR) 
	$(CC) $(CFLAGS) $(LIB_OBJ) $(SLAVE_OBJ)  -o SatSlave  $(LDFLAGS) $(LIB_HDR)

SatSolver: $(SOLVE_OBJ)  $(LIB_OBJ) $(LIB_HDR) 
	$(CC) $(CFLAGS) $(LIB_OBJ) $(SOLVE_OBJ) -o SatSolver $(LDFLAGS) $(LIB_HDR)

SatView: $(VIEW_OBJ) $(LIB_OBJ) $(LIB_HDR)
	$(CC) $(CFLAGS) $(LIB_OBJ) $(VIEW_OBJ) -o SatView  $(LDFLAGS) $(LIB_HDR)

$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CC) $(CFLAGS) -c $(LIB_SRC) $(LDFLAGS)

$(SOLVE_OBJ): $(SOLVE_SRC)
	$(CC) $(CFLAGS) -c $(SOLVE_SRC) $(LDFLAGS)

$(SLAVE_OBJ): $(SLAVE_SRC)
	$(CC) $(CFLAGS) -c $(SLAVE_SRC) $(LDFLAGS)

$(VIEW_OBJ): $(VIEW_SRC)
	$(CC) $(CFLAGS) -c $(VIEW_SRC) $(LDFLAGS)


valgrind: $(EXEC)
	valgrind -v ./SatSolver sat/* 

cppcheck: $(EXEC)
	cppcheck --quiet --enable=all --force --inconclusive $(SLAVE_SRC) $(SOLVE_SRC) $(VIEW_SRC) $(LIB_SRC) $(LIB_HDR)


clean:
	rm -f $(LIB_OBJ) $(SLAVE_OBJ) $(SOLVE_OBJ) $(VIEW_OBJ) $(EXEC)


