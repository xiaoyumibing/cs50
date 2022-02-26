#include <stdio.h>
#include <cs50.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_s(string text);
void count_grade(float index);

int main(void)
{
    // variable name be related is best
    string text = get_string("Text:");
    int letter = count_letters(text);
    int words = count_words(text);
    int s = count_s(text);
    printf("letter:%i\n",letter);
    printf("words:%i\n",words);
    printf("sentences:%i\n",s);

    float L = 100.0 * letter / words;
    float S = 100.0 * s / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("L:%f\n",L);
    printf("S:%f\n",S);
    printf("index:%f\n",index);
    count_grade(index);
    // pass value into function ,don's declare the data type
}

int count_letters(string text)
{
    int i = 0;
    int j = 0;
    while(text[i] != '\0')
    {
        if(text[i] <= 'z'&&text[i] >= 'A')
        {
            j ++;
        }
        i ++;
    }
    return j;
}

int count_words(string text)
{
    int i = 0;
    int j = 0;
    while(text[i] != '\0')
    {
        if(text[i] == ' ')
        {
            j ++;
        }
        i ++;
    }
    return j+1;
    // the number of chararcter is better than
    // the number of space,more 1
}

int count_s(string text)
{
    int i = 0;
    int j = 0;
    while(text[i] != '\0')
    {
        if(text[i] == '.'||text[i] == '!'||text[i] == '?')
        {
            j ++;
        }
        i ++;
    }
    return j;
}

void count_grade(float index)
{
    if(index > 1 && index < 16)
    {
        printf("Grade %i\n",(int)(index+0.5));
    }
    else if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if(index <= 1)
    {
        printf("Before Grade 1\n");
    }
}

// 数据类型 函数命名 逻辑运算符 看错误的提示符号
