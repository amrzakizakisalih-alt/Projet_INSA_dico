#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dico.h"

DICO *creer_dico(){

    DICO *tab= malloc(27* sizeof(DICO));
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le dictionnaire.\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<26;i++){
        tab[i].lettre='a'+i;
        tab[i].liste_mots = NULL;
    }
    return tab;
}




int char_permis(char mot[MAX]) {
    if (strlen(mot) == 0) {  
        return 1;  // Retourne 1 si le mot est vide (non valide)
    }

    for (int i = 0; i < strlen(mot); i++) {

        if (!((mot[i] >= 'A' && mot[i] <= 'Z') || (mot[i] >= 'a' && mot[i] <= 'z') || (mot[i] == '-') || (mot[i] == ' ') || (mot[i] == '\'') || (mot[i] == ','))) {
            return 1;  // Retourne 1 si un caractere non autorise est trouve
        }
    }

    return 0;  // Retourne 0 si tous les caractères sont valides
}


void inserer_mot(DICO *tab,char mot_ins[MAX],char def_ins[MAX2]){
    int verif;
    char lettre = mot_ins[0];
    int index;
    verif=char_permis(mot_ins);
    if(verif==1){
        printf("Erreur : Mot invalide\n");
        return;
    }
    if(lettre >= 'A' && lettre <= 'Z'){
        index = lettre - 'A';
    }else{
        index = lettre - 'a';
    }

    MOTS *nouveau =malloc(sizeof(MOTS));
    strcpy(nouveau->mot,mot_ins);
    strcpy(nouveau->def,def_ins);

    // Ajouter la définition à la liste des définitions
    DEFS *nouveau_def = malloc(sizeof(DEFS));
    strcpy(nouveau_def->def, def_ins);
    nouveau_def->suivant =NULL;
    nouveau->liste_defs = nouveau_def;
    nouveau_def->liste_lien=NULL;

    if (tab[index].liste_mots == NULL || strcasecmp(tab[index].liste_mots->mot, mot_ins) > 0) { 
        nouveau->suivant = tab[index].liste_mots;
        tab[index].liste_mots = nouveau;
    } else {
        MOTS *p = tab[index].liste_mots;

        while (p->suivant != NULL && strcasecmp(p->suivant->mot, mot_ins) < 0){
            p=p->suivant;
        }
        // Si le mot existe déjà, ajouter la définition à liste_defs
        if (strcasecmp(p->mot, mot_ins) == 0) {
            DEFS *nouveau_def = malloc(sizeof(DEFS));
            strcpy(nouveau_def->def, def_ins);
            nouveau_def->suivant = p->liste_defs;
            p->liste_defs = nouveau_def;
            free(nouveau); // Libérer la mémoire du mot doublon
            return;
        }

        nouveau->suivant = p->suivant;
        p->suivant = nouveau;
    }

}


int len(DEFS *liste){
    int compteur=0;
    DEFS *courant= liste;
    while(courant!=NULL){
        compteur++;
        courant = courant->suivant ;
    }
    return compteur;
}


void affiche_dico(DICO *tab) {
    printf("\n\n");
    printf
      ("                #############################################\n"
       "                ##                                         ##\n"
       "                ##   Bienvenue sur Votre Dictionnaire      ##\n"
       "                ##                MSD, AZS                 ##\n"
       "                ##                                         ##\n"
       "                #############################################\n");

    printf("\n\n");

    for (int i = 0; i < 26; i++) {
        printf("\n==========| Lettre : %c |==========\n", tab[i].lettre);
        MOTS *courant = tab[i].liste_mots;

        if (courant == NULL) {
            printf("Aucun mot disponible pour cette lettre.\n");
        } else {
            while (courant != NULL) {
                printf("Mot : %-20s | Définitions : %d\n", courant->mot, len(courant->liste_defs));//%-20 force alignement a gauche
                
                DEFS *courant_def = courant->liste_defs;
                int def_count = 1;

                while (courant_def != NULL) {
                    printf("\t[%d] %s\n", def_count, courant_def->def);
                    courant_def = courant_def->suivant;
                    def_count++;
                }

                printf("\n");
                courant = courant->suivant;
            }
        }
    }
    printf("\nFin du dictionnaire.\n");
}

void contenue_dico(DICO *tab){
    int contenue[26];
    int total_mot=0;
    for(int i=0;i<26;i++){
        int compteur=0;
        MOTS *courant= tab[i].liste_mots;
        while(courant!=NULL){
            compteur++;
            courant = courant->suivant ;
        }
        contenue[i]=compteur;
        total_mot+=compteur;

    }
    printf("votre dico contient un total de : %d mots\n",total_mot);
    for(int i=0;i<26;i++){
        printf("pour %c, on a : %d mots\n",tab[i].lettre,contenue[i]);
    }

}

