#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct Pnode
{
	struct Pnode *next;
	char name[10];
	int run;
	int all;
	char state;
}*Process;

void Init_PCB(Process &Pro)
{

}