/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

// ----- CONSTANTES DEL JUEGO -----
const int FILAS = 6;   // número de filas del tablero
const int COLUMNAS = 7; // número de columnas
const char VACIO = '.'; // símbolo para espacios vacíos
const char JUGADOR1 = 'X'; // ficha del jugador 1
const char JUGADOR2 = 'O'; // ficha del jugador 2

// ----- FUNCIÓN PARA MOSTRAR EL TABLERO -----
void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n";
    // Muestra los números de las columnas
    for (int c = 0; c < COLUMNAS; c++) {
        cout << " " << c + 1;
    }
    cout << "\n";

    // Muestra cada fila del tablero
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            cout << " " << tablero[f][c];
        }
        cout << "\n";
    }
    cout << "\n";
}

// ----- FUNCIÓN PARA COLOCAR UNA FICHA -----
int colocarFicha(vector<vector<char>>& tablero, int columna, char ficha) {
    // Empieza desde la última fila hacia arriba (como si la ficha cayera)
    for (int f = FILAS - 1; f >= 0; f--) {
        if (tablero[f][columna] == VACIO) {
            tablero[f][columna] = ficha; // coloca la ficha
            return f; // devuelve la fila donde cayó
        }
    }
    return -1; // si la columna está llena
}

// ----- FUNCIÓN PARA REVISAR SI HAY 4 EN LÍNEA -----
bool hayGanador(const vector<vector<char>>& tablero, int fila, int columna, char ficha) {
    // direcciones: horizontal, vertical y diagonales
    int df[4] = {0, 1, 1, 1};
    int dc[4] = {1, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        int contador = 1;

        // Avanza hacia un lado
        for (int k = 1; k < 4; k++) {
            int nf = fila + df[i] * k;
            int nc = columna + dc[i] * k;
            if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS && tablero[nf][nc] == ficha)
                contador++;
            else
                break;
        }

        // Avanza hacia el otro lado
        for (int k = 1; k < 4; k++) {
            int nf = fila - df[i] * k;
            int nc = columna - dc[i] * k;
            if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS && tablero[nf][nc] == ficha)
                contador++;
            else
                break;
        }

        // Si hay 4 o más seguidas -> gana
        if (contador >= 4)
            return true;
    }

    return false;
}

// ----- PROGRAMA PRINCIPAL -----
int main() {
    // Crear tablero vacío
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, VACIO));

    char jugador = JUGADOR1; // empieza el jugador X
    bool fin = false;

    cout << "=== 💡 JUEGO: CONECTA 4 💡 ===\n";
    mostrarTablero(tablero);

    while (!fin) {
        int columna;

        // Pedir columna
        cout << "Turno del jugador " << jugador << ". Elige una columna (1-" << COLUMNAS << "): ";
        cin >> columna;
        columna--; // ajusta para índice (0-6)

        // Verificar que la columna sea válida
        if (columna < 0 || columna >= COLUMNAS) {
            cout << "Columna invalida. Intenta otra.\n";
            continue;
        }

        // Colocar ficha
        int fila = colocarFicha(tablero, columna, jugador);
        if (fila == -1) {
            cout << "Esa columna está llena. Intenta otra.\n";
            continue;
        }

        // Mostrar tablero actualizado
        mostrarTablero(tablero);

        // Verificar si hay ganador
        if (hayGanador(tablero, fila, columna, jugador)) {
            cout << "¡Jugador " << jugador << " ha ganado! 🎉\n";
            fin = true;
        }

        // Cambiar de jugador
        if (!fin) {
            if (jugador == JUGADOR1)
                jugador = JUGADOR2;
            else
                jugador = JUGADOR1;
        }
    }

    cout << "Gracias por jugar💡.\n";
    return 0;
}