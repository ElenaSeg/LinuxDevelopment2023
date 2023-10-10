CC = cc 
CFLAGS += -fPIC
GENERATES = prog prog-a prog-so  
TRASH = *.o *~ o.* *.a *.so ./test

all:    $(GENERATES)

prog:   const.o fun.o prog.o
	$(CC) $^ -o $@

prog-a: prog.o static
	$(CC) -L. $< -loutput_static -o $@ 

prog-so:	prog.o shared
	cc -L. prog.o -loutput -o $@

fun.o:  outlib.h

static: fun.o const.o
	ar -rcs liboutput_static.a $^

shared: fun.o const.o
	$(CC) -shared $^ -o liboutput.so

clean:
	rm -rf $(TRASH)

distclean:      clean
	rm -f $(GENERATES)

test: prog prog-a prog-so	
	@echo Testing...
	@mkdir -p test
	@./prog 2> test/test1_prog 
	@./prog abc > test/test2_prog 
	@./prog a b c > test/test3_prog 

	@./prog-a 2> test/test1_prog-a 
	@./prog-a abc > test/test2_prog-a 
	@./prog-a a b c > test/test3_prog-a 

	@LD_LIBRARY_PATH=$(PWD) ./prog-so 2> test/test1_prog-so 
	@LD_LIBRARY_PATH=$(PWD) ./prog-so abc > test/test2_prog-so 
	@LD_LIBRARY_PATH=$(PWD) ./prog-so a b c > test/test3_prog-so 

	-cmp test/test1_prog test/test1_prog-a 
	-cmp test/test1_prog test/test1_prog-so
	-cmp test/test1_prog-a test/test1_prog-so
	
	cmp test/test2_prog test/test2_prog-a 
	cmp test/test2_prog test/test2_prog-so
	cmp test/test2_prog-a test/test2_prog-so

	cmp test/test3_prog test/test3_prog-a 
	cmp test/test3_prog test/test3_prog-so
	cmp test/test3_prog-a test/test3_prog-so

	@echo "\nEnd testing."
