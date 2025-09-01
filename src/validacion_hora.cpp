#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

class ControlHorarios {
private:
    struct Horario {
        int hora;
        int minuto;
    };

public:
    // Función para validar formato y convertir a horas y minutos
    bool validarHora(const string& input, int &hora, int &minuto) {
        // Verificar longitud y formato básico
        if (input.size() != 5 || input[2] != ':') {
            return false;
        }

        // Verificar que los caracteres sean dígitos
        for (int i = 0; i < 5; i++) {
            if (i == 2) continue; // saltar el ':'
            if (!isdigit(input[i])) {
                return false;
            }
        }

        // Extraer hora y minuto
        string horaStr = input.substr(0, 2);
        string minutoStr = input.substr(3, 2);

        try {
            hora = stoi(horaStr);
            minuto = stoi(minutoStr);
        } catch (...) {
            return false;
        }

        // Validar rangos
        if (hora < 0 || hora > 23) return false;
        if (minuto < 0 || minuto > 59) return false;

        return true;
    }

    // Calcular horas trabajadas, considerando turnos que cruzan medianoche
    double calcularHorasTrabajadas(int hEntrada, int mEntrada, int hSalida, int mSalida) {
        int totalEntrada = hEntrada * 60 + mEntrada;
        int totalSalida = hSalida * 60 + mSalida;

        // Si salida es menor que entrada, significa que pasó a día siguiente
        if (totalSalida < totalEntrada) {
            totalSalida += 24 * 60; // agregar 24 horas en minutos
        }

        int minutosTrabajados = totalSalida - totalEntrada;
        return minutosTrabajados / 60.0; // convertir a horas con decimales
    }

    void mostrarHeader() {
        cout << "╔═════════════════════════════════════════════════════════╗\n";
        cout << "║              🕐 CONTROL DE HORARIOS EMPLEADOS 🕐        ║\n";
        cout << "║                Sistema de Registro v1.0                ║\n";
        cout << "╚═════════════════════════════════════════════════════════╝\n\n";
    }

    void mostrarInstrucciones() {
        cout << "📋 INSTRUCCIONES:\n";
        cout << "• Ingresa las horas en formato HH:MM (ejemplo: 08:30, 14:45)\n";
        cout << "• Horas válidas: 00-23, Minutos válidos: 00-59\n";
        cout << "• El sistema maneja turnos nocturnos automáticamente\n";
        cout << "═══════════════════════════════════════════════════════════\n\n";
    }

    void mostrarEjemplosErrores() {
        cout << "\n❌ EJEMPLOS DE ENTRADAS INVÁLIDAS:\n";
        cout << "• 25:70 (hora > 23, minuto > 59)\n";
        cout << "• 12:99 (minuto > 59)\n";
        cout << "• 8:30 (falta cero inicial)\n";
        cout << "• 08-30 (separador incorrecto)\n";
        cout << "• abc:de (caracteres no numéricos)\n\n";
    }

    void ejecutarRegistro() {
        string entrada, salida;
        int hEntrada, mEntrada, hSalida, mSalida;

        mostrarHeader();
        mostrarInstrucciones();

        // Solicitar hora de entrada
        cout << "🔹 Ingresa hora de ENTRADA (formato HH:MM): ";
        cin >> entrada;

        if (!validarHora(entrada, hEntrada, mEntrada)) {
            cout << "\n❌ ERROR: Hora de entrada inválida.\n";
            cout << "   Formato requerido: HH:MM (ejemplo: 08:30)\n";
            mostrarEjemplosErrores();
            return;
        }

        // Solicitar hora de salida
        cout << "🔹 Ingresa hora de SALIDA (formato HH:MM): ";
        cin >> salida;

        if (!validarHora(salida, hSalida, mSalida)) {
            cout << "\n❌ ERROR: Hora de salida inválida.\n";
            cout << "   Formato requerido: HH:MM (ejemplo: 17:30)\n";
            mostrarEjemplosErrores();
            return;
        }

        // Calcular horas trabajadas
        double horasTrabajadas = calcularHorasTrabajadas(hEntrada, mEntrada, hSalida, mSalida);

        // Mostrar resultados
        cout << "\n✅ REGISTRO EXITOSO\n";
        cout << "═══════════════════════════════════════════════════════════\n";
        cout << "📅 RESUMEN DEL TURNO:\n";
        cout << "🕐 Hora de Entrada: " << setw(2) << setfill('0') << hEntrada 
             << ":" << setw(2) << mEntrada << "\n";
        cout << "🕕 Hora de Salida : " << setw(2) << setfill('0') << hSalida 
             << ":" << setw(2) << mSalida << "\n";
        cout << "⏱️  Horas Trabajadas: " << fixed << setprecision(2) 
             << horasTrabajadas << " horas\n";

        // Información adicional
        if (horasTrabajadas > 8.0) {
            cout << "⚠️  Nota: Turno de más de 8 horas (posible tiempo extra)\n";
        }

        if ((hSalida < hEntrada) || (hSalida == hEntrada && mSalida < mEntrada)) {
            cout << "🌙 Turno nocturno detectado (cruza medianoche)\n";
        }

        cout << "═══════════════════════════════════════════════════════════\n";
    }

