#include <cs50.h>
#include <stdio.h>

void iscreditcard(long n);

int main(void)
{
    long n = get_long("Number: ");
    iscreditcard(n);
}

void iscreditcard(long n)
{
    // 验证数字有效
    long data1 = n;
    long data2 = n;
    long temp1, temp2, temp3, temp4, sum1, sum2;
    long middlesum = 0;
    while (data1 > 0)
    {
        temp1 = data1 % 10;
        middlesum += temp1;
        data1 /= 100;
    }
    sum1 = middlesum;
    //printf("%ld\n",sum1); // for debug
    middlesum = 0;
    data2 /= 10;
    //printf("%ld\n",data2); // for debug
    while (data2 > 0)
    {
        temp2 = data2 % 10;
        temp3 = temp2 * 2;
        // 需判断是否大于10， 大于10要把这个数字拆开求和
        if (temp3 >= 10)
        {
            temp4 = temp3 % 10 + (temp3 / 10) % 10;
        }
        else
        {
            temp4 = temp3;
        }
        //printf("%ld\n",temp2); // for debug
        middlesum += temp4;
        //printf("%ld\n",middlesum); // for debug
        data2 /= 100;
        //printf("%ld\n",data2); // for debug
    }
    sum2 = middlesum;
    //printf("%ld\n",sum2); // for debug
    int sum = sum1 + sum2;
    //printf("%d\n",sum); // for debug
    if (sum % 10 == 0)
    {
        //判断哪个信用公司
        //首先获取该数字前两位
        char s[20];
        int y1, y2;
        sprintf(s, "%ld", n);
        sscanf(s, "%1d", &y1);
        sscanf(s, "%2d", &y2);

        int i;
        int count = 0;

        for (i = 0; i <= n * 10; i++)
        {
            n /= 10;
            count++;
        }
        if (count == 15 && (y2 == 34 || y2 == 37))
        {
            printf("AMEX\n");
        }
        else if ((count == 13 || count == 16) && y1 == 4)
        {
            printf("VISA\n");
        }
        else if (count == 16 && (y2 == 51 || y2 == 52 || y2 == 53 || y2 == 54 || y2 == 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}