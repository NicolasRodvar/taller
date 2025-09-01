#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

class ZodiacSystem {
private:
    struct ZodiacSign {
        std::string name;
        std::string description;
        int startMonth, startDay;
        int endMonth, endDay;
    };

    std::vector<ZodiacSign> signs;

public:
    ZodiacSystem() {
        // Inicializar los signos zodiacales con rangos exactos
        signs = {
            {"Capricornio", "Ambicioso y disciplinado", 12, 22, 1, 19},
            {"Acuario", "Innovador e independiente", 1, 20, 2, 18},
            {"Piscis", "Intuitivo y compasivo", 2, 19, 3, 20},
            {"Aries", "Energético y valiente", 3, 21, 4, 19},
            {"Tauro", "Estable y determinado", 4, 20, 5, 20},
            {"Géminis", "Versátil y comunicativo", 5, 21, 6, 20},
            {"Cáncer", "Emocional y protector", 6, 21, 7, 22},
            {"Leo", "Carismático y generoso", 7, 23, 8, 22},
            {"Virgo", "Analítico y perfeccionista", 8, 23, 9, 22},
            {"Libra", "Equilibrado y diplomático", 9, 23, 10, 22},
            {"Escorpio", "Intenso y misterioso", 10, 23, 11, 21},
            {"Sagitario", "Aventurero y optimista", 11, 22, 12, 21}
        };
    }

    bool isValidDate(int day, int month) {
        if (month < 1 || month > 12) return false;

        int daysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (day < 1 || day > daysInMonth[month - 1]) return false;

        return true;
    }

    std::string getZodiacSign(int day, int month) {
        if (!isValidDate(day, month)) {
            return "Fecha inválida";
        }

        for (const auto& sign : signs) {
            // Caso especial para Capricornio (cruza el año)
            if (sign.name == "Capricornio") {
                if ((month == 12 && day >= 22) || (month == 1 && day <= 19)) {
                    return sign.name;
                }
            }
            // Casos normales
            else if ((month == sign.startMonth && day >= sign.startDay) ||
                     (month == sign.endMonth && day <= sign.endDay)) {
                return sign.name;
            }
        }

        return "Error en el cálculo";
    }

    std::string getSignDescription(const std::string& signName) {
        for (const auto& sign : signs) {
            if (sign.name == signName) {
                return sign.description;
            }
        }
        return "Descripción no encontrada";
    }

    std::string getSignDateRange(const std::string& signName) {
        for (const auto& sign : signs) {
            if (sign.name == signName) {
                std::string range = "Del " + std::to_string(sign.startDay) + " de ";
                range += getMonthName(sign.startMonth) + " al " + std::to_string(sign.endDay);
                range += " de " + getMonthName(sign.endMonth);
                return range;
            }
        }
        return "Rango no encontrado";
    }

private:
    std::string getMonthName(int month) {
        std::string months[] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio",
                               "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
        return (month >= 1 && month <= 12) ? months[month] : "mes inválido";
    }
};

class AppInterface {
private:
    ZodiacSystem zodiac;

public:
    void clearScreen() {
        system(CLEAR_SCREEN);
    }

    void showHeader() {
        std::cout << "╔══════════════════════════════════════════════╗\n";
        std::cout << "║          🌟 SECCIÓN DE ENTRETENIMIENTO 🌟    ║\n";
        std::cout << "║              Descubre tu Signo Zodiacal      ║\n";
        std::cout << "╚══════════════════════════════════════════════╝\n\n";
    }

    void showMenu() {
        std::cout << "┌─────────────────────────────────────────────┐\n";
        std::cout << "│  1. Consultar signo zodiacal                │\n";
        std::cout << "│  2. Ver todos los signos y sus rangos       │\n";
        std::cout << "│  3. Probar casos específicos (15 y 25 marzo)│\n";
        std::cout << "│  4. Salir                                   │\n";
        std::cout << "└─────────────────────────────────────────────┘\n";
        std::cout << "Selecciona una opción: ";
    }

    void consultZodiacSign() {
        int day, month;

        std::cout << "\n📅 Ingresa tu fecha de nacimiento:\n";
        std::cout << "Día (1-31): ";
        std::cin >> day;
        std::cout << "Mes (1-12): ";
        std::cin >> month;

        std::string sign = zodiac.getZodiacSign(day, month);

        if (sign == "Fecha inválida" || sign == "Error en el cálculo") {
            std::cout << "\n❌ " << sign << ". Por favor, verifica los datos ingresados.\n";
        } else {
            std::cout << "\n🌟 ¡Tu signo zodiacal es: " << sign << "! 🌟\n";
            std::cout << "📝 Descripción: " << zodiac.getSignDescription(sign) << "\n";
            std::cout << "📆 Rango de fechas: " << zodiac.getSignDateRange(sign) << "\n";
        }

        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    void showAllSigns() {
        std::cout << "\n🌟 TODOS LOS SIGNOS ZODIACALES Y SUS RANGOS 🌟\n";
        std::cout << "═══════════════════════════════════════════════\n";

        std::vector<std::string> signNames = {
            "Capricornio", "Acuario", "Piscis", "Aries", "Tauro", "Géminis",
            "Cáncer", "Leo", "Virgo", "Libra", "Escorpio", "Sagitario"
        };

        for (const auto& name : signNames) {
            std::cout << "• " << std::setw(12) << std::left << name 
                      << ": " << zodiac.getSignDateRange(name) << "\n";
        }

        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    void testSpecificCases() {
        std::cout << "\n🧪 PRUEBA DE CASOS ESPECÍFICOS 🧪\n";
        std::cout << "═══════════════════════════════════════\n";

        // Caso 1: 15 de marzo (debe ser Piscis)
        std::string sign1 = zodiac.getZodiacSign(15, 3);
        std::cout << "📅 15 de marzo: " << sign1 << " ✓\n";
        std::cout << "   Rango: " << zodiac.getSignDateRange(sign1) << "\n\n";

        // Caso 2: 25 de marzo (debe ser Aries)
        std::string sign2 = zodiac.getZodiacSign(25, 3);
        std::cout << "📅 25 de marzo: " << sign2 << " ✓\n";
        std::cout << "   Rango: " << zodiac.getSignDateRange(sign2) << "\n\n";

        // Casos adicionales de prueba
        std::cout << "🔍 Casos adicionales de prueba:\n";
        std::cout << "• 20 de marzo: " << zodiac.getZodiacSign(20, 3) << " (último día de Piscis)\n";
        std::cout << "• 21 de marzo: " << zodiac.getZodiacSign(21, 3) << " (primer día de Aries)\n";
        std::cout << "• 31 de diciembre: " << zodiac.getZodiacSign(31, 12) << "\n";
        std::cout << "• 1 de enero: " << zodiac.getZodiacSign(1, 1) << "\n";

        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    void run() {
        int option;

        do {
            clearScreen();
            showHeader();
            showMenu();
            std::cin >> option;

            switch (option) {
                case 1:
                    consultZodiacSign();
                    break;
                case 2:
                    showAllSigns();
                    break;
                case 3:
                    testSpecificCases();
                    break;
                case 4:
                    std::cout << "\n👋 ¡Gracias por usar nuestra sección de entretenimiento!\n";
                    break;
                default:
                    std::cout << "\n❌ Opción inválida. Presiona Enter para continuar...";
                    std::cin.ignore();
                    std::cin.get();
            }
        } while (option != 4);
    }
};

int main() {
    AppInterface app;
    app.run();
    return 0;
}