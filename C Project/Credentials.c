#include <stdio.h>
#include "LibCredential.h"

void encrypt(char password[] , int key){
    for(int i = 0 ; i < strlen(password) ; i++){
        //password[i] += key;
    }
}

void decrypt(char password[] , int key){
    for(int i = 0 ; i < strlen(password) ; i++){
        //password[i] -= key;
    }
}


// Function to update the password for a specific website
int updatePassword(const char *filename, const char *targetWebsite, char *newPassword)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0; // File not found or unable to open
    }

    struct Credentials creds;
    struct Credentials updatedCreds;
    int found = 0;
    encrypt(newPassword , 0XAED);

    // Create a temporary file to store the updated data
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error creating temporary file");
        fclose(file);
        return 0;
    }

    while (fscanf(file, "%s %s", creds.website, creds.password) == 2)
    {
        if (strcmp(creds.website, targetWebsite) == 0)
        {
            strcpy(updatedCreds.website, creds.website);
            strcpy(updatedCreds.password, newPassword);
            fprintf(tempFile, "%s %s\n", updatedCreds.website, updatedCreds.password);
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%s %s\n", creds.website, creds.password);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Rename the temporary file to the original filename
    if (rename("temp.txt", filename) != 0)
    {
        perror("Error updating file");
        return 0;
    }

    return found; // Return 1 if the website was found and updated, 0 otherwise
}


int main()
{
    char masterPassword[50];
    printf("Enter the master password: ");
    scanf("%s" , masterPassword);
    if (strcmp(masterPassword, "your_master_password") != 0)
    {
        printf("Access denied. Incorrect master password.\n");
        return 1;
    }

    printf("Welcome\n");
    printf("Enter 0 for storing new website and password\n");
    printf("Enter 1 for retrieve password for given website\n");
    printf("Enter 2 for updating the password for given website\n");

    int input;
    scanf("%d", &input);
    struct Credentials myCreds;
    struct Credentials retrievedCreds;

    if (input == 0)
    {

        // Take user input for website and password
        printf("Enter website: ");
        scanf("%s", myCreds.website);

        printf("Enter password: ");
        scanf("%s" , myCreds.password);

        while(!isStrongPassword(myCreds.password)) {
        printf("Password is weak. Please use a stronger password Enter New password : .\n");
        scanf("%s" , myCreds.password);
    }




        // Save user input credentials to a file
        saveCredentials("credentials.txt", &myCreds);
    }
    else if (input == 1)
    {
        // Search for a specific website and retrieve its corresponding password
        printf("Enter website to retrieve password: ");
        scanf("%s", myCreds.website);

        if (findCredentials("credentials.txt", myCreds.website, &retrievedCreds))
        {
            printf("Password for Website %s: %s\n", retrievedCreds.website, retrievedCreds.password);
        }
        else
        {
            printf("Website not found.\n");
        }
    }
    else if (input == 2)
    {
        // Update the password for a specific website
        printf("Enter website to update password: ");
        scanf("%s", myCreds.website);

        printf("Enter new password: ");
        scanf("%s" , myCreds.password);

        while(!isStrongPassword(myCreds.password)) {
        printf("Password is weak. Please use a stronger password Enter New password : .\n");
        scanf("%s" , myCreds.password);
    }

        if (updatePassword("credentials.txt", myCreds.website, myCreds.password))
        {
            printf("Password for Website %s updated.\n", myCreds.website);
        }
        else
        {
            printf("Website not found or error updating password.\n");
        }
    }
    else
    {
        printf("Invalid Selection");
    }

    return 0;
}
