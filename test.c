int a;
int main()
{
	a = 3;
	int a;
	a = 4;
	{
		a = 5;
		int a;
		a = 6;
		{
			int a;
			a = 7;
		}
	}
	return a;
}