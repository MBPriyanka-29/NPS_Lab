#include<stdio.h>
#include<math.h>
int main()
{
	int r,c,i=0,n,pos=0,x;
	printf("\n Senders side : ");

	// enter the data bits
	printf("\n Enter data bits(m) : ");
	scanf("%d",&n);

	// compute r

	while(n > (int)pow(2,i)-(i+1))
		i++;
	r=i;
	c=r+n;
	printf("redundant bits number : %d",r);
	// initialise arrays
	int data[n+1],rcode[c+1],scode[c+1],red[r+1],syn[r+1];

	// Take data word as input
	printf("\nEnter data word : d0 to d%d :",n-1);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&data[i]);
	}
	printf("\nEntered dataword is : ");
	for(i=1;i<=n;i++)
	{
		printf("%d ",data[i]);
	}

	// place redundant bits
	int k=0,j=1;
	for(i=1;i<=c;i++)
	{
		if(i==(int)pow(2,k))	
		{
			scode[i]=5;
			k++;		
		}
		else
		{
			scode[i]=data[j];
			j++;		
		}
	}

	// printing postions of red and data bits
	printf("\nprinting postions of red and data bits :");
	for(i=1;i<=c;i++)
		printf("%d ",scode[i]);
	printf("\n");

	// find redundant bits
	for(i=0;i<r;i++)
	{
		red[i]=0;
		for(j=1;j<=c;j++)
		{
			if(scode[j]==5)
				continue;
			else
			{
				if((j>>i)&1)
					red[i]+=scode[j];

			}
		}
		red[i]=red[i]%2;
	}
	printf("\nRed bits are : ");
	for(i=0;i<r;i++)
		printf("%d ",red[i]);

	// place red bits in scode
	k=0;
	for(j=1;j<=c;j++)
	{
		if(scode[j]==5)
		{
		scode[j]=red[k];
		k++;
		}
	}	

	// printing code word
	printf("\n Code word at sender's side : ");
	for(i=1;i<=c;i++)
		printf("%d ",scode[i]);
	printf("\n");

	/*********************************************************** RECIEVER ************************************/

	printf("\n Recievers side : ");

	// Take code word as input
	printf("\nEnter code word : d0 to d%d :",c-1);
	for(i=1;i<=c;i++)
	{
		scanf("%d",&rcode[i]);
	}
	printf("\nEntered codeword is : ");
	for(i=1;i<=c;i++)
	{
		printf("%d ",rcode[i]);
	}

	// find syndrome bits

	for(i=0;i<r;i++)
	{
		syn[i]=0,k=0;
		for(j=1;j<=c;j++)
		{
			if(j==(int)pow(2,k))	
				k++;
			else
			{
				x=(j>>i)&1;
				if(x==1)
					syn[i]+=rcode[j];

			}
		}
		syn[i]=(syn[i]+red[i])%2;
	}
	printf("\nsyn bits are : ");
	for(i=0;i<r;i++)
		printf("%d ",syn[i]);

	// find the faulty bit
	for(i=0;i<r;i++)
		pos+=syn[i]*((int)pow(2,i));
	if(pos==0)
		printf("\nNo errors\n");
	else
	{
		printf("\n Error in pos : %d",pos);
		// correct the data

		if(rcode[pos]==0)
			rcode[pos]=1;
		else
			rcode[pos]=0;

	}


		// printing data word
		printf("\n Code word at recievers's side : ");
		k=0;
		for(i=1;i<=c;i++)
		{
		if(i==(int)(pow(2,k)))
			k++;
		else
		printf("%d ",rcode[i]);
		}
		printf("\n");
}
