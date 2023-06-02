int a;
int func(int p)
{
    p = p - 1;
    return p;
}
int add()
{
    return 1 + 1;
}
int main()
{
    int b;
    a = 10;
    b = add();
    b = func(a);

    return b;
}
