#ifndef GRAPH_MOD_H
#define GRAPH_MOD_H

struct graphe_matrice
{
	int **mat;
	int taille;
};
typedef struct graphe_matrice graphe_matrice;

graphe_matrice * initialisation(int nbS);

void set_edge_matrice(graphe_matrice *g,int a, int b,int val);

int degre_matrice(graphe_matrice *g,int s);

void affichage_graphe_matrice(graphe_matrice *g);

graphe_matrice * creation_graphe_complet(int n);

graphe_matrice * ajouter_sommet(graphe_matrice *g);

graphe_matrice * supprimer_sommet(graphe_matrice *g, int s);

void ponderation(graphe_matrice *g, int min, int max);

//void zero_graph(graphe_matrice *g);

void grille(graphe_matrice *g, int longueur_r);

void etoile(graphe_matrice *g, int coeur);

void cycle(graphe_matrice *g);

//void chemin(graphe_matrice *g);

graphe_matrice * randomgraph(int n,int p);

graphe_matrice * hypercube(int degre);

#endif