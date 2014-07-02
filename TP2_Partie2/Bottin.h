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

/*! \typedef Employe
 *  \struct Personne
 *  \brief Structure pour d�finir une personne pr�sente dans le bottin t�l�phonique.
 */
typedef struct Personne {
  std::string nom;         /*!< Le nom de la personne. */
  std::string prenom;      /*!< Le pr�nom de la personne. */
  std::string tel;         /*!< Le num�ro de t�l�phone de la personne. */
  std::string fax;         /*!< Le num�ro de fax de la personne. */
  std::string courriel;    /*!< L'adresse courriel de la personne. */
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
    * Pr�pare deux tables de dispersions vides de taille 101 multipli� par 1.3 par d�faut.
    * Sinon, peut �tre utilis� avec un argument explicite. Dans ce cas, le constructeur doit
    * pr�parer deux tables vides de taille �gale au prochain nombre premier qui suit la valeur
    * de l'argument multipli� par 1.3.
    *
    * \post Une instance de la classe Bottin est initialis�e.
    */
   Bottin(int taille = 101);

   /**
    * \brief Constructeur avec arguments.
    *
    * Ce constructeur s'occupe de charger le bottin � partir d'un fichier en entr�e.
    * Il retourne �galement le nombre de collisions total rencontr�es dans les deux tables de
    * dispersions � travers nbCollisions.
    *
    * \post Une instance de la classe Bottin est initialis�e.
    */
   Bottin(std::istream &fichier, int &nbCollisions);

   /**
    * \brief Destructeur.
    *
    * \post L'instance de Bottin est d�truite.
    */
   ~Bottin() {};

   /**
    * \brief Cette m�thode permet de vider les deux tables de dispersions.
    *
    * \post Les deux tables de dispersions sont vides.
    */
   void rendreVide();

   /**
    * \brief Cette m�thode permet de rechercher un employ� � partir d'une cl�.
    *
    * \post VRAI est retourn� si l'employ� est pr�sent, FAUX sinon.
    */
   bool contient(const std::string & c);

   /**
    * \brief Cette m�thode permet d'ajouter un employ� dans le bottin.
    *
    * \pre L'employ� n'est pas d�j� pr�sent dans le bottin.
    *
    * \post L'employ� est ajout� dans le tableau des entr�es et dans les deux tables de dispersions,
    *       avec pour cl�s le num�ro de t�l�phone et le Nom/Pr�nom.
    *
    * \exception logic_error : si l'employ� est d�j� pr�sent dans le bottin (doublon).
    */
   void ajouter(const std::string & nom, const std::string & prenom, const std::string & tel,
                const std::string & fax, const std::string & courriel);

   /**
    * \brief Cette m�thode permet de supprimer un employ� du bottin.
    *
    * \pre L'employ� doit �tre pr�sent dans le bottin.
    *
    * \post L'employ� est supprim� des deux tables de dispersions.
    *
    * \exception logic_error : si l'employ� n'est pas pr�sent dans le bottin.
    */
   void supprimer(const std::string & c);

   /**
    * \brief Cette m�thode retourne le nombre de collisions rencontr�es dans la table de
    *        dispersion tabTelephone.
    *
    * \post Le nombre de collisions est retourn�.
    */
   int getCollisionsTel() const;

   /**
    * \brief Cette m�thode retourne le nombre de collisions rencontr�es dans la table de
    *        dispersion tabNomPrenom.
    *
    * \post Le nombre de collisions est retourn�.
    */
   int getCollisionsNom() const;

   /**
    * \brief Cette m�thode permet de rechercher un employ� avec une paire Nom/Pr�nom.
    *
    * \pre L'employ� doit �tre pr�sent dans le bottin.
    *
    * \post L'employ� recherch�, ainsi que ces informations, est retourn�.
    *
    * \exception logic_error : si l'employ� n'est pas pr�sent dans le bottin.
    */
   Employe trouverAvecNomPrenom(const std::string & c, int &nbCollisions);

   /**
    * \brief Cette m�thode permet de rechercher un employ� avec un num�ro de t�l�phone.
    *
    * \pre L'employ� doit �tre pr�sent dans le bottin.
    *
    * \post L'employ� recherch�, ainsi que ces informations, est retourn�.
    *
    * \exception logic_error : si l'employ� n'est pas pr�sent dans le bottin.
    */
   Employe trouverAvecTelephone(const std::string & c, int &nbCollisions);

   /**
    * \brief Cette m�thode retourne les informations d'un employ�.
    *
    * \post Les informations de l'employ� sont retourn�es dans une cha�ne de caract�res.
    */
   std::string infosEmploye(const Employe& e) const;


private:

   /**
    * \enum TypeEntree
    * \brief Les �tiquettes pour d�finir l'�tat d'une entr�e dans la table.
    */
   enum TypeEntree
   {
      ACTIVE,     /*!< L'entr�e est occup�e. */
      VIDE,       /*!< L'entr�e est vide. */
      SUPPRIMEE   /*!< L'entr�e a �t� supprim�e. */
   };

   /**
    * \class Entree
    *
    * \brief Classe interne pour repr�senter une entr�e du bottin.
    */
   class Entree
   {
   public:
      std::string nom;        /*!< Le nom de la personne. */
      std::string prenom;     /*!< Le pr�nom de la personne. */
      std::string tel;        /*!< Le num�ro de t�l�phone de la personne. */
      std::string fax;        /*!< Le num�ro de fax de la personne. */
      std::string courriel;   /*!< L'adresse courriel de la personne. */

      /**
       * \brief Constructeur avec arguments pour initialiser les membres de la classe.
       *
       * \post Une instance de la classe Entree est initialis�e.
       */
      Entree(const std::string & n, const std::string & p, const std::string & t,
             const std::string & f, const std::string & c) :
             nom(n), prenom(p), tel(t), fax(f), courriel(c) {}
   };

   /**
    * \class HashEntree
    *
    * \brief Classe interne pour repr�senter une entr�e dans les tables de dispersions.
    */
   class HashEntree
   {
   public:
      std::string clef; /*!< La cl� de hachage. */
      int position;     /*!< La position de tabEntree associ�e � la cl�. */
      TypeEntree info;  /*!< �tiquette de l'�tat de l'entr�e (active, vide ou supprim�e). */

      /**
       * \brief Constructeur par d�faut pour permettre d'initialiser la table � une certaine grandeur.
       *
       * \post Une instance de la classe HashEntree est initialis�e.
       */
      HashEntree() : position(0), info(VIDE) {}

      /**
       * \brief Constructeur avec arguments pour initialiser les membres de la classe.
       *
       * \post Une instance de la classe HashEntree est initialis�e.
       */
      HashEntree(const std::string & c, const int & p, TypeEntree i = VIDE) :
                 clef(c), position(p), info(i) {}
   };


   // Attributs de la classe Bottin

   std::vector<Entree> tabEntree;         /*!< Le tableau des entr�es. */

   std::vector<HashEntree> tabTelephone;  /*!< Table de dispersion sur la cl� t�l�phone. */
   std::vector<HashEntree> tabNomPrenom;  /*!< Table de dispersion sur la cl� Nom/Pr�nom. */

   int collisionsTel;       /*!< Le nombre de collisions � l'insertion dans tabTelephone. */
   int collisionsNom;       /*!< Le nombre de collisions � l'insertion dans tabNomPrenom. */

   unsigned int tailleTel;  /*!< Le nombre d'�l�ments courant dans tabTelephone. */
   unsigned int tailleNom;  /*!< Le nombre d'�l�ments courant dans tabNomPrenom. */

   static const int TAUX_MAX = 50;  /*!< 50% : taux de remplissage maximum dans la table. */


   // M�thodes priv�es

   /**
    * \brief Cette m�thode permet de cr�er une cl� en supprimant les caract�res qui ne sont pas
    *        des chiffres ou des lettres.
    */
   std::string _creerClef(const std::string & c);

   /**
    * \brief Cette m�thode v�rifie si une position est active (occup�e).
    *
    * \post VRAI est retourn� si la position est active, FAUX sinon.
    */
   bool _estActive(const std::string & clef, int positionCourante) const;

   /**
    * \brief Cette m�thode ins�re une paire (cl�, valeur) dans la table de dispersion.
    *
    * Une redispersion quadratique est utilis�e en cas de collision.
    * La m�thode fait appel � la m�thode priv�e _trouverPosition() pour localiser
    * une place vacante dans la table de dispersion.
    *
    * Si apr�s une insertion le taux de remplissage atteint le maximum, on double la taille
    * de la table de dispersion en appelant la m�thode priv�e _rehash().
    *
    * \pre La cl� � ins�rer n'est pas d�j� pr�sente dans la table.
    *
    * \post La paire (cl�, valeur) est ins�r�e dans la table de dispersion.
    *
    * \exception logic_error : si la cl� est d�j� pr�sente dans la table.
    */
   void _inserer(const std::string & c, const int & pos);

   /**
    * \brief Cette m�thode permet de trouver la position d'une cl� dans la table de dispersion.
    *
    * Cette m�thode est utilis�e par les m�thodes qui font l'insertion, la recherche et
    * la suppression.
    */
   int _trouverPosition(const std::string & clef);

   /**
    * \brief Cette m�thode permet de redimensionner la capacit� des tables de dispersions.
    *
    * Cette m�thode peut �tre appel�e par _inserer(). Si, apr�s une insertion, le taux de
    * remplissage atteint le maximum, cette m�thode augmente la taille des tables de dispersions.
    */
   void _rehash();

   /**
    * \brief Cette m�thode permet de v�rifier si un nombre est premier.
    *
    * On assume que le nombre est plus grand que 0.
    */
   bool _premier(int n);

   /**
    * \brief Cette m�thode permet de chercher le prochain nombre premier apr�s le nombre n.
    *
    * On assume que le nombre est plus grand que 0.
    */
   int _premierSuivant(int n);
};

} //Fin du namespace

#endif /* BOTTIN__H */
