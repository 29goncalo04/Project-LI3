CC = gcc
CFILES=$(wildcard src/*.c)
PNTH=$(wildcard include/*.h)
FLAGS= -Iinclude -Wall -Wextra -pedantic -O2 -g
DIREC:=objetos/
RESULTADOS:=Resultados/
OBJFILES=$(CFILES:src/%.c=$(DIREC)%.o)

run: $(OBJFILES)
	$(CC) -o programa-principal $^ $(FLAGS) -lncurses -lm


compile: run
	./programa-principal


valgrind: ./programa-principal
	valgrind --leak-check=full --show-leak-kinds=all ./programa-principal dataset/data/ dataset/input.txt


objetos:
	mkdir -p $(DIREC)


$(DIREC)%.o: src/%.c | objetos
	$(CC) $(FLAGS) -o "$@" -c "$<"  

clean:
	rm -rf $(DIREC) $(RESULTADOS)*.csv $(RESULTADOS)*.txt programa-principal *.o