#!/bin/bash

TRACE_FILE=trace

MAIN_APP=main

######## COLORS ########
RED_BOLD='\e[1;31m'
GREEN_BOLD='\e[1;32m'
END_LINE='\e[0m\n'
########################

export MALLOC_TRACE=$PWD/$TRACE_FILE

function build {
  if gcc test.c lib/plog.c -g -o $MAIN_APP -std=c11 -lpthread; then
    echo -ne "${GREEN_BOLD}Compil ok${END_LINE}"
  else
    echo -ne "${RED_BOLD}Some error while compiling${END_LINE}"
    exit 1
  fi;
}

function run_valgrind {
  check_valgrind
  build
  valgrind --leak-check=yes ./$MAIN_APP
}

function check_valgrind {
  if [ -z valgrind ]; then
    echo -ne "${RED_BOLD}For continue you need to install valgrind!"
    exit 1
  fi;
}

function help {
  echo "
Usage:
  build: Run build app
  valgrind: Run build and valgrind memcheck
  help: Show this help
  "
}

case $1 in
  'valgrind')
    run_valgrind
  ;;
  'build')
    build
  ;;
  'help')
    help
  ;;
  *)
    help
  ;;
esac
