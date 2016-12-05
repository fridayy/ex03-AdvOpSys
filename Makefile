all: test_open test_read test_write test_lseek test_mmap test_open_4

test_open:
	gcc -Wall TestOpen.c TestFileHelper.c ./unity/unity.c -o bin/TestOpen

test_read:
	gcc -Wall TestRead.c TestFileHelper.c ./unity/unity.c -o bin/TestRead

test_write:
	gcc -Wall TestWrite.c TestFileHelper.c ./unity/unity.c -o bin/TestWrite

test_lseek:
	gcc -Wall TestLseek.c TestFileHelper.c ./unity/unity.c -o bin/TestLseek

test_mmap:
	gcc -Wall TestMmap.c TestFileHelper.c ./unity/unity.c -o bin/TestMmap

test_open_4:
	gcc -g -Wall openTest4.c -o bin/openTest4

clean:
	rm -f *.o
	rm -f TestOpen
	rm -f openTest4
	rm -f TestRead
	rm -f TestWrite
	rm -f test.txt