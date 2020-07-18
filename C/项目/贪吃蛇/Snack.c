#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

HANDLE handle;

//������ɫ�Ĵ��룺 0=��ɫ  1��ɫ 2 ��ɫ 3����ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8��ɫ 9����ɫ
/* �ı䵱ǰ��귽��ı�����ɫ��������ɫ */
void BackGround(int ForeColor, int BackGroundColor)
{
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10); //�ı䵱ǰ���ı�����������ɫ
}

/* �ı����λ�� */
void gotoxy(int x, int y)
{
	COORD coord; //��ȡ������ṹ��
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord); //�ƶ���굽x��y��
}

/* ���ؿ���̨��� */
void Hide_cursor()
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo); //��ȡ����̨�����Ϣ
	CursorInfo.bVisible = 0;				   //���ؿ���̨���=false
	SetConsoleCursorInfo(handle, &CursorInfo); //���ÿ���̨���״̬
}

/* ��ʼ����ͼ���� */
void restart(int bk[20][20], int look[4], int xy[2], int move[20][20])
{
	//bkΪ�ܵĵ�ͼ���ݼ�¼������ͼ��Ϊ1ʱ��ʾǽ�壬Ϊ2ʱ��ʾ��ʵ��Ϊ3ʱ��ʾ��
	//look��¼���ݣ�Ϊ0ʱ��ʾ����Ϊ1ʱ��ʾ���ȣ�Ϊ3ʱ��ʾʤ�����,Ϊ4��ʾ����
	//move��¼���߹���·�̣�������ӡ��ʱ�ж���
	int pp, qq, i, j; //������¼��ʵ��������꣬��Χ��1-15

	//������Ҫ��ʼ��������ͼ//
	for (i = 0; i <= 16; i++)
		for (j = 0; j <= 16; j++)
		{
			if (i == 0 || i == 16 || j == 0 || j == 16)
				bk[i][j] = 1; //1��ʾǽ��
			else
				bk[i][j] = 0; //0��ʾʲô��û��
			move[i][j] = 0;   //������������¼���ƶ��Ĺ켣
		}
		//���߳�ʼ����8,8������
		xy[1] = xy[0] = 8;
		bk[xy[0]][xy[1]] = 3;
		move[xy[0]][xy[1]] = 1; //���ʱ8,8,�ϵĹ켣��Ӧ�ü�¼Ϊ1
		move[0][0] = 1;			//�ô�����¼����
		look[0] = 1;			//��ʾ����,����
		look[1] = 1;			//��ʾ����
		look[2] = 0;			//��Ϊ1�Ǳ�ʾʧ��
		//��ʼ�������ʵ
		do
		{
			pp = rand() % 15 + 1;
			qq = rand() % 15 + 1;
		} while (bk[pp][qq] != 0);
		bk[pp][qq] = 2; //��ʾ���λ���й�ʵ��
		//������Ҫ���Ƶ�ͼ//
		for (i = 0; i <= 16; i++)
			for (j = 0; j <= 16; j++)
			{
				gotoxy(i * 2, j); //����ƶ�,ÿ����궼�Ǿ���
				switch (bk[i][j])
				{
				case 0:
					BackGround(0, 0);
					break; //���û�ж�����ӡ��ɫ
				case 1:
					BackGround(0, 1);
					break; //ǽ��ӡ��ɫ
				case 2:
					BackGround(0, 2);
					break; //��ʵ��ӡ��ɫ
				case 3:
					BackGround(0, 3);
					break; //�ߴ�ӡ����ɫ
				default:
					break;
				}
				printf("  "); //��ͼ��ֱ�Ӿ���Ϳ�ո��
			}
			//������Ҫ��ʾ����//
			gotoxy(35, 0);
			BackGround(7, 0); //�ð��ֺڵ״�ӡ
			printf("���ڵ÷���:%d,���ٽ�����!^_^", look[1] - 1);
}

