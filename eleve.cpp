#include <iostream>
#include <fstream>
#include <vector>
#include "eleve.h"
# ecrire quelque chose : J ai ecris qlq

using namespace std;

int Eleve::nbreEleves = 0;

int Eleve::numero()
{
    return matricule;
}

void Eleve::lire()
{
    cout<<"Matricule : "; cin>>matricule;
    cout<<"Nom : "; cin>>nom;
    cout<<"Adresse : "; cin>>adresse;
    for(int i=0;i < NB_NOTE;i++)
    {
        cout<<"Entrez la note "<<i+1<<" : ";
        cin >> note[i].valeur;
        cout<<"Entrez le coefficient : ";
        cin >> note[i].coef;

    }
}


void Eleve::afficher()
{
    cout<<"("<<matricule<<","<<nom<<","<<adresse<<")\n";
}

Eleve::Eleve()
{
    matricule = 11;
    nom = "DODO";
    adresse = "france";
    note[0].valeur = 10;
    note[1].valeur = 15;
    note[0].coef = 2;
    note[1].coef = 1;
}

/*
Eleve::Eleve(Eleve const &p)
{

    matricule = p.matricule;
    nom = p.nom;
    adresse = p.adresse;
    for(int i = 0; i < NB_NOTE; i++){
        note[i].valeur = p.note[i].valeur;
        note[i].coef = p.note[i].coef;
    }

}
*/


void Initialisation()
{

    ifstream flux (nom_fich.c_str());
    if(!flux.fail())
    {
        //cout<<"Fichier existant"<<endl;
    }
    else
    {
        cout<<"Creation du fichier en ecriture"<<endl;
        ofstream flux (nom_fich.c_str());
    }
    flux.close();
}

float Eleve::moyenne()
{
    float sommeNote = 0.0;
    int sommeCoef = 0;

    for(int i = 0; i < NB_NOTE; i++){
        sommeNote += (note[i].valeur * note[i].coef);
        sommeCoef += note[i].coef;
    }

    moy = sommeNote/sommeCoef;

    return moy;
}

int Eleve::getNbreEleves()
{
    return nbreEleves;
}

bool ajout(Eleve e)
{

    char reponse;
    do
    {
        system("cls");
        cout<<"                         -------------------"<<endl;
        cout<<"                           AJOUT DES ELEVES"<<endl;
        cout<<"                         -------------------"<<endl;
        Saut_ligne;
        Saut_ligne;
        Saut_ligne;
        e.lire();
        Initialisation();
        ///OUVERTURE DU FICHIER EN ECRITURE EN FIN DE FICHIER
        ofstream fichier(nom_fich.c_str(),ios::app);
        if (fichier){

            fichier << e.matricule << endl;
            fichier << e.nom << endl;
            fichier << e.adresse << endl;
            for(int i = 0; i < NB_NOTE; i++)
            {
                fichier << e.note[i].valeur <<"\t"<< e.note[i].coef << endl;
            }
            //return true

            Eleve::nbreEleves++;

        }
        else
        {
            //return false
        }
        fichier.close();

        cout << "Votre moyenne est : " << e.moyenne() << endl;

        cout<<"Voulez vous  ajouter un autre eleve ?? O/N"<<endl;
        cout<<"Votre reponse :  ";
        cin>>reponse;
    }while(reponse == 'O'||reponse == 'o');
    Menu(e);

}


int count()
{
    int compteur = 0;
    Initialisation();

    ifstream fichier(nom_fich.c_str());
    if(fichier){

        string ligne;
        while(!fichier.eof())  // tant que l'on peut mettre la ligne dans "contenu"
        {
            getline(fichier, ligne);
            if(ligne.length() > 0){

                compteur++;

                getline(fichier, ligne);
                getline(fichier, ligne);
                for(int i = 0; i < NB_NOTE; i++){
                    getline(fichier, ligne);
                }

            }
        }

       fichier.close();
    }

    return compteur;
}


