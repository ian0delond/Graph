#include <stdio.h>
#include<stdlib.h>

struct graphe_tab
{
	int *mat;
	int taille;
};
typedef struct graphe_tab graphe_tab;

graphe_tab * initialisation(int nbS)
{
	int i;
	graphe_tab *g;
	g=(graphe_tab*)malloc(sizeof(graphe_tab));
	g->taille=nbS;
	g->mat=(int*)malloc(sizeof(int)*nbS);

	return g;
}

void set_edge_matrice(graphe_tab *g,int a, int b,int val)
{

}

int degre_matrice(graphe_tab *g,int s)
{
	int i,d=0;
	for(i=0;i<g->taille;i++)
	{
		if(g->mat[s][i]!=0) d++;
	}
	return d;
}
*/
void affichage_graphe_tab(graphe_tab *g)
{
	int i,x,y;
	printf("\n Le graph contient %d sommets",g->taille);
	printf("\n Matrice:\n");
	for (i=0;i<g->taille;i++)
	{
		if(i<10)	printf("[0%d] -- %d\n",i, g->mat[i]);
		else		printf("[%d] -- %d\n",i, g->mat[i]);
	}
	printf("\n");
}

graphe_tab * creation_graphe_complet(int n)
{
	int i;
	graphe_tab * g;
	g=initialisation(n);
	return g;
}
/*
void grille(graphe_tab *g, int longueur_r)
{
	int i,j;
	for(i=0;i<g->taille;i++)
	{
		for(j=0 ; j<g->taille ; j++)
		{
			set_edge_matrice(g,i,j,0);
		}
	}
	for(i=0;i<g->taille;i++)
	{
		if(i < g->taille-1)				set_edge_matrice(g,i,i+1,1);
		if(i < g->taille-longueur_r)	set_edge_matrice(g,i,i+longueur_r,1);
}
}

void etoile(graphe_tab *g, int coeur)
{
	int i,j;

	for(i=0;i<g->taille;i++)
		for(j=0 ; j<g->taille ; j++)
			if(i!=coeur && j!=coeur)set_edge_matrice(g,i,j,0);

}

graphe_tab * ajouter_sommet(graphe_tab *g){
	int i,j;
	graphe_tab *nouv_g;
	nouv_g = creation_graphe_complet(g->taille+1);
	for(i=0;i<g->taille;i++)
	{
		for(j=0;j<i;j++)
			set_edge_matrice(nouv_g,i,j,g->mat[i][j]);
	}
	free(g);
	return nouv_g;
}

graphe_tab * supprimer_sommet(graphe_tab *g, int s)
{
	int i,j;
	graphe_tab *nouv_g;

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
*/
int main()
{
	int i,j;
	graphe_tab* g;
	g=creation_graphe_complet(12);
	//affichage_graphe_tab(g);

	//La génération de grille
	//g=ajouter_sommet(g);
	affichage_graphe_tab(g);
}
