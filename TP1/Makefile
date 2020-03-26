CXX = gcc
CXXFLAGS = -std=c99 -Wall -Wextra -pedantic -g -fsanitize=address
LDFLAGS =  -fsanitize=address

EXEC = solve slave

all: $(EXEC)

slave: 
	$(CXX) slave.c $(CXXFLAGS) -o $@ $(LBLIBS)
solve: 
	$(CXX) aplicacion.c $(CXXFLAGS) -o $@ $(LBLIBS)

clean:
	rm -rf *.o $(EXEC)

run:
	./$(EXEC)
		