/*		����ʹ���ļ��˵��
������Ϊѧ��ͨѶ¼����ϵͳ����ѧ��ͨѶ¼��Ϣ�洢���ļ��У���ʹ�õ����������Ϣ����
*����(����������)��
1.ϵͳ�ڴ漰�˴��㹻��
2.����������ͷ��㡣(ֻӰ�촴���ͱ���������)
3.��ѯʱ�������������ؼ���
4.ֻ�ܶ�ȡ�ɱ��������ɵ�ͨѶ¼�ļ�
*���⣺���ṹ���һ��������󳤶�С��13ʱ�г���Ԫ��һ��Ԫ�ض�������ʾ��д���ļ���
*/



/* ȫ�����ݶ��弰���Ӻ������� */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <direct.h>
#include <windows.h>

#define SNOLEN		20	/* ѧ������ַ��� */
#define NAMELEN		20	/* ��������ַ��� */
#define NUMLEN		20	/* �ֻ�����󳤶� */
#define MAJORLEN	50	/* רҵ������ַ��� */
#define FNAMELEN	80	/* �ļ�������ַ��� */
#define BUFLEN		80	/* ����������ַ��� */
#define bakpath 	"C:\\backups\\"			/* �����ļ�Ŀ¼ */
#define TRUE		1	/* ��ȷ */
#define FALSE		0	/* ����ȷ */

/* �õ�������ͨѶ¼ */
typedef struct People {
	char	sno[SNOLEN];		/* ѧ�� */
	char	name[NAMELEN];		/* ���� */
	char	num[NUMLEN];		/* �ֻ��� */
	char	major[MAJORLEN];	/* רҵ */
	struct People *next;
} People,*Contacts;

FILE *fp;				/* �ļ�ָ�� */
char fname[FNAMELEN];	/* �ļ��� */
Contacts CT;
int COUNT;				/* ��ϵ������ */

void FullScreen();//����̨���
void MainInterface();//��ʼ����
void RepCryp();//����Աģʽ
char *Encry(char *str);//���ݼ����㷨
void CodeInput(char *str);//��������
void CodeVerify();//������֤
void CodeUpdated();//�����޸�
void Welcome1();//����Ա����
void Welcome2();//��ͨ�û�����
void CtsFnameVerify();//����ͨѶ¼�ļ�
int ReadPeople(FILE *fp,People *p);//���ļ���ȡһ����ϵ��(����)
void Menu1();//����Ա�˵�
void Menu2();//��ͨ�û��˵�
void TraverseContactsFile();//��ʾ������ϵ��
void SearchPeople();//��ѯ��ϵ��
void NewPeople();//�½���ϵ�˵��ļ�
int CheckContactsKey(char key[],int start,int cycle);//�ؼ��ֲ���
void WritePeople(FILE *fp,People *p);//���ļ���д��һ������ϵ��(����)
void ShowContacts(Contacts CT);//����������
void ConstructList();//���ļ���������
void SaveContactsByList();//���������ļ�
void BackupRestore();//���ݻ�ԭ�˵�
int CustomCopyFile(char *file1,char *file2);//�ļ�����
void BackupContacts();//�����ļ���C��
void RestoreContacts();//��C�̻�ԭ����
void BakFnameVerify(char a[]);//���뱸���ļ�
int ModifyContacts();//�޸���ϵ����Ϣ
int DeleteContacts();//ɾ����ϵ��
int DeleteContactsByData();//��ֵɾ��
int DeleteContactsByOrder();//�����ɾ��
People *GetContacts(int i);//����Ų��Ҳ����ؽ��ָ��
People *LocationContacts();//��ֵ���Ҳ����ؽ��ָ��

/* ������ */
int main() {
	FullScreen();
	system("color F0");
	MainInterface();
	return 0;
}

/* ���������ݼ��� */

/* ���ݼ����㷨 */
char *Encry(char *str) {
	int i,j=0,Len,Long;
	char code[]="&";
	Len=strlen(code);
	Long=strlen(str);
	for (i=0; i < Long; i++) {
		str[i]=str[i]^code[j];
		j++;
		if (j==Len) j=0;
	}
	return str;
}

/* �������� */
void CodeInput(char *str) {    
	int i;
	char ch;
	for(i=0;i<=20;) {
		ch=getch();
		if(ch=='\r') {
			str[i]='\0';
			break;
		}
		else if(ch=='\b') {
			if(i>0){
				printf("\b \b");
				i=i-1;
			}
		}
		else {
			printf("*");
			str[i]=ch;
			i=i+1;
		}
	}
}

