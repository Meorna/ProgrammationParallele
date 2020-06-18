/*!
  \file triFusion.c
  \author Romane Sallio <sallioroma@eisti.eu>
  \version 1
  \date  29 / 03 / 2020
  \brief TP noté Architecture et Programmation Parallèle exercice 1
*/

#include "triFusion.h"

// Fonction permettant de fusionner tout en triant les tableaux gauche et droit 
void fusion(int tab[],int debutTabDroit,int finTabDroit,int finTabGauche){
    int *tabDroit;
    int debutTabGauche = finTabDroit + 1;
    int compteurTabDroit = debutTabDroit;
    int compteurTabGauche = debutTabGauche;
    int i;
    
    // On alloue la mémoire de tabDroit pour pouvoir y mettre la première moitié de tab
    tabDroit = malloc((finTabDroit - debutTabDroit + 1) * sizeof(int)); 

    //On copie la première moitié de tab dans tabroit
    for(i = debutTabDroit; i <= finTabDroit; i++) {
        tabDroit[i - debutTabDroit] = tab[i];
    }
    // On parcourt tab           
    for(i = debutTabDroit; i <= finTabGauche; i++) { 
        // Si tous les éléments de la moitié gauche de tab ont été utilisés   
        if (compteurTabDroit == debutTabGauche) {
            // Alors tous les éléments sont triés
            break;
        // Sinon si tous les éléments de la moitié droite de tab ont été utilisés
        } else if (compteurTabGauche == (finTabGauche + 1)){
            // Alors on ajoute les éléments de la moitié gauche restants à tab
            tab[i] = tabDroit[compteurTabDroit - debutTabDroit];
            //Le compteur du tableau gauche prend la valeur plus 1
            compteurTabDroit++;
        // Sinon si l'élément du tableau droit est plus petit que l'élément du tableau gauche
        } else if (tabDroit[compteurTabDroit - debutTabDroit] < tab[compteurTabGauche]){
            // On ajoute l'élément du tableau droit au tableau
            tab[i] = tabDroit[compteurTabDroit - debutTabDroit];
            //Le compteur du tableau gauche prend la valeur plus 1
            compteurTabDroit++;       
        // Sinon si l'élément du tableau geuche est plus petit que l'élément du tableau droit
        } else {
            // On ajoute l'élément du tableau droit au tableau
            tab[i] = tab[compteurTabGauche];
            //Le compteur du tableau droit prend la valeur plus 1
            compteurTabGauche++;
        }
    }
    free(tabDroit);
}
        
// Diviser tab en pleins de sous tableau via le milieu de chaque tableau grâce à un appel recurssif puis fusionner les résultats
int triFusion(int tab[], int debut, int fin){
    int milieu;
    int triGauche;
    int triDroit;

    if (debut != fin) {
        // Déterminer le milieu du tableau
        milieu = (debut + fin) / 2;

        //Directive déclarant une tache fille qui exécute la fonction triFusion pour la première moitié du tableau
        #pragma omp task shared(triGauche)
        {
            // On sépare en deux le coté gauche du tableau
            triGauche = triFusion(tab, debut, milieu);
        }

        //Directive déclarant une tache fille qui exécute la fonction triFusion pour la deuxième moitié du tableau
        #pragma omp task shared(triDroit)
        {
            // On sépare en deux le coté droit du tableau
            triDroit = triFusion(tab, milieu + 1, fin);
        }
        // Permet d'attendre que les tâches filles soient terminé avant de continuer
        #pragma omp taskwait
        // On fusionne les tableaux pour obtenir un tableau trié
        fusion(tab, debut, milieu, fin);
    }
    return 1;
}

//Fonction permettant d'afficher un tableau
void affichageTableau(int tab[], int taille){
    for (int i = 0; i < taille; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}
