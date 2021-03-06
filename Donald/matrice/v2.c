#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
		//printf("VOISIN %d - %d\n",i,y);
		p = g->ladj[i] ;
		while(p->mot!=y)
		{	
			p=p->next;
		}
		p->poids++;
	}

	else
	{
		//printf(" %d  ---- %d\n", i,y);

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



int calc_poids(graphe *g, int i)
{
	liste *tmp;
	int pds =0;
	tmp = g->ladj[i];
	while(tmp->next!=NULL)
	{
		pds = pds +tmp->poids;
		tmp=tmp->next;
	}

	return pds;
}

char *gen_nomdot(int j, char* nomdot)
{
	nomdot[2]='.';
	nomdot[3]='d';
	nomdot[4]='o';
	nomdot[5]='t';
	nomdot[6]='\0';

	nomdot[1]=j%10 + '0';
	nomdot[0]=(j/10)%10 + '0';
	return nomdot;
}

void gen_dot(int *valtab, int nbmot, char **tab_mot_unique)
{
	FILE* fichier;
	int i,j=1;
	char nomdot[7];

	while(j<nbmot-1)
	{
		fichier = fopen(gen_nomdot(j,nomdot),"w+");
		fprintf(fichier,"digraph G{\nsize=\"5.0,5.0\";\nratio=\"fill\";\nnode[height=0.1, width=0.1]\n");
		fprintf(fichier, "\t%d [label=\"%s\"]\n",valtab[0], tab_mot_unique[valtab[0]]);

		//ajout de labels permettant de renseigner la chaine de caractere attache a chaque mot
		for(i=1 ; i <= j ; i++)
		{
			fprintf(fichier, "\t%d [label=\"%s\"]\n",valtab[i], tab_mot_unique[valtab[i]]);
		}
		//creation des aretes.
		for(i=1 ; i <= j ; i++)
		{
			fprintf(fichier, "\t%d -> %d\n", valtab[i-1], valtab[i]);
		}
		fputs("}",fichier);
		fclose(fichier);

		j++;
	}
}

void gen_tweet(graphe *g, char **tab_mot_unique)
{
	int val=0, pds_obj, pds, len=0;
	char *mot;
	liste *tmp;
	int valtab[70], i=0; // va servir à enregistrer les valeurs pour la creation du .dot

	char **tab_lien;
	char **tab_hashtag;
	char **tab_handle;
	char *lien 		= "../Lien";
	char *hashtag 	= "../Hashtag";
	char *handle 	= "../Handle";
	int taille_lien, taille_hashtag, taille_handle;
	
	taille_lien 	= nbsommet(lien);
	taille_hashtag 	= nbsommet(hashtag);
	taille_handle 	= nbsommet(handle);

	tab_lien 		= ajout_mot(lien,taille_lien);
	tab_hashtag 	= ajout_mot(hashtag,taille_hashtag);
	tab_handle 		= ajout_mot(handle,taille_handle);


	// le premier mot suit le mot "-"
	while( strcmp(tab_mot_unique[val], "-")!=0)
			val++;
	pds = rand()%((calc_poids(g,val)+1)); //on définit un poids "cible" aléatoire inférieur ou égal au poids max
	tmp = g->ladj[val];
	while(1)
	{
		pds_obj = rand()%((calc_poids(g,val)+1)); //on définit un poids "cible" aléatoire inférieur ou égal au poids max
		tmp = g->ladj[val];

		pds=0;
		while(tmp->next!=NULL && pds_obj > pds)
		{
			pds = pds + tmp->poids;
			tmp=tmp->next;
		}	
		val = tmp->mot;
		valtab[i]=val;
		i++;
		mot=tab_mot_unique[val];

		//si le mot est un lien
		//on selectionne un mot au hasard dans le tableau des liens.
		if(strcmp(mot,"*")==0)
			mot=tab_lien[rand()%taille_lien];
		if(strcmp(mot,"#")==0)
			mot=tab_hashtag[rand()%taille_hashtag];
		if(strcmp(mot,"@")==0)
			mot=tab_handle[rand()%taille_handle];

		// on s'assure que le nombre de caracteres du tweet ne depasse pas 140.
		len = len + strlen(mot) + 1; //+1 pour l'espace
		if (len > 139 || strcmp(mot,"-")==0)
		{
			printf(".\n");
			break;
		}	
		printf(" %s", mot);

	}
	gen_dot(valtab, i, tab_mot_unique);
	printf("\n");
}

void gen_dir_dot (graphe *g, char *nomdot, char **tab_mot_unique)
{
	FILE* fichier;
	liste *temp;
	temp = (liste*)malloc(sizeof(liste)*2);
	int i;
	fichier = fopen(nomdot,"w+");
	fprintf(fichier,"digraph G{\n");
//ajout de labels permettant de renseigner la chaine de caractere attache a chaque mot
	for(i=0 ; i < g->taille ; i++)
	{
		fprintf(fichier, "\t%d [label=\"%s\"]\n",i, tab_mot_unique[i]);
	}
//creation des aretes.
	for(i=0 ; i < g->taille ; i++)
	{
		temp = g->ladj[i];
		while(temp->next!=NULL)
		{
			fprintf(fichier, "%d -> %d\n", i, temp->mot);
			temp = temp->next;
		}
	}
	free(temp);
	printf("label : fait\n");
	fputs("}",fichier);
	fclose(fichier);
}

int main(int argc, char const *argv[])
{
	graphe * g;
	char ** tab_mot_unique;
	char ** tab_mot_tot;
	char * motunique = "../motUnique";
	char * motTot = "../mots";
	int taille_unique, taille_tot;
	int i,j,y;
	time_t t;

	srand((unsigned) time(&t));

	taille_unique = nbsommet(motunique);

	taille_tot = nbsommet(motTot);

	g = creation_graphe_vide(taille_unique);

	tab_mot_unique = ajout_mot(motunique,taille_unique);
	tab_mot_tot = ajout_mot(motTot,taille_tot);

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

	//gen_dir_dot(g,"graphe.dot",tab_mot_unique);

	/*
	//printf("%d\n",i );
	printf("lance print_graphe\n");
	print_graphe(g,tab_mot_unique);
	printf("taille : %d\n", g->taille );
	gen_dir_dot(g,"graph.dot",tab_mot_unique);
*/
	while(1)
	{	
		scanf("%d",&i);
		if(i==0) break;
		gen_tweet(g, tab_mot_unique);
	}
	return 0;
}