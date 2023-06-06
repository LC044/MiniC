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
// int main()
// {
// 	int a;
// 	a = 10;
// 	//a = !a;
// 	if (a > 1) {
// 		a = -1;

// 	} else {
// 		a = 0;
// 	}
// 	return a;
// }
// test if-else-if

int a;

void putint(int k);

int func()
{
	int b;
	b = a;
	int a;
	a = 1;
	if (a == b) {
		a = a + 1;
		return 1;
	} else
		return 0;
}

int main()
{
	a = 7;
	int result;
	result = 0;
	int i;
	i = 0;
	while (i < 100) {
		if (func() == 1)
			result = result + 1;
		i = i + 1;
	}
	if (result < 100)
		putint(1);
	else
		putint(0);
	return 0;
}



