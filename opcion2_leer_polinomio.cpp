#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

vector<int> ingresarPolinomio() {
    vector<int> polinomio;
    string input;
    cout << "Ingrese el polinomio (en formato ax^2 + bx + c): ";
    getline(cin, input);
    stringstream ss(input);
    int coeficiente, grado;
    while (ss >> coeficiente) {
        polinomio.push_back(coeficiente);
        ss.ignore(3, 'x');
        ss >> grado;
        polinomio.push_back(grado);
        ss.ignore(3, '+');
    }
    return polinomio;
}


