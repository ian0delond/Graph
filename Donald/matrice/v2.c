#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct liste 
{
	int mot;
	int poids;
	struct liste *next;
};
typedef struct liste liste;

struct graphe
{
	liste ** ladj;
	int taille;
};
typedef struct graphe graphe;

graphe * creation_graphe_vide(int taille)
{
	int i;
	graphe *g;
	g = (graphe *)malloc(sizeof(graphe));
	g->taille=taille;
	g->ladj = (liste **)malloc(sizeof(liste *)*taille);
	for(i=0;i<taille;i++)
	{
		g->ladj[i]=NULL;
	}
	return g;
}

liste * creation_maillon(int nb,int poids)
{
	liste *l;
	l = (liste *) malloc(sizeof(liste));
	l->mot = nb;
	l->poids = poids;
	l->next = NULL;
	return l;
}

char ** ajout_mot(char * path, int taille)
{
	int i;
	char ** mots = NULL;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(path,"r+");
	for(i=0;i<taille-4;i++)
	{
		getline(&mots[i],&len,fichier);
		mots[i] = strtok(mots[i],"\n");
	}
	fclose(fichier);
	return mots;
}

/*
fonction pour recuperer le nombre de ligne d'un fichier
Et donc vu qu'on a un mot par ligne on obtient le nombre de mots
*/
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
	nb=nb+4;
	return nb;
}

/*
void ponderation(int taille_unique,int taille_tot,char ** tab_mot_Unique,char ** tab_mot_Tot)
{
	int i,j,y;
	int cnt =0;
	for(i=0;i<taille;i++)
	{
//		printf("i = %d --- %s\n", i,g->mots[i]);
		for(j=0;j<taille_tot;j++)
		{
			if(tab_mot_Tot[j]==NULL)
				break;
//			printf("j = %d --- %s\n",j,g2->mots[j]);
			if(strcmp(g->mots[i],tab_mot_Tot[j])==0)
			{
				for(y=0;y<taille_unique;y++)
				{
					if(strcmp(tab_mot_unique[y],tab_mot_Tot[j+1])==0)
					{
						cnt++;
						printf("nb match = %d --- i = %d --- j = %d --- y = %d\n",cnt,i,j,y);
						g->mat[i][y+1]=g->mat[i][y+1]+1;
						break;
					}
				}
			}
		}
	}
}*/

int main(int argc, char const *argv[])
{
	graphe * g;
	char ** tab_mot_unique;
	char ** tab_mot_tot;
	char * motunique = "../motUnique";
	char * motTot = "../mots";
	int taille_unique,taille_tot;

	taille_unique = nbsommet(motunique);
	taille_tot = nbsommet(motTot);

	g = creation_graphe_vide(taille_unique);

	tab_mot_unique = ajout_mot(motunique,taille_unique);
	tab_mot_tot = ajout_mot(motTot,taille_tot);
	ponderation(taille_unique,taille_tot,);

	return 0;
}