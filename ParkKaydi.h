#ifndef PARKKAYDI_H
#define PARKKAYDI_H

#include <string>
#include <ctime>

class ParkKaydi {
private:
    std::string plaka;
    int parkYeriId;
    time_t girisZamani;
    time_t cikisZamani;
    double ucret;

public:
    ParkKaydi(std::string plaka, int parkYeriId);

    void cikisYap();
    void ucretHesapla(double saatlikUcret);

    std::string getPlaka() const;
    int getParkYeriId() const;
    time_t getGirisZamani() const;
    time_t getCikisZamani() const;
    double getUcret() const;
};

#endif // PARKKAYDI_H
