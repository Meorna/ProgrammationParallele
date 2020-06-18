/*!
  \file triFusion.h
  \author Romane Sallio <sallioroma@eisti.eu>
  \version 1
  \date  29 / 03 / 2020
  \brief TP noté Architecture et Programmation Parallèle exercice 1
*/

#ifndef __TRIFUSION_H_
#define __TRIFUSION_H_

/* inclusion des entetes de librairies */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* inclusion des entetes de fonctions */
void affichageTableau(int tab[], int taille);
void fusion(int tab[], int debutTabDroit, int finTabDroit, int finTabGauche);
int triFusion(int tab[], int debut, int fin);

#endif
