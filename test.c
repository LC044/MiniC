// int a;
// int main()
// {
// 	int a, b, c;
// 	a = -1;
// 	b = a + 5;
// 	{
// 		int a;
// 		a = 1;
// 		{
// 			a = 3;
// 			int a;
// 			a = 2;
// 		}
// 	}
// 	int t;
// 	t = 5;
// 	return t;
// }
int ifWhileTest()
{
	int a, b, c;
	int i, j;
	if (a > 0) {
		while (b < 10) {
			if (b % 2 == 1) {
				continue;
				j = 111111; //该行代码可以优化掉
			}
			b++;
		}
	} else if (a > 5 && a < 10) {
		for (i = 0;i < b;i++) {
			if (i > c) {
				break;
				j = 0x99999; //该行代码可以优化掉
			}
			c = b++;
		}
	}
	return b;
	b = b + 15; //该行代码可以优化掉
}
int main()
{
	int i;
	int a;
	a = 0;
	for (i = 0;i < 10;i++) {
		if (i % 2 == 0) { continue; }
		a = a + i;
	}
	return a;
}
