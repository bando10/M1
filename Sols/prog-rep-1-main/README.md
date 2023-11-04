# Projet Programmation Répartie I

<div align="justify"> Ce TP a été réalisé par <b>GUEYE El Hadji Ahmadou</b> et <b>HENRY Nathan</b> dans le cadre de l'enseignement de Programmation Répartie en Master 1 de Génie Logiciel à l'université de Montpellier dans l'année scolaire 2022-2023. </div>

## I) Lancement et Exécution

> Compilation de notre programme
```console
foo@bar:~$ cd /chemin/vers/dossier/racine/projet
foo@bar:~$ make
```

> Lancement d'une seul instance de notre programme
```console
foo@bar:~$ cd /chemin/vers/dossier/racine/projet
foo@bar:~$ ./bin/node -f <chemin_fichier_graph> -p <id_processus>
```

> Lancement de **`x`** instance de notre programme
```console
foo@bar:~$ cd /chemin/vers/dossier/racine/projet
foo@bar:~$ chmod +x ./runner.bash
foo@bar:~$ ./runner.bash -f <chemin_fichier_graph>
```

## II) Exemples

### Lancement de 500 instances de notre programme.

> Nous avons plusieurs fichiers de graphe prêt à l'utilisation dans notre dossier **`network-config`**. Les fichiers **`network125.txt`**, **`network250.txt`**, **`network500.txt`** et **`network1000.txt`** contiennent respectivement **125**, **250**, **500** et **1000** noeuds. 

```console
foo@bar:~$ ./runner.bash -f "network-config/network500.txt"
```

