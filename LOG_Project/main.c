
 /*============================================================================
 Name        : Main.c
 Author      : Omar Medhat Mohamed
 Description : Example for the LOG driver
 Date        : 29/2/2024
 ============================================================================*/

/*******************************************************************************
 *                                Includes                                    *
 *******************************************************************************/
#include <stdio.h>   /* Standard input/output library */
#include <stdlib.h>  /* Standard library */
#include "log.h"     /* Include the custom logging library */

/*******************************************************************************
 *                             Implementation                                   *
 *******************************************************************************/
int main() {
    // Create a log_channel_t object
    log_channel_t channel_info;

    // Set output channels (console and file)
    log_setoutput_channel(&channel_info, LOG_OUT_CONSOLE_AND_FILE);

    // Configure file logging
    log_FileCFG(&channel_info, "log.txt");

    // Input variables
    int a, b;
    printf("Enter two integers (a and b): ");
    fflush(stdout);
    scanf("%d %d", &a, &b);

    // Perform division
    float result;
    int severity;

    if (b == 0) {
        // Error: Division by zero
        severity = ERROR;
        result = 0;
        log_write(&channel_info, severity, "Error: Division by zero. Result set to 0.");
    } else {
        // Divide a by b
        result = (float)a / b;
        if ((int)result == result) {
            // Integer result
            severity = INFO;
            log_write(&channel_info, severity, "Integer result: %d / %d = %d", a, b, (int)result);
        } else {
            // Floating-point result
            severity = WARNING;
            log_write(&channel_info, severity, "Floating-point result: %d / %d = %.2f", a, b, result);
        }
    }

    // Additional condition based on the result and operands
    if (a == 0 && b == 0) {
        severity = CRITICAL;
        log_write(&channel_info, severity, "Both operands are zero.");
    }

    return 0;
}
