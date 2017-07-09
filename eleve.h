#ifndef ELEVE
#define ELEVE

#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdlib.h>

#define Saut_ligne  cout<<""<<endl;
#define NB_NOTE 2

using namespace std;

const string nom_fich("fichier.txt");


void Initialisation();

struct Note {
    float valeur;
    int coef;
};

class Eleve
    {
        private:
            int matricule;
            string nom;
            string adresse;
            Note note[NB_NOTE];
            int rang;
            float moy;
            static int nbreEleves;

        public:

            Eleve();
            int numero();
            string getnom();
            int getrang();
            float moyenne();
            void lire();
            void Init();
            void afficher();

            int getNbreEleves();

            friend int count();
            friend bool ajout(Eleve);
            friend bool rechercher(Eleve& etd);
            friend bool modification(int matricule, Eleve etd);
            friend void classement();
};

void Menu(Eleve e);


#endif // ELEVE