//**�˶�����**//
void map(int bk[20][20], int look[4], int xy[2], int move[20][20])
{
	//bk�ǵ�ͼ��Ϣ��look�����ݼ�¼��xy��¼���꣬move��¼�ߵ��˶��켣
	int b[10], qq = 0, pp = 0, i, j; //b�����������룬qq��pp���������ʼ����ʵ����
	if (_kbhit())			   //��¼���µ����ĸ���������������ASCLLֵ:��72����75����77����80
	{
		b[0] = _getch(); //��b����¼
		if (b[0] == 224)
			b[0] = _getch();				//���Ϊ224��ʾΪ�����������Ҫ��һ�λ�ȡ����
		if (b[0] == 72 && look[0] != 2) //��������Ϊ�ϲ��ҳ���Ϊ��
			look[0] = 1;
		if (b[0] == 80 && look[0] != 1)
			look[0] = 2;
		if (b[0] == 75 && look[0] != 4)
			look[0] = 3;
		if (b[0] == 77 && look[0] != 3)
			look[0] = 4;
	}
	switch (look[0])
	{
	case 1:
		//������
		xy[1]--;
		break;
	case 2:
		//������
		xy[1]++;
		break;
	case 3:
		//������
		xy[0]--;
		break;
	case 4:
		//������
		xy[0]++;
		break;
	}

	//�������߾Ϳ�ʼ�߶���//
	move[0][0]++;					 //�ߵĲ�����һ
	move[xy[0]][xy[1]] = move[0][0]; //��¼��ǰ�������ߵĹ켣
	gotoxy(35, 2);
	BackGround(7, 0);
	printf("������:%d,������:%d", xy[0], xy[1]);
	gotoxy(xy[0] * 2, xy[1]); //������ͷ����ǰ�ƶ���
	BackGround(0, 3);		  //������һ����ɫ
	printf("  ");
	//������˹�ʵ
	if (bk[xy[0]][xy[1]] == 2)
	{
		look[1]++;				//���ȼ�һ
		gotoxy(35, 0);			//���·���
		BackGround(7, 0);
		printf("���ڵ÷���:%d,���ٽ�����!^_^", look[1] - 1);
		while (bk[pp][qq] != 0)
		{
			pp = rand() % 15 + 1;
			qq = rand() % 15 + 1;
		}
		bk[pp][qq] = 2; //������ط���Ϊ��ʵ
		gotoxy(pp * 2, qq);
		BackGround(0, 2);
		printf("  ");
	}
	//���ײ��ǽ�����Լ�//
	if (bk[xy[0]][xy[1]] == 1 || bk[xy[0]][xy[1]] == 3)
	{
		look[2] = 1; //��ʾ�Ѿ�����
		gotoxy(6, 6);
		BackGround(7, 0);
		printf("�����ˣ����÷�:%d", look[1] - 1);
	}
	bk[xy[0]][xy[1]] = 3; //ʹ���λ�ñ����

	//������Ҫ�����Ȼ��ˢ���ߵ�λ��//
	for (i = 0; i <= 16; i++)
		for (j = 0; j <= 16; j++)
			if (move[i][j] == move[xy[0]][xy[1]] - look[1])
			{
				//��������������,���ʾ���Ѿ��ƶ������λ����
				//Ҫɾ�����λ�õ���β��
				//һ��ֻ��һ����������Ҫ��ɣ�
				bk[i][j] = 0;
				gotoxy(i * 2, j);
				BackGround(0, 0);
				printf("  ");
				break; //һ��ֻ��һ��
			}
}

int main()
{
	int bk[20][20], xy[2], move[20][20], look[3];
	handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨�ľ��
	srand((unsigned)time(NULL));			  //��ʼ���������
	system("pause");
	Hide_cursor();
	restart(bk, look, xy, move);
	while (look[2] == 0)
	{
		Sleep(200); //����400msһ��
		map(bk, look, xy, move);
	}
	BackGround(7, 0);
	gotoxy(4, 8);
	printf("��Ϸ������лл����!^_^");
	gotoxy(4, 9);
	system("pause");
	return 0;
}