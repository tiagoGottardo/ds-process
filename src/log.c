#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>



#include "../include/Log.h"

void logErro(char* functionName,char * errorBody);
void initLogFile(const char * fileName);

void logMessage(const char *fileName, const char *format, ...) {
  
  // Verificar se o arquivo existe
  struct stat buffer;
  int fileExists = (stat(fileName, &buffer) == 0);

  if(!fileExists){
    initLogFile(fileName);
  }

  FILE *logFile = fopen(fileName, "a");
  if (logFile == NULL) {
    logErro("log_logmessage","ERRO: não foi possível abrir o arquivo de LOG");
    return;
  }

  // Escrever a mensagem formatada no arquivo de log
  va_list args;
  va_start(args, format);
  vfprintf(logFile, format, args);
  //vprintf(format, args);
  va_end(args);

  // Adicionar uma quebra de linha
  fprintf(logFile, "\n");

  // Fechar o arquivo de log
  fclose(logFile);
}

void logErro(char* functionName,char * errorBody){
  logMessage("log/log.txt","[ERRO] A função [%s] retornou erro: \n[ERRO]:{%s}", functionName, errorBody);
}

void logParserFunctions(char * functionName){
  logMessage("O arquivo de entrada foi lido e chamou a função %s", functionName); 
}

void initLogFile(const char * fileName){
  FILE *logFile = fopen(fileName, "w");
  if (logFile == NULL) {
    logErro("log_initlogfile", "ERRO: Não foi possível criar arquivo de log, o programa tem permição para isso?");
    return;
  }

  fprintf(logFile, "[Início do arquivo de Log]\n");
  fclose(logFile);
}

void initLog(){
    initLogFile("log/log.txt");
    initLogFile("log/AVL.txt");
    initLogFile("log/hash1.txt");
    initLogFile("log/hash2.txt");
    initLogFile("log/hash3.txt");
    initLogFile("log/heap.txt");
}
