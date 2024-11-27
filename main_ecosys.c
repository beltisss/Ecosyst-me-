#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ecosys.h"

int main() {
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int monde[SIZE_X][SIZE_Y] = {{0}};

    // Initialisation de quelques proies et prédateurs
    ajouter_animal(5, 5, 10.0, &liste_proie);
    ajouter_animal(10, 10, 15.0, &liste_predateur);

    // Tester le déplacement et la reproduction
    bouger_animaux(liste_proie);
    bouger_animaux(liste_predateur);

    // Affichage de l'état initial
    afficher_ecosys(liste_predateur, liste_proie);

    // Boucle principale de simulation
    int max_iterations = 200;
    for (int i = 0; i < max_iterations; i++) {
        rafraichir_proies(&liste_proie, monde);
        rafraichir_predateurs(&liste_predateur, &liste_proie);
        rafraichir_monde(monde);

        afficher_ecosys(liste_predateur, liste_proie);

        // Arrêter la simulation si toutes les proies ou tous les prédateurs sont absents (observé manuellement)
        if (!liste_proie || !liste_predateur) {
            break;
        }

        // Pause pour ralentir l'affichage
        usleep(50000);
    }

    // Libération de la mémoire
    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);

    return 0;
}

