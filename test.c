//test domain of global var define and local define
int a;
int b;

int main()
{
	int c;
	a = 3;
	b = 5;
	c = a + b;
	int b;
	b = -2;
	{
		int a;
		a = 1;
		// int a;
		{
			a = 2;
			int a;
			a = 9;
		}
	}
	c = a + b;
	return c;
}

