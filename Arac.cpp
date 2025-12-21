#include "Arac.h"

/*
    Arac SINIFI
    - Tüm araç türleri için temel (base) sınıftır
    - Plaka, araç türü, giriş ve çıkış saatlerini tutar
    - Polimorfizm için bilgileriYazdir() fonksiyonu kullanılır
*/

// ---------------- CONSTRUCTOR ----------------
// Araç nesnesi oluşturulurken plaka ve tür atanır
// Giriş saati otomatik olarak programın çalıştığı an alınır
Arac::Arac(std::string p, std::string t)
    : plaka(p), tur(t) {

    // Aracın otoparka giriş zamanı (şu anki zaman)
    girisSaati = std::time(nullptr);

    // Çıkış saati başlangıçta 0 olarak ayarlanır
    cikisSaati = 0;
}

// ---------------- SETTER ----------------
// Araç çıkışı yapıldığında çıkış saatini günceller
void Arac::setCikisSaati(std::time_t saat) {
    cikisSaati = saat;
}

// ---------------- GETTER'LAR ----------------

// Aracın plaka bilgisini döndürür
std::string Arac::getPlaka() const {
    return plaka;
}

// Aracın türünü döndürür (Otomobil, Kamyonet, Motosiklet vb.)
std::string Arac::getTur() const {
    return tur;
}

// Aracın otoparka giriş saatini döndürür
std::time_t Arac::getGirisSaati() const {
    return girisSaati;
}

// ---------------- BİLGİ YAZDIRMA ----------------
// Sanal (virtual) fonksiyon olarak kullanılır
// Türe bağlı olarak türetilmiş sınıflar tarafından ezilebilir
void Arac::bilgileriYazdir() const {

    // Araç bilgileri ekrana yazdırılır
    std::cout << "Plaka: " << plaka
              << " | Tür: " << tur
              << " | Giriş Saati: " << std::ctime(&girisSaati);
}

