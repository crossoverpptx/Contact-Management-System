#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact
{
	char name[10];
	char tel[20];
	char addr[30];
}con[100];

int m = 0;	// ȫ�ֱ���,���ͨѶ¼��ϵ�˸���
FILE* fp;

void readfile()
{
	if ((fp = fopen("contact.txt", "r")) == NULL)
	{
		printf("ͨѶ¼�ļ�������!\n");
		if ((fp = fopen("contact.txt", "w")) == NULL)
		{
			printf("ͨѶ¼�ļ�����ʧ��!\n");
			exit(0);
		}
		else
		{
			printf("ͨѶ¼�ļ��Զ������ɹ�!\n");
			printf("��ӭʹ��ͨѶ¼����ϵͳ\n");
			system("pause");
			system("cls");
		}
	}
	else
	{
		fseek(fp, 0, 2); // ���ļ�ָ���ƶ����ļ�ĩβ
		if (ftell(fp) >= 0) // ����λ�ñ�ʶ���ĵ�ǰֵ��������������򷵻� -1l��ȫ�ֱ��� errno ������Ϊһ����ֵ
		{
			rewind(fp); // ���ļ��ڲ���λ��ָ������ָ��һ������������/�ļ����Ŀ�ͷ
			// feof()�Ǽ�����ϵ��ļ��������ĺ���������ļ��������򷵻ط�0ֵ�����򷵻�0
			// C �⺯�� size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) �Ӹ����� stream ��ȡ���ݵ� ptr ��ָ���������
			for (m = 0; !feof(fp) && fread(&con[m], sizeof(struct contact), 1, fp); m++); // ���ļ��������ζ������鲢����mֵ���������
			printf("��ӭʹ��ͨѶ¼����ϵͳ\n");
		}
	}
}

void writefile()
{
	int i;
	if ((fp = fopen("contact.txt", "w")) == NULL)
		printf("�ļ���ʧ��!\n");
	for (i = 0; i < m; i++)
	{
		if (fwrite(&con[i], sizeof(struct contact), 1, fp) != 1)
			printf("�ļ��������!\n");
	}
	fclose(fp);
	printf("\n****************************************\n");
	printf("ͨѶ¼�ļ�����ɹ���\n");
	printf("�밴������˳���\n");
	exit(0);
}

// 1�������ϵ����Ϣ
void addPerson()
{
	char a;
	printf("��������Ҫ��ӵ�ͨѶ¼��ϵ����Ϣ\n");
	printf("����������:");
	scanf("%s",con[m].name);
	printf("������绰:");
	scanf("%s",con[m].tel);
	printf("�������ַ:");
	scanf("%s",con[m].addr);
	m++;
	printf("�Ƿ�������(y or n):\n");
	getchar();
	scanf("%c",&a);
	if(a=='y')
		addPerson();

	system("pause");
	system("cls");
}

// 2����ʾ��ϵ����Ϣ
void showPerson()
{
	int i;
	if(m!=0)
	{
		printf("����ΪͨѶ¼��Ϣ\n");
		for(i = 0 ; i < m; i++)
		{
			printf("����:%s\t",con[i].name);
			printf("�绰:%s\t",con[i].tel);
			printf("��ַ:%s\n",con[i].addr);
		}
	}
	else
		printf("ͨѶ¼�����κ���Ϣ��\n");

	system("pause");
	system("cls");
}

//3����ѯ��ϵ����Ϣ
void findPerson()
{
	int i,mark=0;
	char name[10];
	printf("��������Ҫ��ѯ����ϵ������:\n");
	scanf("%s",name);
	for(i=0;i<m;i++)
	{
		if(strcmp(con[i].name,name)==0)
		{
			printf("����������ѯ����ϵ����Ϣ\n");
			printf("����:%s\t",con[i].name);
			printf("�绰:%s\t",con[i].tel);
			printf("��ַ:%s\n",con[i].addr);
			mark++;
		}
	}
	if(mark==0)
		printf("���޴��ˣ�\n");

	system("pause");
	system("cls");
}

//4���޸���ϵ����Ϣ
void modifyPerson()
{
	int i=0;
	char name[10];
	printf("��������Ҫ�޸ĵ���ϵ�˵�����:\n");
	scanf("%s",name);
	while(strcmp(con[i].name,name)!=0&&i<m)
		i++;
	if(i==m)
		printf("���޴��ˣ�\n");
	else
	{
		printf("����������Ҫ�޸ĵ���ϵ�˵���Ϣ\n");
		printf("����:%s\n",con[i].name);
		printf("�绰:%s\n",con[i].tel);
		printf("��ַ:%s\n",con[i].addr);
		printf("������������:");
		scanf("%s",con[i].name);
		printf("�������µ绰:");
		scanf("%s",con[i].tel);
		printf("�������µ�ַ:");
		scanf("%s",con[i].addr);
	}
	
	system("pause");
	system("cls");
}

//5��ɾ����ϵ����Ϣ
void deletePerson()
{
	int i,j,mark=0;
	char name[10];
	printf("��������Ҫɾ������ϵ�˵�����:\n");
	scanf("%s",name);	
	for(i=0;i<m;i++)
	{
		if(strcmp(con[i].name,name)==0)
		{
			printf("����������Ҫɾ������ϵ�˵���Ϣ\n");
			printf("����:%s\t",con[i].name);
			printf("�绰:%s\t",con[i].tel);
			printf("סַ:%s\n",con[i].addr);
			for(j=i;j<m;j++) 
				con[j]=con[j+1];
			m--;
			mark++;
			printf("ɾ���ɹ�\n");
			break;
		}
	}
	if(mark==0)
		printf("���޴��ˣ�\n");

	system("pause");
	system("cls");
}

// ��ʾ�˵�
void showMenu()
{
	printf("******************************\n");
	printf("*****  1�������ϵ����Ϣ  *****\n");
	printf("*****  2����ʾ��ϵ����Ϣ  *****\n");
	printf("*****  3����ѯ��ϵ����Ϣ  *****\n");
	printf("*****  4���޸���ϵ����Ϣ  *****\n");
	printf("*****  5��ɾ����ϵ����Ϣ  *****\n");
	printf("*****  6�������ļ����˳�  *****\n");
	printf("*******************************\n");
}

int main()
{
	readfile();
	while (1)
	{
		int select = 0;

		showMenu();

		printf("��ѡ������Ҫ�����Ĳ���(1-6):\n");
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
			printf("�����������������룡");
			system("pause");
			system("cls");
		}
			break;
		}
	}

	return 0;
}
