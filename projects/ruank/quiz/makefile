default: testme

testme:
	gcc -Wall -std=c99 -o testme testme.c -ftest-coverage -fprofile-arcs
	./testme
		
clean:
	rm testme

cleanall: 
	rm testme