/* ������֤ */
void CodeVerify() {
	int i,res;
	char code[21],str[21],ori[]="123",choose;
	FILE *fp;
	fp=fopen("code.txt","r");
	if(fp==NULL) {
		printf("%c",'\007');
		printf("\n\t ��ĳ�ʼ����Ϊ %s ,ϵͳ��¼���뼰ʱ�޸�!\n",ori);
		fp=fopen("code.txt","w+");
		Encry(ori);
		fputs(ori,fp);
		rewind(fp);
	}
	fscanf(fp,"%s",code);
	Encry(code);
	fclose(fp);					
	printf("\n\t ����������:");
	for(i=1;;i++) {
		CodeInput(str);
		printf("\n");
		res=strcmp(str,code);
		if(res==0)
			break;
		else if(i==3) {
			system("cls");
			printf("\n\t ���Ѿ����������������,�����������,�Ƿ�ѡ���ʼ������(Y/N):"); //�û���������������룬��ѡ���Ƿ��ʼ������
			while(1){
				choose=getch();
				if(choose=='Y'||choose=='y') {
					remove("code.txt");
					printf("\n\t �������ʼ���� %s :",ori);
					CodeInput(str);
					res=strcmp(str,ori);
					if(res==0)
						break;
					else {
						printf("\n\t �Բ���!���Ѷ�������������,��ϵͳ�϶�Ϊ���Ǳ�����Ϸ��û�,��ϵͳ��ǿ���˳�!");
						printf("\n\t �밴������˳�����!");
						exit(0);
					}
				}
				else if(choose=='N'||choose=='n') {
					printf("\t ��ʼ������ʧ��,�밴������˳�����");
					exit(0);
				}
				else {
					puts("\t ���벻�淶,������ Y/N (�����ִ�Сд):");
					printf("\t ");
				}
			}
			break;
		}
		else if(i==5) {
			printf("%c",'\007');
			printf("\t �Բ���!�㲻�Ǳ�����Ϸ��û�!\n\t�밴���������\n"); //�û��������������룬���˳�����
			exit(0);
		}
		printf("%c",'\007');
		printf("\t �����������!\n\t ����������:");
	}
	system("cls");
}

/* �����޸� */
void CodeUpdated() {
	char code1[21],code2[21],ch;
	int res,countl;
	system("cls");
	printf("\n\n         �����޸Ĺ���\n");
	printf("\n**********************************\n\n����������������:");
	fflush(stdin);
	for(countl=1;;countl++) {
		CodeInput(code1);//����������
		printf("\n");
		printf("���ٴ���������������:");
		CodeInput(code2);
		printf("\n");
		res=strcmp(code1,code2);
		if(res==0) {
			fp=fopen("code.txt","w+");
			Encry(code1);
			fputs(code1,fp);
			fclose(fp);
			printf("�޸�����ɹ�!\n�����ϼ�:�����\n�˳�����:��Esc��\n");
			ch=getch();
			printf("\n");
			if(ch==27) {
				printf("\n\t\t��л����ʹ��!");
				exit(0);
			}
			break;
		}
		else {
			if(countl>=3) {
				printf("%c",'\007');
				printf("�Բ���!�����ڲ����޸�����!\n�˳�����:��Esc��    \n�����ϼ�:�����\n");
				ch=getch();
				printf("\n");
				if(ch==27)
					exit(0);
				break;
			}
			else {
				printf("�Բ���!������������벻һ��\n\n����������:");
				printf("%c",'\007');
			}
		}
	}
}



/* �ļ��Ļ������� */

/* ͨѶ¼�ļ��������뼰��֤ */
void CtsFnameVerify() {
	char cts[]=".cts",b[5]="";
	fflush(stdin);
	scanf("%s",fname);
	if(strrchr(fname,'.')) strcpy(b,strrchr(fname,'.'));//��������ĵ�һ��'.'��ʼ��ĩβ�����ļ���չ��
	while(strcmpi(b, cts)) {							//�Ƚ���չ���������ִ�Сд
		printf("\n�ļ������������������������� x.cts ���ļ���.\n");
		scanf("%s",fname);
		if(strrchr(fname,'.')) strcpy(b,strrchr(fname,'.'));
	}
}

/* ͨѶ¼�����ļ��������뼰��֤ */
void BakFnameVerify(char a[]) {
	char bak[]=".bak",b[5]="";
	fflush(stdin);
	scanf("%s",a);
	while(strlen(a) < 21) {
		printf("\n�ļ������������������������� [xxxx-xx-xx]x.bak �ı����ļ���\n");
		scanf("%s",a);
	}
	if(strrchr(a,'.')) strcpy(b,strrchr(a,'.'));
	while(strcmpi(b, bak)) {
		printf("\n�ļ������������������������� [xxxx-xx-xx]x.bak �ı����ļ���.\n");
		scanf("%s",a);
		if(strrchr(a,'.')) strcpy(b,strrchr(a,'.'));
	}
}

