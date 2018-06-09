clear;

TRACE_FILE=trace

export MALLOC_TRACE=$PWD/$TRACE_FILE

if gcc test.c lib/plog.c -g -o main -std=c11 -lpthread; then
  ./main $1 $2 $3
else
  echo -n -e "Some error while compiling\n"
fi;
