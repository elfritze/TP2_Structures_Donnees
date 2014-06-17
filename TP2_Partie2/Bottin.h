/**
 * \file Bottin.h
 * \brief Classe d�finissant un bottin t�l�phonique.
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
	* \brief classe repr�sentant un bottin
	*
	*/
	class Bottin
	{
		public:

			// � compl�ter (voir l'�nonc� du TP Partie2)

		private:
			
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

					Entree(const std::string& n, const std::string & p,  const std::string & t, const std::string & f, const std::string & c )
					 : nom(n), prenom(p), tel(t), fax(f), courriel(c) { }

			};

			std::vector<Entree> tabEntree; // Le tableau des entr�es

			//Vous devez ajouter d'autres param�tres et/ou classes priv�s pour compl�ter le mod�le propos� dans l'�nonc�
			//Vous pouvez ajouter �galement des m�thodes priv�es.
			 
	};

}

#endif /* BOTTIN__H */