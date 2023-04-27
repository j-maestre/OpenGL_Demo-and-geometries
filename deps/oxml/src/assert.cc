#include <stdio.h>
#include <stdlib.h>

#include <oxml/assert.h>

void _oxml_assert(const char* expression, const char* message, const char* file, const char* function, unsigned int line) {
  printf("\x1b[34m======================================\x1b[0m");
  printf("\n\n\x1b[31mAssertion falied!!\x1b[0m\n");
  printf("Message: %s\n", message);
  printf("Expression: \x1b[0m <\x1b[36m%s\x1b[0m>\n", expression);
  printf("Assertion ocurred in: \nFILE: <\x1b[35m%s\x1b[0m>\nFUNCTION: \x1b[35m%s\x1b[0m\nLINE: \x1b[35m%d\x1b[0m\n\n", file, function, line);
  printf("\x1b[34m======================================\x1b[0m");
  abort();
}

void _oxml_static_assert(bool expression, const char* message, const char* file, const char* function, unsigned int line) {
  if (expression) {
    return;
  }
  printf("\x1b[34m======================================\x1b[0m");
  printf("\n\n\x1b[31mAssertion falied!!\x1b[0m\n");
  printf("Message: %s\n", message);
  printf("Assertion ocurred in: \nFILE: <\x1b[35m%s\x1b[0m>\nFUNCTION: \x1b[35m%s\x1b[0m\nLINE: \x1b[35m%d\x1b[0m\n\n", file, function, line);
  printf("\x1b[34m======================================\x1b[0m");
  abort();
}
