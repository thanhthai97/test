#include<fcntl.h>
#include<iostream>

int main()
{
    char ch = '7';
    FILE *file = fopen("data.txt","w");
        if(file == NULL)
        {
            printf("Error !!!");
            exit(1);
        }
        fprintf(file,"%s",ch);
        fclose(file);
        printf("Wrote %s\n",ch);
}