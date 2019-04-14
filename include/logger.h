#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum OutputType {
  LOGGER_STDOUT = 0x000001,
  LOGGER_FILE = 0x000010,
} OutputTypeEnum;

typedef struct LOGGER_STRUCTURE {
  void (*Dispose) ();
  void (*Info) (const char* Format, ...);
  void (*Debug) (const char* Format, ...);
  void (*Error) (const char* Function, int Line, const char* Format, ...);
  void (*Warning) (const char* Format, ...);

  int LoggerOutput;
  FILE* File;
} LOGGER;

int Logger_New(int LoggerOutput);

extern LOGGER* Logger;
#endif
