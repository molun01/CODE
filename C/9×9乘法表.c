#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i, j, result;
	printf("9×9乘法表如下：\n");
	for (i = 9; i > 0; i--)
	{
		for (j = 1; j <= i; j++)
		{
			result = i * j;
			printf("%d*%d=%-4d", j, i, result);//%-4d为左对齐
		}
		printf("\n");
	}
	return 0;
}