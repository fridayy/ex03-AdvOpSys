#!/usr/bin/env bash
RED='\033[0;31m'
NC='\033[0m'
make clean
make
printf "\n${RED}############ TEST OPEN() ################\n${NC}"
./bin/TestOpen
printf "\n${RED}############ TEST READ() ################\n${NC}"
./bin/TestRead
printf "\n${RED}############ TEST WRITE() ################\n${NC}"
./bin/TestWrite
printf "\n${RED}############ TEST LSEEK() ################\n${NC}"
./bin/TestLseek
printf "\n${RED}############ FINISHED CLEANING UP ################\n${NC}"
make clean