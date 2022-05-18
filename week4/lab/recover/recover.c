// what to do
// 1.open memory card
// 2.look for beginning of a JEPG
// 3.open a new JEPG file
// 4.write 512 bytes until a new another JEPG is found

// more detail in JEPG:
// 1.the start of a JPEG usually demarks the end of another
// 2.first three bytes of JPEGs are:
//   0xff 0xd8 0xff
// 3.one photo will take 2048 block
// 4.the image contains 50 JPEGs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open the memory card file
    //"r" mode means read this file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Read first four bytes,iterate
    BYTE buffer[512];
    int count = 0;
    FILE *output = NULL;
    char filename[8];
     //while循环非0即执行
    while (fread(buffer, sizeof(BYTE), 512, input) || feof(input) != 512)
    {
        // find start of new JEPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //发现JEPG文件，判断它是不是第一个JEPG文件
            //如果是第一个JEPG，output就是指向NULL,因为39行的初始化
            //如果不是，说明这是另一个jepg文件的开头，我们需要关闭上一个JEPG文件
            if(output != NULL)
            {
                fclose(output);
                output = NULL;
            }
            //filename 这里是一个字符串，为什么可以用fopen打开？
            //因为fopen的第一个参数就是字符串呀
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count ++;
        }
        if(output != NULL)
        {
            fwrite(buffer,sizeof(buffer),1,output);
        }
    }
    fclose(output);
    fclose(input);
    return 0;
}
