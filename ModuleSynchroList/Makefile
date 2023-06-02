CC = gcc
CFLAGS = -Wall
SRC_DIR = src
OBJ_DIR = obj

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/tools.c $(SRC_DIR)/copy_list.c $(SRC_DIR)/synchro_list.c
    $(CC) $(CFLAGS) -c $< -o $@

app: $(OBJ_DIR)/main.o $(OBJ_DIR)/tools.o $(OBJ_DIR)/copy_list.o $(OBJ_DIR)/synchro_list.o
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(OBJ_DIR)/*.o app