#include<iostream>
#include<cstdlib>
#include<Windows.h>

using namespace std;

typedef struct PNode
{
	struct PNode *next;    //定义指向下一个节点的指针
	char name[10];         //进程名
	int Estimate_time;     //进程估计运行时间
	int Arrive_time;       //进程运行时间
	char state;            //进程状态，'1'表示运行，'0'表示结束
}*Process;

int ProcessNum;            //进程数量

//初始化就绪队列
void Init_PCB(Process &Pro)
{
	cout << "请输入进程数量：";
	cin >> ProcessNum;
	Pro = (Process)malloc(sizeof(PNode));
	Pro->next = NULL;
	Process p = Pro;
	cout << "请依次为"<< ProcessNum <<"个进程输入初始信息" << endl;
	cout << endl;
	while (ProcessNum--)
	{
		p = p->next = (Process)malloc(sizeof(PNode));
		cout << "进程名---估计运行时间---已运行时间：";
		cin >> p->name >> p->Estimate_time >> p->Arrive_time;
		p->state = '1';
		p->state = NULL;
	}
	p->next = Pro->next;
}

//正在运行中的进程信息
void RunProInfo(Process Pro)
{
	Process p = Pro->next;
	do
	{
		if (p->state != '0')     //如果该进程状态不是0，继续运行
		{
			cout << "进程名：" << p->name << "\t估计运行时间：" << p->Estimate_time << "\t" << "\t已运行时间：" << p->Arrive_time << endl;
			cout << endl;
			p = p->next;
		}
		else p = p->next;
		Sleep(500);
	} while (p != Pro->next);
}

//时间片轮转法
void TimeSliceRotation(Process &Pro)
{
	cout << "Begin" << endl << endl;
	int flag = ProcessNum;                 //记录进程数量
	int Rota_Num = 0;                         //记录时间片轮数
	Process p = Pro->next;
	while (p->Estimate_time > p->Arrive_time)
	{
		Rota_Num++;               //更改运行时间
		cout << endl << "第" << Rota_Num << "轮" << "，运行" << p->name << "进程" << endl;
		p->Arrive_time++;
		RunProInfo(Pro);
		if (p->Estimate_time == p->Arrive_time)
		{
			p->state = '0';      //判断进程是否结束
			flag--;
			cout << p->name << "进程已运行结束，进程被删除！" << endl;
		}
		p = p->next;
		while (flag&&p->Estimate_time == p->Arrive_time)
		{
			p = p->next;       //指针指向已结束进程的下一个进程
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