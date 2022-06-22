#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (!(argc == 2))
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    char *s = malloc(8);

    typedef uint8_t BYTE;

    BYTE buffer[512];

    int count = -1;
    bool flag = false;

    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xff) == 0xe0))
        {
            // printf("%x\n", buffer[0]); // 进来50个数
            flag = true;

            count++;

            sprintf(s, "%03i.jpg", count);

            FILE *output = fopen(s, "wb");
            fwrite(buffer, 1, 512, output);
            fclose(output);
        }
        else if (flag == true)
        {
            FILE *output = fopen(s, "a+");
            fwrite(buffer, 1, 512, output);
            fclose(output);
        }
    }
    fclose(file);
    free(s);
}