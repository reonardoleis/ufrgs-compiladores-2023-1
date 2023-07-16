#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


void debug_printf(const char *str, ...);
void debug_printf(const char *str, ...) {
    char * debug = getenv("DEBUG");
    if (debug != NULL && strcmp(debug, "1") == 0) {
        va_list args;
        va_start(args, str);

        char* green_color = "\033[0;32m";
        char* color_end = "\033[0m";
        char* preffix = "[DEBUG] ";
        char* suffix = "\n";
        char* new_str = (char*)calloc(strlen(green_color) + strlen(preffix) + strlen(str) + strlen(suffix) + strlen(color_end) + 1, sizeof(char));
        strcpy(new_str, green_color);
        strcat(new_str, preffix);
        strcat(new_str, str);
        strcat(new_str, suffix);
        strcat(new_str, color_end);

        vfprintf(stderr, new_str, args);
        va_end(args);
    }
}