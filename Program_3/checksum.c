#include <stdio.h>
unsigned fields[10];
unsigned short checksum()
{
    int i;
    int sum = 0;
    printf("\nEnter IP header in the format : 16 bit words\n");
    for (i = 0; i < 9; i++)
    {
        printf("\n Enter for field %d: ", i + 1);
        scanf("%x", &fields[i]);

        sum = sum + (unsigned short)fields[i];
        while (sum >> 16) // right shift sum, if 1, then add it to sum
            sum = (sum & 0xFFFF) + (sum >> 16);
    }
    sum = ~sum;
    return (unsigned short)sum;
}
int main()
{
    unsigned short r1, r2;
    printf("\nSENDER : ");
    r1 = checksum();
    printf("\n Computed checksum at sender %x", r1);
    getchar();
    //fflush(stdin);
    printf("\nRECIEVER");
    r2 = checksum();
    printf("\n Computed checksum at reciever's side %x", r2);
    if (r1 == r2)
        printf("\n NO ERROR \n");
    else
    {
        printf("\n ERROR IN DATA RECIEVED \n ");
    }

    // 4500 003c 1c46 4000 4006 ac10 0a63 ac10 0a0c
}