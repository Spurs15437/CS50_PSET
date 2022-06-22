#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float *count_per_100words(int l, int w, int s);


int main(void)
{
    // 获取用户输入
    string Userinput = get_string("Text: ");

    // 获取 L,S
    int l = count_letters(Userinput);
    int w = count_words(Userinput);
    int s = count_sentences(Userinput);
    float *Array = count_per_100words(l, w, s);

    // 获取 index
    float index = 0.0588 * Array[0] - 0.296 * Array[1] - 15.8;
    //printf("%f\n", *Array);

    // 四舍五入
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = round(index);
        // 输出
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalnum(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int length = strlen(text);
    int count = 1;
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 63 || text[i] == 33)
        {
            count++;
        }
        else if (text[i] == 46)
        {
            if (text[i - 1] == 115 && text[i - 2] == 114 && text[i - 3] == 77)
            {
                continue;
            }
            else if (text[i - 1] == 114 && text[i - 2] == 77)
            {
                continue;
            }
            else
            {
                count++;
            }
        }
    }
    return count;
}

float *count_per_100words(int l, int w, int s)
{
    static float Array[2];
    Array[0] = 100.00 * l / w;
    Array[1] = 100.00 * s / w;
    return Array;
}

