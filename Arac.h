#ifndef ARAC_H
#define ARAC_H

#include <string>   // std::string için
#include <ctime>    // time_t, time() fonksiyonları için
#include <iostream> // cout kullanımı için

/*
    ARAC SINIFI (SOYUT SINIF)
    --------------------------------
    - Otopark sistemindeki tüm araç türleri için temel sınıftır
    - Doğrudan nesnesi oluşturulamaz (abstract class)
    - Polimorfizm için tasarlanmıştır
*/

class Arac {
protected:
    // Araca ait plaka bilgisi
    std::string plaka;

    // Aracın türü (Otomobil, Kamyonet, Motosiklet vb.)
    std::string tur;

    // Aracın otoparka giriş zamanı
    std::time_t girisSaati;

    // Aracın otoparktan çıkış zamanı
    std::time_t cikisSaati;

public:
    /*
        CONSTRUCTOR
        - Plaka ve araç türünü alır
        - Giriş saati otomatik olarak atanır
    */
    Arac(std::string p, std::string t);

    /*
        VIRTUAL DESTRUCTOR
        - Polimorfik kullanımda bellek sızıntısını önler
        - Türetilmiş sınıfların destructor'larının
          doğru şekilde çağrılmasını sağlar
    */
    virtual ~Arac() {}
    // Giriş saatini ayarlar
    void setGirisSaati(std::time_t saat) { girisSaati = saat; }
    /*
        SAF SANAL FONKSİYON (PURE VIRTUAL)
        - Her araç türü kendi ücret hesaplama mantığını
          yazmak zorundadır
        - Bu fonksiyon Arac sınıfını soyut (abstract) yapar
    */
    virtual double hesaplaUcret() const = 0;

    // ---------------- GETTER & SETTER METOTLARI ----------------

    // Aracın çıkış saatini ayarlar
    void setCikisSaati(std::time_t saat);

    // Aracın plakasını döndürür
    std::string getPlaka() const;

    // Aracın türünü döndürür
    std::string getTur() const;

    // Aracın otoparka giriş saatini döndürür
    std::time_t getGirisSaati() const;
    
    /*
        Bilgi Yazdırma Fonksiyonu
        - Sanal (virtual) olarak tanımlanmıştır
        - Türetilmiş sınıflar tarafından yeniden tanımlanabilir (override)
    */
    virtual void bilgileriYazdir() const;
};

#endif // ARAC_H
