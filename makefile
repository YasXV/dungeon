HEADER = fichiers_h
SRC_DIR = fichiers_c
OBJ_DIR = fichiers_o
BIN_DIR = .

SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

MAIN_SRC = main.c

MAIN_OBJ = $(OBJ_DIR)/main.o

donjon: $(OBJS) $(MAIN_OBJ)
	gcc $^ -o $(BIN_DIR)/$@ -lm
	$(BIN_DIR)/$@
	rm $(OBJ_DIR)/*.o
	rm $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -o $@ -c $< -I$(HEADER)

$(MAIN_OBJ): $(MAIN_SRC)
	gcc -o $@ -c $< -I$(HEADER)