#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "Sokoban.h"
#pragma comment(lib,"User32.lib")

void Gotoxy(int x, int y)  //��λ���
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Hide() //���ع��
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD coord;
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

void EasyMap(int Map[20][20], int* n, int* m, char* ch) //�򵥹ؿ�
{
	static int cs = 0;
	int guan, i, j;
	if (*ch == '*')
	{
		guan = cs;
		if (guan > 0)
			guan--;
		*ch = '!';
	}
	else 
	{
		guan = cs;
		cs++;
	}

	*n = point[guan].x;
	*m = point[guan].y;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[guan][i][j];
		}
	}
}

void MiddleMap(int Map[20][20], int* n, int* m, char* ch)//�еȹؿ�
{
	static int cs = 0;
	int guan, i, j;
	//fscanf(fp1, "%d", &guanshu2);
	//fclose(fp1);//�ر��ļ�
	if (*ch == '*') 
	{
		guan = cs;
		if (guan > 0)
			guan--;
		*ch = '!';
	}
	else 
	{
		guan = cs;
		cs++;
		//guan=guanshu2;
		//guanshu2++;
	}

	*n = point[guan + 10].x;
	*m = point[guan + 10].y;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[guan + 10][i][j];
		}
	}
}

void DifficultyMap(int Map[][20], int* n, int* m, char* ch) //���ѹؿ�
{
	static int css = 0;
	int guan, i, j;
	if (*ch == '*') 
	{
		guan = css;
		if (guan > 0)
			guan--;
		*ch = '!';
	}
	else
	{
		guan = css;
		css++;
	}

	*n = point[guan + 20].x;
	*m = point[guan + 20].y;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[guan + 20][i][j];
		}
	}
}

void SelectMap(int Map[][20], int* n, int* m, int guan) //ѡ�ص�ͼ char* ch, 
{
	int i, j;
	if (guan > 0)	guan--;
	*n = point[guan].x;
	*m = point[guan].y;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *m; j++)
		{
			Map[i][j] = Maps[guan][i][j];
		}
	}
}

void MenuTwo(char* ch) //�˵���
{
	while (1) 
	{
		int s;
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("\n\n\n\n\n\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t   (1):�򵥹ؿ�\n\n");
		printf("\t\t   (2):�еȹؿ�\n\n");
		printf("\t\t   (3):���ѹؿ�\n\n");
		printf("\t\t   (4):�˳�ҳ��\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t    ��������š�\n");
		s = _getch();
		while (s < '1' || s>'4') 
		{
			printf("������������������:");
			s = _getch();
		}
		if (s == '1')
			EasyGame(ch);
		else if (s == '2')
			MiddleGame(ch);
		else if (s == '3')
			DifficultyGame(ch);
		else if (s == '4')
			MenuOne(ch);
	}
}

