flags = -Wall -Wextra -Werror -pedantic
deps = choose_mover.o powers.o distance_english_to_metric.o
main: main.o $(deps)
	gcc $(flags) main.o $(deps) -o main
main.o: 
	gcc $(flags) -c main.c -o main.o
choose_mover.o:
	gcc $(flags) -c choose_mover.c -o choose_mover.o
powers.o:
	gcc $(flags) -c powers.c -o powers.o
distance_english_to_metric.o:
	gcc $(flags) -c distance_english_to_metric.c -o distance_english_to_metric.o
weekday.o:
	gcc $(flags) -c weekday.c -o weekday.o
clean:
	rm -rf main main.o $(deps) weekday.o 