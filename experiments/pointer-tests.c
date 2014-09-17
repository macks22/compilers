#include <stdio.h>
#include <string.h>

int main()
{
    char *test = "hello";

    printf("\nvalue of `test`:   %s\n", test);
    printf("sizeof(test):      %i\n", (int)sizeof(test));
    printf("sizeof(char *):    %i\n", (int)sizeof(char *));
    printf("strlen(test):      %i\n", (int)strlen(test));
    printf("\n");

    printf("value of  `*test`: %i\n", *test);
    printf("ord('h'):          %i\n", (int)'h');
    printf("sizeof(*test):     %i\n", (int)sizeof(*test));
    printf("sizeof(char):      %i\n", (int)sizeof(char));
    printf("\n");

    printf("value of  `&test`: %p\n", &test);
    printf("sizeof(&test):     %i\n", (int)sizeof(&test));
    printf("sizeof(void *):    %i\n", (int)sizeof(void *));
}
