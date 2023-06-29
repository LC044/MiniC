//test domain of global var define and local define
int a;
int b;

int main()
{
	int c;
	a = 3;
	b = 5;
	{
		int a;
		a = 1;
		c = a + b;
	}
	{
		a = -1;
		int a;
		a = 5;
		c = a + b;
	}
	int i;
	while (i > 0) {
		i++;
		a = a + i;
	}
	return c;
}

