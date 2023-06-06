// int ifWhile()
// {
// 	int a;
// 	a = 0;
// 	int b;
// 	b = 3;
// 	if (a == 5) {
// 		while (b == 2) {
// 			b = b + 2;
// 		}
// 		b = b + 25;
// 	} else
// 		while (a < 5) {
// 			b = b * 2;
// 			a = a + 1;
// 		}
// 	return (b);
// }


// int main()
// {
// 	return (ifWhile());
// }
int main()
{
	int a[4][2];
	int b[4][2];
	int c[4][2];
	int d[4][2];
	int e[4][2][1];
	int i;
	i = 1;
	a[2][0] = 7;
	d[3][0] = a[3][0];
	d[2][1] = 1;
	// e[0][i + 1][0] = d[2][1];
	e[0][i][0] = 0;
	e[3][1][0] = 5;

	return e[1 * 2][1][0] + e[0][0][0] + e[0][1][0] + d[3][0];
}