void Autor(char* ch) //���ߡ�����
{
	char hh = '!';
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("\n\n\n\n");
	printf("    ����Ϸ�ǳ���ª����Ȼ�ң�������ڣ��Ѿ��ǳ�Ŭ���ˣ�");
	printf("�������˼����ʱ�䣬д�����Ϸ�������ֺ�ѧϰ��Ҳ�����ɺϡ�");
	printf("֮����Ҫд����Ϊ���ɴ����Ͽ���һ����C����д�����ӵķ�����");
	printf("�����Լ�������һ��дһ�������ӵ�С��Ϸ���뷨�����������ʱ��");
	printf("����д��һ���ǳ����׵�������С��Ϸ�����С��Ϸ����д������ʮ����ˣ����ڼ���ֵ�BUG��Ⱥ�޾����Լ��Ǹ����ָ�,");
	printf("������Ϊֹ���϶��ǻ��кö�BUG��ͨ��д���������С��Ϸ������֪���ˣ���һ����Ϸ");
	printf("�Ƕ�ô���ѣ��������˼�ª��С��Ϸ��Ҳ������һǧ�ٶ��еĴ��롣\n");
	printf("    ���������ּ����ˣ��÷�������������������ĺ��鷳��һֱ������ˣ�̫ʹ���ˣ�");
	printf("������ W S A D �ĸ����������ⲻ��̫���ء�");
	printf("�ٶ�һ��˵ʲô˫���壬������gotoxy()���������ܽ���������⣬�ðɸ������ᣬ����̫���ˡ������������ɡ�\n");
	printf("    �汾1.0��ֻ��һ����ͼ��ʲô��û�С��汾1.1��������ж�ͨ�صĹ��ܡ��汾1.2�������˶���ؿ����޸��˶��BUG��");
	printf("�汾2.0����ӽ��棬�Լ�����ģʽ���汾2.1���ٴ����ӹؿ����ؿ�������50�ء��汾2.2������˵�ͼ�в�ͬ��Ʒ�Լ�������ʾ��ͬ��ɫ��");
	printf("�汾2.3�����Ӽ�¼�ƶ������Ĺ���,�޸����BUG���汾2.4.0���Ż��˽��档�汾2.4.1���޸�����ѡ��ģʽ�¼�¼�����������õ����⡣");
	printf("�汾2.6.1���޸��������벻��ɾ�������⡣2.6.5�汾�޸�һЩBUG��\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("\t\t    �˳��밴   ����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	Gotoxy(28, 27);
	printf("ESC");
	hh = _getch();
	if (hh == 27)
		Introduction(ch);
}

void Menu(char* ch) {//���˵�
	while (1) 
	{
		int s;
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("\n\n\n\n\n\t       ��        ��        ��\n\n");
		printf("\n\n\t\t       ������\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t   (1):��ʼ��Ϸ\n\n");
		printf("\t\t   (2):��������\n\n");
		printf("\t\t   (3):��Ϸ����\n\n");
		printf("\t\t   (4):�˳���Ϸ\n\n");
		printf("         ------------------------------------\n\n");
		printf("****************��һ�����ȹۿ���������****************\n\n");
		printf("\t\t    ��������š�\n");
		s = _getch();
		while (s < '1' || s>'4')
		{
			printf("\t\t�����������������롣\n");
			s = _getch();
		}
		if (s == '1')
			MenuOne(ch);
		else if (s == '2')
			Operation(ch);
		else if (s == '3')
			Introduction(ch);
		else
		{
			int i = MessageBox(NULL, TEXT("\nȷ��Ҫ�˳���Ϸ��"), TEXT("�˳���ʾ"), MB_YESNO);
			if (i == IDYES)
				exit(0);
		}

	}
}

void MenuOne(char* ch) {//�˵�һ
	while (1) 
	{
		int s;
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("\n\n\n\n\n\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t   (1):����ģʽ\n\n");
		printf("\t\t   (2):ѡ��ģʽ\n\n");
		printf("\t\t   (3):�˳�ҳ��\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t    ��������š�\n");
		s = _getch();
		while (s < '1' || s>'3')
		{
			printf("\t\t�����������������롣\n");
			s = _getch();
		}
		if (s == '1')
			MenuTwo(ch);
		else if (s == '2')
			Select(ch);
		else
			Menu(ch);
	}
}

void Select(char* ch) //ѡ��
{
	int guan;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t��������Ҫѡ��\n\n\t\t\t�Ĺؿ�(1-40��)��\n\n\t\t\t����0���˵���һҳ��\n\n\t\t\t֮�󰴻س�����");
	scanf("%d", &guan);
	while (guan < 0 || guan>40)
	{
		printf("\t\t�����������������롣\n");
		scanf("%d", &guan);
	}
	if (guan == 0)
		MenuOne(ch);
	SelectGameReady(ch, guan);
}

void SelectGame(char* ch, int guan)
{
	int Map[20][20], n, m;
	int sum = 0, data = 0, sl = 0;
	memset(Map, -1, sizeof(Map));
	while (1)
	{
		SelectMap(Map, &n, &m, guan);
		data = BoxData(Map, &n, &m);
		sl = GroundData(Map, &n, &m);
		while (1) 
		{
			system("cls");//����
			sum = DrawMap(Map, &n, &m, &guan);//��ͼ
			sum -= sl;
			if (sum == data) {
				printf("\n\t\t    �� ϲ ͨ �أ�\n\n");
				printf("\t       ���Ե�,�������ùؿ���\n");
				MyTime();
				break;
			}
			PlayGame(Map, &n, &m, ch);//��������
			if (*ch == '*') {
				*bushu = 0;
				break;
			}
		}
		if (*ch == '*') 
		{
			*ch = '!';
			break;
		}
	}
}

int SelectGameReady(char* ch, int guan) {//��Ϸ׼��
	while (1)
	{
		int s;
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("\n\n\n\n\n\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t   (1):��Ϸ��ʼ\n\n");
		printf("\t\t   (2):��Ϸ�˳�\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t    ��������š�\n");
		s = _getch();
		while (s != '1' && s != '2')
		{
			printf("\t\t�����������������롣\n");
			s = _getch();
		}
		if (s == '1')
			SelectGame(ch, guan);
		else
			Select(ch);
	}
	return 0;
}

void Password(char* ch) //���������ж�
{
	char passwords[10], Passwords[10] = { "123456789" };
	while (1)
	{
		int t = _getch(), i;
		system("cls");
		printf("\n\n\n\n\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("    ˵����\n\t       ��������󰴻س�����\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t (1):��������\n\n");
		printf("\t\t (2):�˳�ҳ��\n\n");
		printf("         ------------------------------------\n\n");
		printf("\t\t    �������\n\n");
		//printf("\n\n\n");
		if (t == '1')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//��ɫ
			printf("\t\t���룺");
			for (i = 0; i < 100; i++) 
			{
				passwords[i] = _getch();
				if (passwords[i] == 8)
				{
					i -= 2;
					printf("\b \b");
				}
				else if (passwords[i] == '\r')
					break;
				else
					printf("*");
			}
			passwords[i] = '\0';
			if (strcmp(passwords, Passwords) == 0)
				break;
			else
				MessageBox(NULL, TEXT("\t    ������󣡣���\t\n\t�������������롣\t"), TEXT("������ʾ"), MB_OK);
		}
		else
			Introduction(ch);
	}
}

void Introduction(char* ch)
{
	int s;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//��ɫ
	printf("\n\n\n\n\n\n\n");
	printf("         ------------------------------------\n\n");
	printf("\t\t (1):��Ϸ����:������\n\n");
	printf("\t\t (2):��Ϸ���:->(next)\n\n");
	printf("\t\t (3):�������:2018��3��\n\n");
	printf("\t\t (4):����:�������->(next)\n\n");
	printf("\t\t (5):QQ:2117610943\n\n");
	printf("\t\t (6):�汾:%d.%d.%d\n\n", A, B, C);
	printf("\t\t (7):�˳�ҳ��\n\n");
	printf("         ------------------------------------\n\n");
	printf("\t\t    ��������š�\n");
	s = _getch();
	while (s != '2' && s != '7' && s != '4') 
	{
		printf("\t\tSorry�������û����һҳ�ˡ�\n");
		s = _getch();
	}
	if (s == '2')
		Gameintor(ch);
	else if (s == '7')
		Menu(ch);
	else if (s == '4') 
	{
		MessageBox(NULL, TEXT("\t          ���������롣\t\n\t������ʮ�����ֻ���ĸ��\t"), TEXT("������ʾ"), MB_OK);
		Password(ch);
		Autor(ch);
	}

}

void Gameintor(char* ch) {//��Ϸ����
	while (1) 
	{
		char hh = '!';
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);//��ɫ
		printf("\n\n\n\n\n");
		printf("   �������ӡ���һ��������Ϸ��1982�����ձ�Thinking Rabbit��˾�״η���");
		printf("֮��������Ϸ�����������������ƻ�������Ʒ����ʹ�����ӳ�Ϊ������Ϸ�Ĵ����ʡ�");
		printf("��ϷҪ�������һ����С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�ã��Բ�С�ľͻ����");
		printf("t�����޷��ƶ�����ͨ������ס�������������Ҫ������������޵Ŀռ��ͨ��������");
		printf("t�����ƶ��Ĵ����λ�ã�����˳����������� \n");
		printf("    ��������һ�������ձ��Ĺ�����Ϸ��Ŀ������ѵ����ҵ��߼�˼����������һ����");
		printf("С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�ã��Բ�С�ľͻ���������޷��ƶ�����ͨ������");
		printf("ס�������������Ҫ������������޵Ŀռ��ͨ�����������ƶ��Ĵ����λ�ã�����˳");
		printf("�����������\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("        ע����Ϸ�ؿ���Դ�ھ��������ӹؿ���\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("\t\t  �˳��밴   ����\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		Gotoxy(26, 21);
		printf("ESC");
		hh = _getch();
		if (hh == 27)
			Introduction(ch);
	}
}

void Operation(char* ch) {//��������
	char hh = '!';
	while (1) 
	{
		system("cls");
		printf("\n\n\n\n\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("\t\t\t����˵��:\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//��ɫ
		printf("   (W):�����ƶ� (S):�����ƶ� (A):�����ƶ� (D):�����ƶ�\n\n");
		printf("      (��):�������� (��):������   (��):����Ŀ�ĵ�\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("\t        *������ǰ����������뷨��\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("\t\t     �˳��밴   ����\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		Gotoxy(29, 16);
		printf("ESC");
		hh = _getch();
		if (hh == 27)
			Menu(ch);
	}
}

int BoxData(int Map[][20], int* n, int* m)//����������
{
	int sum = 0, i, j;
	for (i = 0; i < *n; i++) {
		for (j = 0; j < *m; j++) {
			if (Map[i][j] == 3)
				sum++;
		}
	}
	return sum;
}

int GroundData(int Map[][20], int* n, int* m) //�������ӿ�ʼʱ����Ŀ�ĵص���Ŀ
{
	int sum = 0, i, j;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *m; j++) 
		{
			if (Map[i][j] == 7)
				sum++;
		}
	}
	return sum;
}

int DrawMap(int Map[20][20], int* n, int* m, int* guanshu) //������ͼ
{
	int sum = 0, i, j;
	Gotoxy(0,0);
	printf("\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t\t     ��  %d  ��\n\n\n", *guanshu);
	for (i = 0; i < *n; i++) 
	{
		printf("\t\t   ");
		for (j = 0; j < *m; j++) 
		{
			switch (Map[i][j]) {
			case 1://��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//�ı���ɫ����
				printf("��");
				break;
			case 0://�յ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("  ");
				break;
			case 3://Ŀ�ĵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("��");
				break;
			case 4://����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("��");
				break;
			case 5://��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				printf("��");
				break;
			case 7://������Ŀ�ĵ� 4+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("��");
				sum++;
				break;
			case 8://����Ŀ�ĵ�  5+3
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("��");
				break;
			}
		}
		printf("\n");
	}
	if (kongge == 1) 
	{
		printf("\n\t\t     ��ǰ����Ϊ%d����    \n", *bushu);
		if (yanchi == 10)
		{
			kongge = 0;
			yanchi = 0;
		}
		yanchi++;
		xianshi = 1;
	}
	if (xianshi == 0)
	{
		printf("\n\t\t  ���ո���鿴��ǰ������\n");
	}
	xianshi = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("\n     ��ESC���˳�����Ϸ��֮�����½���Ӹù����¿�ʼ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("\n\t   ��ʼ��Ϸǰ���뷨��������Ӣ�Ĵ�д��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	Gotoxy(12, 23);
	printf("W/��:����");
	Gotoxy(32, 23);
	printf("S/��:����");
	Gotoxy(12, 25);
	printf("A/��:����");
	Gotoxy(32, 25);
	printf("D/��:����");
	return sum;
}

void PlayGame(int Map[20][20], int* n, int* m, char* ch)//��Ϸ����/*************���������Ҫ��**************/
{
	char input;
	int i, j;
	//ȷ���˵�λ��
	for (i = 0; i < *n; i++) 
	{
		for (j = 0; j < *m; j++) 
		{
			if (Map[i][j] == 5 || Map[i][j] == 8)
				break;
		}
		if (Map[i][j] == 5 || Map[i][j] == 8)
			break;
	}
	input = _getch();//ͷ�ļ�conio.h
	switch (input) 
	{
	case 72:
	case 'W'://��
	case 'w':
		if (Map[i - 1][j] == 0 || Map[i - 1][j] == 3)//��ǰ���ǿյػ�����ǰ����Ŀ�ĵ�
		{
			Map[i - 1][j] += 5;
			Map[i][j] -= 5;
			data++;
		}
		else if (Map[i - 1][j] == 4 || Map[i - 1][j] == 7) //�˵�ǰ�������ӵ����
		{
			if (Map[i - 2][j] == 0 || Map[i - 2][j] == 3) 
			{
				Map[i - 2][j] += 4;
				Map[i - 1][j] += 1;
				Map[i][j] -= 5;
				data++;
			}
		}
		break;
	case 80:
	case 'S'://��
	case 's':
		if (Map[i + 1][j] == 0 || Map[i + 1][j] == 3)//��ǰ���ǿյػ�����ǰ����Ŀ�ĵ�
		{
			Map[i + 1][j] += 5;
			Map[i][j] -= 5;
			data++;
		}
		else if (Map[i + 1][j] == 4 || Map[i + 1][j] == 7)//�˵�ǰ�������ӵ����
		{
			if (Map[i + 2][j] == 0 || Map[i + 2][j] == 3) 
			{
				Map[i + 2][j] += 4;
				Map[i + 1][j] += 1;
				Map[i][j] -= 5;
				data++;
			}
		}
		break;
	case 75:
	case 'A'://��
	case 'a':
		if (Map[i][j - 1] == 0 || Map[i][j - 1] == 3) //��ǰ���ǿյػ�����ǰ����Ŀ�ĵ�
		{
			Map[i][j - 1] += 5;
			Map[i][j] -= 5;
			data++;
		}
		else if (Map[i][j - 1] == 4 || Map[i][j - 1] == 7) //�˵�ǰ�������ӵ����
		{
			if (Map[i][j - 2] == 0 || Map[i][j - 2] == 3) 
			{
				Map[i][j - 2] += 4;
				Map[i][j - 1] += 1;
				Map[i][j] -= 5;
				data++;
			}
		}
		break;
	case 77:
	case 'D'://��
	case 'd':
		if (Map[i][j + 1] == 0 || Map[i][j + 1] == 3) //��ǰ���ǿյػ�����ǰ����Ŀ�ĵ�
		{
			Map[i][j + 1] += 5;
			Map[i][j] -= 5;
			data++;
		}
		else if (Map[i][j + 1] == 4 || Map[i][j + 1] == 7)//�˵�ǰ�������ӵ����
		{
			if (Map[i][j + 2] == 0 || Map[i][j + 2] == 3) 
			{
				Map[i][j + 2] += 4;
				Map[i][j + 1] += 1;
				Map[i][j] -= 5;
				data++;
			}
		}
		break;
	case 27:
		*ch = '*';
		break;
	case 32:
		kongge = 1;
		break;
	}
}

void MyTime() //����ʱ
{
	int t = 0, i;
	for (i = 9; i >= 0; i--) 
	{
		Sleep(500);
		Gotoxy(25, 23);
		if (t == 3)
			t = 0;
		if (t == 0)
			printf("%d.  ", i);
		else if (t == 1)
			printf("%d.. ", i);
		else
			printf("%d...", i);
		t++;
	}
}

int GameReady() //��Ϸ׼��
{
	int s;
	system("cls");
	Hide();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//��ɫ
	printf("\n\n\n\n\n\n\n");
	printf("         ------------------------------------\n\n");
	printf("\t\t   (1):��Ϸ��ʼ\n\n");
	printf("\t\t   (2):��Ϸ�˳�\n\n");
	printf("         ------------------------------------\n\n");
	printf("\t\t    ��������š�\n");
	s = _getch();
	while (s != '1' && s != '2') {
		printf("\t\t�����������������롣\n");
		s = _getch();
	}
	return s;
}

void GameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch)//��Ϸ��������
{
	system("cls");//����
	while (1)
	{
		clock_t start, end;
		start = clock();
		*js = 0;
		*sum = DrawMap(Map, n, m, guanshu);//��ͼ
		*sum -= *sl;
		if (*sum == *data)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("\n\n\n\n\n\n\n\n\n\n\n\t\t    �� ϲ ͨ �أ�\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("\n\t\t ͨ�����ò���Ϊ%d����\n\n", *bushu);
			end = clock();
			printf("\n\t        ͨ������ʱ��Ϊ%.3lf��\n\n", (double)(end - start) / 9.56);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("\n\t       ���Ե�,���ڴ�����һ�ء�\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			MyTime();
			*bushu = 0;
			kongge = 0;
			break;
		}
		PlayGame(Map, n, m, ch);//��������
		if (*ch == '*') 
		{
			int i = MessageBox(NULL, TEXT("\t\nȷ��Ҫ�˳���Ϸ��\n\n����ʾ���˳������½�����˳��Ĺؿ���ʼ����"), TEXT("�˳���ʾ"), MB_YESNO);
			if (i == IDYES) 
			{
				*bushu = 0;
				kongge = 0;
				*js = 1;
				break;
			}
			else 
			{
				*ch = '!';
				continue;
			}
		}
	}
}

void EasyGameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch)//��Ϸ��������
{
	system("cls");//����
	while (1) 
	{
		int t;
		*js = 0;
		*sum = DrawMap(Map, n, m, guanshu);//��ͼ
		*sum -= *sl;
		if (*sum == *data)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("\t\t\t\t\t    �� ϲ ͨ �أ�\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			t = MessageBox(NULL, TEXT("\t      �����������\n\n\t�Ƿ������һ�أ�"), TEXT("��ʾ"), MB_YESNO);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("\t\t ͨ�����ò���Ϊ%d����\n", *bushu);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("\t       ���Ե�,���ڴ�����һ�ء�");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			MyTime();
			if (t == IDYES)
			{
				*bushu = 0;
				kongge = 0;
				break;
			}
			else 
			{
				*bushu = 0;
				*js = 2;
				break;
			}
		}
		PlayGame(Map, n, m, ch);//��������
		if (*ch == '*')
		{
			int i = MessageBox(NULL, TEXT("\t\nȷ��Ҫ�˳���Ϸ��\n\n����ʾ���˳������½�����˳��Ĺؿ���ʼ����"), TEXT("�˳���ʾ"), MB_YESNO);
			if (i == IDYES)
			{
				*bushu = 0;
				kongge = 0;
				*js = 1;
				break;
			}
			else 
			{
				*ch = '!';
				continue;
			}
		}
	}
}

void EasyGame(char* ch)//�򵥹ؿ�����
{
	int Map[20][20], n, m, js;
	static int guanshu = 1;
	int sum = 0, data = 0, sl = 0;
	memset(Map, -1, sizeof(Map));
	while (1) 
	{
		int t = GameReady();
		if (t == '2')
			break;
		while (1) 
		{
			int s;
			EasyMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			EasyGameOperate(Map, &n, &m, &js, &sum, &data, &sl, &guanshu, ch);
			if (js == 0) 
			{
				guanshu++;
				if (guanshu < 11)
					s = 1;
				else 
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("��ϲ���Ѿ�ͨ��ȫ���򵥹ؿ�,���������еȹؿ��ȴ���ȥ��ս\n");
					Gotoxy(19, 26);
					printf("������������");
				}
			}
			else if (js == 1)
				break;
			else if (js == 2) {
				*ch = '*';
				continue;
			}
			if (s == '2')
				break;
		}
	}
}

void MiddleGame(char* ch)//�еȹؿ�����
{
	int Map[20][20], n, m, js;
	static int guanshu = 1;
	int sum = 0, data = 0, sl = 0;
	memset(Map, -1, sizeof(Map));
	while (1) 
	{
		int t = GameReady();
		if (t == '2')
			break;
		while (1) 
		{
			int s;
			MiddleMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			GameOperate(Map, &n, &m, &js, &sum, &data, &sl, &guanshu, ch);
			if (js == 0)
			{
				guanshu++;
				if (guanshu < 11)
					s = 1;
				else 
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("��ϲ���Ѿ�ͨ��ȫ���еȹؿ�,�����������ѹؿ��ȴ���ȥ��ս\n");
					Gotoxy(19, 26);
					printf("������������");
				}
			}
			else if (js == 1)
				break;
			if (s == '2')
				break;
		}
	}
}

void DifficultyGame(char* ch) {//���ѹؿ�����
	int Map[20][20], n, m, js;
	static int guanshu = 1;
	int sum = 0, data = 0, sl = 0;
	memset(Map, -1, sizeof(Map));
	while (1)
	{
		int t = GameReady();
		if (t == '2')
			break;
		while (1) 
		{
			int s;
			DifficultyMap(Map, &n, &m, ch);
			data = BoxData(Map, &n, &m);
			sl = GroundData(Map, &n, &m);
			EasyGameOperate(Map, &n, &m, &js, &sum, &data, &sl, &guanshu, ch);
			if (js == 0) 
			{
				guanshu++;
				if (guanshu < 21)
					s = 1;
				else 
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("��ϲ���Ѿ�ͨ��ȫ���ؿ�!\n");
					Gotoxy(19, 26);
					printf("������������");
				}
			}
			else if (js == 1)
				break;
			else if (js == 2) 
			{
				*ch = '*';
				continue;
			}
			if (s == '2')
				break;
		}
	}
}

int main() {//������
	char ch = '!';
	system("title ������C����2.6.5��---�����������");//���ñ���
	system("mode con cols=55 lines=30");//���ƴ��ڴ�С
	Hide();
	while (1)
	{
		system("cls");//�����Ļ
		Menu(&ch);//�˵�һ
	}
	return 0;
}
