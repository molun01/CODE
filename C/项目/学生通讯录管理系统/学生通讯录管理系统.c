/*		程序和代码的简介说明
本程序为学生通讯录管理系统，将学生通讯录信息存储到文件中，并使用单链表进行信息管理。
*条件(不考虑因素)：
1.系统内存及运存足够大；
2.程序设置了头结点。(只影响创建和遍历单链表)
3.查询时必须输入完整关键字
4.只能读取由本程序生成的通讯录文件
*问题：当结构体第一个数据最大长度小于13时有出错，元素一和元素二并行显示和写入文件。
*/



/* 全局数据定义及各子函数声明 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <direct.h>
#include <windows.h>

#define SNOLEN		20	/* 学号最大字符数 */
#define NAMELEN		20	/* 姓名最大字符数 */
#define NUMLEN		20	/* 手机号最大长度 */
#define MAJORLEN	50	/* 专业名最大字符数 */
#define FNAMELEN	80	/* 文件名最大字符数 */
#define BUFLEN		80	/* 缓冲区最大字符数 */
#define bakpath 	"C:\\backups\\"			/* 备份文件目录 */
#define TRUE		1	/* 正确 */
#define FALSE		0	/* 不正确 */

/* 用单链表定义通讯录 */
typedef struct People {
	char	sno[SNOLEN];		/* 学号 */
	char	name[NAMELEN];		/* 姓名 */
	char	num[NUMLEN];		/* 手机号 */
	char	major[MAJORLEN];	/* 专业 */
	struct People *next;
} People,*Contacts;

FILE *fp;				/* 文件指针 */
char fname[FNAMELEN];	/* 文件名 */
Contacts CT;
int COUNT;				/* 联系人总数 */

void FullScreen();//控制台最大化
void MainInterface();//开始界面
void RepCryp();//管理员模式
char *Encry(char *str);//数据加密算法
void CodeInput(char *str);//密码输入
void CodeVerify();//密码验证
void CodeUpdated();//密码修改
void Welcome1();//管理员界面
void Welcome2();//普通用户界面
void CtsFnameVerify();//导入通讯录文件
int ReadPeople(FILE *fp,People *p);//从文件读取一个联系人(解密)
void Menu1();//管理员菜单
void Menu2();//普通用户菜单
void TraverseContactsFile();//显示所有联系人
void SearchPeople();//查询联系人
void NewPeople();//新建联系人到文件
int CheckContactsKey(char key[],int start,int cycle);//关键字查重
void WritePeople(FILE *fp,People *p);//向文件中写入一个新联系人(加密)
void ShowContacts(Contacts CT);//遍历单链表
void ConstructList();//由文件构造链表
void SaveContactsByList();//保存链表到文件
void BackupRestore();//备份还原菜单
int CustomCopyFile(char *file1,char *file2);//文件复制
void BackupContacts();//备份文件到C盘
void RestoreContacts();//从C盘还原备份
void BakFnameVerify(char a[]);//导入备份文件
int ModifyContacts();//修改联系人信息
int DeleteContacts();//删除联系人
int DeleteContactsByData();//按值删除
int DeleteContactsByOrder();//按序号删除
People *GetContacts(int i);//按序号查找并返回结点指针
People *LocationContacts();//按值查找并返回结点指针

/* 主函数 */
int main() {
	FullScreen();
	system("color F0");
	MainInterface();
	return 0;
}

/* 密码与数据加密 */

/* 数据加密算法 */
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

/* 密码输入 */
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

