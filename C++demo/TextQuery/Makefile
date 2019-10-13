CC = g++
DIR_INC = ./include
CFLAGS = -std=c++11 -g -O2 -Wall -I${DIR_INC}
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

ALL: textquery	
textquery: text_query.o main.o
	${CC} ${CFLAGS} text_query.o main.o -o textquery
text_query.o:
	${CC} ${CFLAGS} -c text_query.cpp -o text_query.o
main.o:
	${CC} ${CFLAGS} -c main.cpp -o main.o
 
# ALL: textquery
 
# textquery: $(OBJ)
# 	${CC} ${CFLAGS} $(OBJ) -o textquery
 
# $(OBJ): $(SRC)
# 	${CC} ${CFLAGS} -c $(SRC) -o $(OBJ)