//Following is the declaration for fread() function.
// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
//ptr :where to store
//size:以什么单位存储
//nmemb:这个单位要存储多少个
//stream:存储的东西从哪儿来，input stream
//return value:成功读取的单位数，是int类型，如果！=nmemb, 那么可能是读完了或者bug了

//Practice: write this "this is tutorialspoint" into a file called "filename"
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char c[] = "this is tutorialspoint";
    char buffer[100];

    /* Open file for both reading and writing */
    fp = fopen("file.txt", "w+");

    /* Write data to the file */
   fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   fseek(fp, 0, SEEK_SET);

   /* Read and display data */
   fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);

   return(0);
}
