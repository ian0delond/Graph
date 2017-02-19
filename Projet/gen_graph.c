#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph_mod.h"
#include "graph_algo.h"


int gen_dir_dot (graphe_matrice *g, char *nomdot)
{
	FILE* fichier;
	int i,j;

	fichier = fopen(nomdot,"w");
	fputs("digraph G{\nsize=\"15.0,15.0\";\nratio=\"fill\";\nnode[height=0.1, width=0.1]\n",fichier);
	for(i=0;i<g->taille;i++)
		for(j=0;j<g->taille;j++)
			if(g->mat[i][j]!=0) fprintf(fichier, "\t%d -> %d [label=%d]\n",i,j,g->mat[i][j]);
	fputs("}",fichier);
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
}

int main()
{
	int i,j;
	graphe_matrice* g;
	//g=creation_graphe_complet(30);
	//affichage_graphe_matrice(g);

	time_t t;

	srand((unsigned) time(&t));

	//La génération de grille
	g = hypercube(3);
	ponderation(g,2,8);
	affichage_graphe_matrice(g);
	gen_dir_dot(g,"Z.dot");	
}

/*
gcc *.c -o AA
./AA
dot -Tpng Z.dot -o Z.png
*/