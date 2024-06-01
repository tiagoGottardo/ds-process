#ifndef LOG_H
#define LOG_H

void initLogFile(const char * fileName);
void logErro(char* functionName,char * errorBody);
void logMessage(const char *filename,const char *format, ...);
void initLog();

#endif