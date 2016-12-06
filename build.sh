#!/usr/bin/env bash
RED='\033[0;31m'
NC='\033[0m'
printf "${RED}>> MAKE ALL\n${NC}"
make clean
printf "${RED}>> MAKE\n${NC}"
make
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
printf "\n${RED}>> EXERCISE 2.8 TESTS\n${NC}"
printf "\n${RED}>> TEST READCHAR() \n${NC}"
./bin/TestReadchar_R
printf "\n${RED}>> TEST COUNTM() \n${NC}"
./bin/TestCount_M
printf "\n${RED}>> SHELL TESTS\n${NC}"
printf "\n${RED}>> TEST DIRECTORY OPERTIONS \n${NC}"
./bin/TestDirectoryOperation
printf "\n${RED}>> TEST FILE OPERTIONS \n${NC}"
./bin/TestFileOperation
printf "\n${RED}>> TEST PATH OPERTIONS \n${NC}"
./bin/TestPathOperation
printf "\n${RED}>>FINISHED CLEANING UP \n${NC}"
make clean