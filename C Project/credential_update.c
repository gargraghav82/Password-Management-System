#include "credentials.h"
#include <stdio.h>
#include <string.h>

int updateCredentials(const char *filename, const char *targetWebsite, char *newPassword) {
    // Open the file for reading and writing
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    struct Credentials creds;
    struct Credentials newCreds;

    // Loop through the file to find and update the matching website
    while (fscanf(file, "%s %s", creds.website, creds.password) == 2) {
        if (strcmp(creds.website, newCreds.website) == 0) {
            // Found a matching website, update the password
            fseek(file, -strlen(creds.password) - 1, SEEK_CUR);
            fprintf(file, "%s %s\n", creds.website, newCreds.password);
            fclose(file);
            return 1;
        }
    }

    // If the website doesn't exist, append the new credentials
    fprintf(file, "%s %s\n", newCreds.website, newCreds.password);
    fclose(file);
    return 1;
}

