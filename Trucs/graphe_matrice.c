#include <stdio.h>
#include <stdlib.h>
#include "graph_mod.h"


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

	return g;
}

void set_edge_matrice(graphe_matrice *g,int a, int b,int val)
{
    g->mat[a][b]=val;
    g->mat[b][a]=val;
}

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
		printf("\t degre : %d",degre_matrice(g,y));
	}
}

graphe_matrice * creation_graphe_complet(int n)
{
	int i,j;
	graphe_matrice * g;
	g=initialisation(n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<i;j++)
		{
			if(i!=j) {set_edge_matrice(g,i,j,1);}

		}
	}
	return g;
}

graphe_matrice * ajouter_sommet(graphe_matrice *g){
	int i,j;
	graphe_matrice *nouv_g;
	nouv_g = creation_graphe_complet(g->taille+1);
	for(i=0;i<g->taille;i++)
	{
		for(j=0;j<i;j++)
			set_edge_matrice(nouv_g,i,j,g->mat[i][j]);
	}
	free(g);
	return nouv_g;
}

graphe_matrice * supprimer_sommet(graphe_matrice *g, int s)
{
	int i,j;
	graphe_matrice *nouv_g;

	nouv_g=creation_graphe_complet(g->taille-1);

	for(i=0;i<g->taille-1;i++)
	{
		for(j=0;j<i;j++)
		{
			if(i<s)
			{
				if(j<s)	set_edge_matrice(nouv_g,i,j,g->mat[i][j]);
				else	set_edge_matrice(nouv_g,i,j,g->mat[i][j-1]);
			}
			else		set_edge_matrice(nouv_g,i,j,g->mat[i-1][j-1]);
		}
	}
	free(g);
	return nouv_g;
}

int main()
{
	int i,j;
	graphe_matrice* g;
	g=creation_graphe_complet(12);
	//affichage_graphe_matrice(g);
	//La génération de grille
	etoile(g,4);
	//g=ajouter_sommet(g);
	affichage_graphe_matrice(g);
}
