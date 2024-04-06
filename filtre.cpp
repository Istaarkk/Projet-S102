#include "filtre.h"
#include "Image.h"

//Filtre.h

Filtre::Filtre(const std::vector<std::vector<float>>& matrice, float facteur) : matrice(matrice), facteur(facteur) {}

std::vector<std::vector<int>> Filtre::applyFilter(const std::vector<std::vector<int>>& composante) const
{
    int hauteur = composante.size();
    int largeur = (hauteur > 0) ? composante[0].size() : 0;

    // Initialiser la matrice résultante avec des zéros
    std::vector<std::vector<int>> resultat(hauteur, std::vector<int>(largeur, 0));
    int rayon = 1;
    // Appliquer le filtre à chaque pixel de l'image
    for (size_t x = 0; x < largeur; ++x)
    {
        for (size_t y = 0; y < hauteur; ++y)
        {

            for (int i = -rayon; i <= rayon; ++i)
            {
                for (int j = -rayon; j <= rayon; ++j)
                {
                    if (x + static_cast<size_t>(i) < largeur &&
                            y + static_cast<size_t>(j) < hauteur)
                    {
                        resultat[x][y] +=
                            static_cast<int>(matrice[i + rayon][j + rayon] * composante[x + static_cast<size_t>(i)][y + static_cast<size_t>(j)]);
                    }
                }
            }
        }
    }

/*
    for (int i = 1; i < hauteur - 1; ++i)
    {
        for (int j = 1; j < largeur - 1; ++j)
        {
            resultat[i][j] =
                (composante[i - 1][j - 1] + 16 * composante[i - 1][j] + composante[i - 1][j + 1] +
                 8 * composante[i][j - 1] + composante[i][j] + 8 * composante[i][j + 1] +
                 composante[i + 1][j - 1] + 16 * composante[i + 1][j] + composante[i + 1][j + 1]) /
                50;
        }
    }*/

    return resultat;
}


Image Filtre::application(const Image& image2) const
{
    /*
    // Appliquer le filtre à chaque composante de l'image (rouge, vert, bleu)
    std::vector<std::vector<int>> rougeFiltre = applyFilter(image.getRouge());
    std::vector<std::vector<int>> vertFiltre = applyFilter(image.getVert());
    std::vector<std::vector<int>> bleuFiltre = applyFilter(image.getBleu());
    */
    Image image= image2;
    Image output(image);
    int rayon = 1; //TODO: remove
    for (size_t x = 0; x < image.getLargeur(); ++x) {
		for (size_t y = 0; y < image.getLongueur(); ++y) {
			for (size_t channel = 0; channel < 3; ++channel) {
				output[channel][x][y] = 0;

				for (int i = -rayon; i <= rayon; ++i) {
					for (int j = -rayon; j <= rayon; ++j) {
						if (x + static_cast<size_t>(i) < image.getLargeur() &&
							y + static_cast<size_t>(j) < image.getLongueur()) {
							output[channel][x][y] +=
								static_cast<int>(matrice[i + rayon][j + rayon] * image[channel][x + static_cast<size_t>(i)][(y + static_cast<size_t>(j))] );
						}
					}
				}
			}
		}
	}

    // Créer et retourner une nouvelle image avec les composantes filtrées
    return output;//Image(rougeFiltre, vertFiltre, bleuFiltre);
}

Filtre Filtre::flouG3()
{
    // Définir le filtre flouG3
    std::vector<std::vector<float>> flouG3Action =
    {
        {1.f/16.f, 1.f/8.f, 1.f/16.f},
        {1.f/8.f,  1.f/4.f, 1.f/8.f},
        {1.f/16.f, 1.f/8.f, 1.f/16.f}
    };

    return Filtre(flouG3Action, 1.0 / 50.0);
}
/*
Filtre Filtre::flouG5()
{
    // Définir le filtre flouG3
    std::vector<std::vector<float>> flouG5Action ={
	{01.f, 04.f, 06.f, 04.f, 01.f},
	{04.f, 16.f, 24.f, 16.f, 04.f},
	{06.f, 24.f, 36.f, 24.f, 06.f},
	{04.f, 16.f, 24.f, 16.f, 04.f},
	{01.f, 04.f, 06.f, 04.f, 01.f}
    };

    return Filtre(flouG5Action, 1.0 / 50.0);
}
*/
