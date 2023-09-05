#include <string.h>
#include <ctype.h>

int isStrongPassword(const char *password) {
    int length = strlen(password);
    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigit = 0;
    int hasSpecialChar = 0;

    for (int i = 0; i < length; i++) {
        char c = password[i];
        if (isupper(c)) {
            hasUppercase = 1;
        } else if (islower(c)) {
            hasLowercase = 1;
        } else if (isdigit(c)) {
            hasDigit = 1;
        } else if (ispunct(c) || c == ' ') {
            hasSpecialChar = 1;
        }
    }

    // Check if all criteria are met
    if (length >= 8 && hasUppercase && hasLowercase && hasDigit && hasSpecialChar) {
        return 1; // Strong password
    } else {
        return 0; // Weak password
    }
}
