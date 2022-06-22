#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


char *plain2ciper(string plaintext, int key);

int main(int argc, string argv[])
{
    // 判断获取的数据是否合适
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // 将字符串转为整形
        int origin_key = atoi(argv[1]);
        int key = origin_key % 26;

        // 获取用户明文输入
        string plaintext = get_string("plaintext:  ");

        // 明文转化为密文
        char *ciphertext = plain2ciper(plaintext, key);

        // 输出用户密文
        printf("Ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

char *plain2ciper(string plaintext, int key)
{
    static char ciphertext[50];
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if ((plaintext[i] > 64 && plaintext[i] < 91) && (plaintext[i] + key > 90 && plaintext[i] + key < 97))
        {
            ciphertext[i] = plaintext[i] + key - 26;
            // printf("%s,%lu\n", ciphertext, strlen(plaintext));
        }
        else if ((plaintext[i] > 96 && plaintext[i] < 123) && plaintext[i] + key > 122)
        {
            ciphertext[i] = plaintext[i] + key - 26;
            // printf("%s,%lu\n", ciphertext, strlen(plaintext));
        }
        else if ((plaintext[i] > 64 && plaintext[i] < 91) || (plaintext[i] > 96 && plaintext[i] < 123))
        {
            ciphertext[i] = plaintext[i] + key;
            // printf("%s,%lu\n", ciphertext, strlen(plaintext));
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen((plaintext))] = '\0';
    // printf("%s\n", ciphertext);
    return ciphertext;
}