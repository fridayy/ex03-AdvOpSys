all: test_open test_read test_write test_open_4

test_open:
	gcc TestOpen.c ./unity/unity.c -o bin/TestOpen

test_read:
	gcc TestRead.c TestFileHelper.c ./unity/unity.c -o bin/TestRead

test_write:
	gcc TestWrite.c TestFileHelper.c ./unity/unity.c -o bin/TestWrite

test_open_4:
	gcc -g -Wall openTest4.c -o bin/openTest4

clean:
	rm -f *.o
	rm -f bin/TestOpen
	rm -f bin/openTest4
	rm -f bin/TestRead
	rm -f bin/TestWrite