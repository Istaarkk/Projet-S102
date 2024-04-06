#include "Image.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
//Image.cpp

std::vector<std::vector<int>> Image::getRouge() const
{
    return rouge;
}

std::vector<std::vector<int>> Image::getVert() const
{
    return vert;
}

std::vector<std::vector<int>> Image::getBleu() const
{
    return bleu;
}

int Image::getHauteur() const
{
    return hauteur;
}

int Image::getLargeur() const
{
    return largeur;
}

int Image::getLongueur() const
{
    return longueur;
}

void Image::afficher() const
{
    std::cout << "Image:\n";
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            std::cout << "(" << rouge[i][j] << ", " << vert[i][j] << ", " << bleu[i][j] << ") ";
        }
        std::cout << "\n";
    }
    int longueur=0,hauteur=0;
    for(size_t i=0; i<rouge.size(); i++)
    {
        longueur++;
    }

    for(size_t j=0; j<rouge[1].size(); j++)
    {
        hauteur++;
    }
    std::cout<<"l'image fait du " <<longueur<<"px x "<<hauteur<<"px"<<std::endl;
}



void loadPicture(const std::string &picture, std::vector<std::vector<int>> &red,
                 std::vector<std::vector<int>> &green,
                 std::vector<std::vector<int>> &blue);

Image::Image(const std::string &picture)
{
    loadPicture(picture, rouge, vert, bleu);
    hauteur = rouge.size();
    largeur = (hauteur > 0) ? rouge[0].size() : 0;
    longueur = hauteur;
}

Image::Image(const std::vector<std::vector<int>> &r,
             const std::vector<std::vector<int>> &g,
             const std::vector<std::vector<int>> &b)
    : rouge(r), vert(g), bleu(b)
{
    hauteur = rouge.size();
    largeur = (hauteur > 0) ? rouge[0].size() : 0;
    longueur = hauteur;
}

void Image::displayImage() const
{
    std::cout << "Rouge:\n";
    displayComponent(rouge);
    std::cout << "Vert:\n";
    displayComponent(vert);
    std::cout << "Bleu:\n";
    displayComponent(bleu);
}

void Image::displayComponent(const std::vector<std::vector<int>> &component) const
{
    for (const auto &row : component)
    {
        for (int value : row)
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

bool Image::detection(int rouge, int vert, int bleu) const
{
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            if (this->rouge[i][j] == rouge && this->vert[i][j] == vert && this->bleu[i][j] == bleu)
            {
                return true;
            }
        }
    }
    return false;
}

Image Image::niveauxGris() const
{
    std::vector<std::vector<int>> grayScale(hauteur, std::vector<int>(largeur, 0));
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            int grayValue = (rouge[i][j] + vert[i][j] + bleu[i][j]) / 3;
            grayScale[i][j] = grayValue;
        }
    }
    return Image(grayScale, grayScale, grayScale);
}

Image Image::composanteRouge() const
{
    return Image(rouge, std::vector<std::vector<int>>(hauteur, std::vector<int>(largeur, 0)),
                 std::vector<std::vector<int>>(hauteur, std::vector<int>(largeur, 0)));
}

Image Image::noirEtBlanc(int seuil) const
{
    std::vector<std::vector<int>> grayScale = niveauxGris().rouge;
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            grayScale[i][j] = (grayScale[i][j] > seuil) ? 255 : 0;
        }
    }
    return Image(grayScale, grayScale, grayScale);
}

std::vector<int> Image::histogrammeGris() const
{
    std::vector<int> histogram(256, 0);
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            int grayValue = niveauxGris().rouge[i][j];
            histogram[grayValue]++;
        }
    }
    return histogram;
}

std::vector<std::vector<int>> Image::histogrammeCouleur() const
{
    std::vector<std::vector<int>> histogram(3, std::vector<int>(256, 0));

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            histogram[0][rouge[i][j]]++;
            histogram[1][vert[i][j]]++;
            histogram[2][bleu[i][j]]++;
        }
    }
    return histogram;
}

Image Image::luminosityUp(double factor) const
{
    Image adjustedImage = *this;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            adjustedImage.rouge[i][j] = std::min(static_cast<int>(rouge[i][j] * factor), 255);
            adjustedImage.vert[i][j] = std::min(static_cast<int>(vert[i][j] * factor), 255);
            adjustedImage.bleu[i][j] = std::min(static_cast<int>(bleu[i][j] * factor), 255);
        }
    }

    return adjustedImage;
}

