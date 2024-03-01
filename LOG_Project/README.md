# Logging Driver

## Overview

This logging driver provides a simple interface for logging messages to the console and/or a file. It supports different severity levels for messages and can be configured to log to various output channels.

## Features

- Log messages to the console and/or a file
- Support for different severity levels: INFO, ERROR, WARNING, CRITICAL
- Flexible configuration options

## Usage

### 1. Include the Header File

```c
#include "log.h"
```

### 2. Initialize the Log Channel

```c
log_channel_t channel_info;
log_setoutput_channel(&channel_info, LOG_OUT_CONSOLE_AND_FILE);
log_FileCFG(&channel_info, "log.txt");
```

This initializes a log channel with both console and file output enabled. The log file is specified as `"log.txt"`.

### 3. Log Messages

```c
log_write(&channel_info, INFO, "This is an informational message.");
log_write(&channel_info, WARNING, "This is a warning message.");
log_write(&channel_info, ERROR, "This is an error message.");
```

Log messages are written using the `log_write` function. You can specify the severity level (`INFO`, `WARNING`, `ERROR`, `CRITICAL`) and the message to be logged.

### 4. Customize Output Channels

You can customize the output channels by modifying the `channel_type` field of the `log_channel_t` structure. Use the predefined macros `LOG_OUT_CONSOLE`, `LOG_OUT_FILE`, and `LOG_OUT_CONSOLE_AND_FILE` to specify the desired output channels.

### 5. Configure Log File

To configure the log file, use the `log_FileCFG` function. Provide the log channel object and the filename for the log file.

## Example

Here's a simple example demonstrating how to use the logging driver:

```c
#include <stdio.h>
#include "log.h"

int main() {
    log_channel_t channel_info;
    log_setoutput_channel(&channel_info, LOG_OUT_CONSOLE_AND_FILE);
    log_FileCFG(&channel_info, "log.txt");

    log_write(&channel_info, INFO, "This is an informational message.");
    log_write(&channel_info, WARNING, "This is a warning message.");
    log_write(&channel_info, ERROR, "This is an error message.");

    return 0;
}
```

## Dependencies

- Standard C libraries: `stdio.h`, `stdlib.h`, `time.h`, `string.h`
- Variadic functions are used, so ensure that your compiler supports them.