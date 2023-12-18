GENERATES=*.o maze1.c maze2.c maze3.c maze0 maze1 maze2 maze3 

all:	maze0 maze1 maze2 maze3

maze1.c:	maze0.c
	patch -o maze1.c < 1.patch

maze2.c: maze1.c
	patch -o maze2.c < 2.patch

maze3.c: maze2.c
	patch -o maze3.c < 3.patch

run:	maze0 maze1 maze2 maze3
	./maze0
	./maze1 10
	./maze2 "*_" 10
	./maze3 42 "*_" 10

clean: 
	rm -f $(GENERATES)
