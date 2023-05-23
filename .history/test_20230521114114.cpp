#include<stdio.h>
int main(int argc, char **argv)
{
    char st[2][] = {
        "int","void",
    };
    for (int i = 0; i < 2;i++) {
        printf("%s\n", st[i]);
    }
    return 0;
}