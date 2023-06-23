# compiler and compiler flags
CC = clang++
# source files
SRC = huffman-tree.cpp huffman-tree.hpp main.cpp
# object files
OBJS = huffman-tree.o main.o

huffman: $(OBJS)
	$(CC) $(OBJS)

# produce object file, do not run linker
huffman-tree.o: $(SRC)
	$(CC) -c $(SRC) huffman-tree.hpp


# produce object file, do not run linker
main.o: $(SRC)
	$(CC) -c $(SRC)

.PHONY: clean
clean: $(OBJS)
	rm $(OBJS) *.gch


