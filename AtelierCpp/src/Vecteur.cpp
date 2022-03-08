#include "Vecteur.h"

/** \brief Destructeur de la classe Vecteur. Sert à s'assurer que les éléments internes du Vecteur courant sont détruits et la mémoire est libérée.
 * Techniquement, on pourrait laisser ça vide, car la mémoire des éléments internes dans le vector<double> est libérée dans son destructeur.
 * Pour plus de sûreté (et aussi à des fins pédagogiques), nous allons tout de même vider le vector<double>.
 */
Vecteur::~Vecteur()
{

}

/** \brief Constructeur copie de la classe Vecteur.
 * Sert à créer un nouveau Vecteur basé sur un autre déjà existant. Il est important de s'assurer que les valeurs sont copiées et non qu'on pointe vers
 * celles-ci de sorte que modifier un Vecteur modifie l'autre. L'opérateur d'assignation de vector<double> est parfait pour ça. On assigne le nouveau
 * vector<double> à celui de l'objet en cours de création. Il faut aussi s'assurer de mettre à jour la dimension du Vecteur qu'on va créer.
 * \param _autre: Vecteur qu'on copie.
 */
Vecteur::Vecteur(const Vecteur & _autre)
{

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur basé sur un vector<double>. C'est essentiellement les valeurs internes qu'on passe directement en argument. On utilise
 * une nouvelle fois l'opérateur d'assignation du vector<double> pour faire la copie.
 * \param _valeurs: objet vector<double> contenant les valeurs du Vecteur à créer.
 */
Vecteur::Vecteur(const vector<double> & _valeurs){

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur selon une certaine dimension et une certaine valeur initiale. On prend le vecteur interne et on le redimensionne en lui donnant
 * une valeur identique à chaque position.
 * \param _dimension: de type size_t (essentiellement un entier non signé), correspond à la dimension du Vecteur à créer.
 * \param _valeurInitiale: de type double, correspond à la valeur initiale qu'on donne à chaque index du Vecteur.
 */
Vecteur::Vecteur(const size_t _dimension, const double _valeurInitiale){

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur dont les valeurs sont populées selon un point de départ (_start), un point de fin (_end, exclu) et un pas (_step).
 * \param _start: Point de départ.
 * \param _end: Point de fin (exclu).
 * \param _step: Pas.
 */
Vecteur::Vecteur(const double _start, const double _stop, const double _step){

}

/** \brief Opérateur d'assignation. Permet soit de déclarer un nouveau Vecteur comme `Vecteur v2 = v` où `v` est un Vecteur déjà défini, soit d'écraser
 * un Vecteur déjà existant par un autre, comme `v2 = v` où `v2` et `v` sont des Vecteurs déjà créés. La logique derrière le code est la suite:
 * On regarde si le Vecteur à droite du symbole d'assignation est le même (s'ils ont la même adresse mémoire). Si c'est le cas, on retourne directement
 * l'objet courant (le pointeur `this` déréférencé). Si ce n'est pas le cas, on modifie les attributs internes de l'objet courant pour qu'ils concordent
 * avec ceux du Vecteur à droite du symbole d'assignation. On retourne ensuite l'objet courant (le pointeur `this` déréférencé). On retourne par
 * référence, car on ne veut pas copier l'objet courant, on veut retourner la même instance.
 * \param _autre: Vecteur du côté droit du symbole d'assignation.
 * \return *this, le pointeur de l'objet courant déréférencé (retour par référence, mais ça ne change rient dans le code pour l'instant).
 */
Vecteur & Vecteur::operator=(const Vecteur & _autre)
{
    return (*this); // Retour bidon, peut-être?
}

// À vous maintenant d'implémenter le reste! Vous êtes capables!

/** \brief Méthode permttant d'obtenir une représentation en chaîne de caractères du Vecteur courant.
 * On se base sur un stream `ostringstream` qui permet d'ajouter des caractères ou des strings avec l'opérateur `<<`. On peut ensuite accéder à son
 * contenu avec la méthode `str()`.
 * \return Une représentation en chaîne de caractère du Vecteur courant.
 */
string Vecteur::toString(){
    ostringstream streamInfo;
    string separateur = "\t";
    streamInfo << "[";
    for (size_t i = 0; i < dimension; i++){
        streamInfo << vecteurInterne[i];
        if (i != dimension - 1){
            streamInfo << separateur;
        }
    }
    streamInfo << "]";
    return streamInfo.str();
}

/** \brief Méthode permettant d'afficher en console la représentation en chaîne de caractères du Vecteur courant.
 * \return void, rien.
 */
void Vecteur::afficher(){
    cout << this->toString() << endl;
}
