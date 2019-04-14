#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

LOGGER* Logger = NULL;

void Logger_Debug (const char* Format, ...) {
  printf("DEBUG: ");

  va_list arg;
  va_start (arg, Format);

  if (LOGGER_STDOUT & Logger->LoggerOutput) vfprintf (stdout, Format, arg);
  if (LOGGER_FILE & Logger->LoggerOutput) vfprintf (Logger->File, Format, arg);

  va_end (arg);

  printf("\n");
  return;
}

void Logger_Info (const char* Format, ...) {
  printf("INFO: ");

  va_list arg;
  va_start (arg, Format);

  if (LOGGER_STDOUT & Logger->LoggerOutput) vfprintf (stdout, Format, arg);
  if (LOGGER_FILE & Logger->LoggerOutput) vfprintf (Logger->File, Format, arg);

  va_end (arg);

  printf("\n");
  return;
}

void Logger_Error (const char* Function, int Line, const char* Format, ...) {
  printf("ERROR %s.c:%d: ", Function, Line);

  va_list arg;
  va_start (arg, Format);

  if (LOGGER_STDOUT & Logger->LoggerOutput) vfprintf (stdout, Format, arg);
  if (LOGGER_FILE & Logger->LoggerOutput) vfprintf (Logger->File, Format, arg);

  va_end (arg);

  printf("\n");
}

void Logger_Warning (const char* Format, ...) {
  printf("WARNING: ");

  va_list arg;
  va_start (arg, Format);

  if (LOGGER_STDOUT & Logger->LoggerOutput) vfprintf (stdout, Format, arg);
  if (LOGGER_FILE & Logger->LoggerOutput) vfprintf (Logger->File, Format, arg);

  va_end (arg);

  printf("\n");
}

void Logger_Dispose() {
  if (Logger != NULL) {
    free(Logger);
    Logger = NULL;
  }
}

static void Logger_SetOutputType(int LoggerOutput) {
  Logger->Info("Logger_SetLoggerOutput Begins\n");

  FILE* File = NULL;

  if (LOGGER_STDOUT & LoggerOutput) {
    Logger->LoggerOutput |= LOGGER_STDOUT;
  }

  if (LOGGER_FILE & LoggerOutput) {
    File = fopen("./mouse-posyx.log", "a+");

    if (File == NULL) {
      Logger->Warning("Error to open mouse-posyx.log file. Using stdout as default");  
      Logger->LoggerOutput = LOGGER_STDOUT;

      goto FINISH;
    }

    Logger->File = File;

    Logger->LoggerOutput |= LOGGER_FILE;
  }

FINISH:
  Logger->Info("Logger_SetOutputType Finished\n");
  return;
}

int Logger_New(int LoggerOutput) {
  int Status = 0;

  if (Logger != NULL) {
    Logger->Warning("You are trying to allocate Logger Library again!");
    goto FINISH;
  }

  Logger = calloc(1, sizeof(LOGGER));
  if (Logger == NULL) {
    printf("ERROR: Allocate Logger data strucuture failed\n");
    Status = -1;
    goto FINISH;
  }

  Logger->File = NULL;
  Logger->Dispose = Logger_Dispose;
  Logger->Info = Logger_Info;
  Logger->Debug = Logger_Debug;
  Logger->Error = Logger_Error;
  Logger->Warning = Logger_Warning;

  Logger_SetOutputType(LoggerOutput);

FINISH:
  if (Logger != NULL) Logger->Info("Logger ready");

  return Status;
}
