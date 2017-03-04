#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph_mod.h"
#include "graph_algo.h"
#include <sys/types.h>
#include <unistd.h>

int gen_dir_dot (graphe_matrice *g, char *nomdot)
{
	FILE* fichier;
	int i,j;

	fichier = fopen(nomdot,"w");
	fputs("digraph G{\nsize=\"5.0,5.0\";\nratio=\"fill\";\nnode[height=0.1, width=0.1]\n",fichier);
	for(i=0;i<g->taille;i++)
		for(j=0;j<g->taille;j++)
			if(g->mat[i][j]!=0) fprintf(fichier, "\t%d -> %d [label=%d]\n",i,j,g->mat[i][j]);
	fputs("}",fichier);
}

int gen_dot (graphe_matrice *g, char *nom)
{
	FILE* fichier;
	int i,j;
	/*char*nomdot,command;
	strcpy(nomdot,nom);
	strcat(nomdot,".dot");*/
	fichier = fopen(nom,"w");
	fputs("graph G{\nsize=\"5.0,5.0\";\nratio=\"fill\";\nnode[height=0.1, width=0.1]\n",fichier);
	for(i=0;i<g->taille;i++)
		for(j=0;j<g->taille;j++)
			if(g->mat[i][j]!=0) fprintf(fichier, "%d -- %d [label=%d]\n",i,j,g->mat[i][j]);
	fputs("}",fichier);
	/*i = system(command);*/

}

int main()
{
	int i,j;
	graphe_matrice* g;
	g=randomgraph(6,1);

	time_t t;

	srand((unsigned) time(&t));
	//La génération de grille
	ponderation(g,1,9);
	affichage_graphe_matrice(g);

	dijkstra(g,3);
	//gen_dir_dot(g,"dijdot.dot");

	return 0;
}

/*
gcc *.c -o AA
./AA
dot -Tpng Z.dot -o Z.png
*/