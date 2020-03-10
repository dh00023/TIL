#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 어떤 수에서 자릿수의 위치를 바꾸었을때 소수인것을 구하시오. ex) 23은소수, 32는 합성수
/*
    1. 숫자 자릿수 분리하기
    2. 순열 만들기
    3. 자료 정렬하기
    4. 소수 확인하기
 */
int a[6];
int allnum[2000],alli;

int compare(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}

int chk(int n)
{
    int i;
    if(n==1) return -1;
    
    for(i=2;i<n;i++)
        if(n%i==0) return -1;
    return 0;
}
void swap(int *a,int *b)
{
    int temp;
    temp=*a; *a=*b; *b=temp;
}
void P(int i,int last)
{
    int num=0,j,k;
    if(i==last)
    {
        for(k=0;k<=last;k++)
            num+=a[k]*(int)pow((double)10,(double)k);
        allnum[alli++]=num;
    }
    else
        for(j=i;j<=last;j++)
        {
            swap(&a[i],&a[j]);
            P(i+1,last);
            swap(&a[i],&a[j]);
        }
}

int main(){
    int n,i,last,prev=-1;
    scanf("%d",&n);
    for(i=0;i<6;i++)
        if(n!=0)
        {
            a[i]=n%10;
            n/=10;
            last = i;
        }
    P(0,last);
    qsort(allnum,alli,sizeof(int),compare);
    for(i=0;i<alli;i++)
    {
        if(chk(allnum[i])==0)
            if(prev!=allnum[i])
            {
                printf("%d ",allnum[i]);
                prev=allnum[i];
            }
    }
    if(prev==1)printf("0");
    return 0;
}
