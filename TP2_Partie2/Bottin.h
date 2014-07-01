/**
 * \file Bottin.h
 * \brief Classe définissant un bottin téléphonique.
 * \author Mathieu L'Écuyer, Éric Guillemette
 * \version 0.1
 * \date juillet 2014
 */

#ifndef BOTTIN__H
#define BOTTIN__H

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <fstream>#include <string>
#include <sstream>#include <vector>

/**
 * \namespace TP2P2
 *
 * Espace de nommage regroupant les définitions du TP2, deuxième partie.
 */
namespace TP2P2
{

/**
 * \struct Personne
 * \brief Structure pour définir une personne présente dans le bottin téléphonique.
 */
typedef struct Personne {
  std::string nom;            /*!< Le nom de la personne */
  std::string prenom;         /*!< Le prénom de la personne */
  std::string tel;            /*!< Le numéro de téléphone de la personne */
  std::string fax;            /*!< Le numéro de fax de la personne */
  std::string courriel;       /*!< L'adresse courriel de la personne */
} Employe;

/**
 * \class Bottin
 *
 * \brief Classe représentant un bottin téléphonique.
 *
 * La recherche dans le bottin se fait à l'aide de deux tables de dispersions, l'une avec une clé
 * correspondant au numéro de téléphone de la personne, l'autre avec une clé correspondant au
 * Nom/Prénom de la personne.
 *
 * Les collisions des deux tables sont gérées par adressage ouvert avec redispersion quadratique.
 */
class Bottin
{
public:

   /**
    * \brief Constructeur par défaut.
    *
    * \post Une instance de la classe Bottin est initialisée.
    */
   Bottin(int taille = 101);

   Bottin(std::istream &fichier, int &nbCollisions);

   ~Bottin();

   void rendreVide();

   bool contient(const std::string & s);

   void ajouter(const std::string & nom, const std::string & prenom, const std::string & tel,
                const std::string & fax, const std::string & courriel);

   void supprimer(const std::string & s);

   int getCollisionsTel() const;

   int getCollisionsNom() const;

   Employe trouverAvecNomPrenom(const std::string & s, int &nbCollisions);

   Employe trouverAvecTelephone(const std::string & s, int &nbCollisions);

   std::string infosEmploye(const Employe& e) const;

private:
   /**
    * \enum TypeEntree
    * \brief Les tags pour définir l'état d'une entrée dans la table.
    */
   enum TypeEntree
   {
      ACTIVE, /*!< l'entrée est occupée */
      VIDE, /*!< l'entrée est vide */
      SUPPRIMEE /*!< l'entrée a été supprimée */
   };

   /**
    * \class Entree
    *
    * \brief classe représentant une entrée du bottin
    *
    */
   class Entree
   {
   public:
      std::string nom;
      std::string prenom;
      std::string tel;
      std::string fax;
      std::string courriel;

      Entree(const std::string & n, const std::string & p, const std::string & t,
             const std::string & f, const std::string & c) :
             nom(n), prenom(p), tel(t), fax(f), courriel(c) {}
   };

   class HashEntree
   {
   public:
      std::string clef; /*!< la clé de hachage */
      int position; /*!< la valeur associée à la clé */
      TypeEntree info; /*!< tag pour préciser l'état de l'entrée (vide, active ou supprimée) */

      // Constructeur par défaut pour permettre d'initialiser le tableau à une certaine grandeur.
      HashEntree() : position(0), info(VIDE) {}

      HashEntree(const std::string & c, const int & p, TypeEntree i = VIDE) :
                 clef(c), position(p), info(i) {}
   };

   std::vector<Entree> tabEntree; // Le tableau des entrées

   std::vector<HashEntree> tabTelephone; // Table de dispersion sur la clé téléphone

   std::vector<HashEntree> tabNomPrenom; // Table de dispersion sur la clé Nom/Prénom

   int collisionsTel; /*!< le nombre de collisions à l'insertion dans tabTelephone */

   int collisionsNom; /*!< le nombre de collisions à l'insertion dans tabNomPrenom */

   unsigned int tailleTel;  /*!< le nombre d'éléments courant dans tabTelephone */

   unsigned int tailleNom;  /*!< le nombre d'éléments courant dans tabTelephone */

   static const int TAUX_MAX = 50;  /*!< 50% : taux de remplissage maximum dans la table */


   // Méthodes privées.

   std::string _creerClef(const std::string & s);

   bool _estActive(const std::string & clef, int positionCourante) const;

   void _inserer(const std::string & s, const int & pos);

   int _trouverPosition(const std::string & clef);

   void _rehash();

   bool _premier(int n);

   int _premierSuivant(int n);

};

} //Fin du namespace

#endif /* BOTTIN__H */
