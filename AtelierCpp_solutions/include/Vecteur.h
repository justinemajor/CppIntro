#ifndef VECTEUR_H
#define VECTEUR_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

class Vecteur
{
    public:
        // Constructeurs + destructeur + assignation + accesseur
        virtual ~Vecteur();
        Vecteur(const Vecteur & _autre);
        Vecteur(const vector<double> & _valeurs);
        Vecteur(const size_t _dimension, const double _valeurInitiale);
        Vecteur(const double _start, const double _stop, const double _step);
        Vecteur& operator=(const Vecteur & _autre);
        double & operator[](const size_t _index);

        // Mathématiques vecteur avec vecteur
        Vecteur operator+(const Vecteur & _autre);
        Vecteur & operator+=(const Vecteur & _autre);
        Vecteur operator-(const Vecteur & _autre);
        Vecteur & operator-=(const Vecteur & _autre);
        double operator*(const Vecteur & _autre);

        // Mathématiques vecteur avec scalaire
        Vecteur operator+(const double _autre);
        Vecteur & operator+=(const double _autre);
        Vecteur operator-(const double _autre);
        Vecteur & operator-=(const double _autre);
        Vecteur operator*(const double _autre);
        Vecteur & operator*=(const double _autre);
        Vecteur operator/(const double _autre);
        Vecteur & operator/=(const double _autre);

        // Mathématiques autres
        double dot(const Vecteur & _autre);
        Vecteur cross(const Vecteur & _autre);
        Vecteur exposant(const double _puissance);
        double somme();
        double prod();
        double norme();

        // Méthodes utilitaires
        size_t getDimension();
        string toString();
        void afficher();

    protected:

    private:
        vector<double> vecteurInterne;
        size_t dimension;
};

#endif // VECTEUR_H
