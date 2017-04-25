#include <stdio.h>
#include <stdlib.h>
#define MIN_PID 300//PID最小範圍
#define MAX_PID 5000//PID最大範圍
#define range MAX_PID-MIN_PID+1//PID範圍
#define work 5//5個工作


int *p;
int allocate_map(void)//產生及初始化PID
{
	p=(int *)calloc(range,sizeof(int));
	if(p>0)
		return 1;//成功
	else
		return -1;//失敗
}
int allocate_pid(void)//配置和傳回PID
{
int i;
for(i=0;i<range;i++)//4701個工作
	{
		if(p[i]==0)//PID可分配
		{
		p[i]=1;
		return  MIN_PID+i;
		//加上MIN_PID才是第幾個PID
		}

	}
return -1;//配置失敗
}
void release(int pid)//釋放PID
{
p[pid-MIN_PID]=0;
}
int main()
{
	allocate_map();
	int i,j;
	
	for(i=0;i<3;i++)//跑三回合 每回合五個工作
	{
		printf("round %d begin\n",i+1);//回合開始
		if(i==1)
			release(303);//釋放
		else if(i==2)
		{
			release(301);//釋放
			release(302);//釋放
		}
	
		for(j=0;j<work;j++)
		{
			int pid=allocate_pid();//配置
			if(pid>0)
				printf("%d\n",pid);//PID
			else
				printf("fail\n");//PID滿了
		}
		printf("round %d end\n",i+1);//回合結束
	}
}

