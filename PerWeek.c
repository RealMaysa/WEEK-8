#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main(){
    int x;
    int y;
    printf(" X: ");
    scanf("%d",&x);
    printf(" Y: ");
    scanf("%d",&y);
    FILE*fp;
    fp=fopen("a.txt", "w");
    fprintf(fp,"%d %d",x,y);
    fclose(fp);
    int a, b, c, suma=0, sumb=0, sumc = 0;
    fp = fopen("a.txt", "r");
while (!feof(fp)){
    a=0; b=0;
fscanf(fp, "%d %d", &a, &b);
suma += a+b; 
}
fp=fopen("b.txt", "w");
fprintf(fp,"%d\n", suma);
fclose(fp);
return 0;
}