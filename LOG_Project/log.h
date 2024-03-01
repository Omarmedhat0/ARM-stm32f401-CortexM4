#ifndef LOG_H
#define LOG_H

#include <stdarg.h> /* Library for variable argument lists */
#include <stdio.h>  /* Standard input/output library */
#include <stdlib.h> /* Standard library */
#include <time.h>   /* Time library */
#include <string.h> /* String manipulation library */

/* Define log output channels */
#define LOG_OUT_CONSOLE           0x1
#define LOG_OUT_FILE              0x2
#define LOG_OUT_CONSOLE_AND_FILE  0x3
#define CRITICAL                  0x4
#define ERROR                     0x5
#define WARNING                   0x6
#define INFO                      0x7

/* Define log channel structure */
typedef struct  {
    int channel_type; /* Channel type: Console, File, or both */
    char* file_name;  /* File name for logging */
} log_channel_t;

/* Function prototypes */

/*
 * @brief    : Set output channel for logging.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: channel The output channel(s) to be set. It can be LOG_OUT_CONSOLE, LOG_OUT_FILE, or LOG_OUT_CONSOLE_AND_FILE.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function sets the output channel(s) for logging.
 */
int log_setoutput_channel(log_channel_t *channel_info, int channel);

/*
 * @brief    : Configure log file for writing.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: FileName Pointer to the file name string.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function configures the log file for writing.
 */
int log_FileCFG(log_channel_t *channel_info, char *FileName);

/*
 * @brief    : Write a log message.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: Serverity_Level Severity level of the log message (INFO, ERROR, WARNING, CRITICAL).
 * @param[in]: msg Pointer to the format string for the log message.
 * @param[in]: ... Additional arguments for formatting the log message.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function writes a log message to the console and/or log file.
 */
int log_write(log_channel_t *channel_info, int Serverity_Level, const char *msg , ...);

#endif /* LOG_H */
