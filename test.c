//test break
int main()
{
	int i;
	i = 0;
	int sum;
	sum = 0;
	if (i != -1) {
		return 0;
	} else {
		while (i < 100) {
			if (i == 50) {
				break;
			}
			if (i % 2 == 0) {
				sum = sum + i;
				continue;
			}
			sum = sum + i * 2;
			i = i + 1;
		}
	}

	return sum;
}