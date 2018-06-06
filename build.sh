# clear;

if gcc main.c -o main -std=c11 -lpthread -lGL -lglfw; then
  ./main $1 $2 $3
else
  echo -n -e "Some error while compiling\n"
fi;
