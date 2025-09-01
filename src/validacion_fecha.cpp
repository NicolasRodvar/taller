#include <iostream>
#include <ctime>

// Funcion para determinar si un anio es bisiesto
bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int main() {
    int dia, mes, anio;
    
    // Pedir la fecha de nacimiento al usuario
    std::cout << "Ingrese la fecha de nacimiento (dia mes anio): ";
    std::cin >> dia >> mes >> anio;

    bool fechaValida = true;
    int diasEnMes;

    // Validar el mes
    if (mes < 1 || mes > 12) {
        fechaValida = false;
    } else {
        // Determinar el numero de dias en el mes
        if (mes == 2) {
            diasEnMes = esBisiesto(anio) ? 29 : 28;
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diasEnMes = 30;
        } else {
            diasEnMes = 31;
        }

        // Validar el dia
        if (dia < 1 || dia > diasEnMes) {
            fechaValida = false;
        }
    }

    // Comprobar la elegibilidad para la promocion
    if (!fechaValida) {
        std::cout << "La fecha ingresada no es valida. No se puede aplicar el descuento." << std::endl;
    } else {
        // Obtener el mes actual del sistema
        time_t t = time(0);
        tm* now = localtime(&t);
        int mesActual = now->tm_mon + 1;

        if (mes == mesActual) {
            std::cout << "La fecha es valida. El cliente es elegible para el descuento." << std::endl;
        } else {
            std::cout << "La fecha es valida, pero el cliente no es elegible para la promocion este mes." << std::endl;
        }
    }

    return 0;
}