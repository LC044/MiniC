#include<stdio.h>
#include<string.h>
int add(int a, int b)
{
    return a + b;
}
int main(int argc, char **argv)
{
    char st[20] = "int";
    int a = 4, b, c;
    a = c = 2;
    a = add(a, c);
    printf("a = %d, b = %d", a, strcmp(st, "int"));
    return 0;
}