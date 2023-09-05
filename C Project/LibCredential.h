#include "credentials.h"

void saveCredentials(const char *filename, const struct Credentials *creds);
int findCredentials(const char *filename, const char *targetWebsite, struct Credentials *result);
int updateCredentials(const char *filename, const char *targetWebsite, char *newPassword) ;