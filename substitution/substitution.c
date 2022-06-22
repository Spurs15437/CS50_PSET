#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// 如何建立 一个字典


char *plain2ciper(string plaintext, string key);
bool isRecur(string key);

int main(int argc, string argv[])
{
    // 判断获取的数据是否合适
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }

        int n = strlen(argv[1]);
        if (n == 26)
        {
            if (isRecur(argv[1])) // 判断是否有重复字符
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
            else
            {
                // key

                // 获取用户明文输入
                string plaintext = get_string("plaintext:  ");

                // 明文转化为密文
                char *ciphertext = plain2ciper(plaintext, argv[1]);

                // 输出用户密文
                printf("ciphertext: %s\n", ciphertext);
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

char *plain2ciper(string plaintext, string key)
{
    static char ciphertext[100];
    int transform_[26];
    for (int k = 0, l = strlen(key); k < l; k++)
    {
        transform_[k] = toupper(key[k]) - (65 + k);
        // printf("%i\n", transform_[k]);
    }


    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            ciphertext[i] = plaintext[i] + transform_[plaintext[i] - 65];
        }
        else if (plaintext[i] > 96 && plaintext[i] < 123)
        {
            ciphertext[i] = plaintext[i] + transform_[plaintext[i] - 97];
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen((plaintext))] = '\0';
    return ciphertext;
}

bool isRecur(string key)
{
    for (int i = 0, n = strlen(key); i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                return true;
            }
        }
    }
    return false;
}