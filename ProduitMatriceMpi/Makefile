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
	echo "Instructions pour compiler et exécuter le code et utiliser le makefile : \n    Compiler : make \n    Exécuter : mpirun -np 3 ./exe \n    Nettoyer : make clean \n    Créer doc : make doc \n    Créer archive : make give \n\nFonctionnement du code : \n    main.c: \n        int main(int argc, char const *argv[]) : Pour commencer on initialise l'environnement MPI, on récupère le nombre de processus et le rang du processus en cours, \n        on vérifie que le reste de la division euclidienne du nombre de ligne de la matrice A est bien divisible par le nombre de processus lancé par l'utilisateur, \n        si oui on divise le nombre de ligne par le nombre de processus pour obtenir le nombre d'éléments pour chaque sous matrice, \n        sinon on affiche un message d'erreur et on termine l'exécution de l'environnement. \n        Ensuite, si le processus en cours a pour valeur 0 on initialise les matrices A et B avec des entiers. \n        Pour continuer, le processus 0 partage la matrice B aux autres processus puis divise la matrice A en sous matrice pour partager chaque sous matrice à un processus. \n        Chaque sous-matrice calcule sa partie du produit matricielle puis les calculs sont rassemblés. Si on se trouve dans le processus 0 on affiche la matrice C qui contient le résultat. \n        Pour finir, on désactive l'environnement MPI.\n            MPI_Init(&argc,&argv) : Initialiser l'environnement MPI. \n            MPI_Comm_size(MPI_COMM_WORLD, &nombreProcessus) : Retourner le nombre de processus. \n            MPI_Comm_rank(MPI_COMM_WORLD, &rang) : Retourner le rang du processus en cours. \n            printf(texte) : Ecrire un message dans la console. \n            fprintf(stderr, "nombreColonneA = %d doit être divisible par nombreProcessus = %d\n", nombreColonneA, nombreProcessus) : Ecrire dans un fichier erreur et afficher dans la console. \n            MPI_Abort(MPI_COMM_WORLD, 1) : Terminer l'environnement MPI avec un code retour d'erreur. \n            MPI_Bcast(B, nombreColonneA * nombreColonneB, MPI_INT, 0, MPI_COMM_WORLD) : Partager à tous les processus la matrice d'entier B à partir du processus 0. \n            MPI_Scatter(A, nombreColonneA * nombreElement, MPI_INT, A[rang * nombreElement], nombreColonneA * nombreElement, MPI_INT, 0, MPI_COMM_WORLD) : Diviser la matrice d'entier A par nombre de nombreElement lignes qui seront distribués entre tous les processus. \n            MPI_Gather(C[rang * nombreElement], nombreColonneB * nombreElement, MPI_INT, C, nombreColonneB * nombreElement, MPI_INT, 0, MPI_COMM_WORLD) : Rassembler les valeurs détarminées par tous les processus. \n            MPI_Finalize() : Finaliser l'environnement MPI. \n\nDécision de design : \n    Pour cet exercice, j'ai décidé de ne pas utilisé la base de code proposé par le professeur mais plutôt de reprendre la base de l'exercice deux que j'ai fait. \n    Au lieu d'utiliser la fonction MPI_Reduce_scatter j'ai d utiliser la fonction MPI_Gather pour faire marcher mon code.\n\nRésultat obtenu : \n    Nombre Processus : 3, Rang : 2 \n    Nombre Processus : 3, Rang : 1 \n    Nombre Processus : 3, Rang : 0 \n    A = \n        1     2 \n        3     4 \n        5     6 \n    B = \n        1     3     5     1     3 \n        2     4     6     2     4 \n    C = \n        5     11     17     5     11 \n        11     25     39     11     25 \n        17     33     61     17     39 \n\nSection de références : \n    https://arel.eisti.fr/documents/67238 \n    https://arel.eisti.fr/documents/67321 \n    http://www.idris.fr/media/formations/mpi/idrismpitp.pdf \n    https://www.open-mpi.org/doc/v4.0/"> $(docdir)README
	
.PHONY : give
give :
		$(RM) $(PROG)
		tar zcvf sallioroma-produitMatricesParallele.tar.gz $(srcdir) $(bindir) $(docdir) Makefile

.PHONY : restore
