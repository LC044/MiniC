int a, b[2][5][3];
int add(int a_, int b)
{
    int v;
    a = a * 2 + b * 2;
    if (a++ + 1 > b + 1 || b < 2) {
        b = 2;
    } else {
        b = 3;
    }
    return v + 1;
}
int ght;