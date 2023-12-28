# Project: Aventure

## Ce que j'ai appris

### Les modèles / template

un **"modèle"** (ou **"template"** en anglais) se réfère à une fonction ou à une classe générique
qui peut être utilisée avec différents types de données sans réécrire le code pour chaque
type spécifique. Les modèles permettent de créer des fonctions et des classes polymorphes,
capables de travailler avec des types variés.

Il existe deux types principaux de modèles en C++ : `les modèles de fonction` et `les modèles de classe` 

#### Modèle de Fonction :

Un modèle de fonction permet de définir une fonction qui prend un ou plusieurs types de paramètres en tant que paramètres génériques.

```cpp
template <typename T>
T addition(const T& a, const T& b) {
    return a + b;
}
```

### Modèle de Classe :

Un modèle de classe permet de définir une classe générique qui peut être instanciée avec différents types.

```cpp
template <typename T>
class Container {
public:
    Container(const T& value) : data(value) {}

    T getData() const {
        return data;
    }

private:
    T data;
};
```

Cette classe Container peut être instanciée avec n'importe quel type, et elle stockera et fournira un accès à une valeur de ce type.

L'utilisation de modèles offre une abstraction puissante et permet de créer du code générique, ce qui rend le code plus réutilisable et flexible. Les modèles sont largement utilisés dans la bibliothèque standard C++ pour des conteneurs tels que `std::vector`, `std::map`, etc.

[En savoir plus](https://learn.microsoft.com/fr-fr/cpp/cpp/templates-cpp?view=msvc-170)

## Ellipses et modèles variadiques

### Ellipses (...)

Les ellipses, souvent appelées "points de suspension", sont utilisées pour déclarer une fonction prenant un nombre variable d'arguments.

```cpp
#include <iostream>
#include <cstdarg>  // Nécessaire pour utiliser va_list

void printNumbers(int num, ...) {
    va_list args;
    va_start(args, num);

    for (int i = 0; i < num; ++i) {
        std::cout << va_arg(args, int) << " ";
    }

    va_end(args);
}

int main() {
    printNumbers(3, 1, 2, 3);

    return 0;
}
```

### Modèles Variadiques :

Les modèles variadiques sont une fonctionnalité plus moderne et puissante introduite avec C++11. Ils permettent de créer des modèles de fonctions ou de classes qui peuvent accepter un nombre variable d'arguments de types différents.


```cpp
#include <iostream>

// Modèle variadique pour imprimer des éléments
template <typename T>
void printElements(const T& element) {
    std::cout << element << " ";
}

template <typename T, typename... Args>
void printElements(const T& first, const Args&... rest) {
    std::cout << first << " ";
    printElements(rest...);
}

int main() {
    printElements(1, 2.5, "hello");

    return 0;
}
```

Dans un modèle variadique, les points de suspensions sont nommés des ***packs de paramètres***.

Dans ces exemples, Arguments est un pack de paramètres. La classe classname peut accepter un nombre variable d’arguments.

```cpp
# La convention: les pts de suspension sont attachés à typename
# ----- pack de paramètres ---|-- nom du paramètre
template<typename... Arguments> class Classname;
# OU
template<typename ...Arguments> class Classname;
# OU
template<typename ... Arguments> class Classname;
```

### Les metafonctions:

Les métafonctions se réfèrent généralement à des fonctionnalités de programmation générique au niveau de la méta-programmation.

La méta-programmation est une technique qui permet d'écrire des programmes qui génèrent du code pendant la compilation plutôt que d'exécuter du code pendant l'exécution. Les métafonctions sont des fonctions utilisées à ce niveau pour effectuer des opérations sur les types au moment de la compilation.

1. std::is_same :
    - Description : Vérifie si deux types sont identiques.
    - Exemple : `std::is_same<T, U>::value` est `true` si `T` est le même type que `U`, sinon `false`.

2. std::enable_if :
    - Description : Utilisé pour conditionner la compilation en fonction d'une condition.
    - Exemple : template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>.
                
3. std::conditional :
    - Description : Sélectionne un type conditionnellement.
    - Exemple : std::conditional<std::is_integral<T>::value, int, double>::type.

4. std::remove_reference :
    -  Description : Supprime la référence d'un type.
    -  Exemple : std::remove_reference<T>::type.

5. std::is_pointer :
    - Description : Vérifie si un type est un pointeur.
    - Exemple : std::is_pointer<T>::value.

6. std::is_array :
    - Description : Vérifie si un type est un tableau.
    - Exemple : std::is_array<T>::value.

7. std::is_convertible :
    - Description : Vérifie si un type est convertible en un autre type.
    - Exemple : `std::is_convertible<T, U>::value`.

8. std::is_integral :
    - Description : Vérifie si un type est de type entier.
    - Exemple : `std::is_integral<T>::value`.

9. std::conjunction_v:
    - Description: est une métafonction introduite dans C++17 qui est utilisée pour vérifier la conjonction (ET logique) d'un ensemble de conditions booléennes sur les types. Elle prend un ensemble de booléens (via std::is_same, std::is_integral, ou d'autres métafonctions qui retournent un bool) comme arguments template et évalue si toutes ces conditions sont vraies (true)
    - Exemple: 

        ```cpp
        #include <iostream>
        #include <type_traits>

        template <typename T>
        struct CheckConditions {
            static constexpr bool value =
                std::conjunction_v<std::is_integral<T>, std::is_signed<T>>;
        };

        int main() {
            std::cout << std::boolalpha;
            std::cout << CheckConditions<int>::value << std::endl;        // true (int est un type intégral et signé)
            std::cout << CheckConditions<unsigned int>::value << std::endl; // false (unsigned int n'est pas signé)
            std::cout << CheckConditions<float>::value << std::endl;       // false (float n'est pas un type intégral)
            
            return 0;
        }
        ```

    - Exemple 2:

        ```cpp
        #include <iostream>
        #include <type_traits>

        template <typename... Ts>
        struct CheckIntegral {
            static constexpr bool value = std::conjunction_v<std::is_integral<Ts>...>;
        };

        int main() {
            std::cout << std::boolalpha;
            std::cout << CheckIntegral<int, short, long>::value << std::endl;  // true (tous sont des types intégraux)
            std::cout << CheckIntegral<int, float, long>::value << std::endl;  // false (float n'est pas un type intégral)

            return 0;
        }
        ```

### Fold expressions

Les `Fold expressions` sont une fonctionnalité introduite dans le standard C++17 qui permet de traiter un pack expansions de manière concise et expressive en déployant (unfolding) ou en dépliant (expanding) une expression sur chaque élément du pack.

Ces expressions facilitent la manipulation de types variadiques et simplifient le code en éliminant la nécessité d'utiliser des techniques plus complexes comme la récursion sur les templates.

On peut donc réaliser une somme simplement en écrivant :

```cpp
template <typename... Ts>
bool allTrue(Ts... values) {
    return (values && ...);
}

bool result = allTrue(true, true, false, true);
// Le résultat sera false, car tous les éléments ne sont pas vrais.
```

Ou encore

```cpp
template <typename... Values>
auto sum(const Values&... values)
{
    return (values + ... + 10);
    // on ajoute 10 à la fin du reducer
}
```
