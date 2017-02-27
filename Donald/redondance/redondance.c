#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE * fichier = NULL;
	FILE * fichier1 = NULL;
	int lignes=0;
	int i,j,y;
	char ** mot;
	char lettre;
	size_t len =0;
	fichier = fopen("../mots","r+");
	fichier1 = fopen("../motUnique","w+");
	while((lettre = fgetc(fichier))!=EOF)
	{
		if(lettre=='\n')
			lignes++;
	}
	fclose(fichier);

	fichier = fopen("../mots","r+");
    mot = (char **) malloc(sizeof(char *)*lignes);
    for(i=0;i<lignes;i++){
    	mot[i] = (char *) malloc(sizeof(char)*40);
    }
    //calculer la taille
    i=0;
    for(i=0;i<lignes;i++)
	{
		getline(&mot[i],&len,fichier);
	}
	for(i=0;i<lignes;i++)
	{
		for(j=i+1;j<lignes;j++)
		{
			y=j;
			if(strcmp(mot[i],mot[j])!=0)
			{
				mot[y]=mot[j];
				y++;
			}
			else
			{
				mot[j]="";
			}
		}	
	}

	for(i=0;i<lignes;i++)
		fprintf(fichier1,"%s", mot[i]);

	fclose(fichier1);
	fclose(fichier);
	return 0;
}