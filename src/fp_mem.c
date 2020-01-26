#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(void)
{
    FILE       *fp;
    int        lineCnt;
    int        sharpLines = 0;
    int        sharp_flag = 0;
    int        braceLines = 0;
    int        brace_flag =0;
    int        ch;

    if ((fp = fopen("a.c", "r")) == NULL) {
        printf("open error\n");
        exit(EXIT_FAILURE);
    }
    while((ch = fgetc(fp)) != EOF) {
        if (ch =='\n') {
            if (sharp_flag == 1) 
                sharpLines++;
            if (brace_flag ==1)
                braceLines++;
            sharp_flag = 0;
        }
        else if (!isspace(ch)){
            if (ch == '{' || ch == '}')
                if(brace_flag==0)
                    brace_flag=1;
            else
                brace_flag=2;
        }
        if (ch=='#') {
            sharp_flag = 1;
        }
    }
    printf("pre = %d\n", sharpLines);
    printf("surronds = %d\n", braceLines);
    
    return 0;
}