Image Image::luminosityDown(double factor) const
{
    Image adjustedImage = *this;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            adjustedImage.rouge[i][j] = static_cast<int>(rouge[i][j] * factor);
            adjustedImage.vert[i][j] = static_cast<int>(vert[i][j] * factor);
            adjustedImage.bleu[i][j] = static_cast<int>(bleu[i][j] * factor);
        }
    }

    return adjustedImage;
}

Image Image::contrasteUp(double factor) const
{
    Image adjustedImage = *this;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            adjustedImage.rouge[i][j] = std::min(std::max(static_cast<int>((rouge[i][j] - 128) * factor + 128), 0), 255);
            adjustedImage.vert[i][j] = std::min(std::max(static_cast<int>((vert[i][j] - 128) * factor + 128), 0), 255);
            adjustedImage.bleu[i][j] = std::min(std::max(static_cast<int>((bleu[i][j] - 128) * factor + 128), 0), 255);
        }
    }

    return adjustedImage;
}

Image Image::contrasteDown(double factor) const
{
    Image adjustedImage = *this;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            adjustedImage.rouge[i][j] = std::min(std::max(static_cast<int>((rouge[i][j] - 128) * factor + 128), 0), 255);
            adjustedImage.vert[i][j] = std::min(std::max(static_cast<int>((vert[i][j] - 128) * factor + 128), 0), 255);
            adjustedImage.bleu[i][j] = std::min(std::max(static_cast<int>((bleu[i][j] - 128) * factor + 128), 0), 255);
        }
    }

    return adjustedImage;
}

Image Image::rognerD(int nb) const
{
    if (nb >= largeur)
    {
        throw std::invalid_argument("Nombre de colonnes à rogner trop grand");
    }

    std::vector<std::vector<int>> newRouge = rouge;
    std::vector<std::vector<int>> newVert = vert;
    std::vector<std::vector<int>> newBleu = bleu;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < nb; ++j)
        {
            newRouge[i].pop_back();
            newVert[i].pop_back();
            newBleu[i].pop_back();
        }
    }

    return Image(newRouge, newVert, newBleu);
}

Image Image::rognerG(int nb) const
{
    if (nb >= largeur)
    {
        throw std::invalid_argument("Nombre de colonnes à rogner trop grand");
    }

    std::vector<std::vector<int>> newRouge = rouge;
    std::vector<std::vector<int>> newVert = vert;
    std::vector<std::vector<int>> newBleu = bleu;

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < nb; ++j)
        {
            newRouge[i].erase(newRouge[i].begin());
            newVert[i].erase(newVert[i].begin());
            newBleu[i].erase(newBleu[i].begin());
        }
    }

    return Image(newRouge, newVert, newBleu);
}

Image Image::rognerH(int nb) const
{
    if (nb >= hauteur)
    {
        throw std::invalid_argument("Nombre de lignes à rogner trop grand");
    }

    std::vector<std::vector<int>> newRouge = rouge;
    std::vector<std::vector<int>> newVert = vert;
    std::vector<std::vector<int>> newBleu = bleu;

    for (int i = 0; i < nb; ++i)
    {
        newRouge.erase(newRouge.begin());
        newVert.erase(newVert.begin());
        newBleu.erase(newBleu.begin());
    }

    return Image(newRouge, newVert, newBleu);
}
Image Image::rognerB(int nb) const
{
    if (nb >= hauteur)
    {
        throw std::invalid_argument("Nombre de lignes à rogner trop grand");
    }

    std::vector<std::vector<int>> newRouge = rouge;
    std::vector<std::vector<int>> newVert = vert;
    std::vector<std::vector<int>> newBleu = bleu;

    for (int i = 0; i < nb; ++i)
    {
        newRouge.pop_back();
        newVert.pop_back();
        newBleu.pop_back();
    }

    return Image(newRouge, newVert, newBleu);

}

Image Image::rotationD() const
{
    std::vector<std::vector<int>> newRouge(largeur, std::vector<int>(hauteur, 0));
    std::vector<std::vector<int>> newVert(largeur, std::vector<int>(hauteur, 0));
    std::vector<std::vector<int>> newBleu(largeur, std::vector<int>(hauteur, 0));

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            newRouge[j][hauteur - i - 1] = rouge[i][j];
            newVert[j][hauteur - i - 1] = vert[i][j];
            newBleu[j][hauteur - i - 1] = bleu[i][j];
        }
    }

     return Image(newRouge, newVert, newBleu);
}


