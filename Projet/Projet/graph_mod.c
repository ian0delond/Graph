#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void set_edge_matrice_uni(graphe_matrice *g,int a, int b,int val)
{
    g->mat[a][b]=val;
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
		printf("\t degre : %d\n",degre_matrice(g,y));
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

void ponderation(graphe_matrice *g, int min, int max)
{
	int i,j;
	for(i=0;i<g->taille;i++)
		for(j=0;j<g->taille;j++)
			if(g->mat[i][j]!=0)
				g->mat[i][j]=rand()%(max-min)+min;
}

void grille(graphe_matrice *g, int longueur_r)
{
	int i,j;
	for(i=0;i<g->taille;i++)
		for(j=0 ; j<g->taille ; j++)
			set_edge_matrice(g,i,j,0);

	for(i=0;i<g->taille;i++)
	{
		if(i < g->taille-1)				set_edge_matrice(g,i,i+1,1);
		if(i < g->taille-longueur_r)	set_edge_matrice(g,i,i+longueur_r,1);
	}
}

void etoile(graphe_matrice *g, int coeur)
{
	int i,j;

	for(i=0;i<g->taille;i++)
		for(j=0 ; j<g->taille ; j++)
			if(i!=coeur && j!=coeur)set_edge_matrice(g,i,j,0);

}

void cycle(graphe_matrice*g)
{
	int i;

	for(i=0;i<g->taille-1;i++)
		set_edge_matrice_uni(g,i,i+1,1);
	set_edge_matrice_uni(g,i,0,1);
}

graphe_matrice * randomgraph(int n,int p)
{
	int i,j;
	graphe_matrice* g;

	g = initialisation(n);

	for ( i = 0; i < n; i++)
		for( j = 0; j < n; j++)
			if(i!=j && rand()%n > p) set_edge_matrice_uni(g,i,j,1);

	return g;
}

int puiss(int degre)
{
	int i,S=1;

	for(i=0;i<degre;i++)
		S=S*2;
	return S;
}

graphe_matrice* hypercube(int degre)
{
	if(degre<=0)
	{
		perror("degré de l'hypercube doit être positif");
		exit(3);
	}

	int S,d,i,j;
	graphe_matrice*g;

	S=puiss(degre);
	printf("degré : %d -- sommets : %d\n", degre,S);
	g=initialisation(S);

	S=1;
	for(d=0;d<degre;d++)
	{
		//clone cube précédent
		for(i=0;i<S;i++)
			for(j=0;j<S;j++)
				set_edge_matrice(g,i+S,j+S,g->mat[i][j]);
		//relie les cubes
		for(i=0;i<S;i++)
		{
			set_edge_matrice(g,i,i+S,1);
		}
		S=S*2;
	}
	//nettoie tableau
	for(i=0;i<puiss(degre);i++)
		for(j=0;j<i;j++)
			set_edge_matrice_uni(g,i,j,0);

	return g;
}