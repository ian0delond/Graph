#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int test=0;
    char lecture;
    int i=0;
    FILE * fichier = NULL;
    FILE * fichier1 = NULL;
    FILE * fichier2 = NULL;
    FILE * fichier3 = NULL;
    fichier = fopen("../Trumptweet","r+");
    fichier1 = fopen("../mots","w+");
    fichier2 = fopen("../mentions","w+");
    fichier3 = fopen("../link","w+");
    while(1)
    {
        lecture = fgetc(fichier);
        if(lecture==EOF)
        {
            break;
        }
        //printf("Lecture = %c\n",lecture);
        while((lecture<='Z'&&lecture>='A')||(lecture<='z'&&lecture>='a')||lecture=='\'')
        {
            //printf("Lecture = %c\n",lecture);
            fprintf(fichier1,"%c",lecture);
            lecture = fgetc(fichier);
            test=1;
        }
        if(lecture=='@')
        {
     	    while((lecture<='Z'&&lecture>='A')||(lecture<='z'&&lecture>='a')||lecture=='_'||lecture=='@')
            {
                printf("mentions\n");
                fprintf(fichier2,"%c",lecture);
                lecture = fgetc(fichier);
            }
            fprintf(fichier2,"\n");
        }

        if(test==1)
        {
            fprintf(fichier1,"\n");
            test=0;
        }
        i++;
    }

    fclose(fichier);
    fclose(fichier1);
    return 0;
}