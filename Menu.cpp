#include "Image.h"
#include "utils.h"
#include <iostream>
#include <fstream>
//this is a version of the first menue

void Image::displayImageInfo() const {
    int hauteur = rouge.size();
    int longueur = (hauteur > 0) ? rouge[0].size() : 0;

    std::cout << "Largeur : " << longueur << " Hauteur : " << hauteur << std::endl;
}

void Image::saveToPPM(const std::string &filename) const {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }

    // Write the PPM header
    outputFile << "P3\n";
    outputFile << largeur << " " << longueur << "\n";
    outputFile << "255\n";

    // Write the pixel values
    for (int i = 0; i < longueur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            outputFile << rouge[i][j] << " " << vert[i][j] << " " << bleu[i][j] << " ";
        }
        outputFile << "\n";
    }

    std::cout << "Image sauvegardée dans : " << filename << std::endl;
}

void Image::applyTransformation() {
    int choix;
    do {
        displayMenu();
        choix = getUserChoice();
        switch (choix) {
            case 1:
                displayImageInfo();
                break;
            case 2:
                saveToPPM("output.ppm");
                break;
            case 3:
                composanteRouge().displayImageInfo();
                break;
            case 4:
                noirEtBlanc(128).displayImageInfo();
                break;
            case 5:
                // Uncomment the following line once implemented
                // displayHistogramGris();
                break;
            case 6:
                // Uncomment the following line once implemented
                // displayHistogramCouleur();
                break;
            case 7:
                luminosityUp(1.2).displayImageInfo();
                break;
            case 8:
                luminosityDown(0.8).displayImageInfo();
                break;
            case 9:
                contrasteUp(1.2).displayImageInfo();
                break;
            case 10:
                contrasteDown(0.8).displayImageInfo();
                break;
            case 11:
                //reglageAuto().displayImageInfo();
                break;
            case 12:
                //reglageAutoGris().displayImageInfo();
                break;
            case 0:
                std::cout << "Programme terminé.\n";
                break;
            default:
                std::cout << "Choix non valide. Veuillez réessayer.\n";
                break;
        }
    } while (choix != 0);
}

int Image::getUserChoice() {
    int choix;
    std::cout << "Entrez votre choix : ";
    std::cin >> choix;
    return choix;
}

void Image::displayMenu() const {
    std::cout << "Menu :\n";
    std::cout << "1. Afficher les informations de l'image\n";
    std::cout << "2. Sauvegarder l'image\n";
    std::cout << "3. Afficher la composante rouge\n";
    std::cout << "4. Convertir en noir et blanc\n";
    std::cout << "5. Afficher l'histogramme de l'image en niveaux de gris\n";
    std::cout << "6. Afficher l'histogramme de l'image en couleur\n";
    std::cout << "7. Augmenter la luminosité\n";
    std::cout << "8. Diminuer la luminosité\n";
    std::cout << "9. Augmenter le contraste\n";
    std::cout << "10. Diminuer le contraste\n";
    std::cout << "11. Réglage automatique\n";
    std::cout << "12. Réglage automatique en niveaux de gris\n";
    std::cout << "0. Quitter\n";
}
