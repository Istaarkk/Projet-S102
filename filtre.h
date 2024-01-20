// Filtre.h
#include "Image.h"
#ifndef FILTRE_H
#define FILTRE_H

#include <vector>

class Filtre
{
private:
    std::vector<std::vector<float>> matrice;
    float facteur;

public:
    Filtre(const std::vector<std::vector<float>>& matrice, float facteur);
    Image application(const Image&) const;
    std::vector<std::vector<int>> applyFilter(const std::vector<std::vector<int>>& composante) const;
    static Filtre flouG3();
    //static Filtre flouG5();


};

#endif // FILTRE_H
