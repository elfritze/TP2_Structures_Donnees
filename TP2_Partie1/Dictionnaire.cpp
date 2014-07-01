/**
 * \file Dictionnaire.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Dictionnaire
 * \author Étudiant 1, étudiant 2
 * \version 0.1
 * \date juillet 2014
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "Dictionnaire.h"
#include <string.h>
namespace TP2P1
{

	/**
	 * \fn Dictionnaire:: Dictionnaire()
	 */
	Dictionnaire:: Dictionnaire()
	{
		racine = 0; 
		cpt=0;
	}

	/**
	 * \fn  Dictionnaire::Dictionnaire(std::ifstream &fichier)
	 * \param[in] fichier : Fichier utilisé
	 */
	Dictionnaire::Dictionnaire(std::ifstream &fichier)
	{
		racine = 0; 
		cpt=0;

		chargerDictionnaire(fichier);
	}

	/**
	 * \fn  Dictionnaire::~Dictionnaire(std::ifstream &fichier)
	 */
	Dictionnaire::~Dictionnaire()
	{
		_auxDetruire(racine);
	}

	/**
	 * \fn void  Dictionnaire::ajouteMot(const std ::string& motOriginal, const std ::string& motTraduit)
	 * \param[in] motOriginal : Mot à ajouter
	 * \param[in] motTraduit : Une traduction possible
	 */
	void Dictionnaire::ajouteMot(const std ::string& motOriginal, const std ::string& motTraduit)
	{
		_auxInserer(racine, motOriginal,motTraduit);
	}

	/**
	 * \fn void  Dictionnaire::supprimeMot(const std::string& motOriginal)
	 * \param[in] motOriginal : Mot à supprimer
	 */
	void Dictionnaire::supprimeMot(const std::string& motOriginal)
	{
		if( racine == 0 )
			throw std::logic_error("enlever: Le dictionnaire est vide\n");

		if( _auxAppartient(racine, motOriginal) == 0 )
			throw std::logic_error("enlever: Le mot ne fait pas partie du dictionnaire\n");

		_auxEnlever(racine, motOriginal);
	}


	/**
	 * \fn bool  Dictionnaire::appartient(const std::string &mot)
	 * \param[in] motOriginal : Mot à vérifier
	 */
	bool Dictionnaire::appartient(const std::string &mot)
	{
		return _auxAppartient(racine, mot)!=0;
	}

	/**
	 * \fn std::vector<std::string> Dictionnaire::suggereCorrections(const std::string& motMalEcrit)
	 * \param[in] motMalEcrit : Mot à corriger
	 */
	std::vector<std::string> Dictionnaire::suggereCorrections(const std::string& motMalEcrit)
	{
		//On met une sensibilité de correction minimale.
		double min = .4;
		std::vector<std::string> corrections;
		_auxsuggereCorrections(racine, motMalEcrit,min,corrections);
		return corrections;
	}

	/**
	 * \fn double Dictionnaire::similitude(const std ::string& mot1, const std ::string& mot2)
	 * \param[in] mot1 : Premier mot
	  * \param[in] mot2 : Dexieme mot
	 */
	double Dictionnaire::similitude(const std ::string& mot1, const std ::string& mot2)
	{
		int j;
		bool streak = true;
		double similarity = 0.;
		std::string bigger = mot1.size() > mot2.size() ? mot1 : mot2;
		std::string smaller = mot1.size() > mot2.size() ? mot2 : mot1;

		//On parcoure chacune des lettre du plus petit mot
		for (j=0; j < smaller.size(); j++)
		{
			//On parcoure le reste du mot à partir de la lettre actuelle
			for(int i = 0; i < smaller.size() - j;i++){
				//on teste si mot partiel est trouvable dans le plus grand mot.
				std::string motyo = smaller.substr(j,i + 1);
				if(bigger.find(motyo) != std::string::npos){
					similarity++;
				}
			}
			
		}

		double score = similarity  / (smaller.size() * smaller.size());
		return score;
	}


	
	/**
	 * \fn std::vector<std::string> Dictionnaire::traduit(const std ::string& mot)
	 * \param[in] mot : Mot à traduire.
	 */
	std::vector<std::string> Dictionnaire::traduit(const std ::string& mot){
		std::vector<std::string> traductions = _auxTraduit(racine,mot);
		return traductions;
	}

	/**
	 * \fn std::vector<std::string> & Dictionnaire::_auxTraduit( elem & arbre,const std::string& mot)
	 * \param[in] arbre : Noeud dans le dictionnaire
	 * \param[in] mot : Mot à traduire.
	 */
	std::vector<std::string> & Dictionnaire::_auxTraduit( elem & arbre,const std::string& mot)
	{
		//Si l'arbre est vide
		if(arbre == 0){
			std::vector<std::string> traductions;
			return traductions;
		}
		
		if(arbre->mot == mot) //Si le mot est trouvé
			return arbre->traductions;
		else if(arbre->mot > mot)
			_auxTraduit(arbre->gauche, mot);
		else
			_auxTraduit(arbre->droite, mot);
	}

	/**
	 * \fn  Dictionnaire::_auxsuggereCorrections(elem & arbre,const std::string& motMalEcrit,double& min,std::vector<std::string> &corrections)
	 * \param[in] arbre : Noeud dans le dictionnaire
	 * \param[in] motMalEcrit : Mot à corriger
	  * \param[in] min : Sensibilité pour la comparaison des mots
	   * \param[in] corrections : Liste des corrections à remplir
	 */
	void Dictionnaire::_auxsuggereCorrections(elem & arbre,const std::string& motMalEcrit,double& min,std::vector<std::string> &corrections)
		{
			if (arbre == 0)
			{
				return;
			}
			if ( similitude(arbre->mot,motMalEcrit) > .4  ) // Si la similitude depasse la sensibilité minimal on considère le mot
			{
				if(corrections.size() >= 10) // Si déjà 10 corrections sont trouvées
				{
					if( similitude(arbre->mot,motMalEcrit) > min) //Si la similitude du mot actuel est plus grande la minimale de la liste de corrections
					{
						int i = 0;
						bool found = false;
						while(!found && i < corrections.size())
						{
							// On trouve une correction avec la sensibilité minimale pour la remplacer
							if(similitude(corrections.at(i),motMalEcrit) == min){
								corrections.at(i) = arbre->mot;
								found = true; 
							}

							i++;
						}
						min =  similitude(arbre->mot,motMalEcrit);
					}
				}
				else
					corrections.push_back(arbre->mot); // On ajoute la correction à la liste
			}


			_auxsuggereCorrections(arbre->gauche, motMalEcrit,min,corrections);
		
			_auxsuggereCorrections(arbre->droite, motMalEcrit,min,corrections);

		}


	/**
	 * \fn  void Dictionnaire::_auxEnlever( elem & arbre, const std::string& mot)
	 * \param[in] arbre : Noeud dans le dictionnaire
	 * \param[in] mot : Mot à enlever
	 */
	void Dictionnaire::_auxEnlever( elem & arbre, const std::string& mot)
	{
		if( arbre->mot.compare(mot) >  0)
			_auxEnlever( arbre->gauche, mot);

		else if( arbre->mot.compare(mot) < 0 )
			_auxEnlever( arbre->droite, mot);

		// si on se rend jusqu'ici, c'est qu'on a trouvé le noeud
		// qui contient la valeur recherchée
		else if( arbre->gauche != 0 && arbre->droite != 0 ) 
		{
			// deux enfants: il faut trouver la valeur suivante dans la
			// séquence et la mettre à la place de la valeur du noeud actuel
	        
			//chercher le noeud qui contient la valeur minimale dans le sous-arbre de droite
			elem temp = arbre->droite;
			while ( temp->gauche != 0) temp = temp->gauche;
			arbre->mot = temp->mot;
			_auxRetireMin( arbre->droite ); // Retirer minimum dans le sous-arbre droit
		}
		else
		{
			// le noeud n'a aucun enfant ou qu'un seul enfant, il suffit donc de retirer
			// ce noeud et pointer sur l'éventuel enfant 
			elem vieuxNoeud = arbre;
			arbre = ( arbre->gauche != 0 ) ? arbre->gauche : arbre->droite;  
			delete vieuxNoeud;  
			cpt--;
		}	
	}


	/**
	 * \fn void Dictionnaire:: _auxRetireMin( elem & arbre) const
	 * \param[in] arbre : Noeud dans le dictionnaire
	 */
	void Dictionnaire:: _auxRetireMin( elem & arbre) const
	{
		
		if (arbre->gauche != 0)
			_auxRetireMin(arbre->gauche );
		else
		{
			elem tmp = arbre;
			arbre = arbre->droite;
			delete tmp;
		}
	}


	/**
	 * \fn Dictionnaire::elem Dictionnaire::_auxAppartient(elem arbre, const std::string &mot) const
	 * \param[in] arbre : Noeud dans le dictionnaire
	 * \param[in] mot : Mot à trouver
	 */
	 Dictionnaire::elem Dictionnaire::_auxAppartient(elem arbre, const std::string &mot) const
	 {
		 if (arbre == 0)
			return 0;

		 if ( arbre->mot.compare(mot) == 0  )
			return arbre;

		if ( arbre->mot.compare(mot) > 0 )
			return _auxAppartient(arbre->gauche, mot);
		else
			return _auxAppartient(arbre->droite, mot);
		
	 }

	 /**
	 * \fn void Dictionnaire::_auxInserer(elem &arbre, const std::string &motOriginal, const std::string &motTraduit)
	 * \param[in] arbre : Noeud dans le dictionnaire
	 * \param[in] motOriginal : Mot à insérer
	 * \param[in] motTraduit : Traduction possible
	 */
	void Dictionnaire::_auxInserer(elem &arbre, const std::string &motOriginal, const std::string &motTraduit)
	{
		//Si l'arbre est vide
		if (arbre == 0)
		{
			arbre = new NoeudDictionnaire(motOriginal,motTraduit);
			cpt++;
			return;
		}
		else if(arbre->mot.compare(motOriginal) == 0){ //Si le mot est déjà présent on insère seulement ses traductions
			arbre->traductions.push_back(motTraduit);
			return;
		}
		if( arbre->mot.compare(motOriginal) > 0 ) //Sinon on insère a gauche ou a droite
		{	_auxInserer(arbre->gauche, motOriginal,motTraduit);
			if ((_hauteur(arbre->gauche) - _hauteur(arbre->droite)) == 2) //Équilibre
			{
				if (arbre->gauche->mot.compare(motOriginal) > 0)
					_zigZigGauche(arbre);
			   else
					_zigZagGauche(arbre);
			} 
			else
			{
				arbre->hauteur = 1 + _maximum(_hauteur(arbre->gauche), _hauteur(arbre->droite));
			}
		}
		else
		{
			_auxInserer(arbre->droite, motOriginal,motTraduit);
			if ((_hauteur(arbre->droite) - _hauteur(arbre->gauche)) == 2)  //Équilibre
			{
				if ( arbre->droite->mot.compare(motOriginal) <= 0) // pour le cas d'un doublon
				{
					_zigZigDroit(arbre);
				} 
				else
				{
					_zigZagDroit(arbre);
				}
			} 
			else
			{
				arbre->hauteur = 1 + _maximum(_hauteur(arbre->droite), _hauteur(arbre->gauche));
			}
		}
	}


	/**
	 * \fn int Dictionnaire:: _hauteur(elem noeud) const
	 * \param[in] noeud : Noeud dans le dictionnaire
	 */
	int Dictionnaire:: _hauteur(elem noeud) const
	{
		if (noeud == 0)
			return -1;
		return noeud->hauteur;
	}


	/**
	 * \fn int Dictionnaire:: _maximum(int ent1, int ent2) const
	 * \param[in] ent1 : premier nombre
	  * \param[in] ent2 : deuxieme nombre
	 */
	int Dictionnaire:: _maximum(int ent1, int ent2) const
	{
		if (ent1 <= ent2)
			return ent2;
		else
			return ent1;
	}


	/**
	 * \fn void Dictionnaire:: _zigZigGauche(elem &K2)
	 * \param[in] K2 : Noeud du dictionnaire
	 */
	void Dictionnaire:: _zigZigGauche(elem &K2)
	{
		elem K1;

		K1 = K2->gauche;
		K2->gauche = K1->droite;
		K1->droite = K2;
		K2->hauteur = 1 + _maximum(_hauteur(K2->gauche), _hauteur(K2->droite));
		K1->hauteur = 1 + _maximum(_hauteur(K1->gauche), K2->hauteur);

		K2 = K1;
	}

	/**
	 * \fn void Dictionnaire:: _zigZigDroit(elem &K2)
	 * \param[in] K2 : Noeud du dictionnaire
	 */
	void Dictionnaire:: _zigZigDroit(elem &K2)
	{
		elem K1;

		K1 = K2->droite;
		K2->droite = K1->gauche;
		K1->gauche = K2;
		K2->hauteur = 1 + _maximum(_hauteur(K2->droite), _hauteur(K2->gauche));
		K1->hauteur = 1 + _maximum(_hauteur(K1->droite), K2->hauteur);
		K2 = K1;
	}

	/**
	 * \fn void Dictionnaire:: _zigZagGauche(elem &K3)
	 * \param[in] K2 : Noeud du dictionnaire
	 */
	void Dictionnaire:: _zigZagGauche(elem &K3)
	{
		_zigZigDroit(K3->gauche);
		_zigZigGauche(K3);
	}

	/**
	 * \fn void Dictionnaire:: _zigZagDroit(elem &K3)
	 * \param[in] K2 : Noeud du dictionnaire
	 */
	void Dictionnaire:: _zigZagDroit(elem & K3)
	{
		_zigZigGauche(K3->droite);
		_zigZigDroit(K3);
	}

		/**
	 * \fn void  Dictionnaire::_auxDetruire(Dictionnaire::elem &t)
	 *
	 * \param[in] t : Le sous-arbre à détruire
	 */
	void  Dictionnaire::_auxDetruire(Dictionnaire::elem &t)
	{
		if (t != 0)
		{
			_auxDetruire(t->gauche);
			_auxDetruire(t->droite);
			delete t;
			cpt--;
			t= 0;
		}
	}

		/**
	 * \fn void Dictionnaire::chargerDictionnaire(std::ifstream &fichier)
	 *
	 * \param[in] fichier : Le fichier à utiliser
	 */
	void Dictionnaire::chargerDictionnaire(std::ifstream &fichier)
	{   
		char ligne[200];  /* pour contenir une ligne lu dans le fichier */  
		char *mot, *motTraduit; /* le mot dans la langue original et sa traduction */
		char *ptr;              /* un pointeur de service */
		int posT, posD; /* pour identifier la position d'un tilde ou d'un double-point(:) */
		bool contexte;  /* indique la présence d'un contexte entre () juste après le mot original */
		char *saveptr;
		/* Vérifier si le fichier est correctement ouvert */
		if (fichier == NULL)
		{   
			return;
		}

		
		/* Lire le fichier et ajouter les mots leur(s) traduction(s) */
		std::cout <<  " Chargement du dictionnaire... " <<  std::endl;
		while (!fichier. eof())
		{
			/* lecture d'une ligne */
			fichier.getline(ligne, 199);
        
			/* Ignorer les lignes d'en-tête */
			if (ligne[0] == '#')
			{
				continue;
			}

			posT = 0;
			posD = 0;

			ptr = strchr(ligne, '~');
			if (ptr != NULL)
			{
				posT = (ptr - ligne) / sizeof(char);
			}

			ptr = strchr(ligne, ':');
			if (ptr != NULL)
			{
				posD = (ptr - ligne) / sizeof(char);
			}

			/* Vérifier s'il y a un contexte entre parenthèses  */
			/* tout de suite après le mot original              */
			contexte = false;
			ptr = strchr(ligne, '\t');
			if (ptr != NULL)
			{
				if (*(ptr + 1) == '(')
				{
					contexte = true;
				}
			}

			/* Aller chercher le mot original */
			mot = strtok(ligne, "\t");
        
			/* Passer le contexte s'il y a lieu */
			if (contexte == true)
			{
				ptr = strtok(NULL, "()");
			}

			/* Traiter les cas comme celui-ci :                                                           */
			/* a	un(e): ~ book = un livre. 2.(instead of number one) ~ year ago; il y a un an[Article] */
			if (posD < posT)
			{
				motTraduit = strtok(NULL, ":");
			}

			else
			{
				/* Traiter les cas comme celui-ci :                 */
				/* abode	of no fixed ~ :sans domicile fixe[Noun] */
				if (posT < posD)
				{
					ptr = strtok(NULL, ":");
					motTraduit = strtok(NULL, "([,;\n");
				}
				else
				{
					/* obtenir la traduction */
					motTraduit = strtok(NULL, "([,;\n");
				}
			}
		    
			std::string sMotTraduit = motTraduit;
			std::string sMot = mot;

			ajouteMot(sMot,sMotTraduit);
			
   
		}
	}


}//Fin du namespace
