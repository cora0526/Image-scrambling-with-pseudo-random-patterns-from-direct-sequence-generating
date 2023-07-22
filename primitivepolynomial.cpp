#include <stdio.h>
#include <stdlib.h>
#define STAGE 20

int lfsr(int);

int main (){
    int intial = 0b00111111111111111111;
    int temp = intial;
    char chart[256]={0};
    int a=1;
    int j=0;

    
    

    printf("intial=%d\n",intial); 
    for (int i=1;i<1024*1024;i++)
    {
        printf("i=%2d ",i);
        intial=lfsr(intial);
        if (intial==temp)
        {
            printf("break");
            break;
        }
    }
    
    return 0;
}

int lfsr (int intial)
{
    int l=20;
    int i,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10=0;
    i=1;//20
    if ((i&intial)==1)
    {
        i1=1;   
    }
    else{i1=0;}
    i<<=9;//11
    //printf("i<<1=%d\n",i);
    if ((i&intial)==512)
    {
        i2=1;
    }
    else{i2=0;}
    i<<=3;//8
    //printf("i<<1=%d\n",i);
    if ((i&intial)==4096)
    {
        i3=1;
    }
    else{i3=0;}
    i<<=2;//6
    //printf("i<<1=%d\n",i);
    if ((i&intial)==16384)
    {
        i4=1;
    }
    else{i4=0;}
    i<<=3;//3
    //printf("i<<1=%d\n",i);
    if ((i&intial)==131072)
    {
        i7=1;
    }
    else{i7=0;}
    i<<=1;//2
    //printf("i<<1=%d\n",i);
    if ((i&intial)==262144)
    {
        i8=1;
    }
    else{i8=0;}
     
    
    i=i1^i2^i3^i4^i7^i8;
    i<<=(l-1);
    intial>>=1;
    intial+=i;
    intial&=1048575;
    printf("%d\n",intial);
    return intial;
}
