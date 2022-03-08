#include "Vecteur.h"

/** \brief Destructeur de la classe Vecteur. Sert � s'assurer que les �l�ments internes du Vecteur courant sont d�truits et la m�moire est lib�r�e.
 * Techniquement, on pourrait laisser �a vide, car la m�moire des �l�ments internes dans le vector<double> est lib�r�e dans son destructeur.
 * Pour plus de s�ret� (et aussi � des fins p�dagogiques), nous allons tout de m�me vider le vector<double>.
 */
Vecteur::~Vecteur()
{

}

/** \brief Constructeur copie de la classe Vecteur.
 * Sert � cr�er un nouveau Vecteur bas� sur un autre d�j� existant. Il est important de s'assurer que les valeurs sont copi�es et non qu'on pointe vers
 * celles-ci de sorte que modifier un Vecteur modifie l'autre. L'op�rateur d'assignation de vector<double> est parfait pour �a. On assigne le nouveau
 * vector<double> � celui de l'objet en cours de cr�ation. Il faut aussi s'assurer de mettre � jour la dimension du Vecteur qu'on va cr�er.
 * \param _autre: Vecteur qu'on copie.
 */
Vecteur::Vecteur(const Vecteur & _autre)
{

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur bas� sur un vector<double>. C'est essentiellement les valeurs internes qu'on passe directement en argument. On utilise
 * une nouvelle fois l'op�rateur d'assignation du vector<double> pour faire la copie.
 * \param _valeurs: objet vector<double> contenant les valeurs du Vecteur � cr�er.
 */
Vecteur::Vecteur(const vector<double> & _valeurs){

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur selon une certaine dimension et une certaine valeur initiale. On prend le vecteur interne et on le redimensionne en lui donnant
 * une valeur identique � chaque position.
 * \param _dimension: de type size_t (essentiellement un entier non sign�), correspond � la dimension du Vecteur � cr�er.
 * \param _valeurInitiale: de type double, correspond � la valeur initiale qu'on donne � chaque index du Vecteur.
 */
Vecteur::Vecteur(const size_t _dimension, const double _valeurInitiale){

}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur dont les valeurs sont popul�es selon un point de d�part (_start), un point de fin (_end, exclu) et un pas (_step).
 * \param _start: Point de d�part.
 * \param _end: Point de fin (exclu).
 * \param _step: Pas.
 */
Vecteur::Vecteur(const double _start, const double _stop, const double _step){

}

/** \brief Op�rateur d'assignation. Permet soit de d�clarer un nouveau Vecteur comme `Vecteur v2 = v` o� `v` est un Vecteur d�j� d�fini, soit d'�craser
 * un Vecteur d�j� existant par un autre, comme `v2 = v` o� `v2` et `v` sont des Vecteurs d�j� cr��s. La logique derri�re le code est la suite:
 * On regarde si le Vecteur � droite du symbole d'assignation est le m�me (s'ils ont la m�me adresse m�moire). Si c'est le cas, on retourne directement
 * l'objet courant (le pointeur `this` d�r�f�renc�). Si ce n'est pas le cas, on modifie les attributs internes de l'objet courant pour qu'ils concordent
 * avec ceux du Vecteur � droite du symbole d'assignation. On retourne ensuite l'objet courant (le pointeur `this` d�r�f�renc�). On retourne par
 * r�f�rence, car on ne veut pas copier l'objet courant, on veut retourner la m�me instance.
 * \param _autre: Vecteur du c�t� droit du symbole d'assignation.
 * \return *this, le pointeur de l'objet courant d�r�f�renc� (retour par r�f�rence, mais �a ne change rient dans le code pour l'instant).
 */
Vecteur & Vecteur::operator=(const Vecteur & _autre)
{
    return (*this); // Retour bidon, peut-�tre?
}

// � vous maintenant d'impl�menter le reste! Vous �tes capables!

/** \brief M�thode permttant d'obtenir une repr�sentation en cha�ne de caract�res du Vecteur courant.
 * On se base sur un stream `ostringstream` qui permet d'ajouter des caract�res ou des strings avec l'op�rateur `<<`. On peut ensuite acc�der � son
 * contenu avec la m�thode `str()`.
 * \return Une repr�sentation en cha�ne de caract�re du Vecteur courant.
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

/** \brief M�thode permettant d'afficher en console la repr�sentation en cha�ne de caract�res du Vecteur courant.
 * \return void, rien.
 */
void Vecteur::afficher(){
    cout << this->toString() << endl;
}
