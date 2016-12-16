//
// Created by bnjm on 12/5/16.
//
#include "../TestFileHelper.h"
#include "../unity/unity.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>


int interruptOcc = 0; // will be set if SIGSEGV is caught
jmp_buf buf;

/*
 * Helper function
 */
char * mmapFile() {
    char *fileName = createTestFileWithContent(100, "mmaptest.txt");
    int fd = open(fileName, O_RDWR);

    char *map = mmap(0, 100, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    remove(fileName);

    return map;
}

/*
 * Catches a signal. Used for the munmap test to catch SIGSEGV.
 * Don't try at home kids!
 */
void sighandler(int signum) {
    interruptOcc = 1337; // set...
    longjmp(buf, 1); // ..and get get outta here!
}

/*
 * Test using mmap() to read the contents of a file.
 */
void test_ReadDataContainedInAFile(void) {
    char *fileName = createTestFileWithContent(100, "mmaptest.txt");
    int fd = open(fileName, O_RDWR);

    char *map = mmap(0, 100, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    remove(fileName);
    
    TEST_ASSERT(map != MAP_FAILED);

    for (off_t i = 0; i < 100; ++i) {
        TEST_ASSERT_EQUAL('a', map[i]);
    }

    munmap(map, 100);
}

/*
 * Test reading a file after munmap() has been called.
 * In order to test this a signal handler is required which catches SIGSEGV (not recommended tho).
 */
void test_ReadDataAfterUsingMunmap(void) {
    char *map = mmapFile();
    munmap(map, 100);

    signal(SIGSEGV, sighandler);

    if(!setjmp(buf)) {
        // provoke sigfault
        TEST_ASSERT_EQUAL(1, map[0]);
    } else {
        // welcome back my friend! Now we can assert.
        TEST_ASSERT_EQUAL(1337, interruptOcc);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ReadDataContainedInAFile);
    RUN_TEST(test_ReadDataAfterUsingMunmap);

    return UNITY_END();
}
