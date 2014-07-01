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
* \brief classe représentant un dictionnaire
*
*  La classe gère un pointeur sur la racine du dictionnaire
*/
class Dictionnaire
{
public:

	/*
	*\brief		Constructeur 
	*
	*\post		Une instance vide de la classe a été initialisée
	*
	*/
	Dictionnaire();

	/*
	*\brief		Constructeur de dictionnaire à partir d'un fichier
	*
	*\pre		Il y a suffisament de mémoire
	*\pre		Le fichier est ouvert au préalable
	*
	*\post		Si le fichier est ouvert, l'instance de la classe a été initialisée à partir du fichier de dictionnaire. Sinon, on génère une classe vide.
	*
	*\exception	bad_alloc s'il n'y a pas assez de mémoire
	*
	*/
	Dictionnaire(std::ifstream &fichier);


	/*
	*\brief		Destructeur
	*
	*\post		Une instance de la classe est détruite
	*
	*/
	~Dictionnaire();

	/*
	*\brief		Ajouter un mot au dictionnaire et l'une de ses traductions en équilibrant l'arbre AVL
	*			
	*\pre		Il y a suffisament de mémoire 
	*
	*\post		Le mot est ajouté au dictionnaire
	*
	*\exception	bad_alloc si il n'y a pas suffisament de mémoire
	*
	*/
	void ajouteMot(const std ::string& motOriginal, const std ::string& motTraduit);

	/*
	*\brief		Supprimer un mot et équilibrer l'arbre AVL
	*
	*\pre		L'arbre n'est pas vide
	*\pre		Le mot à enlever appartient au dictionnaire
	*
	*\post		Si le mot appartient au dictionnaire, on l'enlève et on équilibre. Sinon, on ne fait rien.
	*
	*\exception	logic_error si l'arbre est vide
	*\exception	logic_error si le mot n'appartient pas au dictionnaire
	*/
	void supprimeMot(const std ::string& motOriginal);

	/*
	*\brief		Quantifier la similitude entre 2 mots (dans le dictionnaire ou pas)
	*			Ici, 1 représente le fait que les 2 mots sont identiques, 0 représente le fait que les 2 mots sont complètements différents
	*
	*\post		Le dictionnaire est inchangée.
	*\post		On retourne une valeur entre 0 et 1 quantifiant la similarité entre les 2 mots donnés
	*
	*/
	double similitude(const std ::string& mot1, const std ::string& mot2);


	/*
	*\brief		Suggère des corrections pour le mot motMalEcrit sous forme d'une liste de mots, dans un vector, à partir du dictionnaire
	*
	*\pre		Le dictionnaire n'est pas vide
	*
	*\post		S'il y a suffisament de mots, on redonne 10 corrections possibles au mot donné. Sinon, on en donne le plus possible
	*
	*\exception	logic_error si le dictionnaire est vide
	*/
	std::vector<std::string> suggereCorrections(const std ::string& motMalEcrit);

	/*
	*\brief		Trouver les traductions possibles d'un mot
	*
	*\post		Si le mot appartient au dictionnaire, on retoune la liste des traductions du mot donné. 
	*\post		Sinon, on retourne un vecteur vide
	*\post		Le dictionnaire reste inchangée
	*
	*/
	std::vector<std::string> traduit(const std ::string& mot);

	/*
	*\brief		Vérifier si le mot donné appartient au dictionnaire
	*
	*\post		Le dictionnaire reste inchangée
	*\post		On retourne true si le mot est dans le dictionnaire. Sinon, on retourne false.
	*
	*/
	bool appartient(const std::string &data);

	/*
	*\brief		Vérifier si le dictionnaire est vide
	*
	*\post		Le dictionnaire est inchangée
	*
	*/
	bool estVide() const;


private:

	class NoeudDictionnaire
	{
	public:

		std::string mot;						// Un mot (en anglais)

		std::vector<std::string> traductions;	// Les différentes traductions possibles en français du mot en anglais
												// Par exemple, la liste française { "contempler", "envisager" et "prévoir" }
												// pourrait servir de traduction du mot anglais "contemplate".

	    NoeudDictionnaire *gauche, *droite;		// Les enfants du noeud

	    int hauteur;							// La hauteur de ce noeud (afin de maintenir l'équilibre de l'arbre AVL)

		// Vous pouvez ajouter ici un constructeur de NoeudDictionnaire
		NoeudDictionnaire( const std::string&motOriginal,const std::string&motTraduit ): mot( motOriginal ), gauche( 0 ), droite( 0 ), hauteur(0) {traductions.push_back(motTraduit); }
	};

   typedef NoeudDictionnaire * elem;

   elem racine;			// La racine de l'arbre des mots

   int cpt;				// Le nombre de mots dans le dictionnaire

   //Vous pouvez ajouter autant de méthodes privées que vous voulez
   std::vector<std::string> & _auxTraduit( elem & arbre,const std::string& mot);

   /*
	*\brief		Vérifier récursivement pour une corrections
	*
	*\post		Le dictionnaire est inchangé
	*
	*/
   void _auxsuggereCorrections( elem & arbre,const std::string& motMalEcrit,double& min,std::vector<std::string> &corrections);


   /*
	*\brief		Vérifier récursivement pour un mot dans le dictionnaire
	*
	*\post		Le dictionnaire est inchangé
	*
	*/
   elem _auxAppartient(elem arbre, const std::string &mot) const;
   

   /*
	*\brief		Vérifier récursivement pour enlever un mot dans le dfictionnaire
	*
	*\post		L'élément est retiré du dictionnaire
	*
	*/
   void _auxEnlever( elem &, const std::string&);

     /*
	*\brief		Retirer le plus petit élément du dictionnaire
	*
	*\post		L'élément est retiré du dictionnaire
	*
	*/
   void _auxRetireMin( elem & arbre) const;

    /*
	*\brief		Détruire le dictionnaire
	*
	*\post		Le dictionnaire est détruit.
	*
	*/
   void  _auxDetruire(elem &t);

     /*
	*\brief		Charger un dictionnaire avec un fichier texte
	*
	*\post		Le dictionnaire est chargé
	*
	*/
   void chargerDictionnaire(std::ifstream &fichierEntree);


     /*
	*\brief		Insérer un élément récursivement
	*
	*\post		L'élément est inséré
	*
	*/
   void _auxInserer( elem &, const std::string&,const std::string&);


      /*
	*\brief		Donne la hauteur d'un noeud.
	*
	*\post		Le dictionnaire est inchangé
	*
	*/
   int _hauteur(elem noeud) const;

     /*
	*\brief		Donne le plus haut noeud
	*
	*\post		Le dictionnaire est inchangé
	*
	*/

   int _maximum(int ent1, int ent2) const;

   /**                       
	 *  \brief Simple rotation - Déséquilibre gauche-gauche
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
	 */
	void _zigZigGauche(elem &);

	/**                       
	 *  \brief Simple rotation - Déséquilibre droite-droite
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
	 */
	void _zigZigDroit(elem &);

	/**                       
	 *  \brief Double rotation - Déséquilibre gauche-droite
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
	 */
	void _zigZagGauche(elem &);

	/**                       
	 *  \brief Double rotation - Déséquilibre droite-gauche
	 *
	 * \post Le sous-arbre sous-tendu par le noeud critique est balancé
	 */
	void _zigZagDroit(elem &);
};

}

#endif /* DICO_H_ */
