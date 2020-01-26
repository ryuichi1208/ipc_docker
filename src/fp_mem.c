#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int Cstep(const char *filePath, FILE *fp)
{
    int      currentChar;
    int      backChar = 0;
    int      commentFlag = 0;
    int     countFlag = 0;
    int        spaceFlag = 0;
    int     startFlag = 1;
    int        lineCnt = 0;
    int        nonRealCnt = 0;
    int        sharp_flag = 0;
    int        brace_flag = 0;
    int        sharpLines = 0;
    int        braceLines = 0;
    int        cF=0;
    
    while ((currentChar = fgetc(fp)) != EOF) {
        if (currentChar == '/' && backChar == '/') {
            commentFlag = 1;
        }
        else if (currentChar == '*' && backChar == '/') {
            commentFlag = 2;
            cF=2;
        }
        else if (currentChar == '/' && backChar == '*' && cF==0) {
            commentFlag = -1;
            countFlag = 2;
        }
        if(cF>0) cF--;
        if (commentFlag == 1 && backChar == '\n') {
            commentFlag = 0;
        }
        else if (commentFlag == -1) {
            if (countFlag == 0) {
                commentFlag = 0;
            }
            else {
                countFlag--;
            }
        }

        // 非コメント状態又は読み取った文字の1個前が改行文字のいずれか
        if ((startFlag == 0 && commentFlag == 0) || backChar == '\n') {
            
            // 1個前の文字が改行文字だった場合
            if (backChar =='\n') {
                lineCnt++;
                
                if (sharp_flag == 1) {
                    sharpLines++;
                }
                
                if (brace_flag == 1) {
                    braceLines++;
                }
                if (spaceFlag == 0) {
                    nonRealCnt++;
                }
                
                spaceFlag = 0;
                sharp_flag = 0;
                brace_flag = 0;
            }
            else if (!isspace(backChar)) {
                if (backChar == '{' || backChar == '}') {
                    
                    if (brace_flag == 0) {
                        brace_flag = 1;
                    }
                }
                else {
                    brace_flag = 2;
                }
                
                spaceFlag = 1;
            }
            
            if (backChar == '#') {
                sharp_flag = 1;
            }
        }
        
        startFlag = 0;
        backChar = currentChar;
    }
    Print(filePath, lineCnt, nonRealCnt, sharpLines, braceLines);    

    if (startFlag == 0) {
        lineCnt++;
    }



        if (spaceFlag == 0) {
            nonRealCnt++;
        }
        
        if (sharp_flag == 1) {
            sharpLines++;
        }
        
        if (brace_flag == 1) {
            braceLines++;
        }
    }
    
    Print(filePath, lineCnt, nonRealCnt, sharpLines, braceLines);
    return 0;
}

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