/* �ļ��ĸ��ƣ����ļ�1�����ݸ��Ƶ��ļ�2�� */
int CustomCopyFile(char *file1,char *file2) {
	FILE *fp1,*fp2;
	char buf[BUFLEN];
	if((fp1=fopen(file1,"r"))==NULL) return FALSE;
	if((fp2=fopen(file2,"w+"))==NULL) return FALSE;
	while(fscanf(fp,"%s",buf)==1)	fprintf(fp2,"%s\n",buf);
	fclose(fp1);
	fclose(fp2);
	return TRUE;
}

/* ��ͨѶ¼�ļ���ȡһ����ϵ��(����) */
int ReadPeople(FILE *fp,People *p) {
	char buf[BUFLEN];							/* ������ */
	if(fscanf(fp,"%s",buf)!=1)	return 0;	/* �ļ����� */
	strncpy(p->sno,Encry(buf),SNOLEN);
	fscanf(fp,"%s",buf);
	strncpy(p->name,Encry(buf),NAMELEN);
	fscanf(fp,"%s",buf);
	strncpy(p->num,Encry(buf),NUMLEN);
	fscanf(fp,"%s",buf);
	strncpy(p->major,Encry(buf),MAJORLEN);
	return 1;
}

/* ��ͨѶ¼�ļ�д��һ������ϵ��(����) */
void WritePeople(FILE *fp,People *p) {
	char buf[BUFLEN];							/* ���建���������ı�p������ */
	strcpy(buf,p->sno);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->name);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->num);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->major);
	fprintf(fp,"%s\n",Encry(buf));
}

/* ��ͨѶ¼�ļ�����������ϵ�� */
void TraverseContactsFile() {
	People p;
	if((fp=fopen(fname,"r"))==NULL) {
		printf("���ļ�%sʧ��.\n",fname);
		system("pause");
		return;
	}
	while(ReadPeople(fp,&p)!=0) {
		printf("ѧ��	: \t%s\n",p.sno);
		printf("����	: \t%s\n",p.name);
		printf("�ֻ���	: \t%s\n",p.num);
		printf("רҵ	: \t%s\n",p.major);
		puts("\n------------------------------\n");
	}
	printf("\n�ļ� %s �й���%d����ϵ�˼�¼",fname,COUNT);
	fclose(fp);
	system("pause");
}

//���ܶ�fp�����ܶ�fp�����ܶ�fp������(ת��NewPeople())
//startԪ��λ���ɽṹ��Ķ����������ѧ��Ϊ 1.���ѧ���ֻ�����ͬʱ�Ĳ���(�޸�ʱ)����
//cycle,�ṹ�����������������������Ϊ4
/* ���ѧ�ţ��ֻ��ŵȹؼ����Ƿ��ظ����ظ�����TRUE */
int CheckContactsKey(char key[],int start,int cycle) {
	char buf[BUFLEN];
	FILE *fp1;							//�ڲ���fp������±����ļ�
	int i=1;
	if((fp1=fopen(fname,"r"))==NULL) {
		printf("���ļ�%sʧ��.\n",fname);
		system("pause");
		return FALSE;
	}
	for(i=1;i<start;i++) if(fscanf(fp1,"%s",buf)!=1) break;//�����ؼ���֮ǰ��Ԫ��λ
	while(fscanf(fp1,"%s",buf)==1) {		//��������õ�ʽ�������ã��߼�
		if(strcmp(Encry(buf),key)==0) {
			fclose(fp1);
			return TRUE;					/* �����Ѵ�����ͬ�ؼ��� */
		}
		for(i=1;i<cycle;i++) if(fscanf(fp1,"%s",buf)!=1) break;//����һ��ѭ������ 
	}
	fclose(fp1);
	return FALSE;							/* δ������ͬ�ؼ��� */
}



/* �������ز��� */

/* ��ͨѶ¼�ļ��������� */
void ConstructList() {
	People *r,*p;
	if((fp=fopen(fname,"r"))==NULL) {
		printf("���ļ�%sʧ��.\n",fname);
		system("pause");
		return;
	}
	COUNT=0;
	p=(People *)malloc(sizeof(People));
	CT=(People *)malloc(sizeof(People));
	r=CT;
	while(ReadPeople(fp,p)!=0) {
		r->next=p;
		r=r->next;
		p=(People *)malloc(sizeof(People));
		COUNT++;
	}
	r->next=NULL;
	free(p);
	fclose(fp);
}

/* ����������(��ͷ���) */		//����ĺ����Ƕ�����������ã���������ȥ��
void ShowContacts(Contacts CT) {
	People *p=CT->next;
	int order=0;
	if(!p) puts("ͨѶ¼Ϊ�գ�����");
	while(p!=NULL) {
		printf("�� %d ����¼��\n",++order);
		printf("ѧ��	: \t%s\n",p->sno);
		printf("����	: \t%s\n",p->name);
		printf("�ֻ���	: \t%s\n",p->num);
		printf("רҵ	: \t%s\n",p->major);
		puts("\n------------------------------\n");
		p=p->next;
	}
}

