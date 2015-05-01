#Makefile
OBJS = BinarySearchTree.o RedBlackTree.o driver.o 
CPPFLAGS = -Wall -std=c++11
PROG = tree
CC = g++

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	
BinarySearchTree.o: BinarySearchTree.h BinarySearchTree.cpp
	$(CC) -c $(CPPFLAGS) BinarySearchTree.cpp
	
RedBlackTree.o: RedBlackTree.h RedBlackTree.cpp
	$(CC) -c $(CPPFLAGS) RedBlackTree.cpp
	
driver.o: 
	$(CC) -c $(CPPFLAGS) driver.cpp

clean:
	$(RM) $(PROG) $(OBJS)
