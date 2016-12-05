all: test_open test_read test_write test_lseek test_mmap test_close test_open_4 libcount.a main

main.o:
	gcc -Wall -c ./src/main.c

readchar.o:
	gcc -Wall -c ./src/readchar_R.c

count.o:
	gcc -Wall -c ./src/count_M.c

main: libcount.a main.o
	gcc -o ./bin/count main.o libcount.a

libcount.a: readchar.o count.o
	ar -rv libcount.a readchar_R.o count_M.o

test_readchar:
	gcc -Wall ./test/TestReadchar.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestReadchar

test_open:
	gcc -Wall ./test/TestOpen.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestOpen

test_read:
	gcc -Wall ./test/TestRead.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestRead

test_write:
	gcc -Wall ./test/TestWrite.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestWrite

test_lseek:
	gcc -Wall ./test/TestLseek.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestLseek

test_mmap:
	gcc -Wall ./test/TestMmap.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestMmap

test_close:
	gcc -Wall ./test/TestClose.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestClose

test_open_4:
	gcc -g -Wall ./test/openTest4.c -o bin/openTest4

clean:
	rm -f ./test/*.o
	rm -f ./bin/*
	rm -f ./*.o
	rm -f ./*.a