void classement()
{
    //int tronquerFloat = 0
    float sommeNote = 0.0;
    int sommeCoef = 0;

    Initialisation();

    Eleve etd;
    vector<Eleve> eleves;


    ifstream fichier(nom_fich.c_str());
    if(fichier){


        string ligne;
        while(!fichier.eof())  // tant que l'on peut mettre la ligne dans "contenu"
        {
            getline(fichier, ligne);
            if(ligne.length() > 0){

                sommeCoef = 0;
                sommeNote = 0.0;

                etd.matricule = atoi(ligne.c_str());

                getline(fichier, ligne);
                etd.nom = ligne.c_str();

                getline(fichier, ligne);
                etd.adresse = ligne.c_str();

                for(unsigned int j = 0; j < NB_NOTE; j++){
                    fichier >> etd.note[j].valeur;
                    fichier >> etd.note[j].coef;

                    sommeNote += (etd.note[j].valeur * etd.note[j].coef);
                    sommeCoef += etd.note[j].coef;
                }
                etd.moy = sommeNote / sommeCoef;
                etd.rang = 0;

                //tronquerFloat = 100 * etd.moy;
                //etd.moy = (float) tronquerFloat / 100;


                eleves.push_back(etd);
            }
        }

        //Tri des Eleves dans le fichier
        Eleve temp;
        for(unsigned int i = 0; i < eleves.size(); i++){
            for(unsigned int j = 0; j < eleves.size(); j++){
                if(eleves[i].moy > eleves[j].moy){

                    temp.matricule = eleves[i].matricule;
                    temp.nom = eleves[i].nom;
                    temp.adresse = eleves[i].adresse;
                    for(unsigned int k = 0; k < NB_NOTE; k++){
                        temp.note[k].valeur = eleves[i].note[k].valeur;
                        temp.note[k].coef = eleves[i].note[k].coef;
                    }
                    temp.moy = eleves[i].moy;
                    temp.rang = eleves[i].rang;

                    eleves[i].matricule = eleves[j].matricule;
                    eleves[i].nom = eleves[j].nom;
                    eleves[i].adresse = eleves[j].adresse;
                    for(unsigned int k = 0; k < NB_NOTE; k++){
                        eleves[i].note[k].valeur = eleves[j].note[k].valeur;
                        eleves[i].note[k].coef = eleves[j].note[k].coef;
                    }
                    eleves[i].moy = eleves[j].moy;
                    eleves[i].rang = eleves[j].rang;

                    eleves[j].matricule = temp.matricule;
                    eleves[j].nom = temp.nom;
                    eleves[j].adresse = temp.adresse;
                    for(unsigned int k = 0; k < NB_NOTE; k++){
                        eleves[j].note[k].valeur = temp.note[k].valeur;
                        eleves[j].note[k].coef = temp.note[k].coef;
                    }
                    eleves[j].moy = temp.moy;
                    eleves[j].rang = temp.rang;

                }
            }
        }



        //Classement par rang
        eleves[0].rang = 1;

        for(unsigned int i = 1; i < eleves.size(); i++){
            if(eleves[i].moy == eleves[i-1].moy){
                 eleves[i].rang = eleves[i-1].rang;
            }
            else{
                eleves[i].rang = i+1;
            }

        }

        Saut_ligne;
        cout<<"   Le nombre d'elements dans le fichier :   " << count();
        Saut_ligne;
        for(unsigned int i = 0; i < eleves.size(); i++){
            Saut_ligne;
            cout << "Matricule : " << eleves[i].matricule << endl;
            cout << "Nom       : " << eleves[i].nom << endl;
            cout << "Adresse   : " << eleves[i].adresse << endl;
            cout << "Rang      : " << eleves[i].rang << endl;
            cout << "Moyenne   : " << eleves[i].moy << endl;
        }
        Saut_ligne;


       fichier.close();
    }

}

