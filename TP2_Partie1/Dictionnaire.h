/**
 * \file Dictionnaire.h
 * \brief Ce fichier contient l'interface d'un dictionnaire.
 * \author Admin
 * \version 0.1
 * \date juin 2014
 * 
 */


#ifndef DICO_H_
#define DICO_H_

#include <stdexcept>
#include <iostream>
#include <fstream> // pour les fichiers
#include <string>
#include <vector>

namespace TP2P1
{
/**
* \class Dictionnaire
*
* \brief classe repr�sentant un dictionnaire
*
*  La classe g�re un pointeur sur la racine du dictionnaire
*/
class Dictionnaire
{
public:

	/*
	*\brief		Constructeur 
	*
	*\post		Une instance vide de la classe a �t� initialis�e
	*
	*/
	Dictionnaire();

	/*
	*\brief		Constructeur de dictionnaire � partir d'un fichier
	*
	*\pre		Il y a suffisament de m�moire
	*\pre		Le fichier est ouvert au pr�alable
	*
	*\post		Si le fichier est ouvert, l'instance de la classe a �t� initialis�e � partir du fichier de dictionnaire. Sinon, on g�n�re une classe vide.
	*
	*\exception	bad_alloc s'il n'y a pas assez de m�moire
	*
	*/
	Dictionnaire(std::ifstream &fichier);


	/*
	*\brief		Destructeur
	*
	*\post		Une instance de la classe est d�truite
	*
	*/
	~Dictionnaire();

	/*
	*\brief		Ajouter un mot au dictionnaire et l'une de ses traductions en �quilibrant l'arbre AVL
	*			
	*\pre		Il y a suffisament de m�moire 
	*
	*\post		Le mot est ajout� au dictionnaire
	*
	*\exception	bad_alloc si il n'y a pas suffisament de m�moire
	*
	*/
	void ajouteMot(const std ::string& motOriginal, const std ::string& motTraduit);

	/*
	*\brief		Supprimer un mot et �quilibrer l'arbre AVL
	*
	*\pre		L'arbre n'est pas vide
	*\pre		Le mot � enlever appartient au dictionnaire
	*
	*\post		Si le mot appartient au dictionnaire, on l'enl�ve et on �quilibre. Sinon, on ne fait rien.
	*
	*\exception	logic_error si l'arbre est vide
	*\exception	logic_error si le mot n'appartient pas au dictionnaire
	*/
	void supprimeMot(const std ::string& motOriginal);

	/*
	*\brief		Quantifier la similitude entre 2 mots (dans le dictionnaire ou pas)
	*			Ici, 1 repr�sente le fait que les 2 mots sont identiques, 0 repr�sente le fait que les 2 mots sont compl�tements diff�rents
	*
	*\post		Le dictionnaire est inchang�e.
	*\post		On retourne une valeur entre 0 et 1 quantifiant la similarit� entre les 2 mots donn�s
	*
	*/
	double similitude(const std ::string& mot1, const std ::string& mot2);


	/*
	*\brief		Sugg�re des corrections pour le mot motMalEcrit sous forme d'une liste de mots, dans un vector, � partir du dictionnaire
	*
	*\pre		Le dictionnaire n'est pas vide
	*
	*\post		S'il y a suffisament de mots, on redonne 10 corrections possibles au mot donn�. Sinon, on en donne le plus possible
	*
	*\exception	logic_error si le dictionnaire est vide
	*/
	std::vector<std::string> suggereCorrections(const std ::string& motMalEcrit);

	/*
	*\brief		Trouver les traductions possibles d'un mot
	*
	*\post		Si le mot appartient au dictionnaire, on retoune la liste des traductions du mot donn�. 
	*\post		Sinon, on retourne un vecteur vide
	*\post		Le dictionnaire reste inchang�e
	*
	*/
	std::vector<std::string> traduit(const std ::string& mot);

	/*
	*\brief		V�rifier si le mot donn� appartient au dictionnaire
	*
	*\post		Le dictionnaire reste inchang�e
	*\post		On retourne true si le mot est dans le dictionnaire. Sinon, on retourne false.
	*
	*/
	bool appartient(const std::string &data);

