//Devoir 2 INFO3201
// Alexandre Williams
// A00211478
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

 //encoder en Hamming une séquence de données binaire
vector<int> genererCodeHamming(const vector<int>& donnees) {
    cout << "Code original : ";
    for (int i = 0; i < donnees.size(); i++) {
        cout << donnees[i];
    }
    cout << endl;
    int k = 0;//nombre de bits de parite
    while (pow(2, k) < donnees.size() + k + 1) {
        k++;
    }
    int taillecode = k + donnees.size();
    vector<int> code(taillecode, 0);
    int j = 0;
    int n = 0;

    for (int i = 0; i < taillecode; i++) {
        if (i + 1 == pow(2, j)) {
            code[i] = -1;  //-1 valeur initial pour les bits de parite
            j++;
        }
        else {
            code[i] = donnees[n];
            n++;
        }
    }

    //Code pour placer les elements du mot par indices inverses
        //int n = donnees.size()-1;
        //for (int i = 0; i < taillecode; i++) {
        //    if (i + 1 == pow(2, j)) {
        //        code[i] = -1;  //-1 valeur initial pour les bits de parite
        //        j++;
        //    }
        //    else {
        //        code[i] = donnees[n];
        //        n--;
        //    }
        //}


    for (int position = 1; position <= taillecode; position *= 2) {
        int parite = 0;
        //calcul de parite
        for (int i = position - 1; i < taillecode; i += position * 2) {
            for (int j = 0; j < position && i + j < taillecode; j++) {
                int check = i + j;
                if (code[check] == 1) {
                    parite = parite + 1;
                }
            }
        }
        if (parite % 2 == 0) {
            code[position - 1] = 0;
        }
        else if (parite % 2 != 0) {
            code[position - 1] = 1;
        }
    }
    return code;
}
vector<int> introduireErreur(vector<int>& code, int indice) {
    // Simuler une modification de bit en inversant la valeur d'un bit
    if (code[indice] == 1)
    {
        code[indice] = 0;
    }
    else { code[indice] = 1; }
    return code;
}
//Fonction pour détecter et corriger l'erreur
void detecterErreur(vector<int> code1, vector<int> code2)
{
    for (int i = 0; i < code2.size(); i++)
    {
        if (code1[i] != code2[i])
        {
            cout << "Code Recu : ";
            for (int j = 0; j < code2.size(); j++)
            {
                cout << code2[j];
            }
            cout << endl;
            cout << "Detection derreur à l'indice  : " << i << endl;
            if (code2[i] == 1)
            {
                code2[i] = 0;
            }
            else { code2[i] = 1; }
        }
    }
    cout << "code corrigé : ";
    for (int j = 0; j < code2.size(); j++)
    {
        cout << code2[j];
    }
    cout << endl << endl;
}
int main() {
    ifstream fichier("INFO3201-DEV2-entree.txt");
    if (!fichier) {
        throw("Erreur lors de l'ouverture du fichier");
    }
    string sequence;
    while (getline(fichier, sequence)) {
        if (!sequence.empty()) {
            vector<int> donnees;
            for (int i = 0; i < sequence.size(); i++) {
                int bit = sequence[i] - '0';
                donnees.push_back(bit);
            }
            vector<int> codeHamming = genererCodeHamming(donnees);
            cout << "Code de hamming : ";
            for (int bit : codeHamming) {
                cout << bit;
                
            }
            //si on place le mot par indice inverse
            /*for (int i = codeHamming.size() - 1; i >= 0; i--)
            {
                cout << codeHamming[i];
            }*/
            cout << endl;
            vector<int> codeRecu = codeHamming;
            int indice = 4;
            codeRecu = introduireErreur(codeRecu, indice);
            detecterErreur(codeHamming, codeRecu);
        }
    }
    fichier.close();

    return 0;
}