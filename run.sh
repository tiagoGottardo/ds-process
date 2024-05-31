#!/bin/bash

# Nome do projeto
PROJECT_NAME="dsprocess"

# Diretórios
INCLUDE_DIR="include"
SRC_DIR="src"
BUILD_DIR="build"

# Verificar se a pasta build existe, se não, criar
if [ ! -d "$BUILD_DIR" ]; then
  echo "Criando diretório de build..."
  mkdir "$BUILD_DIR"
fi

# Compilar os arquivos .c em objetos .o
echo "Compilando arquivos .c..."
for file in $SRC_DIR/*.c; do
  # Extrair o nome do arquivo sem extensão
  filename=$(basename "$file" .c)
  # Compilar o arquivo .c em um objeto .o
  gcc -c "$file" -I"$INCLUDE_DIR" -o "$BUILD_DIR/$filename.o"
done

# Linkar os objetos .o para criar o executável
echo "Linkando objetos para criar o executável..."
gcc "$BUILD_DIR"/*.o -o "$BUILD_DIR/$PROJECT_NAME"

# Mensagem de sucesso
echo "Build concluído com sucesso! O executável está em $BUILD_DIR/$PROJECT_NAME"