void rechercher_mot(DICO *tab,char mot_ch[MAX]){
    int verif;
    char lettre = mot_ch[0];
    int index;
    verif=char_permis(mot_ch);
    if(verif==1){
        printf("Erreur : Mot invalide\n");
        return;
    }
    if (lettre >= 'A' && lettre <= 'Z'){
        index = lettre - 'A';
    }else{
        index = lettre - 'a';
    }
    MOTS *courant= tab[index].liste_mots;
    while(courant!=NULL && strcasecmp(courant->mot, mot_ch) != 0){
        courant = courant->suivant;
    }
    if(courant==NULL){
        printf("le mot n'est pas present dans le dico\n");
    }else{

        if (courant->liste_defs != NULL) {
            DEFS *def_courant = courant->liste_defs;
            int i = 1;
            while (def_courant != NULL) {
                printf("La definition %i de votre mot %s est : %s\n", i, courant->mot, def_courant->def);
                def_courant = def_courant->suivant;
                i++;
                }
        } else {
            printf("La definition de votre mot %s est :\t%s\n", courant->mot, courant->def);
        }
    }
}

void del_mot(DICO *tab,char mot_ch[MAX]){
    int verif;
    char lettre = mot_ch[0];
    int index;
    verif=char_permis(mot_ch);
    if(verif==1){
        printf("Erreur : Mot invalide\n");
        return;
    }
    if (lettre >= 'A' && lettre <= 'Z'){
        index = lettre - 'A';
    }else{
        index = lettre - 'a';
    }
    MOTS *courant= tab[index].liste_mots;
    MOTS *precedant=NULL;
    while(courant!=NULL && strcasecmp(courant->mot,mot_ch)!=0){
        precedant=courant;
        courant = courant->suivant;
    }
    if(courant==NULL){
        printf("%s n'existe pas dans le dico.",mot_ch);
        return;

    }else if(precedant == NULL){
        tab[index].liste_mots = courant->suivant;
    }else{
        precedant->suivant = courant->suivant;
    }

    DEFS *def_courant = courant->liste_defs;
    while (def_courant != NULL) {

        DEFS *tmp_def = def_courant;

        LIEN *lien_courant = def_courant->liste_lien;
        while (lien_courant != NULL) {
            LIEN *tmp_lien = lien_courant;
            lien_courant = lien_courant->suivant;
            free(tmp_lien);
        }
        def_courant = def_courant->suivant;

        free(tmp_def);

    }

    free(courant);
}


int bool_recherchermot(DICO *tab,char mot_ch[MAX]){
    int verif;
    char lettre = mot_ch[0];
    int index;
    verif=char_permis(mot_ch);
    if(verif==1){
        return 0;
    }
    if (lettre >= 'A' && lettre <= 'Z'){
        index = lettre - 'A';
    }else{
        index = lettre - 'a';
    }
    MOTS *courant= tab[index].liste_mots;
    while(courant!=NULL && strcasecmp(courant->mot, mot_ch) != 0){
        courant = courant->suivant;
    }
    if(courant==NULL){
        return 0;
    }else{
        return 1;
    }
}

MOTS *position_recherchermot(DICO *tab,char mot_ch[MAX]){
    int verif;
    char lettre = mot_ch[0];
    int index;
    verif=char_permis(mot_ch);
    if(verif==1){
        exit;
    }
    if (lettre >= 'A' && lettre <= 'Z'){
        index = lettre - 'A';
    }else{
        index = lettre - 'a';
    }
    MOTS *courant= tab[index].liste_mots;
    while(courant!=NULL && strcasecmp(courant->mot, mot_ch) != 0){
        courant = courant->suivant;
    }
    if(courant==NULL){
        return NULL;
    }else{
        return courant;
    }
}

char *liremot(char *chaine, char *mot) {
    while (*chaine != '\0' && isspace((unsigned char)*chaine)) {
        chaine++;
    }

    char *debut = chaine;

    while (*chaine != '\0' && !isspace((unsigned char)*chaine)) { //avance jusqu'a tomber sur un espace
        chaine++;
    }
    //longeur du mot
    size_t len = chaine - debut;

    if (len > 0) {
        strncpy(mot, debut, len);
        mot[len] = '\0';
        return (*chaine != '\0') ? chaine : NULL;  //return la chaine sans le mot
    } else {
        mot[0] = '\0';
        return NULL;
    }
}

void inserer_fin_lien(LIEN **liste, LIEN *nouveau) {
    nouveau->suivant = NULL;
    if (*liste == NULL) {
        *liste = nouveau;
        return;
    }
    LIEN *courant = *liste;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveau;
}

