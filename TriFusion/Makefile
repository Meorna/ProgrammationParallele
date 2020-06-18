srcdir = src/
bindir = bin/
docdir = doc/
CC = gcc -fopenmp
RM = rm -f
SRC = $(wildcard $(srcdir)*.c)
HEAD = $(wildcard $(srcdir)*.h)
OBJ = $(subst $(srcdir),$(bindir),$(SRC:.c=.o))
PROG = exe
CP = cp -r

all : $(PROG)

$(PROG): $(OBJ)
	$(CC) $^ -o $@ -lm

$(bindir)main.o: $(srcdir)main.c
	$(CC) -c $^ -o $@

$(bindir)%.o: $(srcdir)%.c $(srcdir)%.h
	$(CC) -c $< -o $(@)


.PHONY : clean
clean :
	$(RM) $(OBJ) $(PROG)

.PHONY : doc
doc :
	echo "Instructions pour compiler et exécuter le code et utiliser le makefile : \n    Compiler : make \n    Exécuter : ./exe \n    Nettoyer : make clean \n    Créer doc : make doc \n    Créer archive : make give \n\nFonctionnement du code : \n    main.c: \n        int main(int argc, char const *argv[]) : Créer un tableau à trier, afficher le tableau, \n        appeller la fonction triFusion dans une région parallèle et executé sur un seul thread, afficher le tableau trié et le temps d'exécution. \n            printf(texte) : Ecrire un message dans la console. \n            omp_get_wtime() : Déterminer le temps d'exécution, un appel au début et un appel à la fin du programme. \n            omp_set_num_threads(2) : Définir le nombre de threads. \n            #pragma omp parallel : Définir une région du programme qui doit être éxecuté en parallèle. \n            #pragma omp single nowait : Exécuter le bloc par un seul thread et remplacer la barrière implicite. \n    triFusion.c : \n        void affichageTableau(int tab[], int taille) : Afficher un tableau. \n            printf(texte) : Ecrire un message dans la console. \n        int triFusion(int tab[], int debut, int fin) : Appeler de manière récursive pour diviser le tableau en deux un nombre maximum de fois \n        et appeler la fonction fusion. \n            #pragma omp task shared(triGauche) : Déclarer une tache fille qui exécute le bloc. \n            #pragma omp taskwait : Attendre que les tâches filles soient terminées avant de continuer. \n        void fusion(int tab[], int debutTabDroit, int finTabDroit, int finTabGauche) : Fusionner en triant les tableaux. \n            malloc(taille) : allouer la mémoire. \n            free(tab) : libérer la mémoire. \n\nDécision de design : \n    Pour cet exercice, j'ai décidé de reprendre le concept vu en cours dans l'exercice \n    faisant un calcul parallèle avec OpenMP de l'algoritme de fibonacci en récursif \n    En l'appliquand à l'algorithme de tri fusion en récursif. \n\nRésultat obtenu : \n    Tableau non trié : \n    4 8 5 3 6 9 1 7 2 \n    Thread : 0 \n    Thread : 1 \n    Tableau trié : \n    1 2 3 4 5 6 7 8 9 \n    Temps d'exécution : 0.034038 s\n\nSection de références : \n    https://arel.eisti.fr/documents/67236/download/03-PP-OpenMP-3.pdf \n    https://arel.eisti.fr/documents/67237/download/TP3-PP.pdf \n    https://arel.eisti.fr/documents/62316 \n    http://icps.u-strasbg.fr/~bastoul/teaching/openmp/bastoul_cours_openmp.pdf \n    https://www.lri.fr/~falcou/teaching/par/OpenMP-cours.pdf \n    https://www.labunix.uqam.ca/~tremblay/INF5171/Diapositives/11-open-mp-ac.pdf \n    https://docs.microsoft.com/fr-fr/cpp/parallel/openmp/openmp-c-and-cpp-application-program-interface?view=vs-2019"> $(docdir)README
	
.PHONY : give
give :
		$(RM) $(OBJ) $(PROG)
		tar zcvf sallioroma-triFusionParallele.tar.gz $(srcdir) $(bindir) $(docdir) Makefile

.PHONY : restore