/* 密码验证 */
void CodeVerify() {
	int i,res;
	char code[21],str[21],ori[]="123",choose;
	FILE *fp;
	fp=fopen("code.txt","r");
	if(fp==NULL) {
		printf("%c",'\007');
		printf("\n\t 你的初始密码为 %s ,系统登录后请及时修改!\n",ori);
		fp=fopen("code.txt","w+");
		Encry(ori);
		fputs(ori,fp);
		rewind(fp);
	}
	fscanf(fp,"%s",code);
	Encry(code);
	fclose(fp);					
	printf("\n\t 请输入密码:");
	for(i=1;;i++) {
		CodeInput(str);
		printf("\n");
		res=strcmp(str,code);
		if(res==0)
			break;
		else if(i==3) {
			system("cls");
			printf("\n\t 您已经连续输错三次密码,如果忘记密码,是否选择初始化密码(Y/N):"); //用户连续输错三次密码，可选择是否初始化密码
			while(1){
				choose=getch();
				if(choose=='Y'||choose=='y') {
					remove("code.txt");
					printf("\n\t 请输入初始密码 %s :",ori);
					CodeInput(str);
					res=strcmp(str,ori);
					if(res==0)
						break;
					else {
						printf("\n\t 对不起!您已多次输入密码错误,被系统认定为不是本程序合法用户,本系统将强制退出!");
						printf("\n\t 请按任意键退出程序!");
						exit(0);
					}
				}
				else if(choose=='N'||choose=='n') {
					printf("\t 初始化密码失败,请按任意键退出程序");
					exit(0);
				}
				else {
					puts("\t 输入不规范,请输入 Y/N (不区分大小写):");
					printf("\t ");
				}
			}
			break;
		}
		else if(i==5) {
			printf("%c",'\007');
			printf("\t 对不起!你不是本程序合法用户!\n\t请按任意键结束\n"); //用户连续输错五次密码，则退出程序
			exit(0);
		}
		printf("%c",'\007');
		printf("\t 密码输入错误!\n\t 请重新输入:");
	}
	system("cls");
}

/* 密码修改 */
void CodeUpdated() {
	char code1[21],code2[21],ch;
	int res,countl;
	system("cls");
	printf("\n\n         密码修改功能\n");
	printf("\n**********************************\n\n请输入您的新密码:");
	fflush(stdin);
	for(countl=1;;countl++) {
		CodeInput(code1);//新密码输入
		printf("\n");
		printf("请再次输入您的新密码:");
		CodeInput(code2);
		printf("\n");
		res=strcmp(code1,code2);
		if(res==0) {
			fp=fopen("code.txt","w+");
			Encry(code1);
			fputs(code1,fp);
			fclose(fp);
			printf("修改密码成功!\n返回上级:任意键\n退出程序:【Esc】\n");
			ch=getch();
			printf("\n");
			if(ch==27) {
				printf("\n\t\t感谢您的使用!");
				exit(0);
			}
			break;
		}
		else {
			if(countl>=3) {
				printf("%c",'\007');
				printf("对不起!您现在不能修改密码!\n退出程序:【Esc】    \n返回上级:任意键\n");
				ch=getch();
				printf("\n");
				if(ch==27)
					exit(0);
				break;
			}
			else {
				printf("对不起!两次输入的密码不一致\n\n请重新输入:");
				printf("%c",'\007');
			}
		}
	}
}



/* 文件的基本操作 */

/* 通讯录文件名的输入及验证 */
void CtsFnameVerify() {
	char cts[]=".cts",b[5]="";
	fflush(stdin);
	scanf("%s",fname);
	if(strrchr(fname,'.')) strcpy(b,strrchr(fname,'.'));//从右往左的第一个'.'开始到末尾，即文件扩展名
	while(strcmpi(b, cts)) {							//比较扩展名，不区分大小写
		printf("\n文件名输入有误！请重新输入形如 x.cts 的文件名.\n");
		scanf("%s",fname);
		if(strrchr(fname,'.')) strcpy(b,strrchr(fname,'.'));
	}
}

