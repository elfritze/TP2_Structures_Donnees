/**
 * \file Principal.cpp
 * \brief Fichier test pour le bottin téléphonique
 * \author Mathieu L'Écuyer, Éric Guillemette
 * \version 0.1
 * \date juillet 2014
 */

#include "Bottin.h"

using namespace std;
using namespace TP2P2;

/**
 * \fn int main()
 * \brief Fonction principale pour tester les méthodes du bottin téléphonique.
 *
 * \return 0 - Arrêt normal du programme.
 */
int main()
{
   try
   {
      // Fichier texte pour faire les tests.
      ifstream fichier("Bottin.txt", ios::in);
      if (!fichier)
      {
         cerr << "Le fichier Bottin.txt est introuvable." << endl;
         return 1;
      }

      int nbCollisions = 0;   // compteur pour le nombre de collisions

      // Chargement du bottin à partir d'un fichier texte
      Bottin bottin(fichier, nbCollisions);

      // Fermeture du fichier texte
      fichier.close();


      // Le nombre de collisions totales...
      //
      cout << "Le nombre de collisions dans tabTelephone = " << bottin.getCollisionsTel() << endl;
      cout << "Le nombre de collisions dans tabNomPrenom = " << bottin.getCollisionsNom() << endl;
      cout << "------------------------------------------------" << endl;
      cout << "Le total des collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;


      // Tests de recherche avec la clé téléphone
      //
      cout << "Test de recherche avec la clé téléphone :" << endl;
      Employe t1 = bottin.trouverAvecTelephone("(959) 787-5537", nbCollisions);
      cout << ">> Recherche de " << t1.tel << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(t1) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;
      //
      cout << "Test de recherche avec la clé téléphone :" << endl;
      Employe t2 = bottin.trouverAvecTelephone("(559) 884-6422", nbCollisions);
      cout << ">> Recherche de " << t2.tel << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(t2) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;


      // Tests de recherche avec la clé Nom/Prénom
      //
      cout << "Test de recherche avec la clé Nom/Prénom :" << endl;
      Employe n1 = bottin.trouverAvecNomPrenom("Hawks, David", nbCollisions);
      cout << ">> Recherche de " << n1.nom << ", " << n1.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n1) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;
      //
      cout << "Test de recherche avec la clé Nom/Prénom :" << endl;
      Employe n2 = bottin.trouverAvecNomPrenom("Worker, Steven", nbCollisions);
      cout << ">> Recherche de " << n2.nom << ", " << n2.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n2) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;


      // Ajout d'employé dans le bottin
      //
      bottin.ajouter("Blo", "Joe", "(123) 456-7890", "(987) 654-3210", "joe.blo@test.edu");
      //
      // la ligne qui suit retourne une erreur puisque c'est un doublon
      // bottin.ajouter("Worker", "Steven", "(530) 754-8519", "(530) 754-8541", "jawolpert@ucdavis.edu");


      // Vérification que l'ajout s'est bien fait
      //
      cout << "Vérification de l'ajout :" << endl;

      bottin.contient("Blo, Joe") ?
            cout << ">> L'employé est présent dans le bottin.\n" :
            cout << ">> L'employé n'est pas présent dans le bottin.\n";
      cout << "------------------------------------------------" << endl;
      //
      // Récupération des informations de l'employé
      //
      Employe a1 = bottin.trouverAvecTelephone("(123) 456-7890", nbCollisions);
      cout << bottin.infosEmploye(a1) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;


      // Suppression d'employé du bottin
      //
      bottin.supprimer("Adams, Thomas E");
      //
      // la ligne qui suit retourne une erreur puisqu'il n'y pas d'entrée correspondante
      // bottin.supprimer("Doe, John");


      // Vérification que la suppression s'est bien faite
      //
      cout << "Test de suppression de l'employé :" << endl;
      bottin.contient("(530) 752-1266") ?
            cout << ">> L'employé est présent dans le bottin.\n" :
            cout << ">> L'employé n'est pas présent dans le bottin.\n";
      cout << endl << endl;


      // Test de recherche après suppression
      //
      cout << "Test de recherche après suppression :" << endl;
      Employe n3 = bottin.trouverAvecNomPrenom("Zivnuska, John", nbCollisions);
      cout << ">> Recherche de " << n3.nom << ", " << n3.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n3) << endl;
      cout << "Le nombre de collisions rencontrées = " << nbCollisions << endl;
      cout << endl << endl;


      // Test pour vider le bottin
      //
      bottin.rendreVide();

      // Vérification pour le bottin vide
      //
      cout << "Vérification que le bottin est vide :" << endl;
      bottin.contient("Abbott, Ursula K") ?
            cout << ">> L'employé est présent dans le bottin.\n" :
            cout << ">> L'employé n'est pas présent dans le bottin.\n";
      bottin.contient("Zivnuska, John") ?
            cout << ">> L'employé est présent dans le bottin.\n" :
            cout << ">> L'employé n'est pas présent dans le bottin.\n";


   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

    return 0;
}
