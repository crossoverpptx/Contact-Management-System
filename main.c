#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact
{
	char name[10];
	char tel[20];
	char addr[30];
}con[100];

int m = 0;	// 全局变量,存放通讯录联系人个数
FILE* fp;

void readfile()
{
	if ((fp = fopen("contact.txt", "r")) == NULL)
	{
		printf("通讯录文件不存在!\n");
		if ((fp = fopen("contact.txt", "w")) == NULL)
		{
			printf("通讯录文件创建失败!\n");
			exit(0);
		}
		else
		{
			printf("通讯录文件自动创建成功!\n");
			printf("欢迎使用通讯录管理系统\n");
			system("pause");
			system("cls");
		}
	}
	else
	{
		fseek(fp, 0, 2); // 将文件指针移动到文件末尾
		if (ftell(fp) >= 0) // 返回位置标识符的当前值。如果发生错误，则返回 -1l，全局变量 errno 被设置为一个正值
		{
			rewind(fp); // 将文件内部的位置指针重新指向一个流（数据流/文件）的开头
			// feof()是检测流上的文件结束符的函数，如果文件结束，则返回非0值，否则返回0
			// C 库函数 size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 从给定流 stream 读取数据到 ptr 所指向的数组中
			for (m = 0; !feof(fp) && fread(&con[m], sizeof(struct contact), 1, fp); m++); // 将文件数据依次读入数组并计算m值即数组个数
			printf("欢迎使用通讯录管理系统\n");
		}
	}
}

void writefile()
{
	int i;
	if ((fp = fopen("contact.txt", "w")) == NULL)
		printf("文件打开失败!\n");
	for (i = 0; i < m; i++)
	{
		if (fwrite(&con[i], sizeof(struct contact), 1, fp) != 1)
			printf("文件保存错误!\n");
	}
	fclose(fp);
	printf("\n****************************************\n");
	printf("通讯录文件保存成功！\n");
	printf("请按任意键退出！\n");
	exit(0);
}

// 1、添加联系人信息
void addPerson()
{
	char a;
	printf("请输入需要添加的通讯录联系人信息\n");
	printf("请输入姓名:");
	scanf("%s",con[m].name);
	printf("请输入电话:");
	scanf("%s",con[m].tel);
	printf("请输入地址:");
	scanf("%s",con[m].addr);
	m++;
	printf("是否继续添加(y or n):\n");
	getchar();
	scanf("%c",&a);
	if(a=='y')
		addPerson();

	system("pause");
	system("cls");
}

// 2、显示联系人信息
void showPerson()
{
	int i;
	if(m!=0)
	{
		printf("以下为通讯录信息\n");
		for(i = 0 ; i < m; i++)
		{
			printf("姓名:%s\t",con[i].name);
			printf("电话:%s\t",con[i].tel);
			printf("地址:%s\n",con[i].addr);
		}
	}
	else
		printf("通讯录中无任何信息！\n");

	system("pause");
	system("cls");
}

//3、查询联系人信息
void findPerson()
{
	int i,mark=0;
	char name[10];
	printf("请输入需要查询的联系人姓名:\n");
	scanf("%s",name);
	for(i=0;i<m;i++)
	{
		if(strcmp(con[i].name,name)==0)
		{
			printf("以下是您查询的联系人信息\n");
			printf("姓名:%s\t",con[i].name);
			printf("电话:%s\t",con[i].tel);
			printf("地址:%s\n",con[i].addr);
			mark++;
		}
	}
	if(mark==0)
		printf("查无此人！\n");

	system("pause");
	system("cls");
}

//4、修改联系人信息
void modifyPerson()
{
	int i=0;
	char name[10];
	printf("请输入需要修改的联系人的姓名:\n");
	scanf("%s",name);
	while(strcmp(con[i].name,name)!=0&&i<m)
		i++;
	if(i==m)
		printf("查无此人！\n");
	else
	{
		printf("以下是您需要修改的联系人的信息\n");
		printf("姓名:%s\n",con[i].name);
		printf("电话:%s\n",con[i].tel);
		printf("地址:%s\n",con[i].addr);
		printf("请输入新姓名:");
		scanf("%s",con[i].name);
		printf("请输入新电话:");
		scanf("%s",con[i].tel);
		printf("请输入新地址:");
		scanf("%s",con[i].addr);
	}
	
	system("pause");
	system("cls");
}

//5、删除联系人信息
void deletePerson()
{
	int i,j,mark=0;
	char name[10];
	printf("请输入需要删除的联系人的姓名:\n");
	scanf("%s",name);	
	for(i=0;i<m;i++)
	{
		if(strcmp(con[i].name,name)==0)
		{
			printf("以下是您需要删除的联系人的信息\n");
			printf("姓名:%s\t",con[i].name);
			printf("电话:%s\t",con[i].tel);
			printf("住址:%s\n",con[i].addr);
			for(j=i;j<m;j++) 
				con[j]=con[j+1];
			m--;
			mark++;
			printf("删除成功\n");
			break;
		}
	}
	if(mark==0)
		printf("查无此人！\n");

	system("pause");
	system("cls");
}

// 显示菜单
void showMenu()
{
	printf("******************************\n");
	printf("*****  1、添加联系人信息  *****\n");
	printf("*****  2、显示联系人信息  *****\n");
	printf("*****  3、查询联系人信息  *****\n");
	printf("*****  4、修改联系人信息  *****\n");
	printf("*****  5、删除联系人信息  *****\n");
	printf("*****  6、保存文件并退出  *****\n");
	printf("*******************************\n");
}

int main()
{
	readfile();
	while (1)
	{
		int select = 0;

		showMenu();

		printf("请选择您需要操作的步骤(1-6):\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			addPerson();
			break;
		case 2:
			showPerson();
			break;
		case 3:
			findPerson();
			break;
		case 4:
			modifyPerson();
			break;
		case 5:
			deletePerson();
			break;
		case 6:
			writefile();
			break;
		default:
		{	
			printf("输入有误，请重新输入！");
			system("pause");
			system("cls");
		}
			break;
		}
	}

	return 0;
}
