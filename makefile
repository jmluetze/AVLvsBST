OBJS = scanner.o value.o testvalue.o
OPTS = -Wall -g -std=c99 -Wextra

trees : main.o BinarySearchTree.o queue.o avlt.o scanner.o
	gcc main.o BinarySearchTree.o queue.o avlt.o scanner.o -o trees -lm
main.o : main.c BinarySearchTree.h queue.h avlt.h scanner.h
	gcc $(OPTS) -c main.c BinarySearchTree.h queue.h avlt.h
BinarySearchTree.o: BinarySearchTree.c BinarySearchTree.h
	gcc $(OPTS) -c BinarySearchTree.c 
queue.o: queue.c queue.h
	gcc $(OPTS) -c queue.c
clean:
	rm *.o *.h.gch trees
test: test3a test3b test5a test5b test4a test4b testa testb test6a test6b test7b test7a

testa:
	./trees -a corpus commands
testb:
	./trees -b corpus commands
test2a:
	./trees -a long command
test2b:
	./trees -b long command
test3a:
	./trees -a s.txt command
test3b:
	./trees -b s.txt command
test4a:
	./trees -a corpusu blanku
test4b:
	./trees -b corpusu blanku
test5a:
	./trees -a corpusb blank
test5b:
	./trees -b corpusb blank
test6a:
	./trees -a corpus commandDbutOne
test6b:
	./trees -b corpus commandDbutOne
test7a:
	./trees -a corpus commandDAll
test7b:
	./trees -b corpus commandDAll

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c
avlt.o : avlt.c avlt.h
		gcc $(OPTS) -c avlt.c