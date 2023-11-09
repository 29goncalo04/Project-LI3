CC = gcc
CFILES=$(wildcard src/*.c)
PNTH=$(wildcard include/*.h)
FLAGS= -Iinclude -Wall -Wextra -pedantic -O2 -g
DIREC:=objetos/
RESULTADOS:=Resultados/
OBJFILES=$(CFILES:src/%.c=$(DIREC)%.o)

run: $(OBJFILES)
	$(CC) -o programa-principal $^ $(FLAGS) -lm


compile: run
	./programa-principal


valgrind: run
	valgrind --leak-check=full ./programa-principal


objetos:
	mkdir -p $(DIREC)


$(DIREC)%.o: src/%.c | objetos
	$(CC) $(FLAGS) -o "$@" -c "$<"  

clean:
	rm -rf $(DIREC) $(RESULTADOS)*.csv $(RESULTADOS)*.txt programa-principal *.o