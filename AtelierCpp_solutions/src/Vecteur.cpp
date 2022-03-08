#include "Vecteur.h"

/** \brief Destructeur de la classe Vecteur. Sert � s'assurer que les �l�ments internes du Vecteur courant sont d�truits et la m�moire est lib�r�e.
 * Techniquement, on pourrait laisser �a vide, car la m�moire des �l�ments internes dans le vector<double> est lib�r�e dans son destructeur.
 * Pour plus de s�ret� (et aussi � des fins p�dagogiques), nous allons tout de m�me vider le vector<double>.
 */
Vecteur::~Vecteur()
{
    vecteurInterne.clear();
}
/** \brief Constructeur copie de la classe Vecteur.
 * Sert � cr�er un nouveau Vecteur bas� sur un autre d�j� existant. Il est important de s'assurer que les valeurs sont copi�es et non qu'on pointe vers
 * celles-ci de sorte que modifier un Vecteur modifie l'autre. L'op�rateur d'assignation de vector<double> est parfait pour �a. On assigne le nouveau
 * vector<double> � celui de l'objet en cours de cr�ation. Il faut aussi s'assurer de mettre � jour la dimension du Vecteur qu'on va cr�er.
 * \param _autre: Vecteur qu'on copie.
 */
Vecteur::Vecteur(const Vecteur & _autre)
{
    vecteurInterne = _autre.vecteurInterne;
    dimension = _autre.dimension;
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur selon une certaine dimension et une certaine valeur initiale. On prend le vecteur interne et on le redimensionne en lui donnant
 * une valeur identique � chaque position.
 * \param _dimension: de type size_t (essentiellement un entier non sign�), correspond � la dimension du Vecteur � cr�er.
 * \param _valeurInitiale: de type double, correspond � la valeur initiale qu'on donne � chaque index du Vecteur.
 */
Vecteur::Vecteur(const size_t _dimension, const double _valeurInitiale){
    vecteurInterne.resize(_dimension, _valeurInitiale);
    dimension = _dimension;
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur bas� sur un vector<double>. C'est essentiellement les valeurs internes qu'on passe directement en argument. On utilise
 * une nouvelle fois l'op�rateur d'assignation du vector<double> pour faire la copie.
 * \param _valeurs: objet vector<double> contenant les valeurs du Vecteur � cr�er.
 */
Vecteur::Vecteur(const vector<double> & _valeurs){
    vecteurInterne = _valeurs;
    dimension = _valeurs.size();
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert � cr�er un Vecteur dont les valeurs sont popul�es selon un point de d�part (_start), un point de fin (_end, exclu) et un pas (_step).
 * \param _start: Point de d�part.
 * \param _end: Point de fin (exclu).
 * \param _step: Pas.
 */
Vecteur::Vecteur(const double _start, const double _stop, const double _step){
    vector<double> interne;
    for (double i = _start; i < _stop; i += _step){
        interne.push_back(i);
    }
    vecteurInterne = interne;
    dimension = vecteurInterne.size();
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
    if (this == & _autre){
        return *this;
    }
    dimension = _autre.dimension;
    vecteurInterne = _autre.vecteurInterne;
    return *this;
}

/** \brief Op�rateur [<arguments>] qui permet d'indexer le Vecteur courant (un peu comme en Python avec les listes, etc.). En plus de donner la valeur
 * � un certain index, on peut aussi modifier cette valeur (d'o� le retour par r�f�rence). � noter que l'index est un entier non sign� et qu'il doit �tre
 * strictement plus petit que la dimension du vecteur (sinon, out of range).
 * \param _index: de type size_t, index de l'�l�ment qu'on veut acc�der. Doit �tre strictement plus petit que la dimension du vecteur, sinon une erreur
 * est lanc�e.
 * \return la r�f�rence vers la valeur contenue � l'index donn�. Ainsi, on peut non seulement acc�der � cette valeur, mais aussi la modifier.
 */
double & Vecteur::operator[](const size_t _index){
    if (_index >= dimension){
        throw runtime_error("L'index est en-dehors du vecteur.");
    }
    return vecteurInterne[_index];
}

/** \brief Op�rateur `+` pour additionner deux Vecteurs ensemble. Pas trop compliqu�. On s'assure que les deux Vecteurs soient de m�me dimension.
 * On se cr�e un Vecteur de retour (ici, `retour`) de m�me dimension que ceux impliqu�s dans l'addition.
 * \param _autre: Vecteur qu'on veut additionner � l'objet courant. Doit �tre de m�me dimension que celui courant.
 * \return Le Vecteur contenant l'addition des deux autres. On ne retourne pas par r�f�rence, car comme l'objet est cr�� dans la fonction, d�s qu'on
 * sort du scope (i.e. de la fonction), ce Vecteur n'existera plus (� cause du garbage collector). Il faut donc en retourner une copie (pas de &).
 */
Vecteur Vecteur::operator+(const Vecteur & _autre){
    if (dimension != _autre.dimension){
        throw runtime_error("Les dimensions ne concordent pas pour l'addition vectorielle.");
    }
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] + _autre.vecteurInterne[i];
    }
    return retour;
}

/** \brief Op�rateur `+=`, �quivalent � `courant = courant + autre` o� `courant` et `autre` sont deux Vecteurs d�j� d�finis.
 * On se cr�e un Vecteur temporaire qui contient l'addition `(*this) + _autre` et ensuite on affecte � l'objet courant ce Vecteur temporaire.
 * On retourne ensuite (en r�f�rence) le pointeur de l'objet courant d�r�f�renc�.
 * \param _autre: Vecteur � additionner � l'objet courant. On se base sur l'impl�mentation de l'op�rateur `+` pour ne pas dupliquer du code
 * inutilement. Ainsi, les deux Vecteurs doivent �tre de m�me dimension.
 * \return (*this), le pointeur de l'objet courant d�r�f�renc� (tout �a en r�f�rence, car encore on ne veut pas dupliquer l'objet courant)!
 */
Vecteur & Vecteur::operator+=(const Vecteur & _autre){
    Vecteur retour = (*this) + _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Op�rateur `-` pour soustraire deux Vecteurs. Tr�s semblable � l'op�rateur `+`, sauf qu'on soustrait au lieu d'additionner les valeurs internes.
 * \param _autre: Vecteur qu'on veut soustraire � celui courant. Doivent �tre de m�me dimension.
 * \return Un nouveau Vecteur (retour par copie parce que sinon on perd le Vecteur d�clar� � l'interne).
 */
Vecteur Vecteur::operator-(const Vecteur & _autre){
    if (dimension != _autre.dimension){
        throw runtime_error("Les dimensions ne concordent pas pour l'addition vectorielle.");
    }
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] - _autre.vecteurInterne[i];
    }
    return retour;
}

/** \brief Op�rateur `-=`, �quivalent � `courant = courant - autre` o� `courant` et `autre` sont deux Vecteurs d�j� d�finis. Logique identique � celle de
 * `+=`, sauf pour la soustraction au lieu de l'addition.
 * \param _autre: Vecteur � soustraire au Vecteur courant. Doivent �tre de m�me dimension.
 * \return (*this), le pointeur de l'objet courant d�r�f�renc� (tout �a en r�f�rence, car encore on ne veut pas dupliquer l'objet courant)!
 */
Vecteur & Vecteur::operator-=(const Vecteur & _autre){
    Vecteur retour = (*this) - _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Op�rateur `*`, ici d�fini comme le produit scalaire entre deux Vecteurs.
 * Pour plus d'informations sur le produit scalaire, voir la m�thode `dot(...)`, d�finie plus bas.
 * \param _autre: Vecteur avec lequel faire le produit scalaire. Doit �tre de dimension �gale � l'objet courant.
 * \return le produit scalaire entre les deux Vecteurs (un double).
 */
double Vecteur::operator*(const Vecteur & _autre){
    return dot(_autre);
}

/** \brief M�thode qui calcule le produit scalaire entre deux Vecteurs de m�me dimension.
 * L'algorithme est simple: on it�re sur les �l�ments des deux vecteurs et on somme le produit des �l�ments.
 * \param _autre: Vecteur avec lequel faire le produit scalaire. Doit �tre de m�me dimension que l'objet courant.
 * \return le produit scalaire entre les deux Vecteurs (un double).
 */
double Vecteur::dot(const Vecteur & _autre){
    if (dimension != _autre.dimension){
        throw runtime_error("Les dimensions ne concordent pas pour le produit scalaire.");
    }
    double retour = 0;
    for (size_t i = 0; i < dimension; i++){
        retour += vecteurInterne[i] * _autre.vecteurInterne[i];
    }
    return retour;
}

/** \brief Op�rateur `+`, mais cette fois-ci d�fini pour l'addition avec un scalaire.
 * \param _autre: double qu'on veut additionner au Vecteur courant. Peut �tre aussi d'un autre type comme int (double englobe int).
 * \return Le Vecteur contenant l'addition du Vecteur courant er du scalaire (retour par copie).
 */
Vecteur Vecteur::operator+(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] + _autre;
    }
    return retour;
}