bool rechercher(Eleve& etd)
{
    int mat;
    char reponse;
    do
    {
        system("cls");
        cout<<"                         ----------------------"<<endl;
        cout<<"                           RECHERCHER UN ELEVE"<<endl;
        cout<<"                         ----------------------"<<endl;
        Saut_ligne;
        Saut_ligne;
        Saut_ligne;
    bool trouve = false;
    Initialisation();
    cout<<"Entrer le matricule à rechercher :    ";
    cin>>mat;
    cout<<""<<endl;

    ifstream fichier(nom_fich.c_str());
    if(fichier)
    {
        string ligne;
        while(!fichier.eof())  // tant que l'on peut mettre la ligne dans "contenu"
        {
            getline(fichier, ligne);
            if(ligne.length() > 0 && atoi(ligne.c_str()) == mat){

                etd.matricule = atoi(ligne.c_str());
                getline(fichier, etd.nom);
                getline(fichier, etd.adresse);

                for(int i = 0; i < NB_NOTE; i++){
                    fichier >> etd.note[i].valeur;
                    fichier >> etd.note[i].coef;
                }

                trouve = true;
                break;
            }

        }
        fichier.close();

        if(trouve){
            cout << "trouve" << endl;
            cout << etd.matricule << endl;
            cout << etd.nom << endl;
            cout << etd.adresse << endl;
            for(int i = 0; i < NB_NOTE; i++){
                cout << etd.note[i].valeur << endl;
                cout << etd.note[i].coef << endl;
            }

            return true;
        }
        else{
            cout << "non-trouve" << endl;
            return false;
        }

    }
    cout<<"Voulez vous  ajouter un autre eleve ?? O/N"<<endl;
        cout<<"Votre reponse :  ";
        cin>>reponse;
    }while(reponse == 'O'||reponse == 'o');
    Menu(etd);

}

bool modification(int matricule, Eleve etd)
{
    bool trouve = false;
    Initialisation();

    ifstream fichier(nom_fich.c_str());
    ofstream copie("temp.txt");
    if(fichier)
    {
        string ligne;
        while(!fichier.eof())  // tant que l'on peut mettre la ligne dans "contenu"
        {
            getline(fichier, ligne);
            if(ligne.length() > 0 && atoi(ligne.c_str()) == matricule){

                getline(fichier, ligne);
                //copie << ligne << endl;
                copie << etd.matricule << endl;

                getline(fichier, ligne);
                copie << etd.nom << endl;

                getline(fichier, ligne);
                copie << etd.adresse << endl;

                for(int i = 0; i < NB_NOTE; i++){
                    copie << etd.note[i].valeur <<"\t"<< etd.note[i].coef << endl;
                }

                trouve = true;
            }
            else{
                copie << ligne << endl;
            }

        }
        fichier.close();

        if(trouve){
            cout << "trouve" << endl;
            cout << etd.matricule << endl;
            cout << etd.nom << endl;
            cout << etd.adresse << endl;
            for(int i = 0; i < NB_NOTE; i++){
                cout << etd.note[i].valeur << endl;
                cout << etd.note[i].coef << endl;
            }

            return true;
        }
        else{
            cout << "non-trouve" << endl;
            return false;
        }

    }

}

void Menu(Eleve e)
{
    int rep = 0;
    system("cls");
    system("COLOR F0");
    cout<<"                         -----------------------------"<<endl;
    cout<<"                             GESTION DES ETUDIANTS"<<endl;
    cout<<"                         -----------------------------"<<endl;
    Saut_ligne;
    Saut_ligne;
    Saut_ligne;
    cout<<"                       |          MENU"<<endl;
    Saut_ligne;
    cout<<"                       |      1.   AJOUT"<<endl;
    cout<<"                       |      2.   CONSULTATION"<<endl;
    cout<<"                       |      3.   RECHERCHE"<<endl;
    cout<<"                       |      4.   MODIFICATION"<<endl;
    Saut_ligne;
    Saut_ligne;
    cout<<"            Veuillez selectionner une action en entrant son numero ..."<<endl;
    Saut_ligne;
    cout<<"         Votre choix :   ";
    cin>>rep;
    switch(rep)
    {
        case 1 :
                ajout(e);
            break;
        case 2 :
                classement();
            break;
        case 3 :
                rechercher(e);
            break;
        case 4 :
                modification(12, e);
            break;

        default :

            break;
    }
}



