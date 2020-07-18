#include<windows.h>
#include<conio.h>
#include<time.h>
#define width 200//��
#define height 180//��
#define cols (1920 / width)//�У�ǰ������ֺͷֱ����йأ�
#define lines (1080 / height)//��
#define Max (cols * lines)//����
#define Delay 500//�ӳ�
void create(int* p, int Cols, int Lines, int Alive)//��������
{
	p[0] = Cols;
	p[1] = Lines;
	p[2] = Alive;
	system("start Screen.exe");//start dos�����������½���,���ɵ�.exe�ļ���ʲô,�������ʲô
}
int main()
{
	char strMapName[6] = "Snake";//�����ڴ�����
	int* pBuf;//�����ڴ�ָ��------0:����; 1:����; 2:����; 3:������;
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName);//���ļ�ӳ�����
	if (hMap == NULL)//������
	{
		system("mode con:cols=16 lines=2");//�޸Ĵ��ڴ�С
		srand((unsigned)time(0));//��ʼ�����������
		hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 16, strMapName);//�����ļ�ӳ���ں˶���
		pBuf = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);//���ļ�ӳ�����ӳ�䵽��ǰ����ĵ�ַ�ռ�
		int map[Max] = { 0 }, hX = 0, hY = 0, len = 4, c = 'd', i = 0;//�����֮ǰ��18��̰���߲�࣬���ﲻ������
		i = rand() % Max, map[i] = -1;//����һ��ʳ��
		create(pBuf, i % cols, i / cols, -1);//��������
		Sleep(100);//��ֹ�������ݷ�����ͻ
		while (1)//��ѭ��
		{
			if (pBuf[3] == ' ')break;//�ո���˳�
			switch (pBuf[3])//�ж����붯��
			{
			case 'a':case 'A':if (c != 'd')c = 'a'; break;//���붯������Ÿı䷽��
			case 'd':case 'D':if (c != 'a')c = 'd'; break;
			case 's':case 'S':if (c != 'w')c = 's'; break;
			case 'w':case 'W':if (c != 's')c = 'w'; break;
			}
			switch (c)//�ƶ�
			{
			case 'a':hX -= hX > 0 ? 1 : 1-cols; break;//���Խ��,�����Ե�ǽ����
			case 'w':hY -= hY > 0 ? 1 : 1-lines; break;
			case 'd':hX += hX < cols - 1 ? 1 : 1-cols; break;
			case 's':hY += hY < lines - 1 ? 1 : 1-lines; break;
			}
			if (map[hY * cols + hX] > 1)break;//���ͷ����������,����,����
			if (map[hY * cols + hX] == -1)//�����ʳ��
			{
				len++;//��������
				do i = rand() % Max;//ѭ������
				while (map[i]);//ֱ�����ɵ�λ��Ϊ�յ�Ϊֹ,��ֹ����������
				map[i] = -1;//��ֵ
				create(pBuf, i % cols, i / cols, -1);//����ʳ�����
				Sleep(100);//ͬ��Ҳ��Ҫ�ӳ�
			}
			else//ʣ�¾�ֻ�пյ���
				for (i = 0; i < Max; i++)
					if (map[i] > 0)map[i] -= 1;//ȫ��ֵ-1
			map[hY * cols + hX] = len;//ͷ���긳ֵ
			create(pBuf, hX, hY, len);//�����������
			Sleep(Delay);//�ӳ�
		}
		pBuf[2] = 0;//�߳���Ϊ0,��ֹ��������������ѭ��
	}
	else//�ӽ���
	{
		pBuf = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);//���ļ�ӳ�����ӳ�䵽��ǰ����ĵ�ַ�ռ�
		HWND hWnd = GetConsoleWindow();//��ȡ����̨���ھ��
		int i = 0, j = 0;
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);//���ر�����
		MoveWindow(hWnd, pBuf[0] * width, pBuf[1] * height, width, height, 1);//�ƶ�����λ�ü���С
		if (pBuf[2] == -1)//ʳ��
		{
			system("color fc");//�ı䴰����ɫ
			j = 1;
			while (pBuf[2] && pBuf[2] < 0)Sleep(10);//ֱ������������Ϊֹ(�糤��Ϊ0ͬ��������ֹ��ѭ��)
			i = pBuf[2];//��¼��ǰ�߳�
		}
		while (1)
		{
			if (_kbhit())pBuf[3] = _getch();//������붯��
			Sleep(10);//�ӳ�
			if (j)
			{
				if (i != pBuf[2] || !pBuf[2])break;
			}
			else
			{
				if (pBuf[2] < 0)Sleep(100), i += 100;//�����ʳ������(�����ӳ�),���ӳٶ�Ӧʱ��
				else if (!pBuf[2] || clock() > pBuf[2] * Delay + i)break;//ֱ������Ϊ0�����ʱ�䳬������*�ӳ�ʱ��,����
			}
		}
	}
	UnmapViewOfFile(pBuf);//ֹͣ�ڴ�ӳ��
	CloseHandle(hMap);//�ر�һ���ں˶���
}