/* ����Ų��Ҳ����ؽ��ָ�� */
People *GetContacts(int i) {
    People *p;
    int j;
    p=CT;
    j=0;
	if(i<0)	return NULL;			//����λ��С��0�ǲ��Ϸ���
    while(p!=NULL&&j<i) {
        p=p->next;
        j++;
    }
    return p;
}

/* ��ֵ���Ҳ����ؽ��ָ��,����λ(ֻ���ѧ�ţ��ֻ���) */
People *LocationContacts() {
	People *p;
	char key[20],choose;
	int i=1;
	p=CT->next;
	system("cls");
	puts("��1������ѧ�Ų��Ҽ�¼.");
	puts("��2�������ֻ��Ų��Ҽ�¼.");
	while(i) {
		puts("���������");
		fflush(stdin);
		choose=getche();
		printf("\n");
		switch(choose) {
			case '1':
				puts("������ѧ�ţ�");
				scanf("%s",key);
				while(p!=NULL&&strcmp(p->sno,key)!=0)
					p=p->next;
				i=0;
				break;
			case '2':
				puts("�������ֻ��ţ�");
				scanf("%s",key);
				while(p!=NULL&&strcmp(p->num,key)!=0)
					p=p->next;
				i=0;
				break;
			default:
				puts("����������󣡣���");
				break;
		}
	}
	return p;
}

/* ɾ��������ĵ�i����� */
int DeleteContactsByOrder() {
	People *p,*q;
	int i=-1;
	printf("��ǰͨѶ¼�й��� %d λ��ϵ�ˣ�\n",COUNT);
	printf("��Ҫɾ������ϵ�����Ϊ��\n");
	fflush(stdin);
	scanf("%d",&i);
	p=GetContacts(i-1);
	if(p==NULL || p->next==NULL) {
		printf("ɾ��λ�ò��Ϸ�!\n");      //��i����������ǰ����㲻���ڣ�����ִ��ɾ������
		return FALSE;
	}
	q=p->next;
	p->next=p->next->next;
	free(q);
	return TRUE;
}

/* ��ֵɾ���������еĽ��,������ɾ�� */
int DeleteContactsByData() {
    People *p,*q;
	char choose,key[BUFLEN];
	int i=1;									//i��������ȷʱ�˳��˵�ѭ���ı�־
    p=CT;
    q=CT->next;
	system("cls");
	puts("��1������ѧ�Ų��Ҽ�¼��ɾ��.");
	puts("��2�������ֻ��Ų��Ҽ�¼��ɾ��.");
	puts("��0����������һ��.");
	while(i) {
		puts("���������");
		fflush(stdin);
		choose=getch();
		switch(choose) {
			case '1':
				system("cls");
				puts("������Ҫɾ������ϵ�˵�ѧ�ţ�");
				scanf("%s",key);
				while(q!=NULL&&(strcmp(q->sno,key)!=0)) {
					q=q->next;
					p=p->next;
				}
				i=0;
				break;
			case '2':
				system("cls");
				printf("������Ҫɾ������ϵ�˵��ֻ��ţ�");
				scanf("%s",key);
				while(q!=NULL&&(strcmp(q->num,key)!=0)) {
					q=q->next;
					p=p->next;
				}
				i=0;
				break;
			case '0':
				return FALSE;
			default:
				puts("����������󣡣���");
				break;
		}

	}
    if(q==NULL) {
        printf("���� %s �ļ�¼�����ڣ�\n",key);       //Ҫɾ����ֵ�����ڻ�����Ϊ��
        return FALSE;
    }
	p->next=p->next->next;
	free(q);
	return TRUE;
} 

/* �ϲ�����ɾ����ʽ */
int DeleteContacts() {
    char choose,result;
	int i=1;
    puts("��ѡ������ɾ��������");
	puts("��1���������ɾ��.");
	puts("��2����������ֵɾ��.");
	puts("��0����������һ��.");
	while(i) {
		puts("���������");
		choose=getch();
		switch(choose) {
			case '1':
				result=DeleteContactsByOrder();
				i=0;
				break;
			case '2':
				result=DeleteContactsByData();
				i=0;
				break;
			case '0':
				return FALSE;
			default:
				puts("����������󣡣���");
				break;
		}
	}
	if(result) {
		system("cls");
		COUNT--;
		puts("ɾ���ɹ���ͨѶ¼��������ϵ�����£�");
		ShowContacts(CT);
		printf("ɾ���ɹ���");
		system("pause");
		return TRUE;
	}
	else {
		printf("ɾ��ʧ�ܣ�");
		system("pause");
	    return FALSE;
	}
}

