#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"



int main(void) {
  int i;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  float energie= 10.7;

  srand(time(NULL));

  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  liste_proie=a1;

  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;


  liste_predateur=a5;
  
  
  afficher_ecosys(liste_proie,liste_predateur);  
  
   ajouter_animal(5, 5, 10.0, &liste_proie);
   ajouter_animal(2, 3, 8.5, &liste_proie);
   ajouter_animal(7, 8, 6.0, &liste_proie);
   ajouter_animal(3, 4, 12.0, &liste_predateur);
   ajouter_animal(6, 6, 9.5, &liste_predateur);
   
   afficher_ecosys(liste_proie, liste_predateur);
   
   printf("\nAprès déplacement des animaux:\n");
   bouger_animaux(liste_proie);
   bouger_animaux(liste_predateur);
   afficher_ecosys(liste_proie, liste_predateur);

   // Libérer la mémoire allouée pour les animaux
   liberer_liste_animaux(liste_proie);
   liberer_liste_animaux(liste_predateur);


  return 0;
}
