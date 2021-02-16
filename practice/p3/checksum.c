#include<stdio.h>
unsigned fields[10];
unsigned short checksum()
{
	int i;
	int sum=0;
	printf("\nEnter IP header in the format of 16 bit words : \n");
	for(i=0;i<9;i++)
		{
			// its %x !!!!!!!!!!!!1
			scanf("%x",&fields[i]);
			sum=sum+(unsigned short)fields[i];
			while(sum>>16)
				sum=(sum>>16)+(sum & 0xFFFF);
				
		}
	sum = ~sum;
	return (unsigned short)sum;
}
int main()
{
int sender,reciever;
printf("\nSender's side : ");
sender=checksum();
printf("\nchecksum at sender : %x ",sender);
printf("\nReciever's side : ");
reciever=checksum();
printf("\nchecksum at reciever : %x ",reciever);
if(sender==reciever)
	printf("\n There's no error!\n");
else
	printf("\n Error deteched!\n");
}
/*
4500
003c
1c46 
4000 
4006
ac10
0a63
ac10
0a0c
*/
