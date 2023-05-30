// Leonardo Reis da Silva

#pragma once

#define SINGLE_LINE_COMMENT 300
#define ENTER_MULTI_LINE_COMMENT 301
#define EXIT_MULTI_LINE_COMMENT 302

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