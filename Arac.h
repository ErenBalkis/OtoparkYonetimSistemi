#ifndef ARAC_H
#define ARAC_H

#include <string>
#include <ctime>
#include <iostream>

// Soyut Sınıf (Abstract Class)
class Arac {
protected:
    std::string plaka;
    std::string tur; // "Otomobil", "Kamyonet" vb.
    std::time_t girisSaati;
    std::time_t cikisSaati;

public:
    // Constructor
    Arac(std::string p, std::string t);

    // Virtual Destructor (Polimorfizm için şarttır)
    virtual ~Arac() {}

    // Saf Sanal Fonksiyon (Polimorfizm - Türetilen sınıflar bunu ezmek ZORUNDA)
    virtual double hesaplaUcret() const = 0; 

    // Getter & Setter metodları
    void setCikisSaati(std::time_t saat);
    std::string getPlaka() const;
    std::string getTur() const;
    std::time_t getGirisSaati() const;
    
    // Ekrana yazdırma yardımcısı
    virtual void bilgileriYazdir() const;
};

#endif // ARAC_H