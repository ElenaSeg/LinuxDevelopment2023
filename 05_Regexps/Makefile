esub: esub.c
	gcc -o esub $^

test: esub
	rm -f test?
	echo "efgk" >> test1 && ./esub abcd 1234 efgk | cmp test1
	echo "00012cd000" >> test2 && ./esub 'ab(cd)' '12\1' 000abcd000 | cmp test2
	echo "00012ab333cdcd000" >> test3 && ./esub '(ab[0-9]*(cd))' '12\1\2' 000ab333cd000 | cmp test3
	echo 12\\A >> test4 && ./esub 'ab(cd)' '12\\A' abcd | cmp test4

clean:
	rm -f esub test?