void creation_lien(DICO *tab1, DICO *tab2) {

    for (int i = 0; i < TALPH; i++) {
        MOTS *mot_courant = tab1[i].liste_mots;

        while (mot_courant != NULL) {
            DEFS *def_courant = mot_courant->liste_defs;

            while (def_courant != NULL) {
                char mot[MAX];  // Buffer pour le mot extrait
                char *position = def_courant->def;

                while (position != NULL) {
                    position = liremot(position, mot);

                    if (strlen(mot) > 0) {  // Si un mot est extrait
                        LIEN *def_decomposer_mot = malloc(sizeof(LIEN));
                        strcpy(def_decomposer_mot->mot_def, mot);
                        def_decomposer_mot->suivant = NULL;

                        if (bool_recherchermot(tab2, mot)) {
                            def_decomposer_mot->lien_def = position_recherchermot(tab2, mot);
                        } else {
                            def_decomposer_mot->lien_def = NULL;
                        }

                        // Ajouter le lien à la liste des liens
                        inserer_fin_lien(&(def_courant->liste_lien), def_decomposer_mot);
                    }
                }
                def_courant = def_courant->suivant;
            }
            mot_courant = mot_courant->suivant;
        }
    } 
}


void liberer_dico(DICO *tab) {
    for (int i = 0; i < 26; i++) {
        MOTS *courant = tab[i].liste_mots;
        while (courant != NULL) {
            MOTS *tmp = courant;
            DEFS *def_courant = courant->liste_defs;
            while (def_courant != NULL) {

                LIEN *lien_courant = def_courant->liste_lien;
                while (lien_courant != NULL) {
                    LIEN *tmp_lien = lien_courant;
                    lien_courant = lien_courant->suivant;
                    free(tmp_lien);
                }

                DEFS *tmp_def = def_courant;
                def_courant = def_courant->suivant;
                free(tmp_def);
            }
            courant = courant->suivant;
            free(tmp);
        }
    }
    
}

void sauvdico(DICO *tab,FILE *fichier,char nomfichier[MAX],int *boul){  
    fichier = fopen(nomfichier, "w");

    if (fichier == NULL) {
	printf("Erreur lors de l'ouverture du fichier.\n");
	*boul=0;
	return;
    }

    for (int i=0;i<TALPH;i++){
	MOTS *p=tab[i].liste_mots;
	while(p!=NULL){
	    fprintf(fichier,"%s\t%s\n",p->mot, p->def);
	    p=p->suivant;
	}
    }
    *boul=1;

    fclose(fichier);
}

void chargerdico(DICO *tab,FILE *fichier,char nomfichier[MAX],int *boul){
    char mot[MAX];
    char def[MAX2];
    fichier=fopen(nomfichier,"r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        *boul=0;
        return;
    }

    while(fscanf(fichier,"%s\t%[^\n]\n",mot,def)==2){
        inserer_mot(tab,mot,def);
    }
    *boul=1;

    fclose(fichier);
}	


void affiche_lien(DICO *tab) {
    printf("\n============================================\n");
    printf("           Affichage des liens\n");
    printf("============================================\n");

    for (int i = 0; i < TALPH; i++) {
        printf("\n==========| Lettre : %c |==========\n", tab[i].lettre);

        MOTS *courant_mot = tab[i].liste_mots;
        if (courant_mot == NULL) {
            printf("Aucun mot disponible pour cette lettre.\n");
        } else {
            while (courant_mot != NULL) {
                printf("\nMot : %-20s\n", courant_mot->mot);//%-20 force alignement a gauche

                DEFS *courant_def = courant_mot->liste_defs;
                int def_index = 1;

                while (courant_def != NULL) {
                    printf("\tDefinition [%d] : %s\n", def_index, courant_def->def);

                    LIEN *courant_lien = courant_def->liste_lien;
                    if (courant_lien == NULL) {
                        printf("\t\tAucun mot lié trouvé.\n");
                    } else {
                        printf("\t\tMots liés :\n");
                    }

                    // Parcours des liens
                    while (courant_lien != NULL) {
                        if (courant_lien->lien_def != NULL) {
                            printf("\t\t\t- Mot : %-15s | Definition : %s\n",
                                   courant_lien->mot_def, courant_lien->lien_def->def);
                        } else {
                            printf("\t\t\t- Mot : %-15s (pas de définition associée)\n",
                                   courant_lien->mot_def);
                        }
                        courant_lien = courant_lien->suivant;
                    }

                    courant_def = courant_def->suivant;
                    def_index++;
                }

                courant_mot = courant_mot->suivant;
            }
        }
    }

    printf("\n============================================\n");
    printf("       Fin de l'affichage des liens\n");
    printf("============================================\n");
}


void lire_fichiers(char sauvegarde_fichiers[MAX][MAX], int nbr_fichier) {
    printf("============================================\n");
    printf("Voici la liste de vos dictionnaire avec leur nom :\n");
    for (int i = 0; i < nbr_fichier; i++) {
        printf("Fichier %d: %s\n", i + 1, sauvegarde_fichiers[i]);
    }
    printf("============================================\n");
}
