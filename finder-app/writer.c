#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog(NULL, 0, LOG_USER);

    if (argc != 3) {
        fprintf(stderr, "number of arguments doesn't match the expected value\n");
        syslog(LOG_ERR, "number of arguments doesn't match the expected value");
        return 1;
    }
    
    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Get the directory path
    char *directory = strdup(writefile);
    if (directory == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    // Find the last '/' to extract the directory path
    char *last_slash = strrchr(directory, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';  // Terminate the string to isolate the directory
    } else {
        // No directory in the path
        strcpy(directory, ".");  // Use current directory if none
    }

    // Write the string to the file
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        perror("Error: Could not create file");
        syslog(LOG_ERR, "Error: Could not create file");
        free(directory);
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    
    if (fputs(writestr, file) == EOF) {
        perror("Error: Could not write to file");
        syslog(LOG_ERR, "Error: Could not create file");
        fclose(file);
        free(directory);
        return 1;
    }

    fclose(file);
    printf("File \"%s\" created with the string: \"%s\"\n", writefile, writestr);
    free(directory);
    return 0;
}