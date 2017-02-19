struct graphe_matrice
{
	int **mat;
	int taille;
};
typedef struct graphe_matrice graphe_matrice;

void grille(graphe_matrice *g, int longueur_r);

void etoile(graphe_matrice *g, int coeur);
