#include <stdio.h>

int degre(int n, int graph[n][n],int S){
	int deg=0,i;

	for(i=0;i<n;i++)
	{
		deg=deg+graph[S][i];
	}
	return deg;
}

void ajout_arete(int n, int graph[n][n]){
	int graphcp[n+1][n+1],i,j;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	graphcp[i][j]=grap[i][j]
		}
		graphcp[i][n+1]=0;
	}
	for (j=0;j<n+1;j++)
		graph[n+1][j]=O;
}

void enleve_arete(){

}

void affiche_sommet(){

}

int main()
{
	int S,n=7;
	int graph[7][7]={	{0,1,1,1,1,1,1},
						{1,0,1,0,0,0,1},
						{1,1,0,1,0,0,0},
						{1,0,1,0,1,0,0},
						{1,0,0,1,0,1,0},
						{1,0,0,0,1,0,1},
						{1,1,0,0,0,1,0}	};
	for(S=0;S<n;S++)
	{
		printf("%d\n",degre(n,graph,S));
	}


	return 0;
}