/** \brief Op�rateur `+=`, mais version scalaire.
 * Utilise � l'interne l'op�rateur `+` (version scalaire bien s�r!) pour faire le calcul et ne pas dupliquer de code inutilement.
 * \param _autre: double qu'on veut additionner au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur courant modifi� par l'addition du scalaire.
 */
Vecteur & Vecteur::operator+=(const double _autre){
    Vecteur retour = (*this) + _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Op�rateur `+`, mais cette fois-ci d�fini pour la soustraction avec un scalaire.
 * \param _autre: double qu'on veut soustraire au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur contenant la soustraction du Vecteur courant et du scalaire (retour par copie).
 */
Vecteur Vecteur::operator-(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] - _autre;
    }
    return retour;
}

/** \brief Op�rateur `-=`, mais version scalaire.
 * Utilise � l'interne l'op�rateur `-` (version scalaire bien s�r!) pour faire le calcul et ne pas dupliquer de code inutilement.
 * \param _autre: double qu'on veut soustraire au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur courant modifi� par la soustraction du scalaire.
 */
Vecteur & Vecteur::operator-=(const double _autre){
    Vecteur retour = (*this) - _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Op�rateur `*`, soit la multiplication du Vecteur courant par un scalaire.
 * \param _autre: double qu'on veut multiplier au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur contenant le Vecteur courant modifi� par le produit avec le scalaire.
 */
Vecteur Vecteur::operator*(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] * _autre;
    }
    return retour;
}

