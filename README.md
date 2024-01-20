# Projet-S102
# Projet Image

Ce projet est une application de traitement d'images en C++. Il offre plusieurs fonctionnalités pour manipuler et transformer des images.

## Comment lancer le programme

1. Assurez-vous d'avoir un compilateur C++ installé sur votre système.
2. Clonez le dépôt depuis [lien du dépôt] ou téléchargez les fichiers source.
3. Compilez le programme en utilisant le compilateur C++.

Exemple de compilation avec g++ :

g++ -o Image.h main.cpp Image.cpp Filtre.cpp utils.cpp -std=c++11


4. Exécutez le programme généré :


## Fonctionnalités incluses

- **Chargement d'image**
- Chargez une image PPM depuis un fichier.

- **Affichage d'informations sur l'image**
- Affiche les détails de l'image, y compris les dimensions et les composantes couleur.

- **Transformation d'image**
- Plusieurs transformations sont disponibles, telles que la composante rouge, niveaux de gris, noir et blanc, etc.

- **Enregistrement d'image**
- Enregistrez l'image modifiée au format PPM.

- **Opérations avancées**
- Composante Rouge
- Niveaux de Gris
- Noir et Blanc
- Histogramme - Niveaux de Gris
- Histogramme - Couleur
- Luminosité Up/Down
- Contraste Up/Down
- Rogner
- Rotation
- Retournement Horizontal/Vertical
- Agrandissement/Retrecissement
- Afficher
- Filtre flouG3

- **Quitter**
- Quittez l'application.

## Utilisation

1. Au lancement, le programme affiche un menu principal.
2. Sélectionnez l'option correspondant à l'action que vous souhaitez effectuer.
3. Suivez les instructions à l'écran pour effectuer des opérations spécifiques.
4. Pour revenir au menu principal à partir des opérations avancées, choisissez l'option appropriée.

