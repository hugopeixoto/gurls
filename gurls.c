#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define HOSTCHARS "[a-z0-9._+-]"
#define PATHCHARS "[a-z0-9._+#=?&:;%/!,~-]"

static const char* url_re =
  "(http|https)://"
  "(" HOSTCHARS "+(:" HOSTCHARS "+)?@)?"
  HOSTCHARS "+\\.[a-z]+"
  "(/" PATHCHARS "*)?";

char* fmgets (FILE* fp) {
  int size = BUFSIZ;
  char* buffer = malloc(size);
  int offset = 0;

  while (fgets(buffer + offset, BUFSIZ, fp)) {
    size += BUFSIZ;
    buffer = realloc(buffer, size);
    offset = strlen(buffer);

    if (buffer[offset - 1] == '\n') {
      break;
    }
  }

  if (!offset) {
    buffer = realloc(buffer, 0);
  }

  return buffer;
}

int main() {
  regex_t url;
  regmatch_t match[1];

  int c = regcomp(&url, url_re, REG_EXTENDED | REG_ICASE);
  if (c != 0) {
    return -1;
  }

  char* buffer = NULL;

  while ((buffer = fmgets(stdin))) {
    char* ptr = buffer;

    while (regexec(&url, ptr, 1, match, REG_NOTBOL | REG_NOTEOL) == 0) {
      printf(
          "%.*s\n",
          match[0].rm_eo - match[0].rm_so,
          ptr + match[0].rm_so);

      ptr += match[0].rm_eo;
    }

    free(buffer);
  }

  return 0;
}
