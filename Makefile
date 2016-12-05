all: test_open test_read test_write test_lseek test_mmap test_close test_open_4

test_open:
	gcc -Wall ./test/TestOpen.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestOpen

test_read:
	gcc -Wall ./test/TestRead.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestRead

test_write:
	gcc -Wall ./test/TestWrite.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestWrite

test_lseek:
	gcc -Wall ./test/TestLseek.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestLseek

test_mmap:
	gcc -Wall ./test/TestMmap.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestMmap

test_close:
	gcc -Wall ./test/TestClose.c ./test/TestFileHelper.c ./test/unity/unity.c -o test/bin/TestClose

test_open_4:
	gcc -g -Wall ./test/openTest4.c -o test/bin/openTest4

clean:
	rm -f *.o
	rm -f ./test/bin/*