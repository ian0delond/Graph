#include <limits.h>

void Dijkstra(graphe_matrice *g, int s)
{
	int u, v;
	int min;
	int i=0;
	int F[u->taille];
	int distance[g->taille];
	int pere[g->taille];

	for (u=0;u<g->taille;u++)
	{
		distance[u]=INT_MAX;
		pere[u]=-1;
	}

	while (i<g-taille){
		//valeur min de F
		for(u=0;u<g->taille;u++)
		{
			if(min>distance[u]) min=u;
		}

		u = min;
		for(v=0;v<g->taille;v++)
			if(v!=u)
				if(distance[v] > distance[u] + g->mat[u][v])
				{
					distance[v] = distance[u] + g->mat[u][v];
					pere[v]=u;
				}
		i++;
	}
	distance[s]=0;
}

int main (){

return 0;
}
