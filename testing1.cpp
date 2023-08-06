//用window跑shift+ctrl+B編譯
//跑./testing1.exe
//如果要在window的VS code跑還需要下載MinGW
//且加入環境變數"C:\MinGW\bin"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
//x^7 + x^3 + 1
//初始值:0b1110010=114
#define SIZEX 10
#define SIZEY 12
#define SIZE 120
#define ERROR 0.05
#define ERRORSIZE 6
#define INITIAL 0b1110010


void arraprint (char*);
int stagedefine (void);
int lfsr (int,int,int*);
void fillerr (char*,int);
int finderror (char*,int);
double findnearerr(char*,int,int);

int main (void){
    int settingmatrix[32]={7,3,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,0,0};
    char matrix [SIZEY][SIZEX]={0};
    int stage = stagedefine();
    int a = lfsr(INITIAL,stage,&settingmatrix[0]);
    for (int i=0;i<ERRORSIZE;i++)
    {   
        if (a>=(SIZEX*SIZEY)){
            printf("i=%d %d pass\n",i,a);
            a = lfsr(a,stage,&settingmatrix[0]);
            i=i-1;
            continue;
        }
        else {
            fillerr(&matrix[0][0],a);
            printf("i=%d %d\n",i,a);
            a = lfsr(a,stage,&settingmatrix[0]);
        }
        
    }
    arraprint(&matrix[0][0]);
    int errorspot = 0;
    double nearest_dis = 0;
    int nearbyerr = 0;
    double avrnearest_dis,neighborratio = 0;
    while(errorspot<SIZEX*SIZEY)
    {
        errorspot=finderror(&matrix[0][0],errorspot);
        // printf("errorspot:%d\n",errorspot);
        if (errorspot == -1)
        {
            // printf("error spot:%d error finding stop\n",errorspot);
            break;
        }
        nearest_dis = findnearerr(&matrix[0][0], errorspot, 1);
        if (nearest_dis==1)
        {nearbyerr=nearbyerr+1;}
        avrnearest_dis=nearest_dis+avrnearest_dis;
        errorspot = errorspot + 1;
    }
    avrnearest_dis= avrnearest_dis/ERRORSIZE;
    neighborratio=nearbyerr/ERRORSIZE;
    printf("neighborratio=%f\navrnearest_dis=%f\n",neighborratio,avrnearest_dis);
    return 0;
}

double findnearerr(char* matrix,int ord,int count)
{
    int x = ord % SIZEX;
    int y = ord / SIZEX;
    int xa = x - count;
    int ya = y - count;
    int pos = 0;
    double dis[2] = {0};
    dis[0] = (2 * count + 1) * sqrt(2);
    for (int i1 = 1; i1 <= count * 2; i1++)
    {
        ya = ya + 1;
        if (ya >= SIZEY || ya < 0 || xa >= SIZEX || xa < 0)
        {
            continue;
        }
        pos = xa + ya * SIZEX;
        if (matrix[pos] == 1)
        {
            dis[1] = sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));
            if (dis[1] < dis[0])
            {
                dis[0] = dis[1];
            }
        }
        else if (matrix[pos] == 0)
        {
            continue;
        }
    }
    for (int i2 = 1; i2 <= count * 2; i2++)
    {
        xa = xa + 1;
        if (ya >= SIZEY || ya < 0 || xa >= SIZEX || xa < 0)
        {
            continue;
        }
        pos = xa + ya * SIZEX;
        if (matrix[pos] == 1)
        {
            dis[1] = sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));
            if (dis[1] < dis[0])
            {
                dis[0] = dis[1];
            }
        }
        else if (matrix[pos] == 0)
        {
            continue;
        }
    }
    for (int i3 = 1; i3 <= count * 2; i3++)
    {
        ya = ya - 1;
        if (ya >= SIZEY || ya < 0 || xa >= SIZEX || xa < 0)
        {
            continue;
        }
        pos = xa + ya * SIZEX;
        if (matrix[pos] == 1)
        {
            dis[1] = sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));
            if (dis[1] < dis[0])
            {
                dis[0] = dis[1];
            }
        }
        else if (matrix[pos] == 0)
        {
            continue;
        }
    }
    for (int i4 = 1; i4 <= count * 2; i4++)
    {
        xa = xa - 1;
        if (ya >= SIZEY || ya < 0 || xa >= SIZEX || xa < 0)
        {
            continue;
        }
        pos = xa + ya * SIZEX;
        if (matrix[pos] == 1)
        {
            dis[1] = sqrt((x - xa) * (x - xa) + (y - ya) * (y - ya));
            if (dis[1] < dis[0])
            {
                dis[0] = dis[1];
            }
        }
        else if (matrix[pos] == 0)
        {
            continue;
        }
    }
    if (dis[1] == 0)
    {
        return findnearerr(matrix, ord, count + 1);
    }
    return dis[0];
}


int finderror (char* mat,int ord){
    int err;
    int i;
    for (i=ord;i<SIZEX*SIZEY;i++)
    {
        if (mat[i]==1)
        {
            err = i;
            return err;
        }
    }
    return -1;
}

void fillerr (char* mat,int s){
    mat[s]=1;
    return;
}

int lfsr (int intial, int s, int* set){
    //設定x^7 + x^3 + 1
    int mat[32]={0};
    //因為最多就32階
    int i,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10=0;
    int tem = pow(2,s)-1;
    i=1;//7
    if ((i&intial)==1)
    {
        mat[0]=1;   
    }
    else{mat[0]=0;}

    int c=0;
    int c1=s;
    int setstop=1;
    int j=1;
    for (int t=1;t<32;t++){
        c=set[t];
        if (c==0)
        {
            break;
        }
        setstop+=1;
        c1=c1-c;
        i<<=c1;
        if ((i&intial)==(pow(2,(s-c))))
        {
            mat[j]=1;
        }
        else{mat[j]=0;} 
        j+=1;
    }
    // i<<=4;//3 
    // //printf("i<<1=%d\n",i);
    // if ((i&intial)==16)
    // {
    //     i2=1;
    // }
    // else{i2=0;}        
    
    // i=i1^i2;
    for (int ii=1;ii<setstop;ii++){
        mat[0]=mat[ii]^mat[0];
    }
    mat[0]<<=(s-1);
    intial>>=1;
    // intial+=i;
    intial+=mat[0];
    intial&=tem;
    // printf("intial:%d\n",intial);
    return intial;
}

int stagedefine (void){
    int x = SIZEX;
    int y = SIZEY;
    int s = 2;
    while (1){
        if (x*y<=pow(2,s)&&x*y>pow(2,s-1)){
            return s;
        }
        s=s+1;
    }
}

void arraprint (char* mat){
    int x = SIZEX;
    int y = SIZEY;
    for (int i=0;i<x*y;i++){
        printf("%d ",mat[i]);
        if (i<x-1){
            continue;
        }
        if((i+1)%(x)==0){
            printf("\n");
        }
    }
    return;
}