# clear;

if gcc test.c -o test -std=c11 -lpthread -lGL -lglfw; then
  ./test $1 $2 $3
else
  echo -n -e "Some error while compiling\n"
fi;
