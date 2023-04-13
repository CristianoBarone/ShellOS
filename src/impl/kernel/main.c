#include "stdprint.h"

#define os_ver "1.0 ("

char *throbber = "|/-|/-\\";

void throb(int* i) {
    stdprint_char(throbber[*i++]);
    stdprint_raw_colstepback();
    *i>7?i=0:0;
}

void kernel_main() {
    stdprint_clear();
    stdprint_set_colour(0b1111, 0b0000);
    stdprint_string("ShellOS v");
    stdprint_string(os_ver);
    stdprint_string(__TIMESTAMP__);
    stdprint_char(')');
    stdprint_newline();
    stdprint_string("Mounting filesystem...");
    stdprint_newline();
    int i = 0;
    throb(&i);

    stdprint_string("Checking autorun...");
    stdprint_newline();
    throb(&i);
}
