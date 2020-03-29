# CXX = gcc
# CXXFLAGS = -std=c99 -Wall -Wextra -pedantic -g -fsanitize=address
# LDFLAGS =  -fsanitize=address

# EXEC = solve slave

# all: $(EXEC)

# slave: 
# 	$(CXX) slave.c $(CXXFLAGS) -o $@ $(LBLIBS)
# solve: 
# 	$(CXX) aplicacion.c $(CXXFLAGS) -o $@ $(LBLIBS)

# clean:
# 	rm -rf *.o $(EXEC)

# run:
# 	./$(EXEC)


CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
LDFLAGS = -fsanitize=address -lrt  -pthread
OBJFILES = shmHelper.o semaphoreHelper.o  
EXEC = SatSolver SatSlave SatView SHMTEST

all: $(EXEC)

SatSlave: $(OBJFILES)
	$(CC) $(CFLAGS) slave.c  -o SatSlave $(OBJFILES) $(LDFLAGS)

SatSolver: $(OBJFILES)
	$(CC) $(CFLAGS) aplication.c -o SatSolver $(OBJFILES) $(LDFLAGS)

SatView: $(OBJFILES)
	$(CC) $(CFLAGS) view.c -o SatView $(OBJFILES) $(LDFLAGS)

SHMTEST:$(OBJFILES)
	$(CC) $(CFLAGS) test.c -o SHMTEST $(OBJFILES) $(LDFLAGS)

clean:
	rm -f *.o $(EXEC)