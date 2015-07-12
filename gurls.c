#include <stdio.h>
#include <regex.h>

#define HOSTCHARS "[a-z0-9._+-]"
#define PATHCHARS "[a-z0-9._+#=?&:;%/!,~-]"

static const char* url_re =
  "(http|https)://"
  "(" HOSTCHARS "+(:" HOSTCHARS "+)?@)?"
  HOSTCHARS "+\\.[a-z]+"
  "(/" PATHCHARS "*)?";

int main() {
  char buffer[BUFSIZ];

  regex_t url;
  regmatch_t match[1];

  int c = regcomp(&url, url_re, REG_EXTENDED | REG_ICASE);
  if (c != 0) {
    return -1;
  }

  while (fgets(buffer, BUFSIZ-1, stdin)) {
    buffer[BUFSIZ-1] = 0;

    if (regexec(&url, buffer, 1, match, REG_NOTBOL | REG_NOTEOL) == 0) {
      printf(
          "%.*s\n",
          match[0].rm_eo - match[0].rm_so,
          buffer + match[0].rm_so);
    }
  }

  return 0;
}
