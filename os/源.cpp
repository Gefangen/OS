#include<iostream>
#include<cstdlib>
#include<Windows.h>

using namespace std;

typedef struct PNode
{
	struct PNode *next;    //����ָ����һ���ڵ��ָ��
	char name[10];         //������
	int Estimate_time;     //���̹�������ʱ��
	int Arrive_time;       //��������ʱ��
	char state;            //����״̬��'1'��ʾ���У�'0'��ʾ����
}*Process;

int ProcessNum;            //��������

//��ʼ����������
void Init_PCB(Process &Pro)
{
	cout << "���������������";
	cin >> ProcessNum;
	Pro = (Process)malloc(sizeof(PNode));
	Pro->next = NULL;
	Process p = Pro;
	cout << "������Ϊ"<< ProcessNum <<"�����������ʼ��Ϣ" << endl;
	cout << endl;
	while (ProcessNum--)
	{
		p = p->next = (Process)malloc(sizeof(PNode));
		cout << "������---��������ʱ��---������ʱ�䣺";
		cin >> p->name >> p->Estimate_time >> p->Arrive_time;
		p->state = '1';
		p->state = NULL;
	}
	p->next = Pro->next;
}

//���������еĽ�����Ϣ
void RunProInfo(Process Pro)
{
	Process p = Pro->next;
	do
	{
		if (p->state != '0')     //����ý���״̬����0����������
		{
			cout << "��������" << p->name << "\t��������ʱ�䣺" << p->Estimate_time << "\t" << "\t������ʱ�䣺" << p->Arrive_time << endl;
			cout << endl;
			p = p->next;
		}
		else p = p->next;
		Sleep(500);
	} while (p != Pro->next);
}

//ʱ��Ƭ��ת��
void TimeSliceRotation(Process &Pro)
{
	cout << "Begin" << endl << endl;
	int flag = ProcessNum;                 //��¼��������
	int Rota_Num = 0;                         //��¼ʱ��Ƭ����
	Process p = Pro->next;
	while (p->Estimate_time > p->Arrive_time)
	{
		Rota_Num++;               //��������ʱ��
		cout << endl << "��" << Rota_Num << "��" << "������" << p->name << "����" << endl;
		p->Arrive_time++;
		RunProInfo(Pro);
		if (p->Estimate_time == p->Arrive_time)
		{
			p->state = '0';      //�жϽ����Ƿ����
			flag--;
			cout << p->name << "���������н��������̱�ɾ����" << endl;
		}
		p = p->next;
		while (flag&&p->Estimate_time == p->Arrive_time)
		{
			p = p->next;       //ָ��ָ���ѽ������̵���һ������
		}
	}
	cout << endl;
}

int main()
{
	Process Pro;
	Init_PCB(Pro);
	RunProInfo(Pro);
	TimeSliceRotation(Pro);
	system("pause");
	return 0;
}