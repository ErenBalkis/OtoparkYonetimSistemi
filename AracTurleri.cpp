#include "AracTurleri.h"

/*
    ARAÇ TÜRLERİ SINIFLARI
    --------------------------------
    - Arac soyut sınıfından türeyen somut sınıflardır
    - Her araç türü kendi ücret tarifesini uygular
    - Polimorfizm bu sınıflar üzerinden sağlanır
*/

// ==================== OTOMOBİL ====================

// Otomobil sınıfı constructor
// Plaka bilgisi alınır ve Arac temel sınıfına iletilir
Otomobil::Otomobil(std::string p)
    : Arac(p, "Otomobil") {}

// Otomobil için ücret hesaplama fonksiyonu
// Sabit bir ücret döndürür (örnek senaryo)
double Otomobil::hesaplaUcret() const {
    return 50.0;
}

// ==================== KAMYONET ====================

// Kamyonet sınıfı constructor
Kamyonet::Kamyonet(std::string p)
    : Arac(p, "Kamyonet") {}

// Kamyonet için ücret hesaplama fonksiyonu
// Otomobile göre daha yüksek ücret uygulanır
double Kamyonet::hesaplaUcret() const {
    return 80.0;
}

// ==================== MOTOSİKLET ====================

// Motosiklet sınıfı constructor
Motosiklet::Motosiklet(std::string p)
    : Arac(p, "Motosiklet") {}

// Motosiklet için ücret hesaplama fonksiyonu
// Daha küçük araç olduğu için daha düşük ücret uygulanır
double Motosiklet::hesaplaUcret() const {
    return 30.0;
}
