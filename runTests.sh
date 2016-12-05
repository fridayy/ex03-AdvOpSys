#!/usr/bin/env bash
RED='\033[0;31m'
NC='\033[0m'
make clean
make
printf "\n${RED}############ TEST OPEN() ################\n${NC}"
./test/bin/TestOpen
printf "\n${RED}############ TEST READ() ################\n${NC}"
./test/bin/TestRead
printf "\n${RED}############ TEST WRITE() ################\n${NC}"
./test/bin/TestWrite
printf "\n${RED}############ TEST LSEEK() ################\n${NC}"
./test/bin/TestLseek
printf "\n${RED}############ TEST MMAP() ################\n${NC}"
./test/bin/TestMmap
printf "\n${RED}############ TEST CLOSE() ################\n${NC}"
./test/bin/TestClose
printf "\n${RED}############ FINISHED CLEANING UP ################\n${NC}"
make clean