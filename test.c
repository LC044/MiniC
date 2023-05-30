int a, b[2][5][3];
int add(int a, int b)
{
    int v;
    v = a + b;
    a = a * 2;
    b = a / b;
    v = b % 2;
    return v + 1;
}
int ght;