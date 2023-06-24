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
		a = 5;
		c = a + b;
	}
	// {
	// 	int a;
	// 	a = 5;
	// 	c = a + b;
	// }
	return c;
}