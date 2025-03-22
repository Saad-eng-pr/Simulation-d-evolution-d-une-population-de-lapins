#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


// ----------------------------------------------------------------------------------------------------- // 
// RabbitEvolPopulation: Calcule la séquence de population des couples de lapins selon Fibonacci         // 
//                                                                                                       // 
// Paramètres: le parametre inMois est le nombre de mois de la simulation                                // 
//                                                                                                       // 
// Retour: le nombre de couples de lapins apres la simulation                                            // 
//                                                                                                       // 
// Exceptions: invalid_argument si le nombre de mois est inferieur a 0                                   // 
// ----------------------------------------------------------------------------------------------------- //
void SimpleRabbitPopulationEvol(int inMois) {
    if (inMois < 1) 
        throw invalid_argument("Le nombre de mois doit etre superieur a 0.");

    int YoungCouple = 1,
        AdultCouple = 0;  

    cout << "Mois 0 : Jeunes = " << YoungCouple << ", Adultes = " << AdultCouple << endl;

    for (int month = 1; month <= inMois; ++month) {
        int new_young = AdultCouple;
        AdultCouple += YoungCouple;
        YoungCouple = new_young;

        cout << "Mois " << month << " : Jeunes = " << YoungCouple << ", Adultes = " << AdultCouple << endl;
    }
    cout << "Total de couples de lapins apres " << inMois << " Mois : " << (YoungCouple + AdultCouple) << endl;
}



int main() {
    int inMois;
    cout << "Entrez le nombre de Mois pour la simulation : ";
    cin >> inMois;

    SimpleRabbitPopulationEvol(inMois);

    return 0;
}

