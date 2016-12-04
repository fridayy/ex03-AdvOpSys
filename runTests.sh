#!/usr/bin/env bash
RED='\033[0;31m'
NC='\033[0m'
make clean
make
./bin/TestOpen
printf "\n${RED}######################################\n${NC}"
./bin/TestRead
printf "\n${RED}######################################\n${NC}"
./bin/TestWrite
printf "\n${RED}######################################\n${NC}"
make clean