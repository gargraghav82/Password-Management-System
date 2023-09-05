#include <stdio.h>
#include <string.h>
#include "credentials.h"


int doesWebsiteExist(const char *filename, const char *website) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0; // Assume it doesn't exist in case of an error
    }

    struct Credentials creds;
    while (fscanf(file, "%s %s", creds.website, creds.password) == 2) {
        if (strcmp(creds.website, website) == 0) {
            fclose(file);
            return 1; // Website with the same name exists
        }
    }

    fclose(file);
    return 0; // Website with the same name does not exist
}

void saveCredentials(const char *filename, const struct Credentials *creds) {
    if (doesWebsiteExist(filename, creds->website)) {
        printf("Website with the same name already exists. Please choose a different name.\n");
        return;
    }

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s %s\n", creds->website, creds->password);
    fclose(file);
}


