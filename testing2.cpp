//用window跑shift+ctrl+B編譯
//跑./testing1.exe
//如果要在window的VS code跑還需要下載MinGW
//且加入環境變數"C:\MinGW\bin"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define INITIAL 0b111

int lfsr (int,int,int*);

int main (void){
    int settingmatrix[32]={22,1,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,0,0};
    int stage = 22;
    int a = lfsr(INITIAL,stage,&settingmatrix[0]);
    int temp = a;
    int i = 0;
    while (1)
        {
            i += 1;
            a = lfsr(a,stage,&settingmatrix[0]);
            if (temp==a)
            {
                printf("i:%d",i);
                break;
            }
            FILE *fp = NULL ;
            fp = fopen("22m-seq.csv","a");
            fprintf(fp,"%d\n",a);
            fclose(fp);
        } 

    return 0;
}



int lfsr (int intial, int s, int* set){
    int mat[32]={0};
    //因為最多就32階
    int tem = pow(2,s)-1;
    int i=1;//7
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