/* ���������޸���ϵ����Ϣ */
int ModifyContacts() {
	char key[20],buf[50],choose;
	People *p;
	int i=1;
	if((p=LocationContacts())==NULL) {
		puts("δ�ҵ���ؼ�¼�����������˵���");
		system("pause");
		return FALSE;
	}
	system("cls");
	puts("���ҵ���Ӧ��¼�����£�");
	printf("ѧ��	: \t%s\n",p->sno);
	printf("����	: \t%s\n",p->name);
	printf("�ֻ���	: \t%s\n",p->num);
	printf("רҵ	: \t%s\n",p->major);
	puts("\n------------------------------\n");
	puts("��ѡ����Ҫ�޸ĵ���Ϣ���˳������ز˵���");
	puts("��1����ѧ��.");
	puts("��2��������.");
	puts("��3�����ֻ���.");
	puts("��4����רҵ.");
	puts("��0����������һ��.");
	while(i) {
		puts("���������");
		fflush(stdin);
		choose=getch();
		system("cls");
		switch(choose) {
			case '1':
				puts("�������µ�ѧ�ţ�");
				scanf("%s",key);
				while(CheckContactsKey(key,1,4)) {
					puts("ѧ���ǿ���Ψһ��ʶ��ϵ����ݵĹؼ��֣������ظ���");
					puts("�������µ�ѧ�ţ�");
					scanf("%s",key);
				}
				strcpy(p->sno,key);
				i=0;
				break;
			case '2':
				puts("�������µ�������");
				scanf("%s",key);
				strcpy(p->name,key);
				i=0;
				break;
			case '3':
				puts("�������µ��ֻ��ţ�");
				scanf("%s",key);
				while(CheckContactsKey(key,3,4)) {
					puts("�ֻ����ǿ���Ψһ��ʶ��ϵ����ݵĹؼ��֣������ظ���");
					puts("�������µ��ֻ��ţ�");
					scanf("%s",key);
				}
				strcpy(p->num,key);
				i=0;
				break;
			case '4':
				puts("�������µ�רҵ����");
				scanf("%s",buf);
				strcpy(p->major,buf);
				i=0;
				break;
			case '0':
				return FALSE;
			default:
				puts("����������󣡣���");
				break;
		}
	}
	system("cls");
	puts("�޸ĺ����ϵ����Ϣ���£�");
	printf("ѧ��	: \t%s\n",p->sno);
	printf("����	: \t%s\n",p->name);
	printf("�ֻ���	: \t%s\n",p->num);
	printf("רҵ	: \t%s\n",p->major);
	puts("\n------------------------------\n");
	puts("�޸ĳɹ�.�����������˵�");
	system("pause");
	return TRUE;
}

/* ����Ķ����ͨѶ¼�ļ� */
void SaveContactsByList() {
	People *p;
	
	p=CT->next;
	fp=fopen(fname,"w+");			
	while(p!=NULL) {
		WritePeople(fp,p);
		p=p->next;
	}
	fclose(fp);
}



/* �ļ��ĸ߼����� */

/* ��ͨѶ¼�ļ���������ϵ�� */
void SearchPeople() {
	int choose,result=0,i=1;					//i��������ȷʱ�˳��˵�ѭ���ı�־
	char key[50];
	People p,s;
	Contacts CT=&p;
	s.next=NULL;CT->next=&s;					//����ͷ���p��Ϊ��ֱ��ʹ��ShowContacts()����
	if((fp=fopen(fname,"r"))==NULL) {
		printf("���ļ�%sʧ��.\n",fname);
		return;
	}
	puts("����Գ������²���.");
	puts("��1������ѧ�Ų���.");
	puts("��2��������������.");
	puts("��3�������ֻ��Ų���.");
	puts("��4������רҵ����.");
	puts("��0����������һ��.");
	while(i) {
		printf("����������:");
		fflush(stdin);
		choose=getch();
		switch(choose) {
			case '1':						/* ��ѧ�Ų��� */
				system("cls");
				printf("������Ҫ���ҵ���ϵ�˵�ѧ�ţ�");
				scanf("%s",key);
				while(ReadPeople(fp,&s)!=0) {
					if(strcmp(s.sno,key)==0) {
						ShowContacts(CT);
						result=1;
					}
				}
				i=0;
				break;
			case '2':
				system("cls");
				printf("������Ҫ���ҵ���ϵ�˵�������");		//������з��������ļ�¼
				scanf("%s",key);
				while(ReadPeople(fp,&s)!=0) {
					if(strcmp(s.name,key)==0) {
						ShowContacts(CT);
						result=1;
					}
				}
				i=0;
				break;
			case '3':
				system("cls");
				printf("������Ҫ���ҵ���ϵ�˵��ֻ��ţ�");
				scanf("%s",key);
				while(ReadPeople(fp,&s)!=0) {
					if(strcmp(s.num,key)==0) {
						ShowContacts(CT);
						result=1;
					}
				}
				i=0;
				break;
			case '4':
				system("cls");
				puts("������Ҫ���ҵ���ϵ�˵�רҵ��");
				scanf("%s",key);
				while(ReadPeople(fp,&s)!=0) {
					if(strcmp(s.major,key)==0) {
						ShowContacts(CT);
						result=1;
					}
				}
				i=0;
				break;
			case '0':
					fclose(fp);
					return;					/* ���ز˵� */
			default:
				puts("");
				puts("����������󣡣���");
				break;
		}
	}
	fclose(fp);
	if(result==0) {
		printf("���� %s �ļ�¼���ļ� %s ��δ�ҵ���\n",key,fname);
		system("pause");
		return;
	}
	else {
		puts("���ҵ���Ӧ��¼.");
		system("pause");
		return;
	}
}

