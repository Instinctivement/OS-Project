# OS-Project

Ce projet est un projet de système réalisé dans le cadre d'un projet de fin d'année en groupe. Il est hébergé sur différents dépôts GitHub.

## Structure du projet

Le projet comprend les éléments suivants :

- **Backup** : représente notre serveur de sauvegarde.
- **Production** : représente notre serveur de production.
- **Modules** : contient notre programme principal. À la racine de ce dossier, vous trouverez :
  - Le fichier Makefile pour la compilation.
  - Le dossier "object" pour les fichiers .o.
  - Le dossier "src" contenant nos différents modules :
    - ModuleTestServer
    - ModuleSynchroList
    - ModuleCopyList
    - ModLog
    - ModStat
  - Le dossier "IntegrationServer" représentant notre serveur d'intégration.
  - Les fichiers .c
  - Le fichier main.c

## Dépendances requises

Les dépendances nécessaires pour exécuter le projet sont les suivantes :

- Compilateur GNU/GCC
- Environnement Unix (de préférence Linux)

## Compilation et exécution

Pour simplifier la tâche, vous aurez besoin de trois terminaux ouverts simultanément :

1. Ouvrez le terminal dans le dossier **Production**.
2. Ouvrez le terminal dans le dossier **Backup**.
3. Ouvrez le terminal dans le dossier **Modules**.

Une fois les trois terminaux ouverts, suivez les étapes suivantes :

### Terminal du dossier Production

1. Dans le terminal du dossier **Production**, exécutez la commande suivante : `gcc -o main prod_server.c`.
2. Ensuite, exécutez la commande : `./main`.
3. Une fois que le serveur de production est en marche, il commencera à générer des fichiers.

### Terminal du dossier Backup

1. Dans le terminal du dossier **Backup**, exécutez la commande suivante : `gcc -o main backup_server.c`.
2. Ensuite, exécutez la commande : `./main`.
3. Le serveur de sauvegarde se mettra en attente, car le serveur de production est déjà en marche et effectue son travail.

### Terminal du dossier Modules

1. Dans le terminal du dossier **Modules**, exécutez la commande suivante : `make app`.
2. Ensuite, exécutez la commande : `./app`.
3. Dans le terminal, vous verrez plusieurs rubriques s'afficher :
   - La première rubrique est celle du "Test des serveurs". Elle affiche l'état des deux serveurs, indiquant s'ils sont allumés (ACTIVER) ou éteints (DESACTIVER). Elle indique également le serveur qui génère les fichiers en ce moment et celui qui est en attente.
   - La deuxième rubrique est celle de la "Synchronisation des serveurs". Elle indique si les différents serveurs possèdent les mêmes données.
   - La troisième rubrique est celle de la "Copie des fichiers du serveur de production". Selon les informations de la rubrique précédente, si tous les serveurs possèdent déjà les mêmes données, rien n'est fait. Sinon, les fichiers sont copiés du serveur de production vers les autres serveurs.
   
Chaque terminal affiche les informations à une fréquence de 4 secondes. Ainsi, s'il y a des changements pendant ce temps, les données affichées seront mises à jour.

## Phase de tests

### Test 1 : Changement de serveur en cas d'arrêt du serveur principal

- Dans le terminal du dossier **Production**, arrêtez le programme en appuyant sur "Ctrl + C". Cela arrêtera le serveur de production.
- Le serveur de sauvegarde affichera alors "en attente" et commencera à générer les fichiers toutes les 4 secondes, effectuant le même travail que le serveur de production.
- Dans le terminal du dossier **Modules**, les informations affichées dans la rubrique "Test des serveurs" changeront. Le serveur de production sera déclaré éteint et désactivé, tandis que le serveur de sauvegarde sera déclaré allumé et activé.
- Pour continuer le test, vous pouvez relancer le serveur de production. Immédiatement, le serveur de sauvegarde repassera en attente et les informations affichées dans le terminal du dossier **Modules** changeront à nouveau.

### Test 2 : Synchronisation des serveurs et copie de fichiers

- Pendant que les serveurs tournent, ajoutez un fichier dans le dossier **Production/home**.
- La présence du fichier sera immédiatement signalée dans le programme, et la copie vers les autres serveurs sera également affichée dans le terminal du programme principal (dossier **Modules**).

### Test 3 : Vérification de la copie

- Vous pouvez vérifier les contenus des dossiers **Production/home**, **Backup/home**, **Modules/src/IntegrationServer/home** avant et après les copies.

Enfin, le terminal du module affiche les statistiques d'erreurs et de fichiers copiés. Les journaux de ces informations sont disponibles dans les dossiers **Modules/src/ModLog** et **Modules/src/ModStat**.

Cela conclut le README pour le projet OS-Project. Un grand Merci à notre professeur Madame **Dhekra Abouda** pour son enseignement fluide et ludique !
