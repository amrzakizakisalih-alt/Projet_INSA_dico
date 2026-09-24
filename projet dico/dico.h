#ifndef DICO_H
#define DICO_H


// Macros
#define MAX 80
#define MAX2 800
#define TALPH 26
#define MAX_DICOS 100

// Structures
typedef struct mots MOTS;  
typedef struct defs DEFS;

typedef struct lien {
    char mot_def[MAX2];
    struct lien *suivant;
    MOTS *lien_def;
} LIEN;

typedef struct defs {
    char def[MAX2];
    LIEN *liste_lien;
    struct defs *suivant;
} DEFS;

typedef struct mots {
    char mot[MAX];
    char def[MAX2];
    struct mots *suivant;
    DEFS *liste_defs;
} MOTS;

typedef struct dico {
    char lettre;
    MOTS *liste_mots;
} DICO;

// fonctions
DICO *creer_dico();
int char_permis(char mot[MAX]);
void inserer_mot(DICO *tab, char mot_ins[MAX], char def_ins[MAX2]);
int len(DEFS *liste);
void affiche_dico(DICO *tab);
void contenue_dico(DICO *tab);
void rechercher_mot(DICO *tab, char mot_ch[MAX]);
void del_mot(DICO *tab, char mot_ch[MAX]);
int bool_recherchermot(DICO *tab, char mot_ch[MAX]);
MOTS *position_recherchermot(DICO *tab, char mot_ch[MAX]);
char *liremot(char *chaine, char *mot);
void inserer_fin_lien(LIEN **liste, LIEN *nouveau);
void creation_lien(DICO *tab1, DICO *tab2);
void liberer_dico(DICO *tab);
void sauvdico(DICO *tab, FILE *fichier, char nomfichier[MAX],int *boul);
void chargerdico(DICO *tab, FILE *fichier, char nomfichier[MAX],int *boul);
void affiche_lien(DICO *tab);
void lire_fichiers(char sauvegarde_fichiers[MAX][MAX], int nbr_fichier);

#endif // DICO_H

