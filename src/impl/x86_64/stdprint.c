#include "stdprint.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t colour;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t colour = 0b1111 | 0b0000 << 4;

void stdprint_clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        colour: colour,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void stdprint_raw_colstepback() {
    col--;
}

void stdprint_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        stdprint_clear_row(i);
    }
}

void stdprint_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    stdprint_clear_row(NUM_COLS - 1);
}

void stdprint_char(char character) {
    if (character == '\n') {
        stdprint_newline();
        return;
    }

    if (col > NUM_COLS) {
        stdprint_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        colour: colour,
    };

    col++;
}

void stdprint_string(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        stdprint_char(character);
    }
}

void stdprint_set_colour(uint8_t foreground, uint8_t background) {
    colour = foreground + (background << 4);
}
