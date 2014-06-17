/**
 * \file Bottin.h
 * \brief Classe définissant un bottin téléphonique.
 * \author Admin
 * \version 0.1
 * \date juin 2014
 * 
 */

#ifndef BOTTIN__H
#define BOTTIN__H

#include <stdexcept>
#include <iostream>
#include <fstream> // pour les fichiers
#include <string>
#include <vector>

namespace TP2P2
{
	/** 
	* \class Bottin
	*
	* \brief classe représentant un bottin
	*
	*/
	class Bottin
	{
		public:

			// À compléter (voir l'énoncé du TP Partie2)

		private:
			
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

					Entree(const std::string& n, const std::string & p,  const std::string & t, const std::string & f, const std::string & c )
					 : nom(n), prenom(p), tel(t), fax(f), courriel(c) { }

			};

			std::vector<Entree> tabEntree; // Le tableau des entrées

			//Vous devez ajouter d'autres paramètres et/ou classes privés pour compléter le modèle proposé dans l'énoncé
			//Vous pouvez ajouter également des méthodes privées.
			 
	};

}

#endif /* BOTTIN__H */