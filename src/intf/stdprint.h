#pragma once

#include <stdint.h>
#include <stddef.h>

void stdprint_clear();
void stdprint_clear_row(size_t row);
void stdprint_raw_colstepback();
void stdprint_newline();
void stdprint_char(char character);
void stdprint_string(char* string);
void stdprint_set_colour(uint8_t foreground, uint8_t background);
