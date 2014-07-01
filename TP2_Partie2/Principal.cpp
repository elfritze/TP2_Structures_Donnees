/**
 * \file Principal.cpp
 * \brief Fichier test pour l'annuaire t�l�phonique
 * \author Mathieu L'�cuyer, �ric Guillemette
 * \version 0.1
 * \date juillet 2014
 *
 */

#include "Bottin.h"

using namespace std;
using namespace TP2P2;

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

      // Chargement du bottin � partir d'un fichier texte
      Bottin bottin(fichier, nbCollisions);

      // Fermeture du fichier texte
      fichier.close();


      // Le nombre de collisions totales...
      //
      cout << "Le nombre de collisions dans tabTelephone = " << bottin.getCollisionsTel() << endl;
      cout << "Le nombre de collisions dans tabNomPrenom = " << bottin.getCollisionsNom() << endl;
      cout << "------------------------------------------------" << endl;
      cout << "Le total des collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;


      // Tests de recherche avec la cl� t�l�phone
      //
      Employe t1 = bottin.trouverAvecTelephone("(269) 533-5695", nbCollisions);
      cout << "Recherche de " << t1.tel << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(t1) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;
      //
      Employe t2 = bottin.trouverAvecTelephone("(559) 884-6422", nbCollisions);
      cout << "Recherche de " << t2.tel << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(t2) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;


      // Tests de recherche avec la cl� Nom/Pr�nom
      //
      Employe n1 = bottin.trouverAvecNomPrenom("Henderson, Patricia", nbCollisions);
      cout << "Recherche de " << n1.nom << ", " << n1.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n1) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;
      //
      Employe n2 = bottin.trouverAvecNomPrenom("Zepeda, Manuel", nbCollisions);
      cout << "Recherche de " << n2.nom << ", " << n2.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n2) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;


      // Ajout d'employ� dans le bottin
      //
      bottin.ajouter("Blo", "Joe", "(123) 456-7890", "(987) 654-3210", "joe.blo@test.edu");
      //
      // la ligne qui suit retourne une erreur puisque c'est un doublon
      // bottin.ajouter("Zepeda", "Manuel", "(559) 884-6422", "(559) 884-2216", "jjrennernantz@ucdavis.edu");


      // V�rification que l'ajout s'est bien fait
      //
      bottin.contient("Blo, Joe") ?
            cout << "ajouter : L'employ� est pr�sent dans le bottin.\n" :
            cout << "ajouter : L'employ� n'est pas pr�sent dans le bottin.\n";
      cout << "------------------------------------------------" << endl;
      //
      // R�cup�ration des informations de l'employ�
      //
      Employe a1 = bottin.trouverAvecTelephone("(123) 456-7890", nbCollisions);
      cout << bottin.infosEmploye(a1) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;


      // Suppression d'employ� du bottin
      //
      bottin.supprimer("Blo, Joe");
      //
      // la ligne qui suit retourne une erreur puisqu'il n'y pas d'entr�e correspondante
      // bottin.supprimer("Doe, John");

      // V�rification que la suppression s'est bien faite
      //
      cout << "Test de suppression de l'employ� :" << endl;
      bottin.contient("Blo, Joe") ?
            cout << ">> L'employ� est pr�sent dans le bottin.\n" :
            cout << ">> L'employ� n'est pas pr�sent dans le bottin.\n";
      cout << endl << endl;


      // Test de recherche apr�s suppression
      //
      Employe n3 = bottin.trouverAvecNomPrenom("Henderson, Patricia", nbCollisions);
      cout << "Recherche de " << n3.nom << ", " << n3.prenom << endl;
      cout << "------------------------------------------------" << endl;
      cout << bottin.infosEmploye(n3) << endl;
      cout << "Le nombre de collisions rencontr�es = " << nbCollisions << endl;
      cout << endl << endl;


      // Test pour vider le bottin
      //
      bottin.rendreVide();

      // V�rification pour le bottin vide
      //
      cout << "V�rification que le bottin est vide :" << endl;
      bottin.contient("Henderson, Patricia") ?
            cout << ">> L'employ� est pr�sent dans le bottin.\n" :
            cout << ">> L'employ� n'est pas pr�sent dans le bottin.\n";
      bottin.contient("Zepeda, Manuel") ?
            cout << ">> L'employ� est pr�sent dans le bottin.\n" :
            cout << ">> L'employ� n'est pas pr�sent dans le bottin.\n";


   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

    return 0;
}
