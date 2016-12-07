#!/bin/bash

# Exportando as bibliotecas a serem ligadas dinamicamente
export LD_LIBRARY_PATH=./libs/:$LD_LIBRARY_PATH

# Lendo o path do arquivo de treinamento
echo "Iniciando o programa, digite o path do arquivo com as classes a serem treinadas: "
read trainingFile

./build/main $trainingFile
