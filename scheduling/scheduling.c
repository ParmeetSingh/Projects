#include<stdlib.h>
#include<stdio.h>
#define MINI 100000
typedef struct process
{
	int arrival;
	int exec;
	float exit;
}process;
int cmp(const void* a,const void* b)
{
	process* pa = (process*) a;
	process* pb = (process*) b;

	return (pa->arrival - pb->arrival);
}
int main(int argv,char** argc)
{
	FILE* f1=fopen(argc[1],"r");
	if(!f1)
    	   printf("file not opened\n");
	process* p=(process*)malloc(1000*sizeof(process));
	FILE* f2=fopen("output.txt","w");
	if(!f2)
    	   printf("file not opened\n");
	
	int i=0;	
	while(fscanf(f1,"%d",&p[i].arrival)!=EOF)
	{
		fscanf(f1,"%d",&p[i++].exec);
	}
	process* fcfs=(process*)malloc(1000*sizeof(process));
	process* srtf=(process*)malloc(1000*sizeof(process));
	process* rr=(process*)malloc(1000*sizeof(process));
	
	int count=i;
	for(i=0;i<count;i++)
		{
		   fcfs[i].arrival=srtf[i].arrival=rr[i].arrival=p[i].arrival;
		   fcfs[i].exec=srtf[i].exec=rr[i].exec=p[i].exec;
		}
		
	
	//first come first serve
	float time,wait_time=0,turnaround_time=0,temp;
	qsort(fcfs,count,sizeof(process),cmp);
		
	time=fcfs[0].arrival;
	for(i=0;i<count;i++)
	{
		//printf("time %f\n",time);
		if(time-fcfs[i].arrival>=0)
			temp=time-fcfs[i].arrival,time+=fcfs[i].exec;	
		else
			temp=0,time=fcfs[i].arrival+fcfs[i].exec;
		wait_time+=temp;
		//printf("%f\n",temp);
		turnaround_time+=fcfs[i].exec+temp;
	}
	fprintf(f2,"\nFirst Come First Serve\n");
	fprintf(f2,"Waiting time----%f\n",wait_time/count);
	fprintf(f2,"Turnaround time-%f\n",turnaround_time/count);

	//srtf start
	int mini,min,j;
	wait_time=turnaround_time=0;
	qsort(srtf,count,sizeof(process),cmp);
	int prev_min=MINI;
	float context_switch=0;
	time=srtf[0].arrival;
	int total_exec=0;
	for(i=0;i<count;i++)
	   {
	   total_exec+=srtf[i].exec;
	   //printf("hellllo %d ",srtf[i].arrival);
	   }
	int flag;
	prev_min=MINI; 
	
	for(i=0;i<count-1;)
	{
	   mini=MINI;
	   min=MINI;
	   flag=0;
	   for(j=0;j<count;j++)
	   {
	   
	   	if(srtf[j].exec>0 && srtf[j].arrival<=time)
	   	{
	   		if(mini>srtf[j].exec)
	   		{
	   			flag=1;
	   			mini=srtf[j].exec;
	   			min=j;
	   		}
	   	}
	   }
	    if(prev_min!=min)
	      context_switch+=0.5,prev_min=min;
	   
	   if(flag==0)
	   {
	   	for(j=0;j<count;j++)
			{
				if(srtf[j].exec>0 && srtf[j].arrival<mini && srtf[j].arrival>time)
				{
						
					mini=srtf[j].arrival;
					min=j;
				}
			}
			time=mini;	   	
	   }
	   if(time+srtf[min].exec>=srtf[i+1].arrival)
	   {
	   	srtf[min].exec-=srtf[i+1].arrival-time;
	   	time=srtf[i+1].arrival;
	   	i++;
	   }
	   else if(time+srtf[min].exec<srtf[i+1].arrival)
	   {
	   	srtf[min].exit=time+srtf[min].exec;
	   	time+=srtf[min].exec;
	   	srtf[min].exec=0;
	   	
	   }
	   
	}
	flag=1;
	while(flag==1)
	{
		mini=MINI;
	   	min=MINI;
	   	flag=0;
	   	
	   	for(j=0;j<count;j++)
	   	{
	   		if(srtf[j].exec>0)
	   		{
	   			flag=1;
	   			if(mini>srtf[j].exec)
	   			{
	   				mini=srtf[j].exec;
	   				min=j;
	   			}
	   		}
	   	   	
	   	}
	   	if(prev_min!=min)
	   	context_switch+=0.5,prev_min=min;
	   	if(flag==1)
	   	{
	   	//wait_time-=srtf[min].exec;
	   	time+=srtf[min].exec;
	   	srtf[min].exec=0;
	   	srtf[min].exit=time;
	   	}	
	}
	//for(j=0;j<count;j++)
	 //  {
//		printf(" %d %d\n",j,srtf[j].exec);	
//	   }
	  
	 for(j=0;j<count;j++)
	   {
	   	wait_time+=srtf[j].exit-srtf[j].arrival;
	   	turnaround_time+=srtf[j].exit-srtf[j].arrival;
	   	//printf("%d %d %f\n",j,srtf[j].arrival,srtf[j].exit);	
	   }
	   wait_time+=context_switch-total_exec;
	   turnaround_time+=context_switch;
	fprintf(f2,"\nShortest Remaining time first\n");
	fprintf(f2,"Waiting time----%f\n",wait_time/count);
	fprintf(f2,"Turnaround time-%f\n",turnaround_time/count);
	
	//Round robin starts
	int abc=3;
	int quant;
	for(abc=1;abc<=3;abc++)
	
	{	
		for(i=0;i<count;i++)
		{
		   rr[i].arrival=p[i].arrival;
		   rr[i].exec=p[i].exec;
		}
		if(abc==1)
		quant=50;
		else if(abc==2)
		quant=100;
		else if(abc==3)
		quant=500;
		
		int sumtotal=total_exec;
		time=rr[0].arrival;
		
		i=-1;
		int temp;
		min=MINI;
		mini=MINI;
		qsort(rr,count,sizeof(process),cmp);
		prev_min=MINI;
		context_switch=0;	
		while(sumtotal>0)
		{
			temp=0;
			while(temp<=count)
			{
			   if(i==count)
			   i=0;
			   else
			   i++;
			     if(rr[i].arrival<=time && rr[i].exec>0)
			     break;
			   temp++;		
			}
			if(prev_min!=min)
			{
				context_switch+=0.5;
				prev_min=min;	
			}
			
			min=MINI;
			mini=MINI;
	
			if(temp>count)
			{
				for(j=0;j<count;j++)
				{
					if(rr[j].exec>0 && rr[j].arrival<mini && rr[j].arrival>time)
					{
						mini=rr[j].arrival;
						min=j;
					}
				}
				i=min;
				time=mini;
			}
			if(rr[i].exec>quant)
			{
				sumtotal-=quant;
				rr[i].exec-=quant;
				time+=quant;
			}
			else if(rr[i].exec<=quant)
			{
				sumtotal-=rr[i].exec;
				time+=rr[i].exec;
				rr[i].exec=0;
				rr[i].exit=time;
			}
			
		}		
		  wait_time=0,turnaround_time=0;
		  for(j=0;j<count;j++)
			{
				wait_time+=rr[j].exit-rr[j].arrival;
				turnaround_time+=rr[j].exit-rr[j].arrival;
			}
			wait_time-=total_exec-context_switch;
			turnaround_time+=context_switch;
			fprintf(f2,"\nRound Robin for Quantum Value %d\n",quant);
			fprintf(f2,"Waiting time----%f\n",wait_time/count);
			fprintf(f2,"Turnaround time-%f\n",turnaround_time/count);
	
	}
	
	fclose(f1);
	fclose(f2);		
}
