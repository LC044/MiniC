//test array define
int main()
{
    int a[4][2];
    int b[4][2];
    int c[4][2];
    int d[4][2];
    int e[4][2];

    a[2][0] = 1;
    b[2][0] = 11;
    c[2][0] = 22;
    d[2][0] = 33;
    e[0][0] = 2;
    e[0][1] = 3;
    e[3][1] = 4;

    return e[3][1] + e[0][0] + e[0][1] + a[2][0];
}