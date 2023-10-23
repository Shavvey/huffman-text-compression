# compiler and compiler flags
CC = clang++ -std=c++17 -Wall
# source files
SRC = huffman-tree.cpp huffman-tree.hpp main.cpp file-handler.cpp file-handler.hpp
# object files
OBJS = huffman-tree.o main.o file-handler.o

huffman: $(OBJS)
	$(CC) $(OBJS) -o huff_tree

# produce object file, do not run linker
huffman-tree.o: $(SRC)
	$(CC) -c $(SRC)

file-handler.o: $(SRC)
	$(CC) -c $(SRC)


# produce object file, do not run linker
main.o: $(SRC)
	$(CC) -c $(SRC)

.PHONY: clean
clean: $(OBJS)
	rm $(OBJS) *.gch


