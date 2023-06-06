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
void putint(int k);

int main()
{
	int a;
	int b;
	int c;
	int d;
	int result;
	a = 5;
	b = 5;
	c = 1;
	d = -2;
	result = (d * 1 / 2) + (a - b) - -(c + 3) % 2;
	putint(result);
	result = ((d % 2 + 67) + -(a - b) - -((c + 2) % 2));
	result = result + 3;
	putint(result);
	return 0;
}


