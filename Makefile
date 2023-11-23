TARGET = bitzer
CC = g++
CFLAGS = -std=c++14 -m64 -g -Wall

SRC = src/
OBJ = obj/
BIN = bin/

INCLUDE = 
LINK = 
LIB = 

SRCS = $(wildcard $(SRC)*.cpp) 
OBJS = $(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(SRCS))
HDRS = $(wildcard $(SRC)*.h)

.PHONY: all clean

$(BIN)$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(INCLUDE) $(LINK) $(LIB)

$(OBJ)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) $(SRC) -c $< -o $@ $(INCLUDE) $(LINK) $(LIB)

run: $(BIN)$(TARGET)
	@$(BIN)$(TARGET)

clean:
	rm $(BIN)$(TARGET)
	rm $(OBJS)