/* �����ϵ�˵��ļ��� */ 
void NewPeople() {
	People p;
	int i,n=0;
	printf("������Ӽ�����ϵ��: ");
	scanf("%d",&n);
	while(n<=0) {
		puts("���������������һ����ϵ�ˣ����������룺");
		fflush(stdin);
		scanf("%d",&n);
		getchar();
	}
	for(i=0;i<n;i++) {
		fp=fopen(fname,"a+");			//ÿ����һ����¼���ر��ļ��Ա��棬��Ϊ�˹ؼ��ּ��
		printf("��ʼ����� %d ��ѧ����¼��\n",i+1);
		printf("����ѧ��ѧ��:\t");
		scanf("%s",p.sno);
		while(CheckContactsKey(p.sno,1,4)) {
			puts("ѧ���ǿ���Ψһ��ʶ��ϵ����ݵĹؼ��֣������ظ���");
			printf("����ѧ��ѧ��: ");
			scanf("%s",p.sno);
		}
		printf("����ѧ������:\t");
		scanf("%s",p.name);
		printf("����ѧ���ֻ���: ");
		scanf("%s",p.num);
		while(CheckContactsKey(p.num,3,4)) {
			puts("�ֻ����ǿ���Ψһ��ʶ��ϵ����ݵĹؼ��֣������ظ���");
			printf("����ѧ���ֻ���: ");
			scanf("%s",p.num);
		}
		printf("����ѧ��רҵ: \t");
		scanf("%s",p.major);
		WritePeople(fp,&p);
		fclose(fp);
	}
	printf("��ӳɹ���");
	ConstructList();
	system("pause");
}

/* ���� */
void BackupContacts() {
	char Time[20],bakfname[FNAMELEN]=bakpath,bak[]=".bak",choose;
	time_t t=time(NULL);
	struct tm *ptr=localtime(&t);
	strftime(Time,20,"[%Y-%m-%d]",ptr);					//�����ǰ����ʱ��������
	system("cls");
	puts("��ǰ����Ϊ��");
	puts(Time);
	puts("��ȷ���������Ҫ���ڱ�����(Y/N)");
	while(1) {
		choose=getch();
		if(choose=='Y'||choose=='y') break;				//��ʼ����
		else if(choose=='N'||choose=='n') return;		//������һ��
		else puts("������������������ (Y/N) ");
	}
	mkdir(bakfname);
	strcat(bakfname,Time);
	strcat(bakfname,fname);
	strcat(bakfname,bak);
	if(CustomCopyFile(fname,bakfname)) printf("���ݳɹ��������ļ�Ϊ %s\n",bakfname);
	else puts("����ʧ�ܣ���������ͨѶ¼�ļ��Ƿ�������Ѿ�������.");
	system("pause");
}

/* ��ԭ */
void RestoreContacts() {
	char choose,bakfname[FNAMELEN]=bakpath,fname2[FNAMELEN],buf[BUFLEN]="",parms[100];
	system("cls");
	puts("Ĭ�ϱ���Ŀ¼�µı����ļ����£�");
	sprintf(parms,"dir /p/b/a-d %s*.bak",bakfname);
	system(parms);
	printf("\n������Ҫ��ԭ��ͨѶ¼�ļ���(����ֱ�Ӵ����渴������)��\n");
	BakFnameVerify(fname2);										//�ȱ�֤��.bak�ļ�
	strcat(bakfname,fname2);
	strncpy(buf,fname2+12,(strlen(fname2)-4-12));				//�⺯���е�ӣ�������ȫ����
	strcpy(fname2,buf);
	if(CustomCopyFile(bakfname,fname2)) printf("��ԭ�ɹ�������\n�����ļ� %s �е�����Ϊ�ѳɹ���ԭ��������ͬĿ¼�µ� %s ��.\n",
	bakfname,fname2);
	else {
		puts("��ԭʧ�ܣ���������ͨѶ¼�����ļ��Ƿ����������.");
		system("pause");
		return;
	}
	puts("��Ҫ���ڴ�����(Y/N)");
	while(1) {
		choose=getch();
		if(choose=='Y'||choose=='y') {
			strcpy(fname,fname2);
			ConstructList();
			puts("�򿪳ɹ��������������˵�.");
			system("pause");
			return;
		}
		else if(choose=='N'||choose=='n') return;		//������һ��
		else puts("������������������ (Y/N) ");
	}
}



