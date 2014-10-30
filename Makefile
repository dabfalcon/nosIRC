all:	test sample run

LOPT=`uname | grep SunOS | sed 's/SunOS/-lnsl -lsocket/'`

test:	test.c Makefile
	gcc -Wall -g -o test test.c $(LOFT)

sample:	sample.c Makefile
	gcc -Wall -g -o sample sample.c $(LOFT)

run: test sample Makefile
	./test ./sample
