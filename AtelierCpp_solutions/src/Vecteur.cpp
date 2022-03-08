#include "Vecteur.h"

/** \brief Destructeur de la classe Vecteur. Sert à s'assurer que les éléments internes du Vecteur courant sont détruits et la mémoire est libérée.
 * Techniquement, on pourrait laisser ça vide, car la mémoire des éléments internes dans le vector<double> est libérée dans son destructeur.
 * Pour plus de sûreté (et aussi à des fins pédagogiques), nous allons tout de même vider le vector<double>.
 */
Vecteur::~Vecteur()
{
    vecteurInterne.clear();
}
/** \brief Constructeur copie de la classe Vecteur.
 * Sert à créer un nouveau Vecteur basé sur un autre déjà existant. Il est important de s'assurer que les valeurs sont copiées et non qu'on pointe vers
 * celles-ci de sorte que modifier un Vecteur modifie l'autre. L'opérateur d'assignation de vector<double> est parfait pour ça. On assigne le nouveau
 * vector<double> à celui de l'objet en cours de création. Il faut aussi s'assurer de mettre à jour la dimension du Vecteur qu'on va créer.
 * \param _autre: Vecteur qu'on copie.
 */
Vecteur::Vecteur(const Vecteur & _autre)
{
    vecteurInterne = _autre.vecteurInterne;
    dimension = _autre.dimension;
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur selon une certaine dimension et une certaine valeur initiale. On prend le vecteur interne et on le redimensionne en lui donnant
 * une valeur identique à chaque position.
 * \param _dimension: de type size_t (essentiellement un entier non signé), correspond à la dimension du Vecteur à créer.
 * \param _valeurInitiale: de type double, correspond à la valeur initiale qu'on donne à chaque index du Vecteur.
 */
Vecteur::Vecteur(const size_t _dimension, const double _valeurInitiale){
    vecteurInterne.resize(_dimension, _valeurInitiale);
    dimension = _dimension;
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur basé sur un vector<double>. C'est essentiellement les valeurs internes qu'on passe directement en argument. On utilise
 * une nouvelle fois l'opérateur d'assignation du vector<double> pour faire la copie.
 * \param _valeurs: objet vector<double> contenant les valeurs du Vecteur à créer.
 */
Vecteur::Vecteur(const vector<double> & _valeurs){
    vecteurInterne = _valeurs;
    dimension = _valeurs.size();
}

/** \brief Variante du constructeur de la classe Vecteur.
 * Sert à créer un Vecteur dont les valeurs sont populées selon un point de départ (_start), un point de fin (_end, exclu) et un pas (_step).
 * \param _start: Point de départ.
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
    if (this == & _autre){
        return *this;
    }
    dimension = _autre.dimension;
    vecteurInterne = _autre.vecteurInterne;
    return *this;
}

/** \brief Opérateur [<arguments>] qui permet d'indexer le Vecteur courant (un peu comme en Python avec les listes, etc.). En plus de donner la valeur
 * à un certain index, on peut aussi modifier cette valeur (d'où le retour par référence). À noter que l'index est un entier non signé et qu'il doit être
 * strictement plus petit que la dimension du vecteur (sinon, out of range).
 * \param _index: de type size_t, index de l'élément qu'on veut accéder. Doit être strictement plus petit que la dimension du vecteur, sinon une erreur
 * est lancée.
 * \return la référence vers la valeur contenue à l'index donné. Ainsi, on peut non seulement accéder à cette valeur, mais aussi la modifier.
 */
double & Vecteur::operator[](const size_t _index){
    if (_index >= dimension){
        throw runtime_error("L'index est en-dehors du vecteur.");
    }
    return vecteurInterne[_index];
}

/** \brief Opérateur `+` pour additionner deux Vecteurs ensemble. Pas trop compliqué. On s'assure que les deux Vecteurs soient de même dimension.
 * On se crée un Vecteur de retour (ici, `retour`) de même dimension que ceux impliqués dans l'addition.
 * \param _autre: Vecteur qu'on veut additionner à l'objet courant. Doit être de même dimension que celui courant.
 * \return Le Vecteur contenant l'addition des deux autres. On ne retourne pas par référence, car comme l'objet est créé dans la fonction, dès qu'on
 * sort du scope (i.e. de la fonction), ce Vecteur n'existera plus (à cause du garbage collector). Il faut donc en retourner une copie (pas de &).
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

/** \brief Opérateur `+=`, équivalent à `courant = courant + autre` où `courant` et `autre` sont deux Vecteurs déjà définis.
 * On se crée un Vecteur temporaire qui contient l'addition `(*this) + _autre` et ensuite on affecte à l'objet courant ce Vecteur temporaire.
 * On retourne ensuite (en référence) le pointeur de l'objet courant déréférencé.
 * \param _autre: Vecteur à additionner à l'objet courant. On se base sur l'implémentation de l'opérateur `+` pour ne pas dupliquer du code
 * inutilement. Ainsi, les deux Vecteurs doivent être de même dimension.
 * \return (*this), le pointeur de l'objet courant déréférencé (tout ça en référence, car encore on ne veut pas dupliquer l'objet courant)!
 */
Vecteur & Vecteur::operator+=(const Vecteur & _autre){
    Vecteur retour = (*this) + _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Opérateur `-` pour soustraire deux Vecteurs. Très semblable à l'opérateur `+`, sauf qu'on soustrait au lieu d'additionner les valeurs internes.
 * \param _autre: Vecteur qu'on veut soustraire à celui courant. Doivent être de même dimension.
 * \return Un nouveau Vecteur (retour par copie parce que sinon on perd le Vecteur déclaré à l'interne).
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

/** \brief Opérateur `-=`, équivalent à `courant = courant - autre` où `courant` et `autre` sont deux Vecteurs déjà définis. Logique identique à celle de
 * `+=`, sauf pour la soustraction au lieu de l'addition.
 * \param _autre: Vecteur à soustraire au Vecteur courant. Doivent être de même dimension.
 * \return (*this), le pointeur de l'objet courant déréférencé (tout ça en référence, car encore on ne veut pas dupliquer l'objet courant)!
 */
Vecteur & Vecteur::operator-=(const Vecteur & _autre){
    Vecteur retour = (*this) - _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Opérateur `*`, ici défini comme le produit scalaire entre deux Vecteurs.
 * Pour plus d'informations sur le produit scalaire, voir la méthode `dot(...)`, définie plus bas.
 * \param _autre: Vecteur avec lequel faire le produit scalaire. Doit être de dimension égale à l'objet courant.
 * \return le produit scalaire entre les deux Vecteurs (un double).
 */
double Vecteur::operator*(const Vecteur & _autre){
    return dot(_autre);
}

/** \brief Méthode qui calcule le produit scalaire entre deux Vecteurs de même dimension.
 * L'algorithme est simple: on itère sur les éléments des deux vecteurs et on somme le produit des éléments.
 * \param _autre: Vecteur avec lequel faire le produit scalaire. Doit être de même dimension que l'objet courant.
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

/** \brief Opérateur `+`, mais cette fois-ci défini pour l'addition avec un scalaire.
 * \param _autre: double qu'on veut additionner au Vecteur courant. Peut être aussi d'un autre type comme int (double englobe int).
 * \return Le Vecteur contenant l'addition du Vecteur courant er du scalaire (retour par copie).
 */
Vecteur Vecteur::operator+(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] + _autre;
    }
    return retour;
}

/** \brief Opérateur `+=`, mais version scalaire.
 * Utilise à l'interne l'opérateur `+` (version scalaire bien sûr!) pour faire le calcul et ne pas dupliquer de code inutilement.
 * \param _autre: double qu'on veut additionner au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur courant modifié par l'addition du scalaire.
 */
Vecteur & Vecteur::operator+=(const double _autre){
    Vecteur retour = (*this) + _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Opérateur `+`, mais cette fois-ci défini pour la soustraction avec un scalaire.
 * \param _autre: double qu'on veut soustraire au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur contenant la soustraction du Vecteur courant et du scalaire (retour par copie).
 */
Vecteur Vecteur::operator-(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] - _autre;
    }
    return retour;
}

/** \brief Opérateur `-=`, mais version scalaire.
 * Utilise à l'interne l'opérateur `-` (version scalaire bien sûr!) pour faire le calcul et ne pas dupliquer de code inutilement.
 * \param _autre: double qu'on veut soustraire au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur courant modifié par la soustraction du scalaire.
 */
Vecteur & Vecteur::operator-=(const double _autre){
    Vecteur retour = (*this) - _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Opérateur `*`, soit la multiplication du Vecteur courant par un scalaire.
 * \param _autre: double qu'on veut multiplier au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur contenant le Vecteur courant modifié par le produit avec le scalaire.
 */
Vecteur Vecteur::operator*(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] * _autre;
    }
    return retour;
}

/** \brief Opérateur `*=`.
 * \param _autre: double qu'on veut multiplier au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur courant modifié par le produit avec le scalaire.
 */
Vecteur & Vecteur::operator*=(const double _autre){
    Vecteur retour = (*this) * _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Opérateur `/`, soit la division du Vecteur courant par un scalaire.
 * \param _autre: double qu'on veut diviser au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur contenant le Vecteur courant modifié par la division avec le scalaire.
 */
Vecteur Vecteur::operator/(const double _autre){
    Vecteur retour(dimension, 0);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = vecteurInterne[i] / _autre;
    }
    return retour;
}

/** \brief Opérateur `/=`.
 * \param _autre: double qu'on veut diviser au Vecteur courant. Peut être aussi d'un autre type comme int.
 * \return Le Vecteur courant modifié par la division avec le scalaire.
 */
Vecteur & Vecteur::operator/=(const double _autre){
    Vecteur retour = (*this) / _autre;
    (*this) = retour;
    return (*this);
}

/** \brief Méthode de produit vectoriel (cross product en anglais). Le Vecteur courant et l'autre doivent être en 3D. Basé sur la méthode du déterminant:
 *         | i   j   k  |
 * v x w = |v_1 v_2 v_3 |
 *         |w_1 w_2 w_3 |
 * \param _autre: Vecteur avec lequel faire le produit vectoriel. Doit être de dimension 3, comme le Vecteur courant.
 * \return Vecteur (copie) contenant les éléments du produit vectoriel.
 *
 */
Vecteur Vecteur::cross(const Vecteur & _autre){
    if (dimension != 3 || _autre.dimension != 3){
        throw runtime_error("Le produit vectoriel est défini seulement pour les vecteurs 3D.");
    }
    Vecteur retour(3, 0);
    retour.vecteurInterne[0] = (vecteurInterne[1] * _autre.vecteurInterne[2]) - (vecteurInterne[2] * _autre.vecteurInterne[1]);
    retour.vecteurInterne[1] = (vecteurInterne[2] * _autre.vecteurInterne[0]) - (vecteurInterne[0] * _autre.vecteurInterne[2]);
    retour.vecteurInterne[2] = (vecteurInterne[0] * _autre.vecteurInterne[1]) - (vecteurInterne[1] * _autre.vecteurInterne[0]);
    return retour;

}


/** \brief Méthode permettant de calculer la puissance des éléments du Vecteur courant. Chaque élément est évalué à une certaine puissance.
 * \param _puissance: double. Puissance à laquelle on veut élever les éléments du Vecteur courant.
 * \return Un Vecteur (copie) dont les éléments sont ceux du Vecteur courant élevés à une certaine puissance.
 */
Vecteur Vecteur::exposant(const double _puissance){
    Vecteur retour(*this);
    for (size_t i = 0; i < dimension; i++){
        retour.vecteurInterne[i] = pow(vecteurInterne[i], _puissance);
    }
    return retour;
}

/** \brief Méthode permettant de calculer la somme des éléments d'un Vecteur.
 * \return La somme des élément du Vecteur courant (double).
 */
double Vecteur::somme(){
    double retour = 0;
    for (size_t i = 0; i < dimension; i++){
        retour += vecteurInterne[i];
    }
    return retour;
}

/** \brief Méthode permettant de calculer le produit des éléments d'un Vecteur.
 * \return Le produit des éléments du Vecteur courant (double)
 */
double Vecteur::prod(){
    double retour = 1;
    for (size_t i = 0; i < dimension; i++){
        retour *= vecteurInterne[i];
    }
    return retour;
}

/** \brief Méthode permettant de calculer la norme du Vecteur courant.
 * \return La norme du Vecteur courant (double).
 *
 */
double Vecteur::norme(){
    return sqrt(dot(*this));
}

/** \brief Méthode permettant d'accéder à l'attribut privé `dimension`.
 * \return La dimension du Vecteur courant.
 */
size_t Vecteur::getDimension(){
    return dimension;
}

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
