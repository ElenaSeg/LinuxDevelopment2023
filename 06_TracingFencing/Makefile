GENERATES = move libprotect.so *.txt *.log

compile: move protect.so

protect.so: 
	cc -shared protect.c -o libprotect.so -ldl

test: compile test0 test1 test2 test3 test4 testProtect1 testProtect2 testProtect3

test0:
	@echo "\n\tTest0 : OK\n"
	echo "abc\n3dworldelite\nnetwork" > in.txt
	@echo "\tInput file content:"
	cat in.txt
	-strace -o temp.log ./move in.txt out.txt
	@echo "\tstrace out:"
	tail -1 temp.log
	@echo "\tCheck output file existence and content:"
	cat out.txt
	@rm -f temp.log out.txt
	@echo

test1:
	@echo "\tTest1 : Args error\n"
	@echo "\t move output:"
	-strace -o temp.log ./move in.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@rm -f temp.log
	@echo

test2:
	@echo "\tTest2 : Reading file error\n"
	echo "abc\n3dworldelite\nnetwork" > in.txt
	chmod -r in.txt
	@echo "\tmove output:"
	-strace -o temp.log ./move in.txt out.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@echo "\tCheck input file existence:"
	-find in*
	@rm -f temp.log *.txt
	@echo

test3:
	@echo "\tTest3 : Creating output file error\n"
	echo "abc\n3dworldelite\nnetwork" > in.txt
	mkdir testarea
	chmod -w testarea
	@echo "\tmove output:"
	-strace -o temp.log ./move in.txt testarea/out.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@echo "\tCheck input file existence:"
	-find in*
	@rm -rf testarea temp.log *.txt
	@echo

test4:
	@echo "\tTest4 : errors on moving files\n"
	cp test_support/broken.txt .
	@echo "\t move output:"
	-strace -o temp.log ./move broken.txt out.txt
	@echo "\t strace output:"
	tail -1 temp.log
	@echo "\t Check input files existence:"
	-find broken*
	@rm -f *.txt
	@echo

testProtect1:
	@echo "\n\tTest with LD_PRELOAD:\n"
	echo "abc\nd\nefg" > inPROTECT.txt
	-LD_PRELOAD=./libprotect.so strace -o temp.log ./move inPROTECT.txt out.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@echo "\tCheck input and output files existence:"
	-find *PROTECT* out*
	@rm -f temp.log *.txt

testProtect2:
	@echo "\n\tTest with LD_PRELOAD (and without PROTECTed file):\n"
	echo "abc\nd\nefg" > in.txt
	-LD_PRELOAD=./libprotect.so strace -o temp.log ./move in.txt out.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@echo "\tCheck output files existence:"
	-find out*
	@rm -f temp.log *.txt

testProtect3:
	@echo "\n\tTest with LD_PRELOAD (with broken input file and PROTECTed output file):\n"
	cp test_support/broken.txt .
	-LD_PRELOAD=./libprotect.so strace -o temp.log ./move broken.txt outPROTECT.txt
	@echo "\tstrace output:"
	tail -1 temp.log
	@echo "\tCheck input and output files existence:"
	-find broken* *PROTECT*
	@rm -f temp.log *.txt


clean:
	rm -rf $(GENERATES)