/** \brief Op�rateur `*=`.
 * \param _autre: double qu'on veut multiplier au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur courant modifi� par le produit avec le scalaire.
 */
Vecteur & Vecteur::operator*=(const double _autre){
    Vecteur retour = (*this) * _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Op�rateur `/`, soit la division du Vecteur courant par un scalaire.
 * \param _autre: double qu'on veut diviser au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur contenant le Vecteur courant modifi� par la division avec le scalaire.
 */
Vecteur Vecteur::operator/(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] / _autre;
    }
    return retour;
}

/** \brief Op�rateur `/=`.
 * \param _autre: double qu'on veut diviser au Vecteur courant. Peut �tre aussi d'un autre type comme int.
 * \return Le Vecteur courant modifi� par la division avec le scalaire.
 */
Vecteur & Vecteur::operator/=(const double _autre){
    Vecteur retour = (*this) / _autre;
    (*this) = retour;
    return (*this);
}

/** \brief M�thode de produit vectoriel (cross product en anglais). Le Vecteur courant et l'autre doivent �tre en 3D. Bas� sur la m�thode du d�terminant:
 *         | i   j   k  |
 * v x w = |v_1 v_2 v_3 |
 *         |w_1 w_2 w_3 |
 * \param _autre: Vecteur avec lequel faire le produit vectoriel. Doit �tre de dimension 3, comme le Vecteur courant.
 * \return Vecteur (copie) contenant les �l�ments du produit vectoriel.
 *
 */
Vecteur Vecteur::cross(const Vecteur & _autre){
    if (dimension != 3 || _autre.dimension != 3){
        throw runtime_error("Le produit vectoriel est d�fini seulement pour les vecteurs 3D.");
    }
    Vecteur retour(3, 0);
    retour.vecteurInterne[0] = (vecteurInterne[1] * _autre.vecteurInterne[2]) - (vecteurInterne[2] * _autre.vecteurInterne[1]);
    retour.vecteurInterne[1] = (vecteurInterne[2] * _autre.vecteurInterne[0]) - (vecteurInterne[0] * _autre.vecteurInterne[2]);
    retour.vecteurInterne[2] = (vecteurInterne[0] * _autre.vecteurInterne[1]) - (vecteurInterne[1] * _autre.vecteurInterne[0]);
    return retour;

}


/** \brief M�thode permettant de calculer la puissance des �l�ments du Vecteur courant. Chaque �l�ment est �valu� � une certaine puissance.
 * \param _puissance: double. Puissance � laquelle on veut �lever les �l�ments du Vecteur courant.
 * \return Un Vecteur (copie) dont les �l�ments sont ceux du Vecteur courant �lev�s � une certaine puissance.
 */
Vecteur Vecteur::exposant(const double _puissance){
    Vecteur retour(*this);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = pow(vecteurInterne[i], _puissance);
    }
    return retour;
}

/** \brief M�thode permettant de calculer la somme des �l�ments d'un Vecteur.
 * \return La somme des �l�ment du Vecteur courant (double).
 */
double Vecteur::somme(){
    double retour = 0;
    for (size_t i = 0; i < dimension; i++){
        retour += vecteurInterne[i];
    }
    return retour;
}

/** \brief M�thode permettant de calculer le produit des �l�ments d'un Vecteur.
 * \return Le produit des �l�ments du Vecteur courant (double)
 */
double Vecteur::prod(){
    double retour = 1;
    for (size_t i = 0; i < dimension; i++){
        retour *= vecteurInterne[i];
    }
    return retour;
}

/** \brief M�thode permettant de calculer la norme du Vecteur courant.
 * \return La norme du Vecteur courant (double).
 *
 */
double Vecteur::norme(){
    return sqrt(dot(*this));
}

/** \brief M�thode permettant d'acc�der � l'attribut priv� `dimension`.
 * \return La dimension du Vecteur courant.
 */
size_t Vecteur::getDimension(){
    return dimension;
}

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
