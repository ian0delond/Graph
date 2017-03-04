#include "graph_algo.h"
#include "graph_mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINI INT_MAX
#define NIL -1

void affichage(graphe_matrice *g){
	int i,j;
	for(i=0;i<g->taille;i++)
	{
		printf("\nSommet %d : \t",i);
		for(j=0;j<g->taille;j++)
		{
			printf("%3d",g->mat[j][i]);
		}
	}
	printf("\n");
}

int fEstVide(int *f,int nbs)
{
	int i;
	for (i=0;i<nbs;i++)
	{
		if(f[i]==1)
			return 0;
	}

	return 1;
}

int extraire_min(int *F,int *distance,int nbs)
{
	int imin=-1;
	int min=INT_MAX;
	int i;
	for(i=0 ; i < nbs ; i++)
	{
		if(F[i]==1)
		{
			if(distance[i]<min)
			{
				imin=i;
				min=distance[imin];
			}
		}
	}
	return imin;
}

void dijkstra(graphe_matrice *g,int s)
{
	int i,u,v;
	int *distance;
	int *pere;
	int *F;

	distance =	(int *)malloc(sizeof(int)*g->taille);
	pere =		(int *)malloc(sizeof(int)*g->taille);
	F =			(int *)malloc(sizeof(int)*g->taille);

	for(i=0;i<g->taille;i++)
	{
		distance[i]=INFINI;
		pere[i]=NIL;
		F[i]=1;
	}

	distance[s]=0;
	while(fEstVide(F, g->taille) == 0)
	{

		u = extraire_min(F, distance, g->taille);
		printf("u = %d\n",u);
		F[u] = 0;

		for(v = 0 ; v < g->taille ; v++)
		{
			if( g->mat[v][u] != 0)
			{
				if( distance[v] > distance[u] + g->mat[v][u])
				{
					distance[v] = distance[u] + g->mat[v][u];
					pere[v] = u;
					printf("v = %d, pere =%d\n",v,pere[v] );
				}
			}
		}
	}
	for(i=0;i<g->taille;i++)
		printf("%d a pour père : %d, distance de %d : %d\n",i,pere[i],i,distance[i]);
}