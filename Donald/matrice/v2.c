#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct liste 
{
	int mot;
	int poids;
	struct liste *next;
};
typedef struct liste liste;

struct graphe
{
	liste ** ladj;
	int taille;
};
typedef struct graphe graphe;

graphe * creation_graphe_vide(int taille)
{
	int i;
	graphe *g;
	g = (graphe *)malloc(sizeof(graphe));
	g->taille=taille;
	g->ladj = (liste **)malloc(sizeof(liste *)*taille);
	for(i=0;i<taille;i++)
	{
		g->ladj[i]=NULL;
	}
	return g;
}

liste * creation_maillon(int nb,int poids)
{
	liste *l;
	l = (liste *) malloc(sizeof(liste));
	l->mot = nb;
	l->poids = poids;
	l->next = NULL;
	return l;
}

char ** ajout_mot(char * path, int taille)
{
	int i;
	char ** mots = NULL;
	size_t len = 0;

	mots = (char **) malloc(sizeof(char **)*taille);
	for(i=0;i<taille;i++)
	{
		mots[i] = (char*)malloc(sizeof(char));
	}
	FILE * fichier;
	fichier = fopen(path,"r+");
	for(i=0;i<taille;i++)
	{
		getline(&mots[i],&len,fichier);
		mots[i] = strtok(mots[i],"\n");
	}
	fclose(fichier);
	return mots;
}

/*
fonction pour recuperer le nombre de ligne d'un fichier
Et donc vu qu'on a un mot par ligne on obtient le nombre de mots
*/
int nbsommet(char * path)
{
	int nb=0;
	char * ligne;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(path,"r+");
	while(getline(&ligne,&len,fichier)!=-1)
		nb++;
	fclose(fichier);
	return nb;
}

/*
void ponderation(int taille_unique,int taille_tot,char ** tab_mot_Unique,char ** tab_mot_Tot)
{
	int i,j,y;
	int cnt =0;
	for(i=0;i<taille;i++)
	{
//		printf("i = %d --- %s\n", i,g->mots[i]);
		for(j=0;j<taille_tot;j++)
		{
			if(tab_mot_Tot[j]==NULL)
				break;
//			printf("j = %d --- %s\n",j,g2->mots[j]);
			if(strcmp(g->mots[i],tab_mot_Tot[j])==0)
			{
				for(y=0;y<taille_unique;y++)
				{
					if(strcmp(tab_mot_unique[y],tab_mot_Tot[j+1])==0)
					{
						cnt++;
						printf("nb match = %d --- i = %d --- j = %d --- y = %d\n",cnt,i,j,y);
						g->mat[i][y+1]=g->mat[i][y+1]+1;
						break;
					}
				}
			}
		}
	}
}*/

int est_voisin (graphe *g , int a , int b )
{
	liste *tmp;
	if(a>=g->taille||b>=g->taille)
		return 0;
	tmp=g->ladj[a];
	while(tmp!=NULL)
	{
		if(tmp->mot==b)
			return 1;		
		tmp=tmp->next;
	}
	return 0;
}

int degre (graphe*g,int s)
{
	liste*tmp;
	int nb=0;
	if(s>=g->taille)return 0;
	tmp=g->ladj[s];
	while(tmp!=NULL)
	{
		nb++;
		tmp=tmp->next;
	}
	return nb;
}

void print_graphe(graphe*g, char**tab_mot_unique)
{
	FILE * fichier1 = NULL;
	fichier1 = fopen("TEST_GRAPH","w+");
	int i;

	liste *tmp;
	for(i=0;i<g->taille;i++)
	{
		fprintf(fichier1,"%d( degre%d -- %s )",i,degre(g,i),tab_mot_unique[i]);
		tmp=g->ladj[i];
		while(tmp!=NULL)
		{
			fprintf(fichier1,"->%d[%d] : %s\n", tmp->mot, tmp->poids, tab_mot_unique[tmp->mot]);
			tmp=tmp->next;
		}
	}
	fclose(fichier1);
}

liste *ajout_maillon(graphe *g, int i, int y)
{
	liste *p, *l; //p : liste temporaire

	l =creation_maillon(y,1);
	
	if(est_voisin(g,i,y)==1) //si i et y sont déjà voisins, on incrément le poids de y
	{
		printf("VOISIN %d - %d\n",i,y);
		p = g->ladj[i] ;
		while(p->mot!=y)
		{	
			p=p->next;
		}
		p->poids++;
	}

	else
	{
		printf(" %d  ---- %d\n", i,y);

		if(g->ladj[i] == NULL) //nouvelle liste
		{
			g->ladj[i] = l;
		}
		else //quand la liste existe déjà, on remonte la pile et on ajoute
		{
			p = g->ladj[i] ; 
			while(p->next!=NULL)
			{
				p=p->next;
			}
			p->next = l;
		}
	}
	return g->ladj[i];
}

int main(int argc, char const *argv[])
{
	graphe * g;
	char ** tab_mot_unique;
	char ** tab_mot_tot;
	char * motunique = "../motUnique";
	char * motTot = "../mots";
	int taille_unique,taille_tot;
	int i,j,y;
	liste *tmp;

	taille_unique = nbsommet(motunique);
	taille_tot = nbsommet(motTot);

	g = creation_graphe_vide(taille_unique);

	tab_mot_unique = ajout_mot(motunique,taille_unique);
	tab_mot_tot = ajout_mot(motTot,taille_tot);
/*	for(int i=0;i<taille_unique;i++)
	{
		printf("mots : %s - %d\n",tab_mot_unique[i],i);
	}*/

	printf("mots : %s - %d\n",tab_mot_tot[taille_tot-1],taille_tot-1);
	printf("mots : %s - %d\n",tab_mot_tot[taille_unique-1],taille_unique-1);

	for(i=0;i<taille_unique;i++)
	{
		for (j=0 ; j < taille_tot-1 ; j++)
		{	//on cherche à retrouver un mot de la liste des mots uniques dans la liste des mots.
			if (strcmp(tab_mot_unique[i], tab_mot_tot[j])==0)
			{
				//on recherche la position du mot suivant le mot trouvé dans la liste des mots uniques
				for(y=0 ; y < taille_unique-1 ; y++) //pourquoi ça semble fonctionner avec "taille_unique-1" ??
					if(strcmp(tab_mot_tot[j+1], tab_mot_unique[y])==0)
						break;
				g->ladj[i] = ajout_maillon(g,i,y);
				//printf("%s(%d) - %s(%d)\n",tab_mot_unique[i],i,tab_mot_unique[y],y);
				//printf("%s\n", tab_mot_unique[y]);
			}
		}
	}
	//printf("%d\n",i );
	print_graphe(g,tab_mot_unique);

	return 0;
}