Image Image::rotationG() const
{
    std::vector<std::vector<int>> newRouge(largeur, std::vector<int>(hauteur, 0));
    std::vector<std::vector<int>> newVert(largeur, std::vector<int>(hauteur, 0));
    std::vector<std::vector<int>> newBleu(largeur, std::vector<int>(hauteur, 0));

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            newRouge[largeur - j - 1][i] = rouge[i][j];
            newVert[largeur - j - 1][i] = vert[i][j];
            newBleu[largeur - j - 1][i] = bleu[i][j];
        }
    }

    return Image(newRouge, newVert, newBleu);
}

Image Image::retournementH() const
{
    std::vector<std::vector<int>> newRouge(hauteur, std::vector<int>(largeur, 0));
    std::vector<std::vector<int>> newVert(hauteur, std::vector<int>(largeur, 0));
    std::vector<std::vector<int>> newBleu(hauteur, std::vector<int>(largeur, 0));

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            newRouge[i][largeur - j - 1] = rouge[i][j];
            newVert[i][largeur - j - 1] = vert[i][j];
            newBleu[i][largeur - j - 1] = bleu[i][j];
        }
    }

    return Image(newRouge, newVert, newBleu);
}

Image Image::retournementV() const
{
    std::vector<std::vector<int>> newRouge(hauteur, std::vector<int>(largeur, 0));
    std::vector<std::vector<int>> newVert(hauteur, std::vector<int>(largeur, 0));
    std::vector<std::vector<int>> newBleu(hauteur, std::vector<int>(largeur, 0));

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            newRouge[hauteur - i - 1][j] = rouge[i][j];
            newVert[hauteur - i - 1][j] = vert[i][j];
            newBleu[hauteur - i - 1][j] = bleu[i][j];
        }
    }

    return Image(newRouge, newVert, newBleu);
}


Image Image::agrandissement(int facteur) const
{
    if (facteur <= 0)
    {
        throw std::invalid_argument("Le facteur d'agrandissement doit être un entier positif.");
    }

    int nouvelleHauteur = hauteur * facteur;
    int nouvelleLargeur = largeur * facteur;

    std::vector<std::vector<int>> newRouge(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));
    std::vector<std::vector<int>> newVert(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));
    std::vector<std::vector<int>> newBleu(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));

    for (int i = 0; i < nouvelleHauteur; ++i)
    {
        for (int j = 0; j < nouvelleLargeur; ++j)
        {
            int originalI = i / facteur;
            int originalJ = j / facteur;

            newRouge[i][j] = rouge[originalI][originalJ];
            newVert[i][j] = vert[originalI][originalJ];
            newBleu[i][j] = bleu[originalI][originalJ];
        }
    }

    return Image(newRouge, newVert, newBleu);
}

Image Image::retrecissement(int facteur) const
{
    if (facteur <= 0)
    {
        throw std::invalid_argument("Le facteur de rétrécissement doit être un entier positif.");
    }

    int nouvelleHauteur = hauteur / facteur;
    int nouvelleLargeur = largeur / facteur;

    std::vector<std::vector<int>> newRouge(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));
    std::vector<std::vector<int>> newVert(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));
    std::vector<std::vector<int>> newBleu(nouvelleHauteur, std::vector<int>(nouvelleLargeur, 0));

    for (int i = 0; i < nouvelleHauteur; ++i)
    {
        for (int j = 0; j < nouvelleLargeur; ++j)
        {
            int sumRouge = 0, sumVert = 0, sumBleu = 0;

            for (int k = 0; k < facteur; ++k)
            {
                for (int l = 0; l < facteur; ++l)
                {
                    sumRouge += rouge[i * facteur + k][j * facteur + l];
                    sumVert += vert[i * facteur + k][j * facteur + l];
                    sumBleu += bleu[i * facteur + k][j * facteur + l];
                }
            }

            newRouge[i][j] = sumRouge / (facteur * facteur);
            newVert[i][j] = sumVert / (facteur * facteur);
            newBleu[i][j] = sumBleu / (facteur * facteur);
        }
    }

    return Image(newRouge, newVert, newBleu);
}

void Image::saveToPPM(const std::string &fileName) const
{
    std::ofstream outputFile(fileName);
    if (!outputFile)
    {
        std::cerr << "Error opening output file: " << fileName << std::endl;
        return;
    }

    outputFile << "P3\n";
    outputFile << largeur << " " << hauteur << "\n";
    outputFile << "255\n";

    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            outputFile << rouge[i][j] << " " << vert[i][j] << " " << bleu[i][j] << " ";
        }
        outputFile << "\n";
    }

    outputFile.close();
}