    void ejecutarPruebas() {
        cout << "\n🧪 EJECUTANDO PRUEBAS DEL SISTEMA\n";
        cout << "═══════════════════════════════════════════════════════════\n";

        // Pruebas de validación
        cout << "📋 Pruebas de Validación:\n";

        string casos[] = {"08:30", "25:70", "12:99", "23:59", "00:00", "8:30", "ab:cd"};
        int hora, minuto;

        for (const string& caso : casos) {
            bool valido = validarHora(caso, hora, minuto);
            cout << "• " << caso << " → " << (valido ? "✅ Válido" : "❌ Inválido") << "\n";
        }

        cout << "\n📊 Pruebas de Cálculo de Horas:\n";

        // Casos de prueba para cálculo
        struct CasoPrueba {
            int hE, mE, hS, mS;
            string descripcion;
        };

        CasoPrueba casos_calculo[] = {
            {8, 30, 17, 30, "Turno normal (8:30 - 17:30)"},
            {22, 0, 6, 0, "Turno nocturno (22:00 - 06:00)"},
            {9, 15, 18, 45, "Turno con minutos (9:15 - 18:45)"},
            {0, 0, 23, 59, "Turno completo (00:00 - 23:59)"}
        };

        for (const auto& caso : casos_calculo) {
            double horas = calcularHorasTrabajadas(caso.hE, caso.mE, caso.hS, caso.mS);
            cout << "• " << caso.descripcion << " → " 
                 << fixed << setprecision(2) << horas << " horas\n";
        }

        cout << "═══════════════════════════════════════════════════════════\n";
    }
};

class MenuPrincipal {
private:
    ControlHorarios control;

public:
    void limpiarPantalla() {
        system(CLEAR_SCREEN);
    }

    void mostrarMenu() {
        cout << "\n┌─────────────────────────────────────────────────────────┐\n";
        cout << "│                    MENÚ PRINCIPAL                       │\n";
        cout << "├─────────────────────────────────────────────────────────┤\n";
        cout << "│  1. Registrar horario de empleado                      │\n";
        cout << "│  2. Ejecutar pruebas del sistema                       │\n";
        cout << "│  3. Ver información del sistema                        │\n";
        cout << "│  4. Salir                                              │\n";
        cout << "└─────────────────────────────────────────────────────────┘\n";
        cout << "Selecciona una opción (1-4): ";
    }

    void mostrarInfo() {
        cout << "\n📋 INFORMACIÓN DEL SISTEMA\n";
        cout << "═══════════════════════════════════════════════════════════\n";
        cout << "🎯 Propósito: Registrar horarios de entrada y salida\n";
        cout << "✅ Validaciones implementadas:\n";
        cout << "   • Formato HH:MM obligatorio\n";
        cout << "   • Horas: 00-23, Minutos: 00-59\n";
        cout << "   • Rechazo de entradas como 25:70, 12:99\n";
        cout << "🌙 Características especiales:\n";
        cout << "   • Manejo de turnos nocturnos\n";
        cout << "   • Cálculo preciso de horas trabajadas\n";
        cout << "   • Detección de tiempo extra (>8 horas)\n";
        cout << "💻 Compatibilidad: Windows, macOS, Linux\n";
        cout << "═══════════════════════════════════════════════════════════\n";

        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();
    }

    void ejecutar() {
        int opcion;

        do {
            limpiarPantalla();
            mostrarMenu();
            cin >> opcion;

            switch (opcion) {
                case 1:
                    limpiarPantalla();
                    control.ejecutarRegistro();
                    cout << "\nPresiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;

                case 2:
                    limpiarPantalla();
                    control.ejecutarPruebas();
                    cout << "\nPresiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;

                case 3:
                    limpiarPantalla();
                    mostrarInfo();
                    break;

                case 4:
                    cout << "\n👋 ¡Gracias por usar el Sistema de Control de Horarios!\n";
                    cout << "💼 Sistema desarrollado para mejorar la gestión de nómina.\n";
                    break;

                default:
                    cout << "\n❌ Opción inválida. Selecciona 1-4.\n";
                    cout << "Presiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
            }
        } while (opcion != 4);
    }
};

int main() {
    MenuPrincipal menu;
    menu.ejecutar();
    return 0;
}