
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
const int length = 1000;
char str[length][length];
void reverseStr(char *one);
void bigSum(char *sSum, char *sFirst, char *sSecond);


int main(){
        char sum[length];
        char fir[length];
        char sec[length];
        scanf("%s\n", fir);
        while(true)
        {
                scanf("%s\n", sec);
                if(strcmp(sec, "0") == 0)
                {
                        break;
                }
                bigSum(sum, fir, sec);
                strcpy(fir,sum);
        }
        printf("%s\n", sum);
        return 0;
}
void bigSum(char *sSum, char *sFirst, char *sSecond){
        int firstLen, secondLen;
        int iFirst, iSecond, iSum;
        int carry;
        int t;
        
        carry = 0;
        t = 0;
        sSum[0] = '\0';
        firstLen = strlen(sFirst) - 1;
        secondLen = strlen(sSecond) - 1;
        while (firstLen >= 0 || secondLen >= 0){
                iFirst = sFirst[firstLen] - 48;
                iSecond = sSecond[secondLen] - 48;
                if (firstLen < 0) iFirst = 0;
                if (secondLen < 0) iSecond = 0;
                iSum = iFirst + iSecond + carry;
                carry = (iSum / 10);
                sSum[t] = (iSum % 10) + 48;
                ++t;
                --firstLen;
                --secondLen;
        }
        if (carry == 1){
                sSum[t++] = carry + 48;
        }
        sSum[t] = '\0';
        reverseStr(sSum);
}
void reverseStr(char *one){
        char temp[length];
        int h = strlen(one) - 1;
        int i = 0;
        for (int j = h; j >= 0; j--){
                temp[i] = one[j];
                ++i;
        }
        temp[i] = '\0'; // must set to null at last for "two" second string
        strcpy(one, temp);
}