/* 通讯录备份文件名的输入及验证 */
void BakFnameVerify(char a[]) {
	char bak[]=".bak",b[5]="";
	fflush(stdin);
	scanf("%s",a);
	while(strlen(a) < 21) {
		printf("\n文件名输入有误！请重新输入形如 [xxxx-xx-xx]x.bak 的备份文件名\n");
		scanf("%s",a);
	}
	if(strrchr(a,'.')) strcpy(b,strrchr(a,'.'));
	while(strcmpi(b, bak)) {
		printf("\n文件名输入有误！请重新输入形如 [xxxx-xx-xx]x.bak 的备份文件名.\n");
		scanf("%s",a);
		if(strrchr(a,'.')) strcpy(b,strrchr(a,'.'));
	}
}

/* 文件的复制，将文件1的数据复制到文件2中 */
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

/* 从通讯录文件读取一个联系人(解密) */
int ReadPeople(FILE *fp,People *p) {
	char buf[BUFLEN];							/* 缓冲区 */
	if(fscanf(fp,"%s",buf)!=1)	return 0;	/* 文件结束 */
	strncpy(p->sno,Encry(buf),SNOLEN);
	fscanf(fp,"%s",buf);
	strncpy(p->name,Encry(buf),NAMELEN);
	fscanf(fp,"%s",buf);
	strncpy(p->num,Encry(buf),NUMLEN);
	fscanf(fp,"%s",buf);
	strncpy(p->major,Encry(buf),MAJORLEN);
	return 1;
}

/* 向通讯录文件写入一个新联系人(加密) */
void WritePeople(FILE *fp,People *p) {
	char buf[BUFLEN];							/* 定义缓冲区，不改变p的数据 */
	strcpy(buf,p->sno);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->name);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->num);
	fprintf(fp,"%s\n",Encry(buf));
	strcpy(buf,p->major);
	fprintf(fp,"%s\n",Encry(buf));
}

/* 从通讯录文件遍历所有联系人 */
void TraverseContactsFile() {
	People p;
	if((fp=fopen(fname,"r"))==NULL) {
		printf("打开文件%s失败.\n",fname);
		system("pause");
		return;
	}
	while(ReadPeople(fp,&p)!=0) {
		printf("学号	: \t%s\n",p.sno);
		printf("姓名	: \t%s\n",p.name);
		printf("手机号	: \t%s\n",p.num);
		printf("专业	: \t%s\n",p.major);
		puts("\n------------------------------\n");
	}
	printf("\n文件 %s 中共有%d条联系人记录",fname,COUNT);
	fclose(fp);
	system("pause");
}

//不能动fp，不能动fp，不能动fp！！！(转到NewPeople())
//start元素位，由结构体的定义决定，如学号为 1.解决学号手机号相同时的查重(修改时)问题
//cycle,结构体中数据种类个数，本程序为4
/* 检查学号，手机号等关键字是否重复，重复返回TRUE */
int CheckContactsKey(char key[],int start,int cycle) {
	char buf[BUFLEN];
	FILE *fp1;							//在不动fp的情况下遍历文件
	int i=1;
	if((fp1=fopen(fname,"r"))==NULL) {
		printf("打开文件%s失败.\n",fname);
		system("pause");
		return FALSE;
	}
	for(i=1;i<start;i++) if(fscanf(fp1,"%s",buf)!=1) break;//跳过关键字之前的元素位
	while(fscanf(fp1,"%s",buf)==1) {		//这里必须用等式，不能用！逻辑
		if(strcmp(Encry(buf),key)==0) {
			fclose(fp1);
			return TRUE;					/* 发现已存在相同关键字 */
		}
		for(i=1;i<cycle;i++) if(fscanf(fp1,"%s",buf)!=1) break;//跳过一个循环周期 
	}
	fclose(fp1);
	return FALSE;							/* 未发现相同关键字 */
}



/* 链表的相关操作 */

