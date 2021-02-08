#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

long int gcd(long int a,long int b)
{
	if(a==0)
		return b;
	if(b==0)
		return a;
	return gcd(b,a%b); // A%B
}

long int isprime(long int a)
{
	int i;
	for(i=2;i<a;i++)  // CHECK FROM 2
	{
		if(a%i==0) // A%I	
			return 0;
	}
	return 1;
}
long int encrypt(char ch,long int e,long int n)
{
	long int temp =ch;
	for(int i=1;i<e;i++)
		temp=(temp*ch)%n;
	return temp;
}

char decrypt(long int ch,long int d,long int n) // check return type
{
	long int temp =ch;
	for(int i=1;i<d;i++)
		temp=(temp*ch)%n;
	return temp;
}
int main()
{
	char text[256],dec_msg[256];
	long int cipher[256];
	int i;

	long int p,q,n,e,d,phi;
	printf("\nEnter the string to encrypt : ");
	scanf("%s",&text);
	printf("\nEntered string : ");
	int len=strlen(text);
	for(i=0;i<strlen(text);i++)
		printf("%c",text[i]);
	do{
		p=rand()%50;
	}while(!isprime(p));

	do{
		q=rand()%50;
	}while(!isprime(q));
	n = p * q;
	phi = (p - 1) * (q - 1);

	do {
		e = rand() % phi;
	} while (gcd(phi, e) != 1);
	printf("\ne : %ld,",e);
	do {
		d = rand() % phi;
	} while (((d*e) % phi) != 1);
		printf("\nd : %ld,",d);

	printf("\n p : %ld\nq : %ld\nn=pq : %ld\n phi=(p-1)(q-1) : %ld\nPublic key{e,n} : %ld,%ld\nPrivate key{d,n} : %ld,%ld\n",p,q,n,phi,e,n,d,n);
	printf("\n Encryped msg : ");

	// write len for all for loops
	for(i=0;i<len;i++)
		cipher[i]=encrypt(text[i],e,n);

	for(i=0;i<len;i++)
		printf("%ld",cipher[i]);

	for(i=0;i<len;i++)
		dec_msg[i]=decrypt(cipher[i],d,n);

		printf("\n Decryped msg : ");
	for(i=0;i<len;i++)
		printf("%c",dec_msg[i]); // its %c !!!!!!!!!!!!!!!!!!!!!!!








}
