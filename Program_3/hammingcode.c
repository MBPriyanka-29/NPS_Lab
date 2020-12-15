#include<stdio.h>
#include<math.h>

int main()
{
	int i,j,r,c,n,a,x,k,pos;
	i=0;r=0;
	printf("Enter the number of data bits(m):\t");
	scanf("%d",&n);
	while (n > (int)pow(2, i) - (i + 1))  
        	i++;  
  	r=i;
    	c=r+n; 
	int scode[c+1], rcode[c+1], data[n+1], red[r+1], syn[r+1];
	printf("Redundant bits(r) : %d",r);
	printf("\nSender side : \n");
	printf("\n Enter the data bits from d0 to d%d : ",n-1);
	j=1;k=0;
	for(i=1;i<=n;i++)
		scanf("%d",&data[i]);

	for(i=1;i<=c;i++)
	{
		if(i==(int)pow(2,k)){
			scode[i]=5;
			k++;
		}
		else{
			scode[i]=data[j];
			j++;
		}
	}
	for(i=0;i<r;i++)
	{	
		red[i]=0;
		for(j=1;j<=c;j++)
		{
			if(scode[j]==5)
				continue;
			else
			{
				x=((j>>i)&1);
				if(x==1)
					red[i]+=scode[j];
			}		
		}
		red[i]=red[i]%2;
	}
	printf("\nRedundant bits are r0 to r%d :\t",r-1);
	for(i=0;i<r;i++)
		printf("%d\t",red[i]);
	printf("\n");
	j=1;k=0;
	for(i=1;i<=c;i++)
	{
		if(scode[i]==5){
			scode[i]=red[k];
			k++;
		}
	}
	printf("The codeword at sender side is: ");
	for(i=1;i<=c;i++)
		printf("%d",scode[i]);
	printf("\n");

	printf("Receiver side\n");
	printf("\nEnter the codeword at receiver side(0 to %d): ",c-1);
	for(i=1;i<=c;i++)
		scanf("%d",&rcode[i]);

	for(i=0;i<r;i++)
	{	
		syn[i]=0;k=0;
		for(j=1;j<=c;j++)
		{
			if(j==(int)pow(2,k))
				k++;
			else
			{
				x=((j>>i)&1);
				if(x==1)
					syn[i]+=rcode[j];
			}		
		}
		syn[i]=(syn[i]+red[i])%2;
	}
	printf("\nSyndrome bits are: ");
	for(i=0;i<r;i++)
		printf("%d\t",syn[i]);
	printf("\n");

	for(i=0;i<r;i++)
		pos+=(syn[i]*(int)pow(2,i));
	if(pos==0)
		printf("There is no error in received bits\n");	
	else
	{
		printf("Error at position %d\n",pos);
		if(rcode[pos]==0)
			rcode[pos]=1;
		else
			rcode[pos]=0;
		printf("\nCorrect data is: ");
		k=0;
		for(j=1;j<=c;j++)
		{
			if(j!=(int)pow(2,k))
				printf("%d",rcode[j]);
			else
				k++;
		}
		printf("\n");	
	}
}
			
