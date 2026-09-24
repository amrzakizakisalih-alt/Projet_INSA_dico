#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dico.h"

int main() {
    int choix;
    int nbr_fichiers=0;
    int nbr_dico = 0;
    DICO *dicos[MAX_DICOS] = {NULL}; // Tableau pour stocker plusieurs dictionnaires
    char sauvegarde_fichiers[MAX][MAX];

    do {
        
        printf("\n============================================\n");
        printf("           MENU PRINCIPAL\n");
        printf("============================================\n");
        printf("1. Saisir manuellement vos dictionnaires\n");
        printf("2. Manipuler des dictionnaires existants\n");

        
        if (nbr_dico >= 2) {
            printf("3. Création de liens entre dictionnaires\n");
            printf("4. Affichage des liens d'un dictionnaire\n");
            printf("5. Afficher la liste de de vos dictionnaire enregistrer\n");
        
        }
        printf("6. Quitter\n");
        printf("Le nombre de dictionnaire disponible est : %d\n", nbr_dico);
        printf("Vous disposez de 3 dictionnaire que vous pouvez importer, dictionnaire1, dictionnaire2, dictionnaire3.\n");
        printf("============================================\n");
              
        do{
            printf("\n\n\nSaisir votre choix : ");
            scanf("%d", &choix);
            getchar(); // Pour le retour à la ligne
        }while(choix<1 && choix >5);
        
        switch (choix) {
            case 1: {
                int nbr=0;
                do{
                    if(nbr+nbr_dico>MAX_DICOS){
                        printf("Nombre saisie invalide ou le nombre macimal de dicos atteint, saisir un nombre entre 1 et %d\n",nbr_dico-MAX_DICOS);
                    }
                    printf("\n\nSaisir le nombre de dictionnaires que vous voulez creer : ");
                    scanf("%d", &nbr);
                    getchar();
                }while(nbr<0&& nbr+nbr_dico>MAX_DICOS);
                //nbr_dico+=nbr;
                

                // Verification de la saisie
                while (nbr <= 0 || nbr > MAX_DICOS) {
                    printf("Saisir un nombre valide de dictionnaires entre [1 - %d] : ", MAX_DICOS);
                    scanf("%d", &nbr);
                    getchar();
                }

                for (int i =nbr_dico ; i < nbr+nbr_dico ; i++) {
                    printf("\nDictionnaire %d\n", i + 1);
                    dicos[i] = creer_dico();

                    int n;
                    do{
                        printf("Saisir le nombre de mots à inserer pour le dictionnaire %d : ", i + 1);
                        scanf("%d", &n);
                        getchar();
                    }while(n<=0);

                    for (int j = 0; j < n; j++) {
                        char mot[MAX];
                        printf("Saisir un mot : ");
                        fgets(mot, MAX, stdin);
                        // Supprimer le retour à la ligne 
                        if (mot[strlen(mot) - 1] == '\n') {
                            mot[strlen(mot) - 1] = 0;
                        }

                        char def[MAX2];
                        printf("Saisir la definition : ");
                        fgets(def, MAX2, stdin);
                        // Supprimer le retour à la ligne 
                        if (def[strlen(def) - 1] == '\n') {
                            def[strlen(def) - 1] = 0;
                        }

                        inserer_mot(dicos[i], mot, def);
                    }

                    printf("Enregistrement du dictionnaire...\n");
                    char nom_fichier[MAX];
                    printf("Saisir le nom que vous voulez donner a votre fichier : ");
                    fgets(nom_fichier,MAX, stdin);
                    // Supprimer le retour à la ligne
                    if (nom_fichier[strlen(nom_fichier) - 1] == '\n') {
                        nom_fichier[strlen(nom_fichier) - 1] = 0;
                    }
      
                    FILE *fichier = fopen(nom_fichier, "w");
                    if (fichier == NULL) {
                        printf("Erreur lors de l'ouverture du fichier \"%s\".\n", nom_fichier);
                    } else {
                        int verif;
                        strcpy(sauvegarde_fichiers[nbr_fichiers], nom_fichier);
                        nbr_fichiers++; 
                        sauvdico(dicos[i], fichier, nom_fichier,&verif);
                        fclose(fichier);
                        printf("Dictionnaire sauvegarde dans \"%s.txt\".\n", nom_fichier);
                    }
                    
                }
                nbr_dico+=nbr;
                break;
            }

            case 2: {
                if (nbr_dico == 0) {
                    printf("============================================\n");
                    printf("Aucun dictionnaire disponible. Vous pouvez :\n");
                    printf("1. Charger un dictionnaire depuis un fichier\n");
                    printf("2. Retourner au menu principal\n");
                    printf("============================================\n");
                    printf("\n\n\nVotre choix : ");
                    int sous_choix1;
                    do{
                      scanf("%d", &sous_choix1);
                      getchar();
                    }while(sous_choix1<1 && sous_choix1>2);

                    if (sous_choix1 == 1) {
                        char nom_fichier2[MAX];
                        int verif_sauvegarde;
                        printf("Saisir le nom du fichier à charger : ");
                        fgets(nom_fichier2, MAX, stdin);
                        if (nom_fichier2[strlen(nom_fichier2) - 1] == '\n') {
                            nom_fichier2[strlen(nom_fichier2) - 1] = 0;
                        }

                        FILE *fichier = NULL;
                        dicos[nbr_dico] = creer_dico();
                        chargerdico(dicos[nbr_dico],fichier,nom_fichier2,&verif_sauvegarde);
                        if(verif_sauvegarde==1){
                            strcpy(sauvegarde_fichiers[nbr_fichiers], nom_fichier2);
                            nbr_fichiers++; 
                            nbr_dico++;
                        }
                    }
                    break;
                    
                }
                printf("============================================\n");
                printf("1. Charger un dictionnaire depuis un fichier\n");
                printf("2. Manipuler un dictionnaire existant\n");
                printf("Le nombre de dictionnaire disponible est : %d\n",nbr_dico);
                printf("============================================\n\n\n");
                
                int sous_choix;
                do{
                    printf("\nVotre choix : ");
                    scanf("%d", &sous_choix);
                    getchar();
                }while(sous_choix<1 && sous_choix>2);

                switch (sous_choix) {
                    case 1: {
                        if (nbr_dico >= MAX_DICOS) {
                            printf("Nombre maximum de dictionnaires atteint.\n");
                        } else {
                            char nom_fichier3[MAX];
                            int verif_sauvegarde;
                            printf("Saisir le nom du fichier à charger : ");
                            fgets(nom_fichier3, MAX, stdin);
                            if (nom_fichier3[strlen(nom_fichier3) - 1] == '\n') {
                                nom_fichier3[strlen(nom_fichier3) - 1] = 0;
                            }

                            FILE *fichier = NULL;
                            dicos[nbr_dico] = creer_dico();
                            printf("en cours de sauvegrade...\n");
                            chargerdico(dicos[nbr_dico],fichier,nom_fichier3,&verif_sauvegarde);
                            printf("fin de sauvegrade.\n");
                            if(verif_sauvegarde==1){
                                strcpy(sauvegarde_fichiers[nbr_fichiers], nom_fichier3);
                                nbr_fichiers++; 
                                nbr_dico++;
                            }
                            
                          
                            
                        }
                        break;
                    }

                    case 2: {
                        int dico_index;
                        printf("Saisir le numero du dictionnaire à manipuler (1-%d) : ", nbr_dico);
                        scanf("%d", &dico_index);
                        getchar();

                        while(dico_index < 1 || dico_index > nbr_dico) {
                            printf("Numero de dictionnaire invalide.\n");
                            printf("Saisir le numero du dictionnaire à manipuler (1-%d) : ", nbr_dico);
                            scanf("%d", &dico_index);
                            getchar();
                        }
                        if(dicos[dico_index-1] == NULL){
                            printf("dicos[dico_index-1] == NULL");
                        }
                        DICO *dico_selectionner = dicos[dico_index - 1];
                        int choix2;

                        do {
                            printf("\n============================================\n");
                            printf("           MENU DICTIONNAIRE %d\n", dico_index);
                            printf("============================================\n");
                            printf("1. Afficher tous les mots\n");
                            printf("2. Afficher un resume du contenue\n");
                            printf("3. Inserer un nouveau mot\n");
                            printf("4. Chercher un mot\n");
                            printf("5. Modifier la definition d'un mot\n");
                            printf("6. Supprimer un mot\n");
                            printf("7. Enregistrer vos modification\n");
                            printf("8. Supprimer le contenue du dictionnaire\n");
                            printf("9. Retour au menu principal\n");
                            printf("============================================\n\n\n");
                            
                            printf("\nVotre choix : ");
                            scanf("%d", &choix2);
                            getchar();                       
                            while(choix2<1 && choix2>8){
                                printf("\nVotre choix est invalide!");
                                printf("\nVotre choix : ");
                                scanf("%d", &choix2);
                                getchar();
                            }
                            
                            switch (choix2) {
                                case 1:{
                                    affiche_dico(dico_selectionner);
                                    break;
                                }
                                
                                case 2:{
                                    contenue_dico(dico_selectionner);
                                    break;
                                }
                                
                                case 3: {
                                    char mot_insr[MAX];
                                    printf("\n\nSaisir le mot à inserer : ");
                                    fgets(mot_insr, MAX, stdin);
                                    if (mot_insr[strlen(mot_insr) - 1] == '\n') {
                                        mot_insr[strlen(mot_insr) - 1] = 0;
                                    }
                                    char def_insr[MAX2];
                                    printf("\n\nSaisir la definition du mot à inserer : ");
                                    fgets(def_insr, MAX2, stdin);
                                    if (def_insr[strlen(def_insr) - 1] == '\n') {
                                        def_insr[strlen(def_insr) - 1] = 0;
                                    }
                                    inserer_mot(dico_selectionner,mot_insr,def_insr);
                                
                                    
                                    break;
                                }
                                
                                case 4: {
                                    char mot[MAX];
                                    printf("\n\nSaisir le mot à chercher : ");
                                    fgets(mot, MAX, stdin);
                                    if (mot[strlen(mot) - 1] == '\n') {
                                        mot[strlen(mot) - 1] = 0;
                                    }
                                    rechercher_mot(dico_selectionner,mot);
                                    break;
                                }
                              
                                case 5: {
                                    char mot[MAX];
                                    printf("\n\nSaisir le mot à modifier : ");
                                    fgets(mot, MAX, stdin);
                                    if (mot[strlen(mot) - 1] == '\n') {
                                        mot[strlen(mot) - 1] = 0;
                                    }
                                    char def_insr[MAX2];
                                    printf("\n\nSaisir la definition du mot à inserer : ");
                                    fgets(def_insr, MAX2, stdin);
                                    if (def_insr[strlen(def_insr) - 1] == '\n') {
                                        def_insr[strlen(def_insr) - 1] = 0;
                                    }
                                    del_mot(dico_selectionner, mot);
                                    inserer_mot(dico_selectionner,mot,def_insr);
                                    break;
                                }
                                


                                case 6: {
                                    char mot[MAX];
                                    printf("\n\nSaisir le mot à supprimer : ");
                                    fgets(mot, MAX, stdin);
                                    if (mot[strlen(mot) - 1] == '\n') {
                                        mot[strlen(mot) - 1] = 0;
                                    }
                                    del_mot(dico_selectionner, mot);
                                    break;
                                }
                                
                                case 7: {
                                    printf("\n\nNom du fichier à ouvrir :  %d  \"%s\"\n",nbr_fichiers, sauvegarde_fichiers[dico_index-1]);
                                    int verif;
                                    FILE *fichier = fopen(sauvegarde_fichiers[dico_index-1], "w");
                                    if (fichier == NULL) {
                                        printf("Erreur lors de l'ouverture du fichier \"%s\".\n", sauvegarde_fichiers[dico_index-1]);
                                    } else {
                                        sauvdico(dico_selectionner, fichier, sauvegarde_fichiers[dico_index-1],&verif);
                                        fclose(fichier);
                                        printf("Modification sauvegardée dans \"%s\".\n", sauvegarde_fichiers[dico_index-1]);
                                    
                                    }
                                    break;

                                }
                                case 8: {
                                    liberer_dico(dico_selectionner);
                                    break;
                                }
                                
                                case 9:
                                    printf("Retour au menu principal...\n");
                                    break;
                                
                                default: 
                                    printf("Choix invalide.\n");
                                    break;
                            }
                                
                        } while (choix2 != 9);
                       break;
                    }

                    default:
                        printf("Choix invalide.\n");
                        break;
                }
                break;
            }
            
            case 3:{
                int index1,index2;
                do{
                    printf("Saisir l'index du premier dictionnaire entre 1 et %d: ",nbr_dico);
                    scanf("%d",&index1);
                  
                }while(index1<1 && index1>nbr_dico);
                
                do{
                    printf("Saisir l'index du second dictionnaire entre 1 et  %d: ",nbr_dico); 
                    scanf("%d",&index2);
                }while(index2<1 && index2>nbr_dico);
                creation_lien(dicos[index1-1],dicos[index2-1]);
                creation_lien(dicos[index2-1],dicos[index1-1]);
                break;
           }
            case 4:{
                int ind;
                do{
                    printf("Saisir l'index du dictionnaire  entre 1 et %d: ",nbr_dico);
                    scanf("%d",&ind);
                }while(ind<1 && ind>nbr_dico);
                affiche_lien(dicos[ind-1]);
                break;
            }
                
            case 5:
                lire_fichiers(sauvegarde_fichiers,nbr_fichiers);
                break;
                
            case 6:
                printf("Quitter le programme...\n");
                break;
                
            default:
                printf("Choix invalide.\n");
                break;
        }
        
    }while (choix != 6);

    // Liberation de la memoire
    for (int i = 0; i < nbr_dico; i++) {
        if (dicos[i] != NULL) {
            liberer_dico(dicos[i]);
        }
    }

    return 0;
}



