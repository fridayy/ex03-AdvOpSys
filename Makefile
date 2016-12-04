all: test_open test_read test_write test_open_4

test_open:
	gcc TestOpen.c ./unity/unity.c -o TestOpen

test_read:
	gcc TestRead.c TestFileHelper.c ./unity/unity.c -o TestRead

test_write:
	gcc TestWrite.c TestFileHelper.c ./unity/unity.c -o TestWrite

test_open_4:
	gcc -g -Wall openTest4.c -o openTest4

clean:
	rm -f *.o
	rm -f TestOpen
	rm -f openTest4
	rm -f TestRead
	rm -f TestWrite
	rm -f test.txt