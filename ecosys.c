#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1 */
/* Part 1, exercice 4, question 2 */

/* Fonction pour créer un nouvel animal avec une position (x, y) et une énergie initiale */
Animal *creer_animal(int x, int y, float energie) {
  assert(x >= 0 && x < SIZE_X); // Vérifie que x est dans les limites de la grille (entre 0 et SIZE_X-1)
  assert(y >= 0 && y < SIZE_Y); // Vérifie que y est dans les limites de la grille (entre 0 et SIZE_Y-1)

  // Alloue de la mémoire pour un nouvel animal
  Animal *nv_a = (Animal *)malloc(sizeof(Animal));
  assert(nv_a); // Vérifie que l'allocation mémoire a réussi ; sinon, le programme s'arrête

  // Initialise les attributs de l'animal
  nv_a->x = x;                          // Attribue la coordonnée x de l'animal
  nv_a->y = y;                          // Attribue la coordonnée y de l'animal
  nv_a->energie = energie;              // Attribue l'énergie initiale
  nv_a->dir[0] = rand() % 3 - 1;        // Initialise le sens de la direction de x (soit -1[à gauche], 0[reste], ou 1[à droite])
  nv_a->dir[1] = rand() % 3 - 1;        // Initialise le sens de la direction de x (soit -1[en bas], 0[reste], ou 1[en haut])
  nv_a->suivant = NULL;                 // Initialise le pointeur suivant à NULL

  return nv_a;                          // Retourne un pointeur vers le nouvel animal
}

/* Part 1, exercice 4, question 3 */

/* Fonction pour ajouter un animal en tête d'une liste chaînée */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);                // Vérifie que l'animal à ajouter n'est pas NULL
  assert(!animal->suivant);      // Vérifie que l'animal n'a pas déjà de suivant (doit être le dernier élément)

  animal->suivant = liste;       // Place l'animal en tête de la liste existante
  return animal;                 // Retourne le nouvel animal comme tête de la liste
}

/* Part 1, exercice 6, question 2 */

/* Fonction pour créer et ajouter un nouvel animal en tête d'une liste chaînée */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  // Crée un nouvel animal et l'ajoute en tête de liste
  *liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x, y, energie));
}

/* Part 1, exercice 5, question 5 */

/* Fonction pour enlever un animal spécifique d'une liste chaînée et libérer sa mémoire */
void enlever_animal(Animal **liste, Animal *animal) {
  // Si la liste est vide ou l'animal à supprimer est NULL, il n'y a rien à faire
  if (liste == NULL || *liste == NULL) return;

  Animal *prec = NULL;          // Pointeur vers l'animal précédent
  Animal *courant = *liste;     // Pointeur pour parcourir la liste depuis la tête

  // Parcourt la liste pour trouver l'animal à enlever
  while (courant) {
    if (courant == animal) {     // Si l'animal courant est celui à supprimer
      if (prec) {
        prec->suivant = courant->suivant; // Le précédent pointe vers le suivant du courant, contournant l'animal
      } else {
        *liste = courant->suivant;        // Si c'est la tête, la liste pointe vers l'animal suivant
      }
      free(courant);                      // Libère la mémoire de l'animal
      return;                             // Fin de la fonction après la suppression
    }
    prec = courant;                       // Avance les pointeurs dans la liste
    courant = courant->suivant;
  }
}

/* Fonction pour libérer la mémoire de tous les animaux dans une liste chaînée */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *temp;
  while (liste) {
    temp = liste;            // Stocke l'animal courant
    liste = liste->suivant;   // Passe au suivant dans la liste
    free(temp);               // Libère la mémoire de l'animal actuel
  }
  return NULL;                // Retourne NULL pour indiquer que la liste est vide
}

/* Part 1, exercice 4, question 4 */

/* Fonction récursive pour compter les animaux dans une liste chaînée */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;          // Si la liste est vide, retourne 0
  return 1 + compte_animal_rec(la->suivant); // Compte l'animal actuel et appelle récursivement pour le suivant
}

/* Fonction itérative pour compter les animaux dans une liste chaînée */
unsigned int compte_animal_it(Animal *la) {
  int cpt = 0;                // Initialise un compteur à 0
  while (la) {                // Parcourt chaque animal de la liste
    ++cpt;                    // Incrémente le compteur
    la = la->suivant;         // Passe à l'animal suivant
  }
  return cpt;                 // Retourne le nombre total d'animaux comptés
}

/* Part 1, exercice 5, question 1 */

