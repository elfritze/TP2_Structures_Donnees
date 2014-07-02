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

/*! \typedef Employe
 *  \struct Personne
 *  \brief Structure pour définir une personne présente dans le bottin téléphonique.
 */
typedef struct Personne {
  std::string nom;         /*!< Le nom de la personne. */
  std::string prenom;      /*!< Le prénom de la personne. */
  std::string tel;         /*!< Le numéro de téléphone de la personne. */
  std::string fax;         /*!< Le numéro de fax de la personne. */
  std::string courriel;    /*!< L'adresse courriel de la personne. */
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
    * Prépare deux tables de dispersions vides de taille 101 multiplié par 1.3 par défaut.
    * Sinon, peut être utilisé avec un argument explicite. Dans ce cas, le constructeur doit
    * préparer deux tables vides de taille égale au prochain nombre premier qui suit la valeur
    * de l'argument multiplié par 1.3.
    *
    * \post Une instance de la classe Bottin est initialisée.
    */
   Bottin(int taille = 101);

   /**
    * \brief Constructeur avec arguments.
    *
    * Ce constructeur s'occupe de charger le bottin à partir d'un fichier en entrée.
    * Il retourne également le nombre de collisions total rencontrées dans les deux tables de
    * dispersions à travers nbCollisions.
    *
    * \post Une instance de la classe Bottin est initialisée.
    */
   Bottin(std::istream &fichier, int &nbCollisions);

   /**
    * \brief Destructeur.
    *
    * \post L'instance de Bottin est détruite.
    */
   ~Bottin() {};

   /**
    * \brief Cette méthode permet de vider les deux tables de dispersions.
    *
    * \post Les deux tables de dispersions sont vides.
    */
   void rendreVide();

   /**
    * \brief Cette méthode permet de rechercher un employé à partir d'une clé.
    *
    * \post VRAI est retourné si l'employé est présent, FAUX sinon.
    */
   bool contient(const std::string & c);

   /**
    * \brief Cette méthode permet d'ajouter un employé dans le bottin.
    *
    * \pre L'employé n'est pas déjà présent dans le bottin.
    *
    * \post L'employé est ajouté dans le tableau des entrées et dans les deux tables de dispersions,
    *       avec pour clés le numéro de téléphone et le Nom/Prénom.
    *
    * \exception logic_error : si l'employé est déjà présent dans le bottin (doublon).
    */
   void ajouter(const std::string & nom, const std::string & prenom, const std::string & tel,
                const std::string & fax, const std::string & courriel);

   /**
    * \brief Cette méthode permet de supprimer un employé du bottin.
    *
    * \pre L'employé doit être présent dans le bottin.
    *
    * \post L'employé est supprimé des deux tables de dispersions.
    *
    * \exception logic_error : si l'employé n'est pas présent dans le bottin.
    */
   void supprimer(const std::string & c);

   /**
    * \brief Cette méthode retourne le nombre de collisions rencontrées dans la table de
    *        dispersion tabTelephone.
    *
    * \post Le nombre de collisions est retourné.
    */
   int getCollisionsTel() const;

   /**
    * \brief Cette méthode retourne le nombre de collisions rencontrées dans la table de
    *        dispersion tabNomPrenom.
    *
    * \post Le nombre de collisions est retourné.
    */
   int getCollisionsNom() const;

   /**
    * \brief Cette méthode permet de rechercher un employé avec une paire Nom/Prénom.
    *
    * \pre L'employé doit être présent dans le bottin.
    *
    * \post L'employé recherché, ainsi que ces informations, est retourné.
    *
    * \exception logic_error : si l'employé n'est pas présent dans le bottin.
    */
   Employe trouverAvecNomPrenom(const std::string & c, int &nbCollisions);

   /**
    * \brief Cette méthode permet de rechercher un employé avec un numéro de téléphone.
    *
    * \pre L'employé doit être présent dans le bottin.
    *
    * \post L'employé recherché, ainsi que ces informations, est retourné.
    *
    * \exception logic_error : si l'employé n'est pas présent dans le bottin.
    */
   Employe trouverAvecTelephone(const std::string & c, int &nbCollisions);

   /**
    * \brief Cette méthode retourne les informations d'un employé.
    *
    * \post Les informations de l'employé sont retournées dans une chaîne de caractères.
    */
   std::string infosEmploye(const Employe& e) const;


private:

   /**
    * \enum TypeEntree
    * \brief Les étiquettes pour définir l'état d'une entrée dans la table.
    */
   enum TypeEntree
   {
      ACTIVE,     /*!< L'entrée est occupée. */
      VIDE,       /*!< L'entrée est vide. */
      SUPPRIMEE   /*!< L'entrée a été supprimée. */
   };

   /**
    * \class Entree
    *
    * \brief Classe interne pour représenter une entrée du bottin.
    */
   class Entree
   {
   public:
      std::string nom;        /*!< Le nom de la personne. */
      std::string prenom;     /*!< Le prénom de la personne. */
      std::string tel;        /*!< Le numéro de téléphone de la personne. */
      std::string fax;        /*!< Le numéro de fax de la personne. */
      std::string courriel;   /*!< L'adresse courriel de la personne. */

      /**
       * \brief Constructeur avec arguments pour initialiser les membres de la classe.
       *
       * \post Une instance de la classe Entree est initialisée.
       */
      Entree(const std::string & n, const std::string & p, const std::string & t,
             const std::string & f, const std::string & c) :
             nom(n), prenom(p), tel(t), fax(f), courriel(c) {}
   };

   /**
    * \class HashEntree
    *
    * \brief Classe interne pour représenter une entrée dans les tables de dispersions.
    */
   class HashEntree
   {
   public:
      std::string clef; /*!< La clé de hachage. */
      int position;     /*!< La position de tabEntree associée à la clé. */
      TypeEntree info;  /*!< Étiquette de l'état de l'entrée (active, vide ou supprimée). */

      /**
       * \brief Constructeur par défaut pour permettre d'initialiser la table à une certaine grandeur.
       *
       * \post Une instance de la classe HashEntree est initialisée.
       */
      HashEntree() : position(0), info(VIDE) {}

      /**
       * \brief Constructeur avec arguments pour initialiser les membres de la classe.
       *
       * \post Une instance de la classe HashEntree est initialisée.
       */
      HashEntree(const std::string & c, const int & p, TypeEntree i = VIDE) :
                 clef(c), position(p), info(i) {}
   };


   // Attributs de la classe Bottin

   std::vector<Entree> tabEntree;         /*!< Le tableau des entrées. */

   std::vector<HashEntree> tabTelephone;  /*!< Table de dispersion sur la clé téléphone. */
   std::vector<HashEntree> tabNomPrenom;  /*!< Table de dispersion sur la clé Nom/Prénom. */

   int collisionsTel;       /*!< Le nombre de collisions à l'insertion dans tabTelephone. */
   int collisionsNom;       /*!< Le nombre de collisions à l'insertion dans tabNomPrenom. */

   unsigned int tailleTel;  /*!< Le nombre d'éléments courant dans tabTelephone. */
   unsigned int tailleNom;  /*!< Le nombre d'éléments courant dans tabNomPrenom. */

   static const int TAUX_MAX = 50;  /*!< 50% : taux de remplissage maximum dans la table. */


   // Méthodes privées

   /**
    * \brief Cette méthode permet de créer une clé en supprimant les caractères qui ne sont pas
    *        des chiffres ou des lettres.
    */
   std::string _creerClef(const std::string & c);

   /**
    * \brief Cette méthode vérifie si une position est active (occupée).
    *
    * \post VRAI est retourné si la position est active, FAUX sinon.
    */
   bool _estActive(const std::string & clef, int positionCourante) const;

   /**
    * \brief Cette méthode insère une paire (clé, valeur) dans la table de dispersion.
    *
    * Une redispersion quadratique est utilisée en cas de collision.
    * La méthode fait appel à la méthode privée _trouverPosition() pour localiser
    * une place vacante dans la table de dispersion.
    *
    * Si après une insertion le taux de remplissage atteint le maximum, on double la taille
    * de la table de dispersion en appelant la méthode privée _rehash().
    *
    * \pre La clé à insérer n'est pas déjà présente dans la table.
    *
    * \post La paire (clé, valeur) est insérée dans la table de dispersion.
    *
    * \exception logic_error : si la clé est déjà présente dans la table.
    */
   void _inserer(const std::string & c, const int & pos);

   /**
    * \brief Cette méthode permet de trouver la position d'une clé dans la table de dispersion.
    *
    * Cette méthode est utilisée par les méthodes qui font l'insertion, la recherche et
    * la suppression.
    */
   int _trouverPosition(const std::string & clef);

   /**
    * \brief Cette méthode permet de redimensionner la capacité des tables de dispersions.
    *
    * Cette méthode peut être appelée par _inserer(). Si, après une insertion, le taux de
    * remplissage atteint le maximum, cette méthode augmente la taille des tables de dispersions.
    */
   void _rehash();

   /**
    * \brief Cette méthode permet de vérifier si un nombre est premier.
    *
    * On assume que le nombre est plus grand que 0.
    */
   bool _premier(int n);

   /**
    * \brief Cette méthode permet de chercher le prochain nombre premier après le nombre n.
    *
    * On assume que le nombre est plus grand que 0.
    */
   int _premierSuivant(int n);
};

} //Fin du namespace

#endif /* BOTTIN__H */
