/*!
  \file main.c
  \author Romane Sallio <sallioroma@eisti.eu>
  \version 1
  \date  29 / 03 / 2020
  \brief TP noté Architecture et Programmation Parallèle exercice 1
*/

#include "triFusion.h"

int main(int argc, char const *argv[]){
    double start;
    double end;
    // Start prend le temps du début du programme en s
    start = omp_get_wtime();
    // Définit le nombre de thread, ici à 2
    omp_set_num_threads(2);

    // Création d'un tableau de taille 9  
    int taille = 9;
    int tab[taille];
    tab[0] = 4;
    tab[1] = 8;
    tab[2] = 5;
    tab[3] = 3;
    tab[4] = 6;
    tab[5] = 9;
    tab[6] = 1;
    tab[7] = 7;
    tab[8] = 2;

    // Affichage du tableau non trié
    printf("Tableau non trié : \n");
    affichageTableau(tab, taille);

    // Vérification que le tableau n'est pas vide
    if (taille > 0){
        // Directive permettant de créer une région parallele sur le modele fork-join
        #pragma omp parallel
        {
            printf("Thread : %d\n", omp_get_thread_num());
            // triFusion est exécuté sur un seul thread et la barrière implicite est remplacé par nowait 
            #pragma omp single nowait
            {
                // Application du tri au tableau
                triFusion(tab, 0, taille-1);
            }
        }
    }
    
    // Affichage du tableau trié
    printf("Tableau trié : \n");
    affichageTableau(tab, taille);

    // End prend le temps de le fin du programme en s
    end = omp_get_wtime();

    printf("Temps d'exécution : %f s\n", end - start);
    return 0;
}