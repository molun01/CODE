#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

int mid_x = 7, mid_y = 60;
int len, width, left, mid, right, time;
char game_map[80][1000];
int game_next[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //��0��1��2��3��
int turn[2][3] = {{0, 3, 1},							  //a -> b   b -> c a -> c  ������
				  {0, 2, 1}};							  //b -> a  c -> b  c -> a	������     //ʵ���Զ��ƶ���·�ߴ���

void Hide_cursor()
{ //���ؿ���̨���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo); //��ȡ����̨�����Ϣ
	CursorInfo.bVisible = 0;				   //���ؿ���̨���=false
	SetConsoleCursorInfo(handle, &CursorInfo); //���ÿ���̨���״̬
}

void gotoxy(int x, int y)
{ //���꺯��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void init_game(int n)
{ //��ʼ����ŵ��
	int i, j, num;
	time = 50 / n;
	left = 1, mid = 2 * (n + 1), right = mid + 2 * n + 1;
	len = 3 * (2 * n + 1);
	width = n + 1;
	for (i = 0; i <= width; i++)
		for (j = 0, num = i; j <= len; j++)
		{
			if (i == 0 || j == 0 || i == width || j == len)
				game_map[i][j] = '';
			if ((i > 1 && i < width) && (j == mid - 1 || j == right - 1))
				game_map[i][j] = '|';
			if (num && (i >= 1 && i <= width - 1) && j % 2 != 0 && j < mid)
			{
				game_map[i][j] = -95;
				game_map[i][j + 1] = -10; //��ӡ ��  ��ռ2���ֽڿ��Բ���
				num--;
			}
		}
	//���׳��ֶ�������
	for (i = 0; i <= width; i++)
	{
		for (j = 0; j <= len; j++)
			printf("%c", game_map[i][j]);
		printf("\n");
	}
}

void play(int x, int y)
{ //��ʾ��ŵ���ƶ��켣
	int turn_0, n = 0, i, j, k, tx, ty, a, b;
	if ((x == mid && y == right) || (x == left && y == mid) || (x == left && y == right))
		turn_0 = 0; //����
	else if ((x == mid && y == left) || (x == right && y == left) || (x == right && y == mid))
		turn_0 = 1; //����
	for (i = 1, j = y; i <= width; i++)
	{ //Ŀ�ĵ�
		if (game_map[i][j] != 0)
		{
			tx = i - 1;
			ty = j;
			break;
		}
	}
	for (i = 1, j = x; i <= width; i++)
	{ //������
		if (game_map[i][j] != 0)
		{
			break;
		}
	}
	while (1)
	{
		while ((i != 1 || j != x) && (i != 1 || j != y) && (i != tx || j != ty))
		{
			if (turn_0 == 0)
				for (k = mid - 3; k >= 0; k--)
				{
					game_map[i + game_next[turn[turn_0][n]][0]][j + game_next[turn[turn_0][n]][1] + k] = game_map[i][j + k];
					game_map[i][j + k] = 0;
				}
			else
				for (k = 0; k < mid - 2; k++)
				{
					game_map[i + game_next[turn[turn_0][n]][0]][j + game_next[turn[turn_0][n]][1] + k] = game_map[i][j + k];
					game_map[i][j + k] = 0;
				}
			gotoxy(0, 0);
			i = i + game_next[turn[turn_0][n]][0];
			j = j + game_next[turn[turn_0][n]][1];
			Sleep(time);
			for (a = 0; a <= width; a++)
			{
				for (b = 0; b <= len; b++)
					printf("%c", game_map[a][b]);
				printf("\n");
			}
		}
		n++; //�ı䷽��;
		if (i == tx && j == ty)
			return;
		if (turn_0 == 0)
			for (k = mid - 3; k >= 0; k--)
			{
				game_map[i + game_next[turn[turn_0][n]][0]][j + game_next[turn[turn_0][n]][1] + k] = game_map[i][j + k];
				game_map[i][j + k] = 0;
			}
		else
			for (k = 0; k < mid - 2; k++)
			{
				game_map[i + game_next[turn[turn_0][n]][0]][j + game_next[turn[turn_0][n]][1] + k] = game_map[i][j + k];
				game_map[i][j + k] = 0;
			}
		Sleep(time);
		i = i + game_next[turn[turn_0][n]][0];
		j = j + game_next[turn[turn_0][n]][1];
		gotoxy(0, 0);
		for (a = 0; a <= width; a++)
		{
			for (b = 0; b <= len; b++)
				printf("%c", game_map[a][b]);
			printf("\n");
		}
		Sleep(time);
	}
}

void move_hnt(int a, int b, int c, int n)
{ //�����ĺ�ŵ���ݹ����
	if (n == 1)
	{
		play(a, c);
		return;
	}
	move_hnt(a, c, b, n - 1);
	play(a, c);
	move_hnt(b, a, c, n - 1);
}

int main()
{
	int i, j, n;
	// getch();
	system("color 70");
	system("mode con cols=125 lines=60");
	Hide_cursor();
	printf("��������Ҫ�ݹ�ĺ�ŵ����Ŀ_");
	while (1)
	{
		printf("��������Ҫ�ݹ�ĺ�ŵ����Ŀ_");
		scanf("%d",&n);
		gotoxy(0, 0);
		system("cls");
		init_game(n);
		move_hnt(left, mid, right, n);
		for (i = 0; i <= width; i++)
			for (j = 0; j <= len; j++)
				game_map[i][j] = 0;
		printf("��ʾ��ϣ������������������");
		getch();
		system("cls");
	}
	return 0;
}