flags = -Wall -Wextra -Werror -pedantic
rm = add_tfp.o test_add_tfp
test_add_tfp: add_tfp.o
	gcc test_add_tfp.c add_tfp.o -o test_add_tfp
add_tfp.o:
	gcc -c add_tfp.c -o add_tfp.o
clean:
	rm -rf $(rm)