/* 由通讯录文件构造链表 */
void ConstructList() {
	People *r,*p;
	if((fp=fopen(fname,"r"))==NULL) {
		printf("打开文件%s失败.\n",fname);
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

/* 遍历单链表(有头结点) */		//这里的函数是对所有链表可用，参数不能去掉
void ShowContacts(Contacts CT) {
	People *p=CT->next;
	int order=0;
	if(!p) puts("通讯录为空！！！");
	while(p!=NULL) {
		printf("第 %d 条记录：\n",++order);
		printf("学号	: \t%s\n",p->sno);
		printf("姓名	: \t%s\n",p->name);
		printf("手机号	: \t%s\n",p->num);
		printf("专业	: \t%s\n",p->major);
		puts("\n------------------------------\n");
		p=p->next;
	}
}

/* 按序号查找并返回结点指针 */
People *GetContacts(int i) {
    People *p;
    int j;
    p=CT;
    j=0;
	if(i<0)	return NULL;			//查找位置小于0是不合法的
    while(p!=NULL&&j<i) {
        p=p->next;
        j++;
    }
    return p;
}

/* 按值查找并返回结点指针,即定位(只针对学号，手机号) */
People *LocationContacts() {
	People *p;
	char key[20],choose;
	int i=1;
	p=CT->next;
	system("cls");
	puts("【1】：按学号查找记录.");
	puts("【2】：按手机号查找记录.");
	while(i) {
		puts("请输入命令：");
		fflush(stdin);
		choose=getche();
		printf("\n");
		switch(choose) {
			case '1':
				puts("请输入学号：");
				scanf("%s",key);
				while(p!=NULL&&strcmp(p->sno,key)!=0)
					p=p->next;
				i=0;
				break;
			case '2':
				puts("请输入手机号：");
				scanf("%s",key);
				while(p!=NULL&&strcmp(p->num,key)!=0)
					p=p->next;
				i=0;
				break;
			default:
				puts("你的输入有误！！！");
				break;
		}
	}
	return p;
}

/* 删除单链表的第i个结点 */
int DeleteContactsByOrder() {
	People *p,*q;
	int i=-1;
	printf("当前通讯录中共有 %d 位联系人：\n",COUNT);
	printf("你要删除的联系人序号为：\n");
	fflush(stdin);
	scanf("%d",&i);
	p=GetContacts(i-1);
	if(p==NULL || p->next==NULL) {
		printf("删除位置不合法!\n");      //第i个结点或它的前驱结点不存在，不能执行删除操作
		return FALSE;
	}
	q=p->next;
	p->next=p->next->next;
	free(q);
	return TRUE;
}

/* 按值删除单链表中的结点,即查找删除 */
int DeleteContactsByData() {
    People *p,*q;
	char choose,key[BUFLEN];
	int i=1;									//i是输入正确时退出菜单循环的标志
    p=CT;
    q=CT->next;
	system("cls");
	puts("【1】：按学号查找记录并删除.");
	puts("【2】：按手机号查找记录并删除.");
	puts("【0】：返回上一级.");
	while(i) {
		puts("请输入命令：");
		fflush(stdin);
		choose=getch();
		switch(choose) {
			case '1':
				system("cls");
				puts("请输入要删除的联系人的学号：");
				scanf("%s",key);
				while(q!=NULL&&(strcmp(q->sno,key)!=0)) {
					q=q->next;
					p=p->next;
				}
				i=0;
				break;
			case '2':
				system("cls");
				printf("请输入要删除的联系人的手机号：");
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
				puts("你的输入有误！！！");
				break;
		}

	}
    if(q==NULL) {
        printf("含有 %s 的记录不存在！\n",key);       //要删除的值不存在或链表为空
        return FALSE;
    }
	p->next=p->next->next;
	free(q);
	return TRUE;
} 

/* 合并两种删除方式 */
int DeleteContacts() {
    char choose,result;
	int i=1;
    puts("请选择以下删除操作：");
	puts("【1】：按序号删除.");
	puts("【2】：按数据值删除.");
	puts("【0】：返回上一级.");
	while(i) {
		puts("请输入命令：");
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
				puts("你的输入有误！！！");
				break;
		}
	}
	if(result) {
		system("cls");
		COUNT--;
		puts("删除成功后通讯录中所有联系人如下：");
		ShowContacts(CT);
		printf("删除成功！");
		system("pause");
		return TRUE;
	}
	else {
		printf("删除失败！");
		system("pause");
	    return FALSE;
	}
}

/* 在链表中修改联系人信息 */
int ModifyContacts() {
	char key[20],buf[50],choose;
	People *p;
	int i=1;
	if((p=LocationContacts())==NULL) {
		puts("未找到相关记录！将返回主菜单。");
		system("pause");
		return FALSE;
	}
	system("cls");
	puts("已找到相应记录，如下：");
	printf("学号	: \t%s\n",p->sno);
	printf("姓名	: \t%s\n",p->name);
	printf("手机号	: \t%s\n",p->num);
	printf("专业	: \t%s\n",p->major);
	puts("\n------------------------------\n");
	puts("请选择你要修改的信息或退出并返回菜单：");
	puts("【1】：学号.");
	puts("【2】：姓名.");
	puts("【3】：手机号.");
	puts("【4】：专业.");
	puts("【0】：返回上一级.");
	while(i) {
		puts("请输入命令：");
		fflush(stdin);
		choose=getch();
		system("cls");
		switch(choose) {
			case '1':
				puts("请输入新的学号：");
				scanf("%s",key);
				while(CheckContactsKey(key,1,4)) {
					puts("学号是可以唯一标识联系人身份的关键字，不可重复！");
					puts("请输入新的学号：");
					scanf("%s",key);
				}
				strcpy(p->sno,key);
				i=0;
				break;
			case '2':
				puts("请输入新的姓名：");
				scanf("%s",key);
				strcpy(p->name,key);
				i=0;
				break;
			case '3':
				puts("请输入新的手机号：");
				scanf("%s",key);
				while(CheckContactsKey(key,3,4)) {
					puts("手机号是可以唯一标识联系人身份的关键字，不可重复！");
					puts("请输入新的手机号：");
					scanf("%s",key);
				}
				strcpy(p->num,key);
				i=0;
				break;
			case '4':
				puts("请输入新的专业名：");
				scanf("%s",buf);
				strcpy(p->major,buf);
				i=0;
				break;
			case '0':
				return FALSE;
			default:
				puts("你的输入有误！！！");
				break;
		}
	}
	system("cls");
	puts("修改后的联系人信息如下：");
	printf("学号	: \t%s\n",p->sno);
	printf("姓名	: \t%s\n",p->name);
	printf("手机号	: \t%s\n",p->num);
	printf("专业	: \t%s\n",p->major);
	puts("\n------------------------------\n");
	puts("修改成功.即将返回主菜单");
	system("pause");
	return TRUE;
}

/* 保存改动后的通讯录文件 */
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



/* 文件的高级操作 */

/* 在通讯录文件中搜索联系人 */
void SearchPeople() {
	int choose,result=0,i=1;					//i是输入正确时退出菜单循环的标志
	char key[50];
	People p,s;
	Contacts CT=&p;
	s.next=NULL;CT->next=&s;					//创建头结点p，为了直接使用ShowContacts()函数
	if((fp=fopen(fname,"r"))==NULL) {
		printf("打开文件%s失败.\n",fname);
		return;
	}
	puts("你可以尝试以下操作.");
	puts("【1】：按学号查找.");
	puts("【2】：按姓名查找.");
	puts("【3】：按手机号查找.");
	puts("【4】：按专业查找.");
	puts("【0】：返回上一级.");
	while(i) {
		printf("请输入命令:");
		fflush(stdin);
		choose=getch();
		switch(choose) {
			case '1':						/* 按学号查找 */
				system("cls");
				printf("请输入要查找的联系人的学号：");
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
				printf("请输入要查找的联系人的姓名：");		//输出所有符合条件的记录
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
				printf("请输入要查找的联系人的手机号：");
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
				puts("请输入要查找的联系人的专业：");
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
					return;					/* 返回菜单 */
			default:
				puts("");
				puts("你的输入有误！！！");
				break;
		}
	}
	fclose(fp);
	if(result==0) {
		printf("含有 %s 的记录在文件 %s 中未找到。\n",key,fname);
		system("pause");
		return;
	}
	else {
		puts("已找到相应记录.");
		system("pause");
		return;
	}
}

/* 添加联系人到文件中 */ 
void NewPeople() {
	People p;
	int i,n=0;
	printf("你想添加几个联系人: ");
	scanf("%d",&n);
	while(n<=0) {
		puts("输入有误，至少添加一个联系人！请重新输入：");
		fflush(stdin);
		scanf("%d",&n);
		getchar();
	}
	for(i=0;i<n;i++) {
		fp=fopen(fname,"a+");			//每输完一个记录，关闭文件以保存，是为了关键字检查
		printf("开始输入第 %d 个学生记录。\n",i+1);
		printf("输入学生学号:\t");
		scanf("%s",p.sno);
		while(CheckContactsKey(p.sno,1,4)) {
			puts("学号是可以唯一标识联系人身份的关键字，不可重复！");
			printf("输入学生学号: ");
			scanf("%s",p.sno);
		}
		printf("输入学生姓名:\t");
		scanf("%s",p.name);
		printf("输入学生手机号: ");
		scanf("%s",p.num);
		while(CheckContactsKey(p.num,3,4)) {
			puts("手机号是可以唯一标识联系人身份的关键字，不可重复！");
			printf("输入学生手机号: ");
			scanf("%s",p.num);
		}
		printf("输入学生专业: \t");
		scanf("%s",p.major);
		WritePeople(fp,&p);
		fclose(fp);
	}
	printf("添加成功！");
	ConstructList();
	system("pause");
}

/* 备份 */
void BackupContacts() {
	char Time[20],bakfname[FNAMELEN]=bakpath,bak[]=".bak",choose;
	time_t t=time(NULL);
	struct tm *ptr=localtime(&t);
	strftime(Time,20,"[%Y-%m-%d]",ptr);					//输出当前日历时间年月日
	system("cls");
	puts("当前日期为：");
	puts(Time);
	puts("请确认您真的需要现在备份吗？(Y/N)");
	while(1) {
		choose=getch();
		if(choose=='Y'||choose=='y') break;				//开始备份
		else if(choose=='N'||choose=='n') return;		//返回上一级
		else puts("输入有误！请重新输入 (Y/N) ");
	}
	mkdir(bakfname);
	strcat(bakfname,Time);
	strcat(bakfname,fname);
	strcat(bakfname,bak);
	if(CustomCopyFile(fname,bakfname)) printf("备份成功！备份文件为 %s\n",bakfname);
	else puts("备份失败！！！请检查通讯录文件是否存在且已经正常打开.");
	system("pause");
}

/* 还原 */
void RestoreContacts() {
	char choose,bakfname[FNAMELEN]=bakpath,fname2[FNAMELEN],buf[BUFLEN]="",parms[100];
	system("cls");
	puts("默认备份目录下的备份文件如下：");
	sprintf(parms,"dir /p/b/a-d %s*.bak",bakfname);
	system(parms);
	printf("\n请输入要还原的通讯录文件名(建议直接从上面复制下来)：\n");
	BakFnameVerify(fname2);										//先保证是.bak文件
	strcat(bakfname,fname2);
	strncpy(buf,fname2+12,(strlen(fname2)-4-12));				//这函数有点坑，不能完全覆盖
	strcpy(fname2,buf);
	if(CustomCopyFile(bakfname,fname2)) printf("还原成功！！！\n备份文件 %s 中的数据为已成功还原到本程序同目录下的 %s 中.\n",
	bakfname,fname2);
	else {
		puts("还原失败！！！请检查通讯录备份文件是否存在且正常.");
		system("pause");
		return;
	}
	puts("需要现在打开它吗？(Y/N)");
	while(1) {
		choose=getch();
		if(choose=='Y'||choose=='y') {
			strcpy(fname,fname2);
			ConstructList();
			puts("打开成功！即将返回主菜单.");
			system("pause");
			return;
		}
		else if(choose=='N'||choose=='n') return;		//返回上一级
		else puts("输入有误！请重新输入 (Y/N) ");
	}
}



/* 菜单页面 */

/* 备份还原菜单 */
void BackupRestore() {
	char choose;
	system("cls");
	printf("学生通讯录管理系统备份文件位于 %s 目录下.\n",bakpath);
	puts("备份文件名形如：[xxxx-xx-xx]fname.bak 其中fname为备份前的通讯录文件名.");
	puts("你可以尝试以下操作：");
	puts("【1】：备份当前文件到C盘.");
	puts("【2】：从C盘还原备份文件.");
	puts("【0】：返回上一级.");
	while(1) {
		puts("请输入命令：");
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
				puts("你的输入有误！！！");
				break;
		}
	}
}

