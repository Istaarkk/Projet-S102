#include <iostream>
#include "Image.h"
#include "filtre.h"
#include "utils.h"
#include <vector>
#include <stdexcept>
//main.cpp

int main()
{
    std::string fileName;
    std::vector<std::vector<int>> rouge = {{255, 255, 0, 0}, {255, 0, 0, 0}, {0, 0, 0, 0}};
    std::vector<std::vector<int>> vert = {{0, 255, 255, 255}, {0, 255, 255, 255}, {255, 255, 255, 0}};
    std::vector<std::vector<int>> bleu = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 255, 255, 255}};

    Image img(rouge, vert, bleu);
    img.displayImage();

    int mainChoice;
    int subChoice;

    do
    {
        // Afficher le menu principal
        std::cout << "\nMain Menu:\n"
                  << "1. Load PPM\n"
                  << "2. Display Image Info\n"
                  << "3. Apply Transformation\n"
                  << "4. Save Image\n"
                  << "5. Advanced Operations\n"
                  << "6. Quit\n"
                  << "Enter your choice: ";
        std::cin >> mainChoice;

        switch (mainChoice)
        {
        case 1:
            fileName = getFileNameFromUser();
            img = Image(fileName);
            break;
        case 2:
            img.displayImage();
            break;
        case 3:
            // img.applyTransformation();
            break;
        case 4:
            img.saveToPPM("New_Image.ppm");
            break;
        case 5:
            do
            {
                std::cout << "\nAdvanced Operations Menu:\n"
                          << "1. Composante Rouge\n"
                          << "2. Niveaux de Gris\n"
                          << "3. Noir et Blanc\n"
                          <<"4. Detection \n"
                          << "5. Histogramme - Niveaux de Gris\n"
                          << "6. Histogramme - Couleur\n"
                          << "7. Luminosité\n"
                          << "8. Contraste\n"
                          << "9. Rogner\n"
                          << "10. Rotation\n"
                          << "11. Retournement\n"
                          << "12. Agrandissement/Retrecissement\n"
                          << "13. Afficher\n"
                          << "14. Filtres\n"
                          << "15. Back to Main Menu\n"
                          << "Enter your choice: ";
                std::cin >> subChoice;

                switch (subChoice)
                {
                case 1:
                    img = img.composanteRouge();
                    img.displayImage();
                    break;
                case 2:
                    img = img.niveauxGris();
                    img.displayImage();
                    break;
                case 3:
                    img = img.noirEtBlanc(128);
                    img.displayImage();
                    break;
                case 4:
                    if(img.detection(255,0,0))
                    {
                        std::cout<<"The color is on the picture"<<std::endl;
                    }
                    else
                    {
                        std::cout<<"The Color is not on the picture"<<std::endl;
                    }
                    break;
                case 5:
                {
                    std::vector<int> histogrammeGris = img.histogrammeGris();
                    for (int valeur : histogrammeGris)
                    {
                        std::cout << valeur << " ";
                    }
                    std::cout << "\n";
                    break;
                }
                case 6:
                {
                    std::vector<std::vector<int>> histogrammeCouleur = img.histogrammeCouleur();
                    for (const auto &ligne : histogrammeCouleur)
                    {
                        for (int valeur : ligne)
                        {
                            std::cout << valeur << " ";
                        }
                        std::cout << "\n";
                    }
                    break;
                }

                case 7:
                    std::cout << "\nSub-menu Luminosity:\n"
                              << "1. Luminosity Up\n"
                              << "2. Luminosity Down\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.luminosityUp(1.5);img.displayImage();}
                    else if (subChoice == 2){
                        img = img.luminosityDown(0.5);
                        img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 8:
                    std::cout << "\nSub-menu Contrast:\n"
                              << "1. Contrast Up\n"
                              << "2. Contrast Down\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.contrasteUp(1.5);img.displayImage();}
                    else if (subChoice == 2){
                        img = img.contrasteDown(0.5);
                        img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 9:
                    std::cout << "\nSub-menu Crop:\n"
                              << "1. Crop Right\n"
                              << "2. Crop Left\n"
                              << "3. Crop Top\n"
                              << "4. Crop Bottom\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.rognerD(1);img.displayImage();}
                    else if (subChoice == 2){
                        img = img.rognerG(1);
                        img.displayImage();}
                    else if (subChoice == 3){
                        img = img.rognerH(1);img.displayImage();}
                    else if (subChoice == 4){
                       img = img.rognerB(1);
                        img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 10:
                    std::cout << "\nSub-menu Rotation:\n"
                              << "1. Rotate Right\n"
                              << "2. Rotate Left\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.rotationD();
                        img.displayImage();}
                    else if (subChoice == 2){
                        img = img.rotationG();
                        img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 11:
                    std::cout << "\nSub-menu Flip:\n"
                              << "1. Flip Horizontal\n"
                              << "2. Flip Vertical\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.retournementH();
                        img.displayImage();}
                    else if (subChoice == 2){
                        img=img.retournementV();img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 12:
                    std::cout << "\nSub-menu Resize:\n"
                              << "1. Enlarge\n"
                              << "2. Shrink\n"
                              << "Enter your choice: ";
                    std::cin >> subChoice;
                    if (subChoice == 1){
                        img = img.agrandissement(2);
                        img.displayImage();}
                    else if (subChoice == 2){
                        img = img.retrecissement(2);
                        img.displayImage();}
                    else
                        std::cout << "Invalid choice. Returning to the main menu.\n";
                    break;
                case 13:
                    img.afficher();
                    break;
                case 14:
                    do
                    {
                        std::cout << "\nSub-menu Filters:\n"
                                  << "1. Blur G3\n"
                                  << "2. Blur G5\n"
                                  << "3. Back to Advanced Operations Menu\n"
                                  << "Enter your choice: ";
                        std::cin >> subChoice;
                        switch (subChoice)
                        {
                        case 1:
                            img = Filtre::flouG3().application(img);
                            break;
                        case 2:
//                            img = Filtre::flouG5().application(img);
                            break;
                        case 3:
                            break;
                        default:
                            std::cout << "Invalid choice. Returning to the Advanced Operations Menu.\n";
                        }
                    }
                    while (subChoice != 3);
                    break;
                case 15:
                    break;  // Retour au menu principal
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            while (subChoice != 15);

            break;
        case 6:
            std::cout << "Program terminated.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    while (mainChoice != 6);

    return 0;
}
