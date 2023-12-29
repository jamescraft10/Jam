#include <stdio.h>

int main(void) {
    int a = 0;
    // printf("abc" + a); a does not work
    printf("abc%d",a); // works
    return 0;
}