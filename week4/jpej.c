#include <stdint.h>
#include <stdio.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    // first argument is the image we want to test
    // second argument is the way we open the file,r is "read"

    // file is NULL
    if (!file)
    {
        return 1;
    }

    // Read first three bytes
    BYTE bytes[3];
    // first argument : read into this buffer
    // second argument : how big this data type is
    // third&forth argument : reads from this file ,three bytes into this array
    fread(bytes, sizeof(BYTE), 3, file);

    // Check first three bytes
    // the three numbers is the margic number of jepj
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("Maybe\n");
    }
    else
    {
        printf("No\n");
    }

    // Close file
    fclose(file);
}
