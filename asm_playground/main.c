#include <stdio.h>
int foo = 0;
int bar = 0;

int a = 1.1;
int x = 0;
int main() {
    foo = 125;

    if (a) {
        x = 111;
    } else {
        x = 222;
    }

    bar = 250;
    return 12;
}