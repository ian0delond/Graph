#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct graphe_matrice
{
	int ** mat;
	char **mots;
	int taille;
};
typedef struct graphe_matrice graphe_matrice;  

int degre_matrice(graphe_matrice *g,int s)
{
	int i,d=0;
	for(i=0;i<g->taille;i++)
	{
		if(g->mat[s][i]!=0) d++;
	}
	return d;
}

void affichage_graphe_matrice(graphe_matrice *g)
{
	int i,x,y;
	printf("\n Le graph contient %d sommets",g->taille);
	printf("\n Matrice:\n\t");
	for (i=0;i<g->taille;i++)
	{
		if(i<10)	printf(" [%d]",i);
		else		printf("[%d",i);
	}
	printf("\n");
	for (y=0;y<g->taille;y++)
	{
		printf("\n[%d]\t",y);
		for(x=0;x<g->taille;x++)
		{
			printf(" %2d ",g->mat[x][y]);
		}
		printf("\t degre : %d\n",degre_matrice(g,y));
	}
}

int gen_dot (graphe_matrice *g, char *nomdot)
{
	FILE* fichier;
	int i,j;

	fichier = fopen(nomdot,"w");
	fputs("graph G{\nsize=\"5.0,5.0\";\nratio=\"fill\";\nnode[height=0.1, width=0.1]\n",fichier);
	for(i=0;i<g->taille;i++)
		for(j=0;j<g->taille;j++)
			if(g->mat[i][j]!=0) fprintf(fichier, "%d -- %d [label=%d]\n",i,j,g->mat[i][j]);
	fputs("}",fichier);

	return 0;
}

void ponderation(graphe_matrice * g,graphe_matrice *g2)
{
	int i,j,y;
	int cnt =0;
	for(i=0;i<g->taille-4;i++)
	{
//		printf("i = %d --- %s\n", i,g->mots[i]);
		for(j=0;j<g2->taille-1;j++)
		{
			if(g2->mots[j]==NULL)
				break;
//			printf("j = %d --- %s\n",j,g2->mots[j]);
			if(strcmp(g->mots[i],g2->mots[j])==0)
			{
				for(y=0;y<g->taille-4;y++)
				{
					if(strcmp(g->mots[y],g2->mots[j+1])==0)
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

}

graphe_matrice * initialisation(int nbS)
{
	int i;
	graphe_matrice *g;
	g=(graphe_matrice*)malloc(sizeof(graphe_matrice));
	g->taille=nbS;
	g->mat=(int**)malloc(sizeof(int*)*nbS);

	for(i=0;i<nbS;i++)
	{
		g->mat[i]=(int*)calloc(nbS,sizeof(int));
	}
	g->mots=(char **)malloc(sizeof(char*)*nbS);
	return g;
}

graphe_matrice * ajout_mot(graphe_matrice * g,char * path)
{
	int i;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(path,"r+");
	for(i=0;i<g->taille-4;i++)
	{
		getline(&g->mots[i],&len,fichier);
		g->mots[i] = strtok(g->mots[i],"\n");
	}
	fclose(fichier);
	return g;

}

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

int main(int argc, char const *argv[])
{
	graphe_matrice *g, *g2;
	char * path = "../motUnique";
	char * mot = "../mots";
	int sommet,sommet2;

	printf("sommet");
	sommet = nbsommet(path);
	sommet2= nbsommet(mot);
	printf("init");
	g = initialisation(sommet);
	g2 = initialisation(sommet2);
	printf("ajout");
	g = ajout_mot(g,path);
	g2 = ajout_mot(g2,mot);
	printf("mot : %d --> %s\n", 17000,g2->mots[17000] );
	printf("Nombre de sommets de g: %d\n",g->taille);
	printf("Nombre de sommets de g2: %d\n",g2->taille);

	printf("ponde");
	ponderation(g,g2);
	gen_dot(g,"AA");

	return 0;
}