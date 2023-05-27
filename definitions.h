#pragma once

#define SINGLE_LINE_COMMENT 300
#define MULTI_LINE_COMMENT_LINE 301

int is_running = 1;
int line_number = 1;

int getLineNumber() {
    return line_number;
}

int increment_line_number() {
    line_number++;
}

int yywrap(void) {
    is_running = 0;
    return 1;
}

int isRunning(void) {
    return is_running;
}