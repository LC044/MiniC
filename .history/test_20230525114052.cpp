#include<stdio.h>
int main(int argc, char **argv)
{
    char st[20] = "hello world";
    for (int i = 0; i < 2;i++) {
        printf("%s\n", st[i]);
    }
    return 0;
}