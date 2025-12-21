#include "AracTurleri.h"

// Otomobil
Otomobil::Otomobil(std::string p)
    : Arac(p, "Otomobil") {}

double Otomobil::hesaplaUcret() const {
    return 50.0; // örnek ücret
}

// Kamyonet
Kamyonet::Kamyonet(std::string p)
    : Arac(p, "Kamyonet") {}

double Kamyonet::hesaplaUcret() const {
    return 80.0;
}

// Motosiklet
Motosiklet::Motosiklet(std::string p)
    : Arac(p, "Motosiklet") {}

double Motosiklet::hesaplaUcret() const {
    return 30.0;
}
