int n;

int counting_sort(int ini_arr[], int sorted_arr[], int n)
{
	int count_arr[10];
	int j;
	count_arr[ini_arr[j - 1]] = count_arr[ini_arr[j - 1]] - 1;
	sorted_arr[count_arr[ini_arr[j - 1]]] = ini_arr[j - 1];
	return 0;
}

void putint(int k);
void putch(int k);
int main()
{
	n = 10;
	int a[10];
	int i;
	int b[10];
	i = counting_sort(a, b, n);
	return 0;
}