/* Fonction qui affiche l'écosystème dans une grille, montrant les proies, les prédateurs, et les cases vides */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y]; // Grille de l'écosystème

  /* Initialise chaque case de la grille avec un espace (case vide) */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j] = ' ';
    }
  }

  /* Ajoute les proies dans la grille */
  Animal *pa = liste_proie;
  while (pa) {
    if (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y) { // Vérifie que les coordonnées sont valides
      ecosys[pa->x][pa->y] = '*';  // Place une étoile pour représenter la présence de proies
    }
    pa = pa->suivant;              // Passe à la proie suivante
  }

  /* Ajoute les prédateurs dans la grille */
  pa = liste_predateur;
  while (pa) {
    if (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y) { // Vérifie que les coordonnées sont valides
      if (ecosys[pa->x][pa->y] == '*') {  // Si une proie est déjà présente dans cette case
        ecosys[pa->x][pa->y] = '@';       // Utilise '@' pour indiquer une proie et un prédateur ensemble
      } else {
        ecosys[pa->x][pa->y] = 'O';       // Utilise 'O' pour indiquer la présence d'un prédateur seul
      }
    }
    pa = pa->suivant;              // Passe au prédateur suivant
  }

  /* Affiche la bordure supérieure de la grille */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) printf("-");
  printf("+\n");

  /* Affiche le contenu de chaque ligne de la grille */
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) putchar(ecosys[i][j]); // Affiche chaque case de la ligne
    printf("|\n");
  }

  /* Affiche la bordure inférieure de la grille */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) printf("-");
  printf("+\n");

  /* Affiche le nombre total de proies et de prédateurs dans la grille */
  int nbproie = compte_animal_it(liste_proie);
  int nbpred = compte_animal_it(liste_predateur);
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

/* Fonction pour effacer l'écran de la console (utilise un code ANSI) */
void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  // Code ANSI pour effacer l'écran et repositionner le curseur
}

/* PARTIE 2 */

/* Part 2, exercice 4, question 1 */

/* Fonction pour déplacer tous les animaux dans la liste en appliquant une toricité (bouclage de la grille) */
void bouger_animaux(Animal *la) {
  while (la != NULL) {            // Parcourt chaque animal de la liste
    // Calcule la nouvelle position avec toricité (le monde est une grille qui boucle sur elle-même)
    la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
    la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;

    // Met à jour la direction de manière aléatoire
    la->dir[0] = rand() % 3 - 1;  // Direction x aléatoire : -1, 0, ou 1
    la->dir[1] = rand() % 3 - 1;  // Direction y aléatoire : -1, 0, ou 1
    
    la = la->suivant;             // Passe à l'animal suivant
  }
}

/* Part 2, exercice 4, question 3 */

/* Fonction pour la reproduction des animaux en fonction d'une probabilité */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *current = *liste_animal; // Pointeur vers le début de la liste

  while (current) { // Parcourt chaque animal
    if ((float)rand() / RAND_MAX < p_reproduce) { // Si l'animal se reproduit (selon p_reproduce)
      ajouter_animal(current->x, current->y, current->energie / 2, liste_animal); // Ajoute une progéniture
      current->energie /= 2; // L'énergie de l'animal est divisée entre lui et sa progéniture
    }
    current = current->suivant; // Passe à l'animal suivant
  }
}

/* Part 2, exercice 6, question 1 */

/* Fonction pour mettre à jour la liste des proies : bouge, réduit l'énergie, et gère la reproduction */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  Animal *courant = *liste_proie;

  while (courant != NULL) {
    bouger_animaux(courant);       // Déplace chaque proie
    courant->energie -= 1;         // Réduit l'énergie de la proie

    if (courant->energie < 0) {    // Si l'énergie de la proie est épuisée
      enlever_animal(liste_proie, courant); // Enlève la proie de la liste
    } else {
      if (rand() / (float)RAND_MAX < PROB_REPRODUCTION) { // Si la proie peut se reproduire
        ajouter_animal(courant->x, courant->y, courant->energie / 2, liste_proie); // Crée une nouvelle proie
      }
    }
    courant = courant->suivant;
  }
}

/* Part 2, exercice 7, question 1 */

/* Fonction pour chercher un animal à une position (x, y) dans une liste */
Animal *animal_en_XY(Animal *l, int x, int y) {
  while (l != NULL) {
    if (l->x == x && l->y == y) { // Si les coordonnées correspondent, l'animal est trouvé
      return l;
    }
    l = l->suivant;
  }
  return NULL; // Aucun animal trouvé à (x, y)
}

/* Part 2, exercice 7, question 2 */

/* Fonction pour mettre à jour la liste des prédateurs */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  Animal *pred = *liste_predateur;

  while (pred != NULL) {
    bouger_animaux(pred);         // Déplace chaque prédateur
    pred->energie -= 1;           // Réduit l'énergie du prédateur

    // Cherche une proie dans la même case que le prédateur
    Animal *proie = animal_en_XY(*liste_proie, pred->x, pred->y);
    if (proie != NULL) {          // Si une proie est trouvée
      pred->energie += proie->energie; // Le prédateur gagne l'énergie de la proie
      enlever_animal(liste_proie, proie); // Supprime la proie
    }
    pred = pred->suivant;
  }
}

/* Part 2, exercice 5, question 2 */

/* Fonction pour mettre à jour l'herbe dans chaque case du monde */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      monde[i][j] += 1; // Incrémente la quantité d'herbe dans chaque case de la grille
    }
  }
}

