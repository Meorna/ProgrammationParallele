/*!
  \file main.c
  \author Romane Sallio <sallioroma@eisti.eu>
  \version 1
  \date  02 / 04 / 2020
  \brief TP noté Architecture et Programmation Parallèle exercice 2
*/

#include "produitMatriceVecteur.h"

int main(int argc, char *argv[]){
    int nombreLigneA = 3;
    int nombreColonneA = 2;
    int A[nombreLigneA][nombreColonneA];
    int* B;
    int* C;
    int* resultatTmp;
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
    // Le nombre de colonne de la matrice A doit être divisible par le nombre de processus donné
    // C'est à dire que le reste de la divion doit être égal à 0 
    if((nombreColonneA % nombreProcessus) == 0){
        // Le résulat est la taille de chaque sous vecteur de B
        nombreElement = nombreColonneA / nombreProcessus;
    } else {
        // Afficher un message d'erreur si l'utilisateur n'a pas saisi un bon nombre de processus
        fprintf(stderr, "nombreColonneA = %d doit être divisible par nombreProcessus = %d\n", nombreColonneA, nombreProcessus);
        // Terminer l'exécution de l'environnement MPI avec 1 comme code d'erreur
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    // On alloue la mémoire pour le vecteur qui contiendra le résultat du produit
    C = malloc(nombreColonneA * sizeof(int));
    // Le processus 0 intialise la matrice A et le vecteur B en allouant la mémoire nécessaire et en leurs indministrant des valeurs
    if(rang == 0){
        B = malloc(nombreColonneA * sizeof(int));
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
        B[0] = 1;
        B[1] = 2;
        printf("B = \n");
        for(int i = 0; i < nombreColonneA; i++) {
            printf("    %d \n", B[i]);
        }
    // Les autres processus allouent la mémoire pour le sous-vecteur de B qu'ils recevront
    } else {
        B = malloc(nombreElement * sizeof(int));
    }
    // Le processus 0 Partage la matrice A à tous les autres processus 
    MPI_Bcast(A, nombreLigneA * nombreColonneA, MPI_INT, 0, MPI_COMM_WORLD);
    // Le processus 0 divise B et partage une partie de B à chaque processus 
    MPI_Scatter(B, nombreElement, MPI_INT, B, nombreElement, MPI_INT, 0, MPI_COMM_WORLD);
    resultatTmp = malloc(nombreLigneA * sizeof(int));
    // On calcule le produit matricielle de A avec un sous-vecteur de B en fonction du processus en cours
    for (int i = 0; i < nombreLigneA; i++){
        somme = 0;
        for (int j = 0; j < nombreElement; j++){
            //printf("A = %d B= %d\n", A[i][rang * nombreElement + j], B[j]);
            somme += (A[i][rang * nombreElement + j] * B[j]);
            //printf("somme = %d\n", somme);
        }
        //printf("i =%d, somme = %d\n\n", i, somme);
        // On place chaque résultat trouvé dans un tableau temporaire
        resultatTmp[i] = somme;
    }
    //On aditionne les différents résultat de chaque processus qu'on place dans C
    MPI_Reduce_scatter(resultatTmp, C, &nombreLigneA, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // Si on se trouve dans le processus 0
    if (rang == 0){
        // On affiche le vecteur résulat C
        printf("C = \n");
        for(int i = 0; i < nombreLigneA; i++) {
            printf("    %d \n", C[i]);
        }
    }
    // On libère la mémoire alloué
    free(C);
    free(B);
    free(resultatTmp);
    //Désactiver l'environnement MPI
    MPI_Finalize();
    return 0;
}
