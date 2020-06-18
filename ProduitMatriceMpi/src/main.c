/*!
  \file main.c
  \author Romane Sallio <sallioroma@eisti.eu>
  \version 1
  \date  04 / 04 / 2020
  \brief TP noté Architecture et Programmation Parallèle exercice 3
*/

#include "produitMatriceMpi.h"

int main(int argc, char *argv[]){
    int nombreLigneA = 3;
    int nombreColonneA = 2;
    int nombreColonneB = 5;
    int A[nombreLigneA][nombreColonneA];
    int B[nombreColonneA][nombreColonneB];
    int C[nombreLigneA][nombreColonneB];
    int nombreElement;
    int nombreProcessus;
    int rang;
    int somme;

    //Initialiser l'environnement MPI
    MPI_Init(&argc,&argv);
    //Retourne le nombre de processus associé au communicateur
    MPI_Comm_size(MPI_COMM_WORLD, &nombreProcessus);
    //Retourne le rang d'un processus actif (entre 0 et nombreProcessus -1)
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    printf("Nombre Processus : %d, Rang : %d \n", nombreProcessus, rang);
    // Le nombre de ligne de la matrice A doit être divisible par le nombre de processus donné
    // C'est à dire que le reste de la divion doit être égal à 0 
    if(nombreLigneA % nombreProcessus == 0){
        // Le nombre de ligne de chque sous-vecteur de la matrice A
        nombreElement = nombreLigneA / nombreProcessus;
    } else {
        // Afficher un message d'erreur si l'utilisateur n'a pas saisi un bon nombre de processus
        fprintf(stderr, "nombreLigneA = %d doit être divisible par nombreProcessus = %d\n", nombreLigneA, nombreProcessus);
        // Terminer l'exécution de l'environnement MPI avec 1 comme code d'erreur
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    // Le processus 0 intialise la matrice A et B en leurs indministrant des valeurs
    if(rang == 0){
        A[0][0] = 1;
        A[0][1] = 2;
        A[1][0] = 3;
        A[1][1] = 4;
        A[2][0] = 5;
        A[2][1] = 6;
        printf("A = \n");
        for(int i = 0; i < nombreLigneA; i++) {
            for(int j = 0; j < nombreColonneA; j++){
                printf("    %d ", A[i][j]);
            }
            printf("\n");
        }
        B[0][0] = 1;
        B[0][1] = 3;
        B[0][2] = 5;
        B[0][3] = 1;
        B[0][4] = 3;
        B[1][0] = 2;
        B[1][1] = 4;
        B[1][2] = 6;
        B[1][3] = 2;
        B[1][4] = 4;
        printf("B = \n");
        for(int i = 0; i < nombreColonneA; i++) {
            for(int j = 0; j < nombreColonneB; j++){
                printf("    %d ", B[i][j]);
            }
            printf("\n");
        }
    }
    // Le processus 0 divise A par nombreElement lignes et partage une partie de A à chaque processus 
    MPI_Scatter(A, nombreColonneA * nombreElement, MPI_INT, A[rang * nombreElement], nombreColonneA * nombreElement, MPI_INT, 0, MPI_COMM_WORLD);
    // Le processus 0 Partage la matrice B à tous les autres processus 
    MPI_Bcast(B, nombreColonneA * nombreColonneB, MPI_INT, 0, MPI_COMM_WORLD);
    // On calcule le produit matricielle d'une partie de A avec la matrice B en fonction du processus en cours
    for (int i = rang * nombreElement; i < (rang + 1) * nombreElement; i++){
        for (int j = 0; j < nombreColonneB; j++){
            somme = 0;
            for(int k = 0; k < nombreColonneA; k++){
                somme += A[i][k]*B[k][j];
                //printf(" Rang : %d, i = %d, j = %d, A = %d, B = %d, C= %d \n", rang, i, j, A[i][k], B[k][j], somme);
            }
            C[i][j] = somme;
            //printf("C= %d \n", C[i][j]);
        }
    }
    //On rassemble les différents résultats de chaque processus dans C
    MPI_Gather(C[rang * nombreElement], nombreColonneB * nombreElement, MPI_INT, C, nombreColonneB * nombreElement, MPI_INT, 0, MPI_COMM_WORLD);
    // Si on se trouve dans le processus 0
    if (rang == 0){
        // On affiche le vecteur résulat C
        printf("C = \n");
        for(int i = 0; i < nombreLigneA; i++) {
            for(int j = 0; j < nombreColonneB; j++){
                printf("    %d ", C[i][j]);
            }
            printf("\n");
        }
    }
    //Désactiver l'environnement MPI
    MPI_Finalize();
    return 0;
}