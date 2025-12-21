#ifndef PARKYERI_H
#define PARKYERI_H

#include <string>

class ParkYeri {
private:
    int id;
    int kat;
    bool doluMu;
    std::string parkEdenPlaka; // Hangi aracın burada olduğunu bilmek için

public:
    ParkYeri(int id, int kat);

    bool isDolu() const;
    void setDurum(bool durum, std::string plaka = "");
    int getId() const;
    int getKat() const;
    std::string getPlaka() const;
};

#endif // PARKYERI_H