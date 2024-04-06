/*
#include "Image.h"
#include <iostream>

//this file is used to test the script

int main()
{
    // Test du constructeur avec le chemin d'une image
    Image img1("couleur.ppm");
    std::cout << "Image charg�e avec succ�s.\n";

    // Test de la m�thode displayImage
    std::cout << "Affichage de l'image originale :\n";
    img1.displayImage();

    // Test de la m�thode niveauxGris
    Image img2 = img1.niveauxGris();
    std::cout << "\nAffichage de l'image en niveaux de gris :\n";
    img2.displayImage();

    // Test de la m�thode composanteRouge
    Image img3 = img1.composanteRouge();
    std::cout << "\nAffichage de la composante rouge de l'image :\n";
    img3.displayImage();

    // Test de la m�thode noirEtBlanc
    Image img4 = img1.noirEtBlanc(128);
    std::cout << "\nAffichage de l'image en noir et blanc :\n";
    img4.displayImage();

    // Test de la m�thode histogrammeGris
    std::vector<int> histGris = img1.histogrammeGris();
    std::cout << "\nHistogramme en niveaux de gris :\n";
    for (int i = 0; i < histGris.size(); ++i)
    {
        std::cout << i << ": " << histGris[i] << " ";
    }
    std::cout << "\n";

    // Test de la m�thode histogrammeCouleur
    std::vector<std::vector<int>> histCouleur = img1.histogrammeCouleur();
    std::cout << "\nHistogramme de couleur :\n";
    for (int i = 0; i < histCouleur.size(); ++i)
    {
        std::cout << "Canal " << i << ": ";
        for (int j = 0; j < histCouleur[i].size(); ++j)
        {
            std::cout << j << ": " << histCouleur[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Test de la m�thode luminosityUp
    Image img5 = img1.luminosityUp(1.5);
    std::cout << "\nAffichage de l'image avec luminosit� augment�e :\n";
    img5.displayImage();

    // Test de la m�thode luminosityDown
    Image img6 = img1.luminosityDown(0.5);
    std::cout << "\nAffichage de l'image avec luminosit� diminu�e :\n";
    img6.displayImage();

    // Test de la m�thode retrecissement
    Image img7 = img1.retrecissement(2);
    std::cout << "\nAffichage de l'image r�tr�cie :\n";
    img7.displayImage();

    // Test de la m�thode agrandissement
    Image img8 = img7.agrandissement(2);
    std::cout << "\nAffichage de l'image agrandie apr�s r�tr�cissement :\n";
    img8.displayImage();

    // Test de la m�thode rotation
    Image img9 = img1.rotationD();
    std::cout << "\nAffichage de l'image tourn�e  :\n";
    img9.displayImage();

 Image img10 = Filtre::flouG3().application(img1);
    std::cout << "\nAffichage de l'image avec le filtre Flou G3 appliqu� :\n";
    img10.displayImage();

    return 0;
}

*/
