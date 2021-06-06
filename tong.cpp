#include <stdio.h>
int s = 0, n;
int main()
{
	printf("Nhap n ", n);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
	{
		s = s + i;
	}
	printf("Tong la: %d", s);
	printf("Hello");
	return 0;
}