/* �˵�ҳ�� */

/* ���ݻ�ԭ�˵� */
void BackupRestore() {
	char choose;
	system("cls");
	printf("ѧ��ͨѶ¼����ϵͳ�����ļ�λ�� %s Ŀ¼��.\n",bakpath);
	puts("�����ļ������磺[xxxx-xx-xx]fname.bak ����fnameΪ����ǰ��ͨѶ¼�ļ���.");
	puts("����Գ������²�����");
	puts("��1�������ݵ�ǰ�ļ���C��.");
	puts("��2������C�̻�ԭ�����ļ�.");
	puts("��0����������һ��.");
	while(1) {
		puts("���������");
		choose=getch();
		switch(choose) {
			case '1':
				BackupContacts();
				return;
			case '2':
				RestoreContacts();
				return;
			case '0':
				return;
			default:
				puts("����������󣡣���");
				break;
		}
	}
}

/* ����Ա�˵� */
void Menu1() {
	char choose;
	while(1) {
		system("cls");
		puts("������������²���.");
		puts("��1�����½���ϵ��.");
		puts("��2������ѯ��ϵ��.");
		puts("��3����ɾ����ϵ��.");
		puts("��4�����޸���ϵ����Ϣ.");
		puts("��5������ʾ������ϵ��.");
		puts("��6���������뻹ԭ.");
		puts("��7�����˳�ͨѶ¼ϵͳ.");
		puts("��0����������һ��.");
		puts("����������:");
		choose=getch();
		system("cls");
		if(choose=='0') {
			return;
			exit(0);
		}
		switch(choose) {
			case '1':
				NewPeople();		/* ���б����ļ����� */
				break;
			case '2':
				SearchPeople();
				break;
			case '3':				/* �����������ɾ����ɾ���ɹ�����TRUE�������ļ� */
				if(DeleteContacts())	SaveContactsByList();
				break;
			case '4':				/* ���������޸ģ����Ը�Ϊ���ļ����޸�(��strcpy()) */
				if(ModifyContacts())	SaveContactsByList();
				break;
			case '5':
				TraverseContactsFile();
				break;
			case '6':
				BackupRestore();
				break;
			case '7':
				printf("\n\t��л����ʹ��!");
				exit(0);
			default:
				puts("����������󣡣�������ϸ��~_~");
				printf("%c",'\007');
				system("pause");
				break;
		}
	}
}

/* ��ͨ�û��˵� */
void Menu2() {
	char choose;
	while(1) {
		system("cls");
		puts("����Խ������²���.");
		puts("��1������ѯ.");
		puts("��2������ʾ������ϵ��.");
		puts("��3�����˳�ͨѶ¼ϵͳ!");
		puts("��0����������һ��!");
		puts("����������:");
		choose=getch();
		system("cls");
		if(choose=='0') {
			return;
		}
		switch(choose) {
			case '1':
				SearchPeople();
				break;
			case '2':
				TraverseContactsFile();
				break;
			case '3':
				system("cls");
				puts("\n\t��л����ʹ��!");
				system("pause");
				exit(0);
			default:
				puts("����������󣡣�������ϸ��~_~");
				printf("%c",'\007');
				system("pause");
				break;
		}
	}
}

/* ����Ա���� */
void Welcome1() {
	char choose;
	while(1) {
		puts("******************** ��ӭʹ��ѧ��ͨѶ¼����ϵͳ ********************");
		puts("˵�����ӱ�����ͬĿ¼�е���ͨѶ¼�ļ���ʹ�þ���·��(�磺1.cts��C:\\1.cts)");
		printf("������Ҫ��ȡ��ͨѶ¼�ļ���,���û�н��ᴴ����: ");
		CtsFnameVerify();//scanf("%s",fname);
		printf("����������ļ�����: %s \n",fname);
		if((fp=fopen(fname,"r"))==NULL) {
			printf("�ļ� %s ������,��Ҫ����������Ӽ�¼��? (Y/N) \n",fname);
			while(1) {
				choose=getche();
				printf("\n");
				if(choose=='Y'||choose=='y') {
					NewPeople();				//�½���¼,�������Ѱ�����������ֱ�ӷ���
					return;
				}
				else if(choose=='N'||choose=='n') {
					system("cls");
					break;
				}
				else {
					printf("%c",'\007');
					puts("������������������ (Y/N) ");
				}
			}
		}
		else break;							//�ļ������Ҷ�ȡ�ɹ�
	}
	system("pause");
	ConstructList();
	fclose(fp);
}