/* 管理员菜单 */
void Menu1() {
	char choose;
	while(1) {
		system("cls");
		puts("你可以以下以下操作.");
		puts("【1】：新建联系人.");
		puts("【2】：查询联系人.");
		puts("【3】：删除联系人.");
		puts("【4】：修改联系人信息.");
		puts("【5】：显示所有联系人.");
		puts("【6】：备份与还原.");
		puts("【7】：退出通讯录系统.");
		puts("【0】：返回上一级.");
		puts("请输入命令:");
		choose=getch();
		system("cls");
		if(choose=='0') {
			return;
			exit(0);
		}
		switch(choose) {
			case '1':
				NewPeople();		/* 已有保存文件操作 */
				break;
			case '2':
				SearchPeople();
				break;
			case '3':				/* 借助链表进行删除，删除成功返回TRUE并保存文件 */
				if(DeleteContacts())	SaveContactsByList();
				break;
			case '4':				/* 在链表中修改，可以改为在文件中修改(用strcpy()) */
				if(ModifyContacts())	SaveContactsByList();
				break;
			case '5':
				TraverseContactsFile();
				break;
			case '6':
				BackupRestore();
				break;
			case '7':
				printf("\n\t感谢您的使用!");
				exit(0);
			default:
				puts("你的输入有误！！！瞧仔细点~_~");
				printf("%c",'\007');
				system("pause");
				break;
		}
	}
}

