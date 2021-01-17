#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 2048
#define MAXLINE 10
#define MAXFILE 15

int readline(FILE* fp, char * buf){
    int i = 0;
    char ch;
    memset(buf, 0, MAXSIZE);
    do{
        ch = getchar();
        if(ch == EOF) return 1;
        if(ch == '\n') return 0;
        if(i == MAXSIZE) return 0;
        buf[i++] = ch;
    }while(1);
    
}

int main() {
    FILE* fp;
    char buf[MAXSIZE];

    char filename[MAXSIZE];
    int fileline = 0;
    int filecnt = 0;

    int res;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    do {

        sprintf(filename,
                "%02d%02d%02d_log_%02d.txt",
                tm.tm_year - 100, tm.tm_mon + 1,
                tm.tm_mday, filecnt);

        fp = fopen(filename, "w");
        if (fp == NULL) printf("can not open file\n");

        for(fileline = 0; fileline < MAXLINE; fileline++){
            res = readline(fp,buf);
            fprintf(fp,"%s\n", buf);
            printf("line:%d read:%s\n", fileline, buf);
            if(res){
                fclose(fp);
                exit(0);
            }
        }
        filecnt++;
        fclose(fp);
    } while (filecnt < MAXFILE);

    fclose(fp);

    return 0;
}

