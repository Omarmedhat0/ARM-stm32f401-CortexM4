
/*
 ============================================================================
 Name        : log.c
 Author      : Omar Medhat Mohamed
 Description : Source file for the LOG driver
 Date        : 29/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes                                    *
 *******************************************************************************/
#include "log.h"

/*******************************************************************************
 *                             Implementation                                   *
 *******************************************************************************/

/*
 * @brief    : Set output channel for logging.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: channel The output channel(s) to be set. It can be LOG_OUT_CONSOLE, LOG_OUT_FILE, or LOG_OUT_CONSOLE_AND_FILE.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function sets the output channel(s) for logging.
 */
int log_setoutput_channel(log_channel_t *channel_info, int channel)
{
    /* Initialize channel type */
    channel_info->channel_type = 0;

    /* Set the output channel */
    channel_info->channel_type |= channel;

    return 0; /* Return 0 for success */
}

/*
 * @brief    : Configure log file for writing.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: FileName Pointer to the file name string.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function configures the log file for writing.
 */
int log_FileCFG(log_channel_t *channel_info, char *FileName)
{
    /* Open the log file in write mode */
    FILE *fPtr = fopen(FileName, "w");
    if (fPtr == NULL)
    {
        /* Print error message if unable to open file */
        printf("Error: Unable to open log file for writing.\n");
        return -1; /* Return -1 for failure */
    }
    
    /* Assign the file name to the channel info */
    channel_info->file_name = FileName;

    /* Close the file */
    fclose(fPtr);

    return 0; /* Return 0 for success */
}

/*
 * @brief    : Write a log message.
 * @param[in]: channel_info Pointer to the log_channel_t structure.
 * @param[in]: Serverity_Level Severity level of the log message (INFO, ERROR, WARNING, CRITICAL).
 * @param[in]: msg Pointer to the format string for the log message.
 * @param[in]: ... Additional arguments for formatting the log message.
 * @return   : 0 for success, -1 for failure.
 * @details  : This function writes a log message to the console and/or log file.
 */
int log_write(log_channel_t *channel_info, int Serverity_Level, const char *msg , ...)
{
    /* Get the current time */
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Buffer to store the formatted time */
    char timeStr[64]; /* Adjust size as needed */
    if (strftime(timeStr, sizeof(timeStr), "%a %b %d %H:%M:%S %Y", timeinfo) == 0) {
        /* Print error message if unable to format time */
        printf("Error formatting time.\n");
        return -1; /* Return -1 for failure */
    }

    /* Format the severity level */
    char severityStr[10] = "";
    switch (Serverity_Level)
    {
        case INFO:
            strcpy(severityStr, "INFO");
            break;
        case ERROR:
            strcpy(severityStr, "ERROR");
            break;
        case CRITICAL:
            strcpy(severityStr, "CRITICAL");
            break;
        case WARNING:
            strcpy(severityStr, "WARNING");
            break;
        default:
            strcpy(severityStr, "UNKNOWN");
            break;
    }

    /* Format the log message */
    char argMsg[256]; /* Adjust size as needed */
    va_list args;
    va_start(args, msg);
    vsnprintf(argMsg, sizeof(argMsg), msg, args);
    va_end(args);
    char formattedMsg[256]; /* Adjust size as needed */
    snprintf(formattedMsg, sizeof(formattedMsg), "[%s] [%s] : %s\n", timeStr, severityStr, argMsg);

    /* Check if logging to console is enabled */
    if ((channel_info->channel_type == LOG_OUT_CONSOLE) || (channel_info->channel_type == LOG_OUT_CONSOLE_AND_FILE))
    {
        /* Print the message to console */
        printf("%s", formattedMsg);
    }

    /* Check if logging to file is enabled */
    if ((channel_info->channel_type == LOG_OUT_FILE) || (channel_info->channel_type == LOG_OUT_CONSOLE_AND_FILE))
    {
        /* Check if file name is provided */
        if (channel_info->file_name != NULL)
        {
            /* Open the log file in append mode */
            FILE *file = fopen(channel_info->file_name, "a");
            if (file != NULL)
            {
                /* Write the message to the file */
                fprintf(file, "%s", formattedMsg);

                /* Close the file */
                fclose(file);
            }
            else
            {
                perror("Error opening log file");
                /* You might want to log this error to console as well if possible */
            }
        }
        else
        {
            printf("Error: File name is missing for file logging.\n");
            /* You might want to log this error to console as well if possible */
        }
    }

    return 0; /* Return 0 for success */
}
