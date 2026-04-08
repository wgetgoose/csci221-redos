flags = -Wall -Wextra -Werror -pedantic
bst = ./bst
io = ./io
bst_test: bst.o
	gcc $(flags) $(bst)/bst.o $(bst)/bst_test.c -o $(bst)/bst_test
bst.o:
	gcc $(flags) -c $(bst)/bst.c -o $(bst)/bst.o
io: io.o
	gcc $(flags) $(io)/echo_chamber.o -o $(io)/echo_chamber
io.o:
	gcc $(flags) -c $(io)/echo_chamber.c -o $(io)/echo_chamber.o
clean:
	rm -rf $(bst)/bst.o
	rm -rf $(bst)/bst_test
	rm -rf $(io)/echo_chamber.o $(io)/echo_chamber