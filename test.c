void putint(int k);
int main()
{
	int a;
	int b[5];
	a = 3;
	int i;
	int j;
	for (i = 0;i < 5;i++) {
		if (i % 2 == 0) {
			i++;
			continue;
		}
		for (j = 4;j > -1;j--) {
			if (j < 3) {
				break;
			}
			b[j] = --a;
		}
		b[i] = a++;
	}
	return --a;
}