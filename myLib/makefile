# Compilador e flags
CC = gcc
CFLAGS = -Wall -fPIC -I$(INCLUDE_DIR)
LDFLAGS = -lcurl -ljansson

# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
TEST_DIR = test

# Alvo principal
TARGET = $(BUILD_DIR)/libmyLib.so

# Arquivos fonte e objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Regras principais
all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	$(CC) -o $(TEST_DIR)/test $(TEST_DIR)/main.c -L$(BUILD_DIR) -lmyLib $(LDFLAGS) -I$(INCLUDE_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) $(TEST_DIR)/test

