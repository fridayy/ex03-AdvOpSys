#!/usr/bin/env bash
RED='\033[0;31m'
NC='\033[0m'


function makeAll {
printf "${RED}>> MAKE\n${NC}"
make
}

function clean {
printf "\n${RED}>>FINISHED CLEANING UP \n${NC}"
make clean

}
function syscalltests {
    printf "\n${RED}>> BASIC SYSCALLS TESTS\n${NC}"
    printf "\n${RED}>> TEST OPEN()\n${NC}"
    ./bin/TestOpen
    printf "\n${RED}>> TEST READ()\n${NC}"
    ./bin/TestRead
    printf "\n${RED}>> TEST WRITE()\n${NC}"
    ./bin/TestWrite
    printf "\n${RED}>> TEST LSEEK()\n${NC}"
    ./bin/TestLseek
    printf "\n${RED}>> TEST MMAP()\n${NC}"
    ./bin/TestMmap
    printf "\n${RED}>> TEST CLOSE() \n${NC}"
    ./bin/TestClose
}

function exercise2tests {
printf "\n${RED}>> EXERCISE 2.8 TESTS\n${NC}"
printf "\n${RED}>> TEST READCHAR() \n${NC}"
./bin/TestReadchar_R
printf "\n${RED}>> TEST COUNTM() \n${NC}"
./bin/TestCount_M

}

function shelltests {
printf "\n${RED}>> SHELL TESTS\n${NC}"
printf "\n${RED}>> TEST DIRECTORY OPERTIONS \n${NC}"
./bin/TestDirectoryOperation
printf "\n${RED}>> TEST FILE OPERTIONS \n${NC}"
./bin/TestFileOperation
printf "\n${RED}>> TEST PATH OPERTIONS \n${NC}"
./bin/TestPathOperation
}

if [ -z "$1" ]
then
    echo "available commands 'all' 'tests' 'assemble' 'clean'"
    exit
fi

if [ $1 == "all" ]
then
    clean
    makeAll
    syscalltests
    exercise2tests
    shelltests
fi

if [ $1 == "tests" ]
then
    clean
    makeAll
    syscalltests
    exercise2tests
    shelltests
    clean
fi


if [ $1 == "assemble" ]
then
    clean
    makeAll
fi

if [ $1 == "clean" ]
then
    clean
fi