/* 普通用户菜单 */
void Menu2() {
	char choose;
	while(1) {
		system("cls");
		puts("你可以进行以下操作.");
		puts("【1】：查询.");
		puts("【2】：显示所有联系人.");
		puts("【3】：退出通讯录系统!");
		puts("【0】：返回上一级!");
		puts("请输入命令:");
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
				puts("\n\t感谢您的使用!");
				system("pause");
				exit(0);
			default:
				puts("你的输入有误！！！瞧仔细点~_~");
				printf("%c",'\007');
				system("pause");
				break;
		}
	}
}

/* 管理员界面 */
void Welcome1() {
	char choose;
	while(1) {
		puts("******************** 欢迎使用学生通讯录管理系统 ********************");
		puts("说明：从本程序同目录中导入通讯录文件或使用绝对路径(如：1.cts或C:\\1.cts)");
		printf("请输入要读取的通讯录文件名,如果没有将会创建它: ");
		CtsFnameVerify();//scanf("%s",fname);
		printf("您所输入的文件名是: %s \n",fname);
		if((fp=fopen(fname,"r"))==NULL) {
			printf("文件 %s 不存在,需要创建它并添加记录吗? (Y/N) \n",fname);
			while(1) {
				choose=getche();
				printf("\n");
				if(choose=='Y'||choose=='y') {
					NewPeople();				//新建记录,操作中已包括构造链表，直接返回
					return;
				}
				else if(choose=='N'||choose=='n') {
					system("cls");
					break;
				}
				else {
					printf("%c",'\007');
					puts("输入有误！请重新输入 (Y/N) ");
				}
			}
		}
		else break;							//文件存在且读取成功
	}
	system("pause");
	ConstructList();
	fclose(fp);
}

