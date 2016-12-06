all: test_open test_read test_write test_lseek test_mmap test_close test_open_4 test_readchar test_count libcount.a main test_fileoperation test_directoryoperation test_pathoperation

main.o:
	gcc -Wall -c ./src/count/main.c

readchar.o:
	gcc -Wall -c ./src/count/readchar_R.c

count.o:
	gcc -Wall -c ./src/count/count_M.c

main: libcount.a main.o
	gcc -o ./bin/count main.o libcount.a

libcount.a: readchar.o count.o
	ar -rv libcount.a readchar_R.o count_M.o

test_pathoperation:
	gcc -Wall ./test/ushell/TestPathOperation.c ./src/ushell/PathOperation.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestPathOperation

test_directoryoperation:
	gcc -Wall ./test/ushell/TestDirectoryOperation.c ./src/ushell/DirectoryOperation.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestDirectoryOperation

test_fileoperation:
	gcc -Wall ./test/ushell/TestFileOperation.c ./src/ushell/FileOperation.c ./test/TestFileHelper.c ./test/unity/unity.c -o bin/TestFileOperation

test_count:
	gcc -Wall ./test/TestCount_M.c ./test/TestFileHelper.c ./src/count/count_M.c ./test/unity/unity.c -o bin/TestCount_M

test_readchar:
	gcc -Wall ./test/TestReadchar_R.c ./test/TestFileHelper.c ./src/count/readchar_R.c ./test/unity/unity.c -o bin/TestReadchar_R

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
	rm -rf ./bin/*
	rm -f ./*.o
	rm -f ./*.a