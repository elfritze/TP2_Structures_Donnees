#include <iostream>
#include <fstream> // pour les fichiers
#include <cstring>
#include <string>

void chargerDictionnaire(std::ifstream &fichierEntree);

#define MAX_MOT 40
#define MAX_PHRASE 100
                   
int main()
{
    char fichier[MAX_PHRASE];

	std::cout << "Entrez le nom du fichier du dictionnaire : ";
	std::cin>>fichier; 

	std::ifstream f(fichier); 
	if(f==NULL) { std::cout<<" \n Erreur dans l'ouverture du fichier \n\n"; return 1;}

    // Chargement du fichier
	chargerDictionnaire(f); 

    return 0;
}


void chargerDictionnaire(std::ifstream &fichier)
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
        mot = strtok_s(ligne, "\t",&saveptr);
        
        /* Passer le contexte s'il y a lieu */
        if (contexte == true)
        {
            ptr = strtok_s(NULL, "()",&saveptr);
        }

        /* Traiter les cas comme celui-ci :                                                           */
        /* a	un(e): ~ book = un livre. 2.(instead of number one) ~ year ago; il y a un an[Article] */
        if (posD < posT)
        {
            motTraduit = strtok_s(NULL, ":",&saveptr);
        }

        else
        {
            /* Traiter les cas comme celui-ci :                 */
            /* abode	of no fixed ~ :sans domicile fixe[Noun] */
            if (posT < posD)
            {
                ptr = strtok_s(NULL, ":",&saveptr);
                motTraduit = strtok_s(NULL, "([,;\n",&saveptr);
            }
            else
            {
                /* obtenir la traduction */
                motTraduit = strtok_s(NULL, "([,;\n",&saveptr);
            }
        }

		std::string sMotTraduit = motTraduit;
		std::string sMot = mot;

		std::cout <<  sMot << " = " << sMotTraduit << std::endl;
   
    }
}
