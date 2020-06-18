srcdir = src/
docdir = doc/
CC = mpicc -Wall -Wextra
RM = rm -f
SRC = $(wildcard $(srcdir)*.c)
HEAD = $(wildcard $(srcdir)*.h)
PROG = exe
CP = cp -r

all : $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $^


.PHONY : clean
clean :
	$(RM) $(PROG)

.PHONY : doc
doc :
	echo "Instructions pour compiler et exécuter le code et utiliser le makefile : \n    Compiler : make \n    Exécuter : mpirun -np 2 ./exe \n    Nettoyer : make clean \n    Créer doc : make doc \n    Créer archive : make give \n\nFonctionnement du code : \n    main.c: \n        int main(int argc, char const *argv[]) : Pour commencer on initialise l'environnement MPI, on récupère le nombre de processus et le rang du processus en cours, \n        on vérifie que le reste de la division euclidienne du nombre de colonne de la matrice A est bien divisible par le nombre de processus lancé par l'utilisateur, \n        si oui on divise le nombre de colonne par le nombre de processus pour obtenir le nombre d'éléments pour chaque sous vecteur, \n        sinon on affiche un message d'erreur et on termine l'exécution de l'environnement, après on alloue la mémoire du vecteur pour le résultat du produit matriciel. \n        Ensuite, si le processus en cours a pour valeur 0 on initialise la matrice et le vecteur avec des entiers sinon on alloue la mémoire des sous vecteurs de taille calculée plus tôt. \n        Pour continuer, le processus 0 partage la matrice aux autres processus puis divise le vecteur en sous vecteur pour partager chaque sous vecteur à un processus. \n        Chaque sous-vecteur calcule sa partie du produit matricielle puis les calculs sont additionnés qu'on place dans un vecteur. Si on se trouve dans le processus 0 on affiche la résultat. \n        Pour finir, on libère la mémoire allouée pour les différents vecteur et désactiver l'environnement MPI.\n            MPI_Init(&argc,&argv) : Initialiser l'environnement MPI. \n            MPI_Comm_size(MPI_COMM_WORLD, &nombreProcessus) : Retourner le nombre de processus. \n            MPI_Comm_rank(MPI_COMM_WORLD, &rang) : Retourner le rang du processus en cours. \n            printf(texte) : Ecrire un message dans la console. \n            fprintf(stderr, "nombreColonneA = %d doit être divisible par nombreProcessus = %d\n", nombreColonneA, nombreProcessus) : Ecrire dans un fichier erreur et afficher dans la console. \n            MPI_Abort(MPI_COMM_WORLD, 1) : Terminer l'environnement MPI avec un code retour d'erreur. \n            malloc(nombreColonneA * sizeof(int)) : Allouer la mémoire d'un tableau. \n            MPI_Bcast(A, nombreLigneA * nombreColonneA, MPI_INT, 0, MPI_COMM_WORLD) : Partager à tous les processus le pointeur d'entier A à partir du processus 0. \n            MPI_Scatter(B, nombreElement, MPI_INT, B, nombreElement, MPI_INT, 0, MPI_COMM_WORLD) : Diviser le vecteur d'entier B en de nombreux sous-vecteur d'entier de taille nombreElement qui seront distribués entre tous les processus. \n            MPI_Reduce_scatter(resultatTmp, C, &nombreLigneA, MPI_INT, MPI_SUM, MPI_COMM_WORLD) : Additioner les différents vecteur d'entier resultatTmp et insérer la somme dans le vecteur C. \n            free(C) : Libérer la mémoire allouée. \n            MPI_Finalize() : Finaliser l'environnement MPI. \n\nDécision de design : \n    Pour cet exercice, j'ai décidé d'utiliser la fonction MPI_Reduce_scatter car elle était imposé dans l'énonncé, \n    j'ai donc construit mon code dans l'objectif de pouvoir utiliser cette fonction. \n\nRésultat obtenu : \n    Nombre Processus : 2, Rang : 1 \n    Nombre Processus : 2, Rang : 0 \n    A = \n        1     2 \n        3     4\n        5     6 \n    B = \n        1 \n        2 \n    C = \n        5 \n        11 \n        17\n\nSection de références : \n    https://arel.eisti.fr/documents/67238 \n    https://arel.eisti.fr/documents/67321 \n    http://www.idris.fr/media/formations/mpi/idrismpitp.pdf \n    https://www.rookiehpc.com/mpi/docs/mpi_reduce_scatter.php\n    https://linux.die.net/man/3/mpi_reduce_scatter \n    https://www.open-mpi.org/doc/v4.0/"> $(docdir)README
	
.PHONY : give
give :
		$(RM) $(PROG)
		tar zcvf sallioroma-produitMatriceVecteurParallele.tar.gz $(srcdir) $(docdir) Makefile

.PHONY : restore
