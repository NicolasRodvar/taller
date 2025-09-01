#include <iostream>
using namespace std;

int main() {
    int n;
    float precio, total = 0;

    cout << "=== CAJA REGISTRADORA ===" << endl;
    cout << "Cuantos productos va a ingresar? ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int cantidad;
        cout << "Producto " << i << endl;
        cout << "Cantidad: ";
        cin >> cantidad;
        cout << "Precio unitario: $";
        cin >> precio;

        // Multiplicacion: cantidad * precio
        float subtotal = cantidad * precio;
        cout << "Subtotal del producto " << i << ": $" << subtotal << endl;

        total += subtotal; // Suma al total
    }

    cout << "\nTOTAL A PAGAR: $" << total << endl;

    // Division: dividir la cuenta entre varias personas
    int personas;
    cout << "Entre cuantas personas se divide la cuenta? ";
    cin >> personas;

    if (personas > 0) {
        cout << "Cada persona debe pagar: $" << total / personas << endl;
    } else {
        cout << "No es posible dividir entre 0 personas." << endl;
    }

    // Pago del cliente
    float pago;
    cout << "\nIngrese con cuanto paga: $";
    cin >> pago;

    if (pago < total) {
        cout << "Dinero insuficiente." << endl;
    } else {
        cout << "Su cambio es: $" << pago - total << endl;
    }

    cout << "\nGracias por su compra!" << endl;

    return 0;
}
