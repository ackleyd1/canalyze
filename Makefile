SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -g -march=armv7-a+simd
OBJS := $(OBJ_DIR)/main.o 

$(BIN_DIR)/canalyze: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
	
.PHONY : clean test debug lint install
