#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
int main()
{
int i;
struct player {
char name[50];
int level;
int score;
};
 player p[10], *ptr;
for (i = 0; i < 5; i++){
    printf("ENTER YOUR NAME: ");
    scanf("%s",&p[i].name);
    printf("LEVEL: ");
    scanf("%s",&p[i].name);
    p[i].score = i*100;
}
 ptr = p;
for (i = 0; i < 10; i++) {
FILE* fp;
fp = fopen("test.txt", "a");
fprintf(fp,"name : %s\t", ptr->name);
fprintf(fp,"level : %d\t", ptr->level);
fprintf(fp,"score : %d\n", ptr->score);
fclose(fp);
ptr++;
}
return 0;
}