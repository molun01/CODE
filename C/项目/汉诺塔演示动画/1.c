#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

char game_hnt[20][300] = {
	{"┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐"},
	{" \\   ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐    /"},
	{"  \\                                                                                                                       /"},
	{"   \\                                                                                                                     /"},
	{"    \\                                                                                                                   /"},
	{"     \\                                                                                                                 /"},
	{"      \\                                                                                                               /"},
	{"       \\                                                                                                             /"},
	{"        \\                                                                                                           /"},
	{"         \\                                                                                                         /"},
	{"          \\                                                                                                       /"},
	{"           \\                                                                                                     /"},
	{"            \\                                                                                                   /"},
	{"             \\  └───────────────────────────────────────────────────────────────────────────────────────────┘  /"},
	{"              \\ _____________________________________________________________________________________________ /"},
	{"               \\ 开始 \\  qq2010   |  汉诺塔自动演示小游戏  |                                        |  12:08 /"},
	{"                \\ __________________________________________________________________________________________/"}};
int mid_x = 7, mid_y = 60;
int len, width, left, mid, right, time;
int ttx = 10, tty = 10;
char game_map[80][1000];
int game_next[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //上0下1左2右3；
int turn[2][3] = {{0, 3, 1},							  //a -> b   b -> c a -> c  上右下
				  {0, 2, 1}};							  //b -> a  c -> b  c -> a	上左下     //实现自动移动的路线储存

/* 隐藏控制台光标 */
void Hide_cursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	;
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo); //获取控制台光标信息
	CursorInfo.bVisible = 0;				   //隐藏控制台光标=false
	SetConsoleCursorInfo(handle, &CursorInfo); //设置控制台光标状态
}

void gotoxy(int x, int y) //坐标函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void init_game(int n)
{ //初始化汉诺塔
	int i, j, num;
	time = 50 / n;
	left = 1, mid = 2 * (n + 1), right = mid + 2 * n + 1;
	len = 3 * (2 * n + 1);
	width = n + 1;
	ttx = mid_x - width / 2;
	tty = mid_y - len / 2;
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
				game_map[i][j + 1] = -10; //打印 ■  ■占2个字节可以拆开来
				num--;
			}
		}
	//容易出现东西卡顿
	for (i = 0; i <= width; i++)
	{
		gotoxy(tty, ttx + i);
		for (j = 0; j <= len; j++)
			printf("%c", game_map[i][j]);
		printf("\n");
	}
}

void play(int x, int y)
{ //显示汉诺塔移动轨迹
	int turn_0, n = 0, i, j, k, tx, ty;
	if ((x == mid && y == right) || (x == left && y == mid) || (x == left && y == right))
		turn_0 = 0; //往右
	else if ((x == mid && y == left) || (x == right && y == left) || (x == right && y == mid))
		turn_0 = 1; //往左
	for (i = 1, j = y; i <= width; i++)
	{ //目的地
		if (game_map[i][j] != 0)
		{
			tx = i - 1;
			ty = j;
			break;
		}
	}
	for (i = 1, j = x; i <= width; i++)
	{ //出发点
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
			gotoxy(j + tty, i + ttx);
			Sleep(time);
			for (k = 0; k < mid - 2; k++)
			{
				printf(" ");
			}
			i = i + game_next[turn[turn_0][n]][0];
			j = j + game_next[turn[turn_0][n]][1];
			gotoxy(j + tty, i + ttx);
			Sleep(time);
			for (k = 0; k < mid - 2; k++)
			{
				printf("%c", game_map[i][j + k]);
			}
		}
		n++; //改变方向;
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
		gotoxy(j + tty, i + ttx);
		for (k = 0; k < mid - 2; k++)
		{
			printf(" ");
		}
		Sleep(time);
		i = i + game_next[turn[turn_0][n]][0];
		j = j + game_next[turn[turn_0][n]][1];
		gotoxy(j + tty, i + ttx);
		for (k = 0; k < mid - 2; k++)
			printf("%c", game_map[i][j + k]);
		Sleep(time);
	}
}

void move_hnt(int a, int b, int c, char aa, char bb, char cc, int n)
{ //正常的汉诺塔递归程序
	if (n == 1)
	{
		//printf("from %c to %c",aa,cc);
		play(a, c);
		return;
	}
	move_hnt(a, c, b, aa, cc, bb, n - 1);
	/*	gotoxy(0,width+1);
	printf("from %c to %c",aa,cc);*/
	play(a, c);
	move_hnt(b, a, c, bb, aa, cc, n - 1);
}

void load_game()
{ //加载汉诺塔程序
	int i;
	gotoxy(0, 0);
	for (i = 0; i <= 16; i++)
	{
		printf("%s\n", game_hnt[i]);
		Sleep(100);
	}
	gotoxy(mid_y - 16, mid_x);
	printf("请输入你要递归的汉诺塔数目_");
}

int main()
{
	int i, j, n;
	//system("pause");
	system("color 70");
	system("mode con cols=125 lines=60");
	Hide_cursor();
	while (1)
	{
		load_game();
		n = getchar() - '0';
		gotoxy(mid_y - 16, mid_x);
		printf("                                               ");
		init_game(n);
		getch();
		move_hnt(left, mid, right, 'a', 'b', 'c', n);
		for (i = 0; i <= width; i++)
			for (j = 0; j <= len; j++)
				game_map[i][j] = 0;
	}
	return 0;
}