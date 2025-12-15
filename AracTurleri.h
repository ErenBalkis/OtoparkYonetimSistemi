#ifndef ARACTURLERI_H
#define ARACTURLERI_H

#include "Arac.h"

// Otomobil Sınıfı
class Otomobil : public Arac {
public:
    Otomobil(std::string p);
    // Override: Kendi ücret tarifesini uygulayacak
    double hesaplaUcret() const override; 
};

// Kamyonet Sınıfı
class Kamyonet : public Arac {
public:
    Kamyonet(std::string p);
    double hesaplaUcret() const override;
};

// Motosiklet Sınıfı
class Motosiklet : public Arac {
public:
    Motosiklet(std::string p);
    double hesaplaUcret() const override;
};

#endif // ARACTURLERI_H