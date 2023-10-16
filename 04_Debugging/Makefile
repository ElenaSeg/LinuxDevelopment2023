GENERATES = range *.log *.out

range: range.c
	gcc -O0 -g $< -o $@

test: test_1 test_2


test_%: gdb_script%.out
	cmp $< $@

gdb_script1.out: gdb_script1 range
	cgdb -x $< ./range
	cat gdb_script1.log | grep "@@@" | sed -E "s/@@@(.*)/\1/" > $@

gdb_script2.out: gdb_script2 range
	cgdb -x $< ./range
	cat gdb_script2.log | grep "@@@" | sed -E "s/@@@(.*)/\1/" > $@

clean:
	rm -f $(GENERATES)
