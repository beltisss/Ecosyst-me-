# Simulation simple d’un écosystème en C

Ce projet propose une simulation simple d’un écosystème en langage C, avec des **proies** et des **prédateurs** évoluant sur une grille.

L’objectif était de manipuler des structures de données dynamiques, de simuler des déplacements et d’observer l’évolution d’une population au fil du temps.

## Contenu du projet

Le programme repose sur :

- une représentation des animaux sous forme de **listes chaînées**
- une gestion des **proies** et des **prédateurs**
- un affichage textuel de l’écosystème dans la console
- une mise à jour progressive du monde à chaque itération

## Fonctionnalités principales

- création et ajout d’animaux
- suppression et libération de mémoire
- comptage récursif et itératif des animaux
- déplacement aléatoire sur la grille
- reproduction des proies
- prédation et mise à jour de l’énergie
- affichage de l’état de l’écosystème

## Fichiers principaux

- `ecosys.c` : fonctions principales de gestion de l’écosystème
- `ecosys.h` : structures et prototypes
- `main_ecosys.c` : simulation principale
- `main_tests.c` : premiers tests
- `main_tests2.c` : tests complémentaires
- `Makefile` : compilation du projet

## Compilation

```bash
make
```

## Exécution

### Lancer la simulation principale

```bash
./ecosys
```

### Lancer les tests

```bash
./tests_ecosys
```

```bash
./tests_ecosys2
```

## Ce que ce projet met en avant

- utilisation du langage **C**
- manipulation de **listes chaînées**
- gestion de la **mémoire dynamique**
- séparation entre logique métier, interface console et tests
- simulation simple d’un système proies / prédateurs

## Auteure

**Belkiss Tiss**