/* ��ͨ�û����� */
void Welcome2() { 
	char choose;
	while(1) {
		system("cls");
		puts("******************** ��ӭʹ��ѧ��ͨѶ¼����ϵͳ ********************");
		puts("              ˵��:������ͨ�û������в�ѯ����");
		puts("˵�����ӱ�����ͬĿ¼�е���ͨѶ¼�ļ���ʹ�þ���·��(�磺1.cts��C:\\1.cts)");
		puts("������ѧ��ͨѶ¼�ļ���,��������ڸ��ļ���ʹ�ù���Ա��ݴ�����:");
		CtsFnameVerify();
		printf("����������ļ�����: %s \n",fname);
		if((fp=fopen(fname,"r"))==NULL) {
			system("cls");
			printf("�ļ�%s������,�����������ļ�������ʹ�ù���Ա��ݴ���!\n",fname);
			puts("��1�����������ļ���");
			puts("��2�������ϼ�,ʹ�ù���Ա��ݴ���");
			printf("\n��ѡ�����Ĳ���:");
			while(1) {
				choose=getch();
				if(choose=='1') break;
				else if(choose=='2') {
					system("cls");
					return;
				}
				else {
					printf("%c",'\007');
					printf("\n�Բ���!û����Ҫ��ѡ��!\n������ѡ��!\n");
				}
			}
		}
		else {
			ConstructList();
			fclose(fp);
			system("pause");
			Menu2();
			break;
		}
	}
}

/* ����Աģʽ */
void RepCryp() {
	char choose;
	while(1) {
		fflush(stdin);
		system("cls");
		printf("\n\n                               ��ӭʹ�ñ�ϵͳ!\n");
		printf("---------------------------------------------------------------------------------\n\n");
		printf("��1��ʹ��ϵͳ���� \n");
		printf("��2���޸����� \n");
		printf("��3���˳� \n");
		printf("��0�������ϲ�\n");
		printf("\n��ѡ�����Ĳ���:");
		choose=getch();
		if(choose=='0') {
			break;
		}
		switch(choose) {
		case '1':
			system("cls");
			Welcome1();
			Menu1();
			break;
		case '2':
			CodeUpdated();
			break;
		case '3':
			system("cls");
			printf("\n\t��л����ʹ��!");
			exit(0);
		default:
			printf("%c",'\007');
			printf("�Բ���!û����Ҫ��ѡ��!\n������ѡ��!\n");
			system("pause");
			break;
		}
	}
}

/* ��ʼ���� */
void MainInterface() {
	char choose, ch;
	while(1) {
		fflush(stdin);
		system("cls");
		printf("\n\n\t                                 ѧ��ͨѶ¼����ϵͳ\n");
		printf("\t-------------------------------------------------------------------------------");
		printf("\n\t*******************************************************************************\n");
		printf("\t*                            ��ӭʹ��ѧ��ͨѶ¼����ϵͳ                       *\n");
		printf("\t*                      ��ϵͳ���ڶ�ѧ��ͨѶ¼��Ϣ����ͳ������                 *\n");
		printf("\t*                        ��Ҳ���Զ�ͨѶ¼��Ϣ���в�ѯ���޸�                   *\n");
		printf("\t*              ע:��ͨ�û����в�ѯ����,��Լ�¼���в�����ʹ�ù���Ա���       *\n");     
		printf("\t*******************************************************************************\n\n");
		printf("\t ��¼��ʽ:\n");
		printf("\t ��1������Ա \n");
		printf("\t ��2����ͨ�û� \n");
		printf("\t ��0���˳�ͨѶ¼ϵͳ \n");
		printf("\n\t ��ѡ���¼��ʽ:");
		choose=getche();
		if(choose=='0') {
			system("cls");
			printf("\n\t ��л����ʹ��!");
			exit(0);
		}
		switch(choose) {
		case '1':
			CodeVerify();//������֤
			RepCryp();//������֤����RepCryp����
			break;
		case '2':
			Welcome2();
			break;
		default:
			printf("\t �Բ���!û����Ҫ��ѡ��!\n\t �˳�����:��Esc��\n\t ȡ���˳�������ѡ��:�����\n");
			printf("%c",'\007');
			ch=getch();
			if(ch==27) {
				printf("\n\t ��л����ʹ��!");
				exit(0);
			}
		}
	}
}

/* ����̨��� */
void FullScreen() {   
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */
    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   /* ��ȡ������Ϣ */
    /* ���ô�����Ϣ ��� (ȡ�����������߿��Ȳ���) */
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE));
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);// & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER
}





