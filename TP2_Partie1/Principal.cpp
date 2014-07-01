/**
 * \file Principal.cpp
 * \brief Fichier test pour le dictionnaire
 * \author Étudiant 1, étudiant 2
 * \version 0.1
 * \date juillet 2014
 *
 */

#include <iostream>
#include <iomanip>
using namespace std;

#include "Dictionnaire.h"
using namespace TP2P1;

	#define MAX_MOT 40
	#define MAX_PHRASE 100



void TraiterMot(Dictionnaire & dico,std::string & token,std::vector<std::string> & phrase);
/**
 * \fn int main()
 * \brief Fonction principale pour tester le dictionnaire.
 *
 * \return 0 - Arrêt normal du programme.
 */
int main()
{
	std::ifstream in;
	
	
	char fichier[MAX_PHRASE];
	//Ouverture du dictionnaire
	std::cout << "Entrez le nom du fichier du dictionnaire : ";
	std::cin>>fichier; 
	
	in.open(fichier);
	if(in.fail()) { std::cout<<" \n Erreur dans l'ouverture du fichier \n\n";  return 1;}
	Dictionnaire dico = Dictionnaire(in);

	
	//Interface principale
	while(true){
		string comm;
		std::string line;
		std::cout<<"\n\n\n\n\n";
		std::cout << "0 : Quitter "<<std::endl;
		std::cout << "1 : Traduire une phrase "<<std::endl;
	

		cin>>comm;
		
		if(comm == "0")
		{
			return 0;
		}
		else if (comm == "1") {
				string phrase;
				std::vector<std::string> phraseTraduite;
				string delimiter = " ";

				std::cout<<"\n\n Entrez une phrase à traduire : ";
				cin.ignore();
				getline(std::cin, phrase);

				size_t pos = 0;
				std::string token;
				 //On analyse chaque mot
				while ((pos = phrase.find(delimiter)) != std::string::npos) {
					token = phrase.substr(0, pos);

					TraiterMot(dico,token,phraseTraduite);
						
					phrase.erase(0, pos + delimiter.length());
				}
				//Dernier mot
				TraiterMot(dico,phrase,phraseTraduite);
				std::cout<<"\n\n Voici le texte traduit en français : ";
				for(int i = 0; i < phraseTraduite.size();i++){
					std::cout<<phraseTraduite.at(i)<<" ";
				}
					
		}
		else{
			std::cout<<"\n\n Commande invalide...";
		}
		
		
	}

	return 0;
}

/**
 * \fn void TraiterMot(Dictionnaire & dico,std::string & token,std::vector<std::string> & phrase)
 * \param[in] dico : Dictionnaire utilisé
 * \param[in] token : mot qui sera traité
  * \param[in] phrase : phrase finale
 */
void TraiterMot(Dictionnaire & dico,std::string & token,std::vector<std::string> & phrase)
{
	
	int comm;
	//Si le mot n'est pas dans le dictionnaire
	if(!dico.appartient(token)){
		bool valid = false;
		std::vector<std::string> corrections = dico.suggereCorrections(token);
		std::cout<<"\n\n Mot introuvable : "<<token<<std::endl;
		std::cout<<"\n\n Veuillez choisir parmi ces "<<corrections.size()<<" mots "<<std::endl;
		for(int i =0;i < corrections.size();i++){
			std::cout<<"\n"<<i<<". "<<corrections.at(i)<<" : "<<std::endl;
		}
		while(!valid){
			try {
				valid = true;
				std::cout<<"\nVotre choix : ";
				std::cin>>comm;
				token = corrections.at(comm);
				 
			}
			catch (...)  { cout << "Commande invalide..."; valid = false;cin.clear();
				std::cin.ignore(32999,'\n');}

		}
		 
		
	}
	//On s'assure que le mot est dans le dictionnaire
	if(dico.appartient(token)){
		bool valid = false;			 
		std::cout<<"\n\n Plusieurs actions sont possibles pour le mot "<<token<<" : "<<std::endl;
		std::vector<std::string> traductions = dico.traduit(token);
		for(int i =0;i < traductions.size();i++){
			std::cout<<"\n"<<i<<". "<<traductions.at(i)<<" : "<<std::endl;
		}
		while(!valid){
			try
			{
				valid = true;
				std::cout<<"\nVotre choix : ";
				std::cin>>comm;
				token = traductions.at(comm); 

			}
			catch (...) { cout << "Commande invalide..."; valid = false;cin.clear();
				std::cin.ignore(32999,'\n');}
		}
		//On ajoute la traduction choisie a la liste
		phrase.push_back(traductions.at(comm));
	}
}
