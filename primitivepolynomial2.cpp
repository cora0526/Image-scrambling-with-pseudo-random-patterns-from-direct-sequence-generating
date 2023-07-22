#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZE 2048
#define ERROR 0.05
#define ERRORSIZE 209715
//0.25 1048576
//0.2 838860
//0.15 629145
//0.1 419430
//0.05 209715

int lfsr(int);
void upset(char*,int);
void arraprint (char*,int);
int finderror (char*,int);
double findnearerr (char*, int, int);

int main (){
    int x;
    for (int j=0;j<1000;j++)
    {
    char matrix [SIZE][SIZE]={0};
    int intial = 0b0011111111111111111111;
    int temp = intial;

    int errorspot=0;
    double nearest_dis=0;
    double avrnearest_dis=0;
    double neighborratio=0;
    double nearbyerr=0;

    printf("intial=%d\n",intial); 
    for (int i=0;i<SIZE*SIZE;i++)
    {
        
        
        intial=lfsr(intial);
        
        if (i>x&&i<ERRORSIZE+x)
        {
            if (i==x+1)
            {
                printf("i=%d   ",i);
            }
            upset(&matrix[0][0],intial);
        }
        if (intial==temp)
        {
            printf("i=%d break\n",i);
            break;
        }
    }
    //arraprint(&matrix[0][0],SIZE); 

    while (errorspot<SIZE*SIZE)
    {
        errorspot=finderror(&matrix[0][0],errorspot);
        //printf("error spot:%d \n",errorspot); 
        if (errorspot==-1)
        {
            //printf("error spot:%d error finding stop\n",errorspot);
            break;
        }
        nearest_dis = findnearerr (&matrix[0][0],errorspot,1);
        //printf("nearest distense:%f \n",nearest_dis);
        if (nearest_dis==1)
        {nearbyerr=nearbyerr+1;}
        //printf("相鄰點數＝ %d\n",nearbyerr);
        avrnearest_dis=nearest_dis+avrnearest_dis;
        errorspot=errorspot+1;      
    }
    
    avrnearest_dis= avrnearest_dis/ERRORSIZE;
    neighborratio=nearbyerr/ERRORSIZE;
    FILE *fp = NULL ;
    fp = fopen("2048Dloss05m-seq.csv","a");
    
    printf("相鄰比率＝%f\n平均距離=%f\n",neighborratio,avrnearest_dis);
    fprintf(fp,"%9f\t%9f\n",neighborratio,avrnearest_dis);
    x=x+2000;
    }

    return 0;
}

void upset (char *arr,int i)
{
    arr[i]=1;
    return;
}

int lfsr (int intial)
{
    int l=22;
    int i,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10=0;
    i=1;//22
    if ((i&intial)==1)
    {
        i1=1;   
    }
    else{i1=0;}
    i<<=5;//17
    //printf("i<<1=%d\n",i);
    if ((i&intial)==32)
    {
        i2=1;
    }
    else{i2=0;}
    i<<=4;//13
    //printf("i<<1=%d\n",i);
    if ((i&intial)==512)
    {
        i4=1;
    }
    else{i4=0;}
    i<<=1;//12
    //printf("i<<1=%d\n",i);
    if ((i&intial)==1024)
    {
        i3=1;
    }
    else{i3=0;}
    i<<=4;//8
    //printf("i<<1=%d\n",i);
    if ((i&intial)==16384)
    {
        i5=1;
    }
    else{i5=0;}
    i<<=1;//7
    //printf("i<<1=%d\n",i);
    if ((i&intial)==32768)
    {
        i6=1;
    }
    else{i6=0;}
    i<<=5;//2
    //printf("i<<1=%d\n",i);
    if ((i&intial)==1048576)
    {
        i7=1;
    }
    else{i7=0;}
    i<<=1;//1
    //printf("i<<1=%d\n",i);
    if ((i&intial)==2097152)
    {
        i8=1;
    }
    else{i8=0;}
    
     
    
    i=i1^i2^i3^i4^i5^i6^i7^i8;
    i<<=(l-1);
    intial>>=1;
    intial+=i;
    intial&=4194303;
    //printf("%d\n",intial);
    return intial;
}

void arraprint(char *arra,int amp)//把整個陣列印出來
{
    
    for (int i=0;i<amp;i++)
    {
        for (int j=0;j<amp;j++)
        {
            printf("%d ",arra[i*amp+j]);
        }
        printf("\n");
    }
    return;
}
int finderror (char* matrix, int ord)//尋找錯誤
{
    int err;
    int i;
    for (i=ord;i<SIZE*SIZE;i++)
    {
        if (matrix[i]==1)
        {
            err = i;
            return err;
        }
    }
    return -1;
}

double findnearerr (char* matrix, int ord, int count)
{
    int x=ord/SIZE;
    int y=ord%SIZE;
    int xa=x-count;
    int ya=y-count;
    int pos=0;
    double dis[2]={0};
    dis[0]= (2*count+1)*sqrt(2);
    for (int i1=1;i1<=count*2;i1++)
    {
        ya = ya+1;
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
        
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i2=1;i2<=count*2;i2++)
    {
        xa=xa+1;
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i3=1;i3<=count*2;i3++)
    {
        ya=ya-1;
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i4=1;i4<=count*2;i4++)
    {
        xa=xa-1;
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    if (dis[1]==0)
    {
        return findnearerr (matrix,ord,count+1);
    }
    return dis[0];
}
