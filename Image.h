#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>

class Image
{
private:
    std::vector<std::vector<int>> rouge;
    std::vector<std::vector<int>> vert;
    std::vector<std::vector<int>> bleu;
    int longueur;
    int largeur;
    int hauteur;

public:
    std::vector<std::vector<int>> getRouge() const;
    std::vector<std::vector<int>> getBleu() const;
    std::vector<std::vector<int>> getVert() const;


    Image(const std::string &picture);
    Image(const std::vector<std::vector<int>> &r,
          const std::vector<std::vector<int>> &g,
          const std::vector<std::vector<int>> &b);


    int getHauteur() const;
    int getLargeur() const;
    int getLongueur() const;

    void setRouge(const std::vector<std::vector<int>>& newRouge);
    void setVert(const std::vector<std::vector<int>>& newVert);
    void setBleu(const std::vector<std::vector<int>>& newBleu);
    void afficher() const;


    void displayMenu() const;
    int getUserChoice();
    void displayImageInfo() const;
    void applyTransformation();
    void saveToPPM(const std::string &filename) const;
    bool detection(int rouge, int vert, int bleu) const;
    Image composanteRouge() const;
    Image niveauxGris() const;
    Image noirEtBlanc(int seuil) const;
    std::vector<int> histogrammeGris() const;
    std::vector<std::vector<int>> histogrammeCouleur() const;
    Image luminosityUp(double factor) const;
    Image luminosityDown(double factor) const;
    Image contrasteUp(double factor) const;
    Image contrasteDown(double factor) const;
    Image reglageAuto() const;
    Image reglageAutoGris() const;
    void displayImage() const;
    void displayComponent(const std::vector<std::vector<int>> &component) const;


    Image rognerD(int nb) const;
    Image rognerG(int nb) const;
    Image rognerH(int nb) const;
    Image rognerB(int nb) const;
    Image rotationD() const;
    Image rotationG() const;
    Image retournementH() const;
    Image retournementV() const;
    Image agrandissement(int factor) const;
    Image retrecissement(int factor) const;
    Image zoom(float k) const;
    std::vector<std::vector<int>>& operator[](size_t index) {
		if (index == 0) {
			return rouge;
		} else if (index == 1) {
			return vert;
		} else if (index == 2) {
			return bleu;
		} else {
			// Handle invalid index (throw an exception, return a default value, etc.)
			// For simplicity, this example throws an exception.
			throw 1;//std::out_of_range("Invalid channel index");
		}
	}
};

#endif // IMAGE_H
