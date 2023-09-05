#include "credentials.h"
#include <stdio.h>
#include <string.h>

int findCredentials(const char *filename, const char *targetWebsite, struct Credentials *result) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0; // File not found or unable to open
    }

    while (fscanf(file, "%s %s", result->website, result->password) == 2) {
        if (strcmp(result->website, targetWebsite) == 0) {
            fclose(file);
            return 1; // Website found
        }
    }

    fclose(file);
    return 0; // Website not found
}