/* 普通用户界面 */
void Welcome2() { 
	char choose;
	while(1) {
		system("cls");
		puts("******************** 欢迎使用学生通讯录管理系统 ********************");
		puts("              说明:您是普通用户，仅有查询功能");
		puts("说明：从本程序同目录中导入通讯录文件或使用绝对路径(如：1.cts或C:\\1.cts)");
		puts("请输入学生通讯录文件名,如果不存在该文件请使用管理员身份创建它:");
		CtsFnameVerify();
		printf("您所输入的文件名是: %s \n",fname);
		if((fp=fopen(fname,"r"))==NULL) {
			system("cls");
			printf("文件%s不存在,请重新输入文件名或者使用管理员身份创建!\n",fname);
			puts("【1】重新输入文件名");
			puts("【2】返回上级,使用管理员身份创建");
			printf("\n请选择您的操作:");
			while(1) {
				choose=getch();
				if(choose=='1') break;
				else if(choose=='2') {
					system("cls");
					return;
				}
				else {
					printf("%c",'\007');
					printf("\n对不起!没有您要的选项!\n请重新选择!\n");
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

/* 管理员模式 */
void RepCryp() {
	char choose;
	while(1) {
		fflush(stdin);
		system("cls");
		printf("\n\n                               欢迎使用本系统!\n");
		printf("---------------------------------------------------------------------------------\n\n");
		printf("【1】使用系统功能 \n");
		printf("【2】修改密码 \n");
		printf("【3】退出 \n");
		printf("【0】返回上层\n");
		printf("\n请选择您的操作:");
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
			printf("\n\t感谢您的使用!");
			exit(0);
		default:
			printf("%c",'\007');
			printf("对不起!没有您要的选项!\n请重新选择!\n");
			system("pause");
			break;
		}
	}
}

/* 开始界面 */
void MainInterface() {
	char choose, ch;
	while(1) {
		fflush(stdin);
		system("cls");
		printf("\n\n\t                                 学生通讯录管理系统\n");
		printf("\t-------------------------------------------------------------------------------");
		printf("\n\t*******************************************************************************\n");
		printf("\t*                            欢迎使用学生通讯录管理系统                       *\n");
		printf("\t*                      本系统用于对学生通讯录信息进行统计整理                 *\n");
		printf("\t*                        您也可以对通讯录信息进行查询和修改                   *\n");
		printf("\t*              注:普通用户仅有查询功能,如对记录进行操作请使用管理员身份       *\n");     
		printf("\t*******************************************************************************\n\n");
		printf("\t 登录方式:\n");
		printf("\t 【1】管理员 \n");
		printf("\t 【2】普通用户 \n");
		printf("\t 【0】退出通讯录系统 \n");
		printf("\n\t 请选择登录方式:");
		choose=getche();
		if(choose=='0') {
			system("cls");
			printf("\n\t 感谢您的使用!");
			exit(0);
		}
		switch(choose) {
		case '1':
			CodeVerify();//密码验证
			RepCryp();//密码验证进入RepCryp函数
			break;
		case '2':
			Welcome2();
			break;
		default:
			printf("\t 对不起!没有您要的选项!\n\t 退出程序:【Esc】\n\t 取消退出并重新选择:任意键\n");
			printf("%c",'\007');
			ch=getch();
			if(ch==27) {
				printf("\n\t 感谢您的使用!");
				exit(0);
			}
		}
	}
}

/* 控制台最大化 */
void FullScreen() {   
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */
    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   /* 获取窗口信息 */
    /* 设置窗口信息 最大化 (取消标题栏及边框先不用) */
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE));
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);// & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER
}





