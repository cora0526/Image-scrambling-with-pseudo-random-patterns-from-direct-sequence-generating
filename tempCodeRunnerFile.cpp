//用char的完整程式
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZE 10
#define ERROR 0.25
#define ERRORSIZE 256

void errorloss (char*,int,int);
void arraprint (char*,int);
void shuffle (char*,size_t);
int finderror (char*,int);
double findnearerr (char*, int, int);

int main (void)
{   

    char matrix [SIZE][SIZE]={0};
    errorloss(&matrix[0][0],ERRORSIZE,SIZE);
    
    //arraprint(&matrix[0][0],SIZE);
    //printf("-------------------------------------------------\n");
    
    
    int errorspot=0;
    double nearest_dis=0;
    double avrnearest_dis=0;
    double neighborratio=0;
    double nearbyerr=0;
    shuffle(&matrix[0][0],SIZE*SIZE);
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
    

    
    printf("相鄰比率＝%f\n平均距離=%f\n",neighborratio,avrnearest_dis);
    
    
    
    
    return 0;
}




void errorloss(char *arra,int val,int amp)
{
    int a = val/amp;
    int b = val%amp;
    for(int i=0;i<a;i++)//整數部分填值
    {
        for (int j=0;j<amp;j++)
        {
            arra[i*amp+j]=1;
        }
        
    }
    for(int t=0;t<b;t++)//餘數部分填值
    {
        arra[(a+1)*amp+t]=1;
    }
    
    return;
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

void shuffle(char *array, size_t n) //打亂矩陣
{
    sleep(1);
    srand(time(NULL));
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
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
