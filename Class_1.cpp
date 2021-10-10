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
 player p[5], *ptr;
for (i = 0; i < 5; i++){
    printf("ENTER YOUR NAME: ");
    scanf("%s",&p[i].name);
    p[i].level = i;
    p[i].score = i*100;
}
 ptr = p;
for (i = 0; i < 5; i++) {
FILE* fp;
fp = fopen("mytestfile.txt", "a");
fprintf(fp,"name : %s\t", ptr->name);
fprintf(fp,"level : %d\t", ptr->level);
fprintf(fp,"score : %d\n", ptr->score);
ptr++;
}
return 0;
}