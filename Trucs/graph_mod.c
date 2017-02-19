struct graphe_matrice
{
	int **mat;
	int taille;
};
typedef struct graphe_matrice graphe_matrice;

void grille(graphe_matrice *g, int longueur_r)
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

void etoile(graphe_matrice *g, int coeur)
{
	int i,j;

	for(i=0;i<g->taille;i++)
		for(j=0 ; j<g->taille ; j++)
			if(i!=coeur && j!=coeur)set_edge_matrice(g,i,j,0);

}
