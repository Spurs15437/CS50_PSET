#include <cs50.h>
#include <stdio.h>

void buildpyramid(int n);

int main(void)
{
    // get the number of user input
    while (true)
    {
        int height = get_int("Please input a height of the pyramid: ");

        // 辨认是否属于0-8的区间
        if (height > 8)
        {
            printf("The number you input need belong to the range of [1-8]\n");
            continue;
        }
        else if (height < 1)
        {
            printf("The number you input need belong to the range of [1-8]\n");
            continue;
        }
        else
        {
            // start plot the result
            //printf("You are right, next step\n");
            //调用函数，进行绘制
            buildpyramid(height);
            break;
        }
    }
}

void buildpyramid(int n)
{

    int i, j, z;

    for (i = 0; i < n; i++)
    {
        // left
        for (j = n - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (z = 0; z <= i; z++)
        {
            printf("#");
        }

        // add two blank
        printf("  ");

        //right
        for (z = 0; z <= i; z++)
        {
            printf("#");
        }
        //for (j = n - i - 1; j > 0; j--)
        //{
        //    printf(" ");
        //}

        // 在句子末尾换行
        printf("\n");
    }
}