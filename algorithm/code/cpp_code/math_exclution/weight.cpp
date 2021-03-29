// 저울 추
// 1,3,9,27,81,243,729g 7개의 추 -> 3의 등비수열 -> 3진수!
// 물건의 무게가 입력되었을 때 양쪽의 접시에 어떤 추들을 올려놓아야 평행을 이루는지 결정하는 프로그램

int w[7]={1,3,9,27,81,243,729};
int output[9];
int three[7];
int i,j,n,idx;

void to3(int num)
{
    for(int i=0; num!=0 ;i++,num=num/3)
        three[i]=num%3;
}

// 3진법의 자릿수가 2인 자리찾기
int chk2(void)
{
    for(int i=0;i<7;i++)
        if(three[i]==2)
        {
            n=n+w[i];
            output[idx++]=w[i];
            return 2;
        }
    return 0;
}

int main(){
    scanf("%d",&n);
    output[idx++]=n;
    
    do
        to3(n);
    while(chk2()==2); // 자릿값에 2가 하나라도 있으면 반복
    
    idx++; // 저울의 중심나타내기 -> 이미 초깃값이 0이므로 index를 더한다.
    
    for(i=0;i<7;i++)
        if(three[i]==1)
            output[idx++]=w[i];
    for(i=0;i<idx;i++)
        printf("%d ",output[i]);
}