	/*
	*\brief		V�rifier si le dictionnaire est vide
	*
	*\post		Le dictionnaire est inchang�e
	*
	*/
	bool estVide() const;


private:

	class NoeudDictionnaire
	{
	public:

		std::string mot;						// Un mot (en anglais)

		std::vector<std::string> traductions;	// Les diff�rentes traductions possibles en fran�ais du mot en anglais
												// Par exemple, la liste fran�aise { "contempler", "envisager" et "pr�voir" }
												// pourrait servir de traduction du mot anglais "contemplate".

	    NoeudDictionnaire *gauche, *droite;		// Les enfants du noeud

	    int hauteur;							// La hauteur de ce noeud (afin de maintenir l'�quilibre de l'arbre AVL)

		// Vous pouvez ajouter ici un constructeur de NoeudDictionnaire
		NoeudDictionnaire( const std::string&motOriginal,const std::string&motTraduit ): mot( motOriginal ), gauche( 0 ), droite( 0 ), hauteur(0) {traductions.push_back(motTraduit); }
	};

   typedef NoeudDictionnaire * elem;

   elem racine;			// La racine de l'arbre des mots

   int cpt;				// Le nombre de mots dans le dictionnaire

   //Vous pouvez ajouter autant de m�thodes priv�es que vous voulez
   std::vector<std::string> & _auxTraduit( elem & arbre,const std::string& mot);

   /*
	*\brief		V�rifier r�cursivement pour une corrections
	*
	*\post		Le dictionnaire est inchang�
	*
	*/
   void _auxsuggereCorrections( elem & arbre,const std::string& motMalEcrit,double& min,std::vector<std::string> &corrections);


   /*
	*\brief		V�rifier r�cursivement pour un mot dans le dictionnaire
	*
	*\post		Le dictionnaire est inchang�
	*
	*/
   elem _auxAppartient(elem arbre, const std::string &mot) const;
   

   /*
	*\brief		V�rifier r�cursivement pour enlever un mot dans le dfictionnaire
	*
	*\post		L'�l�ment est retir� du dictionnaire
	*
	*/
   void _auxEnlever( elem &, const std::string&);

     /*
	*\brief		Retirer le plus petit �l�ment du dictionnaire
	*
	*\post		L'�l�ment est retir� du dictionnaire
	*
	*/
   void _auxRetireMin( elem & arbre) const;

    /*
	*\brief		D�truire le dictionnaire
	*
	*\post		Le dictionnaire est d�truit.
	*
	*/
   void  _auxDetruire(elem &t);

     /*
	*\brief		Charger un dictionnaire avec un fichier texte
	*
	*\post		Le dictionnaire est charg�
	*
	*/
   void chargerDictionnaire(std::ifstream &fichierEntree);


     /*
	*\brief		Ins�rer un �l�ment r�cursivement
	*
	*\post		L'�l�ment est ins�r�
	*
	*/
   void _auxInserer( elem &, const std::string&,const std::string&);


      /*
	*\brief		Donne la hauteur d'un noeud.
	*
	*\post		Le dictionnaire est inchang�
	*
	*/
   int _hauteur(elem noeud) const;

     /*
	*\brief		Donne le plus haut noeud
	*
	*\post		Le dictionnaire est inchang�
	*
	*/

   int _maximum(int ent1, int ent2) const;

   /**                       
	 *  \brief Simple rotation - D�s�quilibre gauche-gauche
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balanc�
	 */
	void _zigZigGauche(elem &);

	/**                       
	 *  \brief Simple rotation - D�s�quilibre droite-droite
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balanc�
	 */
	void _zigZigDroit(elem &);

	/**                       
	 *  \brief Double rotation - D�s�quilibre gauche-droite
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balanc�
	 */
	void _zigZagGauche(elem &);

	/**                       
	 *  \brief Double rotation - D�s�quilibre droite-gauche
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balanc�
	 */
	void _zigZagDroit(elem &);
};

}

#endif /* DICO_H_ */
