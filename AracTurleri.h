#ifndef ARACTURLERI_H
#define ARACTURLERI_H

#include <string>
#include "Arac.h"

/*
    ARAÇ TÜRLERİ SINIFLARI
    --------------------------------
    - Arac soyut sınıfından türeyen somut (concrete) sınıfları içerir
    - Her araç türü kendi ücret hesaplama mantığını uygular
    - Polimorfizm bu sınıflar aracılığıyla sağlanır
*/

// ==================== OTOMOBİL ====================

// Otomobil sınıfı
// Arac sınıfından türetilmiştir
class Otomobil : public Arac {
public:
    // Constructor: Plaka bilgisi alır
    Otomobil(std::string p);

    // Otomobil için ücret hesaplama fonksiyonu
    // Arac sınıfındaki saf sanal fonksiyonu override eder
    double hesaplaUcret() const override; 
};

// ==================== KAMYONET ====================

// Kamyonet sınıfı
// Arac sınıfından türetilmiştir
class Kamyonet : public Arac {
public:
    // Constructor
    Kamyonet(std::string p);

    // Kamyonet için ücret hesaplama fonksiyonu
    double hesaplaUcret() const override;
};

// ==================== MOTOSİKLET ====================

// Motosiklet sınıfı
// Arac sınıfından türetilmiştir
class Motosiklet : public Arac {
public:
    // Constructor
    Motosiklet(std::string p);

    // Motosiklet için ücret hesaplama fonksiyonu
    double hesaplaUcret() const override;
};

#endif // ARACTURLERI_H
