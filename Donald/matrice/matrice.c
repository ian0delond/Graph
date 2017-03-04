#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct graphe_matrice graphe_matrice;  
struct chaine
{
	int indice_matrice;
	int poids;
	struct chaine * next;
};
typedef struct chaine chaine;



//initialisation indice_matrice
chaine * init_indice_matrice(chaine *c,int taille)
{
	int i;
	for(i=0;i<taille;i++){
		c[i].indice_matrice=i;
		c[i].next = NULL; 
	}
	return c;
}

chaine * creation_final(chaine *c,int tailleC,char ** motsUnique,char ** motsComplet,int tailleMotTotal)
{
	int i,j,k;
	for(i=0;i<tailleC;i++)
	{
		for(j=0;j<tailleMotTotal;j++)
		{
			if(motsUnique[i]==motsComplet[j])
			{
				if(c[i].next==NULL)
				{
					for(k=0;k<tailleC;k++)
					{
						if(motsUnique[k]==motsComplet[j+1])
						{
							c[i].next = &c[k];
						}
					}
				}
				else if(motsUnique[c[i].next->indice_matrice]==motsComplet[j+1])
				{
					c[i].poids++;
				}
			}
		}
	}
	return c;
}

// Fonction effectuant l'allocation dynamique du tableau de mots
char ** initialisationTabMots(int taille)
{
	char ** mots;
	int i;
	mots = (char**) malloc(sizeof(char **)*taille);
	//Ne pas oublier d'initialiser chaque sous tableau sinon on se retrouve comme un connard avec une segfault !
	for(i=0;i<taille;i++)
		mots[i]=(char*) malloc(sizeof(char*));
	return mots;
}

// Fonction effectuant l'allocation dynamique du tableau de liste chainé
chaine * initialisationTabChaine(int taille)
{
	chaine * tab;
	int i;
	tab = (chaine *) malloc(sizeof(chaine *)*taille);
	for(i=0;i<taille;i++)
		tab[i].indice_matrice=(int) malloc(sizeof(int));
	for(i=0;i<taille;i++)
		tab[i].poids=(int) malloc(sizeof(int));
	for(i=0;i<taille;i++)
		tab[i].next = malloc(sizeof(int));
	return tab;
}
// Fonction remplissant le tableau avec tous les mots uniques
char  ** ajout_mot(char ** mots,char * path, int taille)
{
	int i;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(path,"r+");
	for(i=0;i<taille;i++)
	{
		if(getline(&mots[i],&len,fichier)!=-1)
		{
			mots[i] = strtok(mots[i],"\n");
		}else
		{
			perror("Getline");
		}
	}
	fclose(fichier);
	return mots;

}

//Fonction calculant le nombre de ligne d'un fichier (permet d'avoir le nombre de mots)
int nbsommet(char * path)
{
	int nb=0;
	char * ligne;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(path,"r+");
	while(getline(&ligne,&len,fichier)!=-1)
		nb++;
	fclose(fichier);
	return nb;
}
//Penser à renommer ce fichier il ne s'agit plus d'une matrice !

int main(int argc, char const *argv[])
{
	char * pathUnique = "../motUnique";
	int taille;
	char ** mots;
	chaine * tab;


	printf("taille\n");
	taille = nbsommet(pathUnique);
	
	//Allocation dynamique de la taille 
	printf("init mots\n");
	mots = initialisationTabMots(taille);

	//allocation  dynamique du tableau de chaine
	printf("init tab\n");
	tab = initialisationTabChaine(taille);
	
	//Remplissage du tableau de mots
	printf("ajout mot\n");
	mots = ajout_mot(mots,pathUnique,taille);

	//Remplissage du tableau de chaine
	printf("Ajout indice_matrice\n");
	tab = init_indice_matrice(tab,taille);

	tab = creation_final(tab,taille,mots,mots,taille);


	return 0;
}