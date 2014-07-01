/**
 * \file Bottin.cpp
 * \brief Le code des opérateurs du bottin téléphonique
 * \author Mathieu L'Écuyer, Éric Guillemette
 * \version 0.1
 * \date juillet 2014
 */

#include "Bottin.h"

using namespace std;

namespace TP2P2
{

Bottin::Bottin(int taille) :
      tabTelephone(_premierSuivant(taille * 1.3)), tabNomPrenom(_premierSuivant(taille * 1.3)),
      collisionsTel(0), collisionsNom(0)
{
   rendreVide();
}

Bottin::Bottin(std::istream &fichier, int &nbCollisions) :
      collisionsTel(nbCollisions), collisionsNom(nbCollisions)
{
   // variables
   int nbPersonnes;
   string nom, prenom, tel, fax, courriel, clefTelephone, clefNomPrenom;

   // on récupère le nombre de personnes dans le fichier texte
   fichier >> nbPersonnes;
   fichier.ignore();

   // on initialise les deux tables de dispersions
   // la taille des tables correspond au nombre premier après le nombre d'employés chargés à
   // partir du fichier, multiplié par 1.30
   tabTelephone.resize(_premierSuivant(nbPersonnes * 1.3));
   tabNomPrenom.resize(_premierSuivant(nbPersonnes * 1.3));
   rendreVide();

   // on récupère les infos des employés pour les stocker dans le tableau des entrées
   // et pour créer les deux tables de dispersions
   for (int i = 0; i < nbPersonnes; i++)
   {
      getline(fichier, nom, ',');
      fichier.ignore();
      getline(fichier, prenom, '\t');
      getline(fichier, tel, '\t');
      getline(fichier, fax, '\t');
      getline(fichier, courriel);

      // ajout dans le tableau des entrées
      tabEntree.push_back(Entree(nom, prenom, tel, fax, courriel));

      // insertion dans les deux tables de dispersions
      _inserer(tel, i);
      _inserer((nom + prenom), i);
   }

   nbCollisions = collisionsTel + collisionsNom;
}

Bottin::~Bottin()
{

}

void Bottin::rendreVide()
{
   tailleTel = 0;
   tailleNom = 0;

   // Pour la table de dispersion avec la clé Téléphone
   for (unsigned int i = 0; i < tabTelephone.size(); i++)
      tabTelephone[i].info = VIDE;

   // Pour la table de dispersion avec la clé Nom/Prénom
   for (unsigned int i = 0; i < tabNomPrenom.size(); i++)
      tabNomPrenom[i].info = VIDE;
}

bool Bottin::contient(const std::string & s)
{
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   string clef = _creerClef(s);
   int positionCourante = _trouverPosition(clef);

   // on conserve le nombre de collisions avant l'appel de la fonction
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;

   return _estActive(clef, positionCourante);
}

void Bottin::ajouter(const std::string & nom, const std::string & prenom, const std::string & tel,
                     const std::string & fax, const std::string & courriel)
{
   // la personne ne doit pas être présente dans la table
   if (contient(tel) || contient(nom + prenom))
      throw std::logic_error ("ajouter: l'entrée est déjà présente dans la table.");

   // ajout dans le tableau des entrées
   tabEntree.push_back(Entree(nom, prenom, tel, fax, courriel));

   // insertion dans les tables de dispersions
   // la position du tableau des entrées = tabEntree.size() - 1
   int position = tabEntree.size() - 1;
   _inserer(tel, position);
   _inserer((nom + prenom), position);
}

void Bottin::supprimer(const std::string & s)
{
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   string clef = _creerClef(s);
   int positionCourante = _trouverPosition(clef);

   if (!_estActive(clef, positionCourante))
      throw std::logic_error ("supprimer: l'entrée n'est pas présente dans la table.\n");

   if (isdigit(clef[0]))
   {
      tabTelephone[positionCourante].info = SUPPRIMEE;
   }
   else
   {
      tabNomPrenom[positionCourante].info = SUPPRIMEE;
   }

   // on conserve le nombre de collisions avant l'appel de la fonction
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;
}

int Bottin::getCollisionsTel() const
{
   return collisionsTel;
}

int Bottin::getCollisionsNom() const
{
   return collisionsNom;
}

Employe Bottin::trouverAvecNomPrenom(const std::string & s, int &nbCollisions)
{
   int collisionEmploye = collisionsNom;

   string clef = _creerClef(s);
   int positionCourante = _trouverPosition(clef);

   nbCollisions = collisionsNom - collisionEmploye;

   if (!_estActive(clef, positionCourante))
         throw std::logic_error ("trouverAvecNomPrenom: l'entrée n'est pas présente dans la table.\n");

   int positionEntree = tabNomPrenom[positionCourante].position;

   // Récupération des infos de l'employé
   Employe e;
   e.nom = tabEntree[positionEntree].nom;
   e.prenom = tabEntree[positionEntree].prenom;
   e.tel = tabEntree[positionEntree].tel;
   e.fax = tabEntree[positionEntree].fax;
   e.courriel = tabEntree[positionEntree].courriel;

   return e;
}

Employe Bottin::trouverAvecTelephone(const std::string & s, int &nbCollisions)
{
   int collisionEmploye = collisionsTel;

   string clef = _creerClef(s);
   int positionCourante = _trouverPosition(clef);

   nbCollisions = collisionsTel - collisionEmploye;

   if (!_estActive(clef, positionCourante))
         throw std::logic_error ("trouverAvecTelephone: l'entrée n'est pas présente dans la table.\n");

   int positionEntree = tabTelephone[positionCourante].position;

   // Récupération des infos de l'employé
   Employe e;
   e.nom = tabEntree[positionEntree].nom;
   e.prenom = tabEntree[positionEntree].prenom;
   e.tel = tabEntree[positionEntree].tel;
   e.fax = tabEntree[positionEntree].fax;
   e.courriel = tabEntree[positionEntree].courriel;

   return e;
}

string Personne::infos() const
{
     ostringstream infos;

     infos << "Nom       : " << nom << "\n";
     infos << "Prénom    : " << prenom << "\n";
     infos << "Téléphone : " << tel << "\n";
     infos << "Fax       : " << fax << "\n";
     infos << "Courriel  : " << courriel << "\n";

     return infos.str();
}

// Méthodes privées

std::string Bottin::_creerClef(const std::string & s)
{
   string clef;

   // on ne garde que les chiffres et les lettres
   for (unsigned int i = 0; i < s.size(); i++)
   {
      if (isdigit(s[i]) || isalpha(s[i]))
      {
         clef += s[i];
      }
   }

   return clef;
}

bool Bottin::_estActive(const std::string & clef, int positionCourante) const
{
   if (isdigit(clef[0]))
   {
      return tabTelephone[positionCourante].info == ACTIVE;
   }
   else
   {
      return tabNomPrenom[positionCourante].info == ACTIVE;
   }
}

void Bottin::_inserer(const std::string & s, const int & pos)
{
   string clef = _creerClef(s);
   int positionCourante = _trouverPosition(clef);

   if (_estActive(clef, positionCourante))
      throw std::logic_error ("inserer: l'entrée est déjà présente dans la table.\n");

   if (isdigit(clef[0]))
   {
      tabTelephone[positionCourante] = HashEntree(clef, pos, ACTIVE);

      if ((++tailleTel/float(tabTelephone.size()))*100 > TAUX_MAX)
         _rehash();
   }
   else
   {
      tabNomPrenom[positionCourante] = HashEntree(clef, pos, ACTIVE);

      if ((++tailleNom/float(tabNomPrenom.size()))*100 > TAUX_MAX)
         _rehash();
   }
}

int Bottin::_trouverPosition(const std::string & clef)
{
   unsigned long positionCourante = 0;
   int offset = 1;

   if (isdigit(clef[0]))
   {
      for (unsigned int i = 0; i < clef.length(); i++)
         positionCourante = 37 * positionCourante + clef[i];

      positionCourante %= tabTelephone.size();

      if (positionCourante < 0)
         positionCourante += tabTelephone.size();

      while (tabTelephone[positionCourante].info != VIDE &&
             tabTelephone[positionCourante].clef != clef)
      {
         collisionsTel++;
         positionCourante += offset;  // Calcule le i-ième sondage
         offset += 2;
         if (positionCourante >= tabTelephone.size())
             positionCourante -= tabTelephone.size();
      }
   }
   else
   {
      for (unsigned int i = 0; i < clef.length(); i++)
         positionCourante = 37 * positionCourante + clef[i];

      positionCourante %= tabNomPrenom.size();

      if (positionCourante < 0)
         positionCourante += tabNomPrenom.size();

      while (tabNomPrenom[positionCourante].info != VIDE &&
             tabNomPrenom[positionCourante].clef != clef)
      {
         collisionsNom++;
         positionCourante += offset;  // Calcule le i-ième sondage
         offset += 2;
         if (positionCourante >= tabNomPrenom.size())
             positionCourante -= tabNomPrenom.size();
      }
   }

   return positionCourante;
}

void Bottin::_rehash()
{
   vector<HashEntree> oldTabTelephone = tabTelephone;
   vector<HashEntree> oldTabNomPrenom = tabNomPrenom;
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   // Création de nouvelles tables 2 fois plus grandes
   tabTelephone.resize(_premierSuivant(2 * oldTabTelephone.size()));
   for (unsigned int j = 0; j < tabTelephone.size(); j++)
   {
      tabTelephone[j].info = VIDE;
   }
   tabNomPrenom.resize(_premierSuivant(2 * oldTabNomPrenom.size()));
   for (unsigned int j = 0; j < tabNomPrenom.size(); j++)
   {
      tabNomPrenom[j].info = VIDE;
   }

   // Copie des tables
   tailleTel = 0;
   tailleNom = 0;
   for (unsigned int i = 0; i < oldTabTelephone.size(); i++)
   {
      if (oldTabTelephone[i].info == ACTIVE)
         _inserer(oldTabTelephone[i].clef, oldTabTelephone[i].position);
   }
   for (unsigned int i = 0; i < oldTabNomPrenom.size(); i++)
   {
      if (oldTabNomPrenom[i].info == ACTIVE)
         _inserer(oldTabNomPrenom[i].clef, oldTabNomPrenom[i].position);
   }

   // on conserve le nombre de collisions avant l'appel de la fonction
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;
}

bool Bottin::_premier(int n)
{
   if (n <= 1)
      return false;

   if (n == 2)              // le seul nombre premier pair
      return true;

   else if (n % 2 == 0)     // sinon, ce n'est pas un nombre premier
      return false;

   else
   {
      int divisor = 3;
      int upperLimit = static_cast<int>(sqrt((float) n) + 1);

      while (divisor <= upperLimit)
      {
         if (n % divisor == 0)
            return false;
         divisor += 2;
      }

      return true;
   }
}

int Bottin::_premierSuivant(int n)
{
   if (n % 2 == 0)
      n++;

   while (!_premier(n))
      n += 2;

   return n;
}

} //Fin du namespace
