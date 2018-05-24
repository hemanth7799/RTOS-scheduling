#include<stdio.h>
#include<string.h>
#include<math.h>

int gcd(int a,int b){
	if(b==0)
		return a;
	else
		gcd(b,a%b);
}

int lcm(int a,int b){
	return((a*b)/gcd(a,b));
}

int hyperperiod(float period[],int n){
	int k=period[0];
	n--;
	while(n>=1){
		k=lcm(k,period[n--]);}
	return k;
}

int edf(float *period,int n,int t,float *deadline){
	int i,small=10000.0f,smallindex=0;
	for(int i=0;i<n;i++){
		if(period[i]<small&&(period[i]-t)<=deadline[i]){
			small=period[i];
			smallindex=i;}}
	if(small==10000.0f)
		return -1;
	return smallindex;
}

int main()
{
	int i,n,c,d,k,j,nexttime=0,time=0,task,preemption_count;
	float exec[20],period[20],individual_util[20],flag[20],release[20],deadline[20],instance[20],ex[20],responsemax[20],responsemin[20],tempmax;
	float util=0;
	printf("\nEarliest Deadline First Algorithm\n");

	FILE *read;
	read=fopen("input1.txt","r");    
	fscanf(read,"%d ",&n);
	for(i=0;i<n;i++)
	{
		fscanf(read,"%f ",&release[i]);
		fscanf(read,"%f ",&period[i]);
		fscanf(read,"%f ",&exec[i]);
		fscanf(read,"%f ",&deadline[i]);
	}
	fclose(read);
	for(i=0;i<n;i++)
	{
		individual_util[i]=exec[i]/period[i];
		util+=individual_util[i];
		responsemax[i]=exec[i];
		deadline[i]=period[i];
		instance[i]=0.0f;
	}
	util=util*100;
	if(util>100)
		printf("\nUtilisation factor = %0.2f \n\nScheduling is not possible as Utilisation factor is above 100 \n",util);
	else
	{
		printf("\nUtilisation factor = %0.2f \n\nScheduling ispossible as Utilisation factor is less than or equal to 100 \n ",util);
		printf("\nHyperperiod of the given task set is : %d\n\n",k=hyperperiod(period , n));
		c=0;
		while(time<k)
		{
			nexttime=time+1;
			task = edf(period,n,time,deadline);
			if(task==-1)
			{
				printf("-");
				time++;
				continue;
			}
			instance[task]++;
			printf("T%d ",task);
			ex[c++]=task;
			if(instance[task]==exec[task])
			{
				tempmax=nexttime-(period[task]-deadline[task]);
				if(instance[task]<tempmax)
				{
					responsemax[task]=tempmax;
				}
				else
				{
					responsemin[task]=instance[task];
				}
				if(deadline[task]==k)
				{
					responsemin[task]=responsemax[task];
				}
				period[task]+=deadline[task];
				instance[task]=0.0f;
			}

			time++;
		}
		printf("\n");
	}
	return 0;
}