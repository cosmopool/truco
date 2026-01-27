#include <stdio.h>

int _log(const char* header, const char *msg) {
  return printf("--- [%s] %s\n", header, msg);
}

int _logInfo(char *msg) {
  return _log("INFO", msg);
}

int _logDebug(char *msg) {
  return _log("DEBUG", msg);
}
