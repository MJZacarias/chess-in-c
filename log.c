#include <stdio.h>
#include <time.h>

void write_to_log(const char *message)
{
    FILE *logFile = fopen("log.txt", "a"); // Open file in append mode, creates if not exists

    if (logFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Get current time
    time_t rawTime;
    struct tm *timeInfo;
    char timeString[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Write date and time along with message to the file
    fprintf(logFile, "[%s] %s\n", timeString, message);

    // Close the file
    fclose(logFile);
}
