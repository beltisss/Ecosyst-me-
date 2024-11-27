#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

int main() {
    Animal *liste_proies = NULL;
    Animal *liste_predateurs = NULL;

    // Créer 20 proies/prédateurs à des positions aléatoires
    for (int i = 0; i < 20; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, (float)(rand() % 50 + 10), &liste_proies);
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, (float)(rand() % 50 + 10), &liste_predateurs);
    }

    
    // Vérifier le nombre de proies et de prédateurs
    printf("Nombre de proies : %d\n", compte_animal_it(liste_proies));
    printf("Nombre de prédateurs : %d\n", compte_animal_it(liste_predateurs));

    // Afficher l'état de l'écosystème
    afficher_ecosys(liste_proies, liste_predateurs);
    


    // Libérer quelques proies et prédateurs aléatoirement
    
    enlever_animal(&liste_proies, liste_proies); // Supprimer la première proie
    enlever_animal(&liste_predateurs, liste_predateurs); // Supprimer le premier prédateur

    // Recompter après suppression
    printf("Après suppression:\n");
    printf("Nombre de proies : %d\n", compte_animal_it(liste_proies));
    printf("Nombre de prédateurs : %d\n", compte_animal_it(liste_predateurs));

    // Libérer la mémoire des listes d'animaux
    liberer_liste_animaux(liste_proies);
    liberer_liste_animaux(liste_predateurs);

    return 0;
}

