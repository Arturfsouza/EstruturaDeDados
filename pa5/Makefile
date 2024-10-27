# Compilador e flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# Pastas
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# Arquivo executável
TARGET = pa5.out

# Fontes e objetos
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

# Regra para gerar arquivos objeto (.o) a partir dos arquivos fonte (.cpp)
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Regra principal para gerar o executável final
all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

# Regra para limpar os arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*
