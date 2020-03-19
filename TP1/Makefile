CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -pedantic  -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = *.c
OBJ = $(SRC:.cc=.o)
EXEC = solve

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf *.o $(EXEC)

run:
	./$(EXEC)
	