/**
 * \file Bottin.h
 * \brief Classe d�finissant un bottin t�l�phonique.
 * \author Mathieu L'�cuyer, �ric Guillemette
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
 * Espace de nommage regroupant les d�finitions du TP2, deuxi�me partie.
 */
namespace TP2P2
{

/**
 * \struct Personne
 * \brief Structure pour d�finir une personne pr�sente dans le bottin t�l�phonique.
 */
typedef struct Personne {
  std::string nom;            /*!< Le nom de la personne */
  std::string prenom;         /*!< Le pr�nom de la personne */
  std::string tel;            /*!< Le num�ro de t�l�phone de la personne */
  std::string fax;            /*!< Le num�ro de fax de la personne */
  std::string courriel;       /*!< L'adresse courriel de la personne */
} Employe;

/**
 * \class Bottin
 *
 * \brief Classe repr�sentant un bottin t�l�phonique.
 *
 * La recherche dans le bottin se fait � l'aide de deux tables de dispersions, l'une avec une cl�
 * correspondant au num�ro de t�l�phone de la personne, l'autre avec une cl� correspondant au
 * Nom/Pr�nom de la personne.
 *
 * Les collisions des deux tables sont g�r�es par adressage ouvert avec redispersion quadratique.
 */
class Bottin
{
public:

   /**
    * \brief Constructeur par d�faut.
    *
    * \post Une instance de la classe Bottin est initialis�e.
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
    * \brief Les tags pour d�finir l'�tat d'une entr�e dans la table.
    */
   enum TypeEntree
   {
      ACTIVE, /*!< l'entr�e est occup�e */
      VIDE, /*!< l'entr�e est vide */
      SUPPRIMEE /*!< l'entr�e a �t� supprim�e */
   };

   /**
    * \class Entree
    *
    * \brief classe repr�sentant une entr�e du bottin
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
      std::string clef; /*!< la cl� de hachage */
      int position; /*!< la valeur associ�e � la cl� */
      TypeEntree info; /*!< tag pour pr�ciser l'�tat de l'entr�e (vide, active ou supprim�e) */

      // Constructeur par d�faut pour permettre d'initialiser le tableau � une certaine grandeur.
      HashEntree() : position(0), info(VIDE) {}

      HashEntree(const std::string & c, const int & p, TypeEntree i = VIDE) :
                 clef(c), position(p), info(i) {}
   };

   std::vector<Entree> tabEntree; // Le tableau des entr�es

   std::vector<HashEntree> tabTelephone; // Table de dispersion sur la cl� t�l�phone

   std::vector<HashEntree> tabNomPrenom; // Table de dispersion sur la cl� Nom/Pr�nom

   int collisionsTel; /*!< le nombre de collisions � l'insertion dans tabTelephone */

   int collisionsNom; /*!< le nombre de collisions � l'insertion dans tabNomPrenom */

   unsigned int tailleTel;  /*!< le nombre d'�l�ments courant dans tabTelephone */

   unsigned int tailleNom;  /*!< le nombre d'�l�ments courant dans tabTelephone */

   static const int TAUX_MAX = 50;  /*!< 50% : taux de remplissage maximum dans la table */


   // M�thodes priv�es.

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
