/**
 * \file Bottin.cpp
 * \brief Le code des op�rateurs du bottin t�l�phonique
 * \author Mathieu L'�cuyer, �ric Guillemette
 * \version 0.1
 * \date juillet 2014
 */

#include "Bottin.h"
using namespace std;

/**
 * \namespace TP2P2
 *
 * Espace de nommage regroupant les d�finitions du TP2, deuxi�me partie.
 */
namespace TP2P2
{

/**
 * \fn Bottin::Bottin(int taille)
 *
 * \param[in] taille : la taille des tables de dispersions.
 */
Bottin::Bottin(int taille) :
      tabTelephone(_premierSuivant(taille * 1.3)), tabNomPrenom(_premierSuivant(taille * 1.3)),
      collisionsTel(0), collisionsNom(0)
{
   rendreVide();
}

/**
 * \fn Bottin::Bottin(std::istream &fichier, int &nbCollisions)
 *
 * \param[in] fichier : un flux d'entr�e contenant un fichier texte.
 * \param[in] nbCollisions : un entier pour retourner le nombre total de collisions rencontr�es.
 */
Bottin::Bottin(std::istream &fichier, int &nbCollisions) :
      collisionsTel(nbCollisions), collisionsNom(nbCollisions)
{
   // variables
   int nbPersonnes;
   string nom, prenom, tel, fax, courriel;

   // on r�cup�re le nombre de personnes dans le fichier texte
   fichier >> nbPersonnes;
   fichier.ignore();

   // on initialise les deux tables de dispersions
   // la taille des tables correspond au nombre premier suivant le nombre d'employ�s charg�s �
   // partir du fichier, multipli� par 1.30
   tabTelephone.resize(_premierSuivant(nbPersonnes * 1.3));
   tabNomPrenom.resize(_premierSuivant(nbPersonnes * 1.3));
   rendreVide();

   // on r�cup�re les infos des employ�s pour les stocker dans le tableau des entr�es
   // et pour cr�er les associations dans les deux tables de dispersions
   for (int i = 0; i < nbPersonnes; i++)
   {
      getline(fichier, nom, ',');
      fichier.ignore();
      getline(fichier, prenom, '\t');
      getline(fichier, tel, '\t');
      getline(fichier, fax, '\t');
      getline(fichier, courriel);

      // ajout dans le tableau des entr�es
      tabEntree.push_back(Entree(nom, prenom, tel, fax, courriel));

      // insertion dans les deux tables de dispersions
      _inserer(tel, i);
      _inserer((nom + prenom), i);
   }

   nbCollisions = collisionsTel + collisionsNom;
}

/**
 * \fn void Bottin::rendreVide()
 */
void Bottin::rendreVide()
{
   tailleTel = 0;
   tailleNom = 0;

   // Pour la table de dispersion avec la cl� T�l�phone
   for (unsigned int i = 0; i < tabTelephone.size(); i++)
      tabTelephone[i].info = VIDE;

   // Pour la table de dispersion avec la cl� Nom/Pr�nom
   for (unsigned int i = 0; i < tabNomPrenom.size(); i++)
      tabNomPrenom[i].info = VIDE;
}

/**
 * \fn bool Bottin::contient(const std::string & c)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant un num�ro de t�l�phone
 *                ou une paire Nom/Pr�nom.
 *
 * \return VRAI si la cl� est pr�sente, FAUX sinon.
 */
bool Bottin::contient(const std::string & c)
{
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   string clef = _creerClef(c);
   int positionCourante = _trouverPosition(clef);

   // on conserve le nombre de collisions avant l'appel de la m�thode _trouverPosition()
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;

   return _estActive(clef, positionCourante);
}

/**
 * \fn void Bottin::ajouter(const std::string & nom, const std::string & prenom,
 *                          const std::string & tel, const std::string & fax,
 *                          const std::string & courriel)
 *
 * \param[in] nom : le nom de la personne � ajouter.
 * \param[in] prenom : le pr�nom de la personne � ajouter.
 * \param[in] tel : le num�ro de t�l�phone de la personne � ajouter.
 * \param[in] fax : le num�ro de fax de la personne � ajouter.
 * \param[in] courriel : l'adresse courriel de la personne � ajouter.
 */
void Bottin::ajouter(const std::string & nom, const std::string & prenom, const std::string & tel,
                     const std::string & fax, const std::string & courriel)
{
   // la personne ne doit pas �tre pr�sente dans la table
   if (contient(tel) || contient(nom + prenom))
      throw std::logic_error ("ajouter: l'entr�e est d�j� pr�sente dans la table.");

   // ajout dans le tableau des entr�es
   tabEntree.push_back(Entree(nom, prenom, tel, fax, courriel));

   // insertion dans les tables de dispersions
   // la position du tableau des entr�es = tabEntree.size() - 1
   int position = tabEntree.size() - 1;
   _inserer(tel, position);
   _inserer((nom + prenom), position);
}

/**
 * \fn void Bottin::supprimer(const std::string & c)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant un num�ro de t�l�phone
 *                ou une paire Nom/Pr�nom.
 */
void Bottin::supprimer(const std::string & c)
{
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   string clef = _creerClef(c);
   int positionCourante = _trouverPosition(clef);

   if (!_estActive(clef, positionCourante))
      throw std::logic_error ("supprimer: l'entr�e n'est pas pr�sente dans la table.\n");


   // Suppression des entr�es dans les deux tables de dispersions
   int positionEntree = 0;

   if (isdigit(clef[0]))
   {
      // Si la cl� est un num�ro de t�l�phone

      // on r�cup�re la position associ�e � la cl� dans le HashEntree
      positionEntree = tabTelephone[positionCourante].position;

      // pour r�cup�rer le nom et le pr�nom dans tabEntree
      string nom = tabEntree[positionEntree].nom;
      string prenom = tabEntree[positionEntree].prenom;

      // on trouve la position de l'entr�e dans tabNomPrenom
      clef = _creerClef(nom + prenom);
      int positionNom = _trouverPosition(clef);

      // on supprime dans les deux tables de dispersions
      tabNomPrenom[positionNom].info = SUPPRIMEE;
      tabTelephone[positionCourante].info = SUPPRIMEE;
   }
   else
   {
      // Sinon, la cl� est une paire Nom/Pr�nom

      // on r�cup�re la position associ�e � la cl� dans le HashEntree
      positionEntree = tabNomPrenom[positionCourante].position;

      // pour r�cup�rer le num�ro de t�l�phone dans tabEntree
      string tel = tabEntree[positionEntree].tel;

      // on trouve la position de l'entr�e dans tabTelephone
      clef = _creerClef(tel);
      int positionTel = _trouverPosition(clef);

      // on supprime dans les deux tables de dispersions
      tabTelephone[positionTel].info = SUPPRIMEE;
      tabNomPrenom[positionCourante].info = SUPPRIMEE;
   }

   // on conserve le nombre de collisions avant l'appel de la m�thode _trouverPosition()
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;
}

/**
 * \fn int Bottin::getCollisionsTel() const
 *
 * \return collisionsTel : le nombre de collisions rencontr�es dans tabTelephone.
 */
int Bottin::getCollisionsTel() const
{
   return collisionsTel;
}

/**
 * \fn int Bottin::getCollisionsNom() const
 *
 * \return collisionsNom : le nombre de collisions rencontr�es dans tabNomPrenom.
 */
int Bottin::getCollisionsNom() const
{
   return collisionsNom;
}

/**
 * \fn Employe Bottin::trouverAvecNomPrenom(const std::string & c, int &nbCollisions)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant une paire Nom/Pr�nom.
 * \param[in] nbCollisions : un entier pour retourner le nombre de collisions rencontr�es.
 *
 * \return Un objet Employe contenant les informations de l'employ�.
 */
Employe Bottin::trouverAvecNomPrenom(const std::string & c, int &nbCollisions)
{
   int collisionEmploye = collisionsNom;

   string clef = _creerClef(c);
   int positionCourante = _trouverPosition(clef);

   // on v�rifie que l'entr�e est pr�sente dans la table
   if (!_estActive(clef, positionCourante))
         throw std::logic_error ("trouverAvecNomPrenom: l'entr�e n'est pas pr�sente dans la table.\n");

   // on calcule le nombre de collisions que l'op�ration a rencontr�es
   nbCollisions = collisionsNom - collisionEmploye;

   // on r�cup�re la position associ�e � la cl� dans le HashEntree
   int positionEntree = tabNomPrenom[positionCourante].position;

   // on r�cup�re les infos de l'employ� pour les retourner dans un objet Employe
   Employe e;
   e.nom = tabEntree[positionEntree].nom;
   e.prenom = tabEntree[positionEntree].prenom;
   e.tel = tabEntree[positionEntree].tel;
   e.fax = tabEntree[positionEntree].fax;
   e.courriel = tabEntree[positionEntree].courriel;

   return e;
}

/**
 * \fn Employe Bottin::trouverAvecTelephone(const std::string & c, int &nbCollisions)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant un num�ro de t�l�phone.
 * \param[in] nbCollisions : un entier pour retourner le nombre de collisions rencontr�es.
 *
 * \return Un objet Employe contenant les informations de l'employ�.
 */
Employe Bottin::trouverAvecTelephone(const std::string & c, int &nbCollisions)
{
   int collisionEmploye = collisionsTel;

   string clef = _creerClef(c);
   int positionCourante = _trouverPosition(clef);

   // on v�rifie que l'entr�e est pr�sente dans la table
   if (!_estActive(clef, positionCourante))
         throw std::logic_error ("trouverAvecTelephone: l'entr�e n'est pas pr�sente dans la table.\n");

   // on calcule le nombre de collisions que l'op�ration a rencontr�es
   nbCollisions = collisionsTel - collisionEmploye;

   // on r�cup�re la position associ�e � la cl� dans le HashEntree
   int positionEntree = tabTelephone[positionCourante].position;

   // on r�cup�re les infos de l'employ� pour les retourner dans un objet Employe
   Employe e;
   e.nom = tabEntree[positionEntree].nom;
   e.prenom = tabEntree[positionEntree].prenom;
   e.tel = tabEntree[positionEntree].tel;
   e.fax = tabEntree[positionEntree].fax;
   e.courriel = tabEntree[positionEntree].courriel;

   return e;
}

/**
 * \fn string Bottin::infosEmploye(const Employe& e) const
 *
 * \param[in] e : un objet Employe.
 *
 * \return Une cha�ne de caract�res pour afficher les informations de l'employ�.
 */
string Bottin::infosEmploye(const Employe& e) const
{
     ostringstream infos;

     infos << "Nom       : " << e.nom << "\n";
     infos << "Pr�nom    : " << e.prenom << "\n";
     infos << "T�l�phone : " << e.tel << "\n";
     infos << "Fax       : " << e.fax << "\n";
     infos << "Courriel  : " << e.courriel << "\n";

     return infos.str();
}

//-------------------------------------------------------------------------------------------------
// M�thodes priv�es
//-------------------------------------------------------------------------------------------------

/**
 * \fn std::string Bottin::_creerClef(const std::string & c)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant un num�ro de t�l�phone
 *                ou une paire Nom/Pr�nom.
 *
 * \return Une cha�ne de caract�res contenant la cl� pour le hachage.
 */
std::string Bottin::_creerClef(const std::string & c)
{
   string clef;

   // on ne garde que les chiffres et les lettres
   for (unsigned int i = 0; i < c.size(); i++)
   {
      if (isdigit(c[i]) || isalpha(c[i]))
         clef += c[i];
   }

   return clef;
}

/**
 * \fn bool Bottin::_estActive(const std::string & clef, int positionCourante) const
 *
 * \param[in] clef : la cl� de hachage.
 * \param[in] positionCourante : la position courante � rechercher.
 *
 * \return VRAI si l'entr�e � la positionCourante est active (occup�e), FAUX sinon.
 */
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

/**
 * \fn void Bottin::_inserer(const std::string & c, const int & pos)
 *
 * \param[in] c : une cha�ne de caract�res repr�sentant un num�ro de t�l�phone
 *                ou une paire Nom/Pr�nom.
 * \param[in] pos : la position de l'entr�e dans le tableau tabEntree.
 */
void Bottin::_inserer(const std::string & c, const int & pos)
{
   string clef = _creerClef(c);
   int positionCourante = _trouverPosition(clef);

   // on v�rifie que l'entr�e n'est pas d�j� pr�sente dans la table
   if (_estActive(clef, positionCourante))
      throw std::logic_error ("inserer: l'entr�e est d�j� pr�sente dans la table.\n");

   // on ins�re l'entr�e dans la table de dispersion
   if (isdigit(clef[0]))
   {
      tabTelephone[positionCourante] = HashEntree(clef, pos, ACTIVE);

      // si la taille de tabTelephone d�passe le TAUX_MAX
      if ((++tailleTel/float(tabTelephone.size()))*100 > TAUX_MAX)
         _rehash();
   }
   else
   {
      tabNomPrenom[positionCourante] = HashEntree(clef, pos, ACTIVE);

      // si la taille de tabNomPrenom d�passe le TAUX_MAX
      if ((++tailleNom/float(tabNomPrenom.size()))*100 > TAUX_MAX)
         _rehash();
   }
}

/**
 * \fn int Bottin::_trouverPosition(const std::string & clef)
 *
 * \param[in] clef : la cl� de hachage.
 *
 * \return La position courante dans la table de dispersion.
 */
int Bottin::_trouverPosition(const std::string & clef)
{
   unsigned long positionCourante = 0;
   int offset = 1;

   if (isdigit(clef[0]))
   {
      // si la cl� est un num�ro de t�l�phone

      for (unsigned int i = 0; i < clef.length(); i++)
         positionCourante = 37 * positionCourante + clef[i];

      positionCourante %= tabTelephone.size();

      if (positionCourante < 0)
         positionCourante += tabTelephone.size();

      // Redispersion si collision...
      while (tabTelephone[positionCourante].info != VIDE &&
             tabTelephone[positionCourante].clef != clef)
      {
         collisionsTel++;
         positionCourante += offset;  // Calcule le i-i�me sondage
         offset += 2;
         if (positionCourante >= tabTelephone.size())
         {
            positionCourante -= tabTelephone.size();
         }
      }
   }
   else
   {
      // sinon, c'est une paire Nom/Pr�nom

      for (unsigned int i = 0; i < clef.length(); i++)
         positionCourante = 37 * positionCourante + clef[i];

      positionCourante %= tabNomPrenom.size();

      if (positionCourante < 0)
         positionCourante += tabNomPrenom.size();

      // Redispersion si collision...
      while (tabNomPrenom[positionCourante].info != VIDE &&
             tabNomPrenom[positionCourante].clef != clef)
      {
         collisionsNom++;
         positionCourante += offset;  // Calcule le i-i�me sondage
         offset += 2;
         if (positionCourante >= tabNomPrenom.size())
         {
            positionCourante -= tabNomPrenom.size();
         }
      }
   }

   return positionCourante;
}

/**
 * \fn void Bottin::_rehash()
 */
void Bottin::_rehash()
{
   vector<HashEntree> oldTabTelephone = tabTelephone;
   vector<HashEntree> oldTabNomPrenom = tabNomPrenom;

   // on veut conserver le nombre de collisions avant cette op�ration
   // les collisions ont d�j� �t� calcul�es sur les insertions qui sont d�j� dans les tables
   int oldCollisionsTel = collisionsTel;
   int oldCollisionsNom = collisionsNom;

   // Cr�ation de nouvelles tables 2 fois plus grandes
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

   // on conserve le nombre de collisions avant l'appel de la fonction _rehash()
   collisionsTel = oldCollisionsTel;
   collisionsNom = oldCollisionsNom;
}

/**
 * \fn bool Bottin::_premier(int n)
 *
 * \param[in] n : un nombre entier plus grand que 0.
 *
 * \return VRAI si n est un nombre premier, FAUX sinon.
 */
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

/**
 * \fn int Bottin::_premierSuivant(int n)
 *
 * \param[in] n : un nombre entier plus grand que 0.
 *
 * \return Un entier correspondant au nombre premier suivant n.
 */
int Bottin::_premierSuivant(int n)
{
   if (n % 2 == 0)
      n++;

   while (!_premier(n))
      n += 2;

   return n;
}

} //Fin du namespace
