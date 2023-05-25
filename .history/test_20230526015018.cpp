#include<stdio.h>
int add(int a, int b)
{
    return a + b;
}
int main(int argc, char **argv)
{
    char st[20] = "hello world";
    int a = 4, b, c;
    a = c = 2;
    add(a, c)++;
    printf("a = %d, b = %d", a, b);
    return 0;
}