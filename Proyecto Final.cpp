#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

vector<string> leerPolinomio(string polinomio){
    cout << "Introduce el polinomio (formato: ax^n+bx+c):" << polinomio << ": ";
    string cadena;
    getline(cin, cadena);
    vector<string> partes;
    string parte;
    int pos = 1;
    // Convertir a minusculas (se usa cctype)
    for(int i = 0; i < cadena.length(); i++) {
        cadena[i] = tolower(cadena[i]);
    }
    // Eliminar espacios
    cadena.erase(remove_if(cadena.begin(), cadena.end(), [](char c) { return isspace(c); }), cadena.end()); 
    //Agregar signo al inicio
    if(cadena[0] == '+'){
        cadena = cadena;
    }
    else if(cadena[0] != '-'){
        cadena = "+" + cadena;
    }
    // Separar por signo y guardar en vector
    while(pos!=cadena.size()){
        if(cadena[pos]=='+' or cadena[pos]=='-'){
            parte=cadena.substr(0,pos);
            partes.push_back(parte);
            cadena.erase(0,pos);
            pos=1;  
        }
        else pos++;
    }
    partes.push_back(cadena);
    return partes;
}

void leerNPolinomios(int n, vector<vector<string>>& polinomios) {
    for (int i = 0; i < n; i++) {
        vector<string> polinomio = leerPolinomio(to_string(i+1));
        polinomios.push_back(polinomio);
    }
}

int encontrarExponente(string monomio) {
    int pos = monomio.find('^');
    if (pos == string::npos) {
        if (monomio.find('x') != string::npos) {
            return 1; // Si no hay '^' pero hay 'x', el exponente es 1
        } else {
            return 0; // Si no hay 'x', el monomio es un número constante y el exponente es 0
        }
    } else {
        return stoi(monomio.substr(pos+1));
    }
}

float encontrarCoeficiente(string monomio) {
    int pos = monomio.find('x');
    if (pos == string::npos) {
        for (auto c : monomio) {
            if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
                cout << "Error: el monomio contiene un carácter no válido: " << c << endl;
                exit(EXIT_FAILURE);
            }
        }
        return stof(monomio); // Si no hay 'x', el monomio es un número constante
    } else if (pos == 0 || monomio[pos-1] == '+' || monomio[pos-1] == '-') {
        // Si 'x' está al principio del monomio, o el caracter antes de 'x' es '+' o '-', el coeficiente es 1 o -1
        if (monomio[0] == '-') {
            return -1;
        } else {
            return 1;
        }
    } else {
        for (int i = 0; i < pos; i++) {
            if (!isdigit(monomio[i]) && monomio[i] != '+' && monomio[i] != '-' && monomio[i] != '.') {
                cout << "Error: el monomio contiene un carácter no válido: " << monomio[i] << endl;
                exit(EXIT_FAILURE);
            }
        }
        return stof(monomio.substr(0, pos));
    }
}


float sumarMonomios(vector<string>& monomios, int exponente) {
    float suma = 0;
    for (auto monomio : monomios) {
        if (encontrarExponente(monomio) == exponente) {
            suma += encontrarCoeficiente(monomio);
        }
    }
    return suma;
}


//Funcion para hacer la suma
vector<pair<float, int>> sumarPolinomios(vector<vector<string>>& polinomios) {
    vector<pair<float, int>> resultado;
    int maxExponente = 0;
    // Encontrar el exponente máximo
    for (auto polinomio : polinomios) {
        for (auto monomio : polinomio) {
            int exponente = encontrarExponente(monomio);
            if (exponente > maxExponente) {
                maxExponente = exponente;
            }
        }
    }
    // Sumar los monomios para cada exponente
    for (int i = maxExponente; i >= 0; i--) {
        float suma = 0;
        for (auto polinomio : polinomios) {
            suma += sumarMonomios(polinomio, i);
        }
        if (suma != 0) {
            resultado.push_back(make_pair(suma, i));
        }
    }
    return resultado;
}

void imprimirPolinomio(vector<pair<float, int>>& polinomio) {
    for (int i = 0; i < polinomio.size(); ++i) {
        auto monomio = polinomio[i];
        if (monomio.second == 0) {
            cout << monomio.first;
        } else if (monomio.second == 1) {
            cout << monomio.first << "*x";
        } else {
            cout << monomio.first << "*x^" << monomio.second;
        }
        if (i != polinomio.size() - 1) { // Solo imprimir el signo más si el monomio no es el último
            cout << " + ";
        }
    }
    cout << endl;
}


int main() {
    int n;
    cout << "Introduce el numero de polinomios: ";
    cin >> n;
    cin.ignore(); // Ignorar el salto de línea después de la entrada de n
    vector<vector<string>> polinomios;
    leerNPolinomios(n, polinomios);
    // Imprimir los vectores de monomios de cada polinomio
    for (int i = 0; i < n; i++) {
        cout << "\nPolinomio" << i+1 << ":" << endl;
        for (auto monomio : polinomios[i]) {
            cout << monomio << endl;
        }
    }
    // Sumar los polinomios y mostrar el resultado
    vector<pair<float, int>> resultado = sumarPolinomios(polinomios);
    cout << "\nEl polinomio suma es de grado: " << resultado[0].second << endl;
    imprimirPolinomio(resultado);
    return 0;
}