🫀 Projet d’Analyse et Détection d’Arhythmies Cardiaques en C++
Objectif
Ce projet implémente une chaîne de traitement complète des signaux ECG pour la détection automatique d’anomalies cardiaques (arythmies).
L’objectif est de :
Lire des signaux ECG bruts (fichiers texte ou CSV),
Extraire les métadonnées (fréquence d’échantillonnage, label, taille, etc.),
Prétraiter les signaux : centrage, filtrage, normalisation,
Préparer les données pour des algorithmes d’apprentissage automatique.

   Étapes du pipeline
 
1 Extraction et stockage
Chaque signal ECG est encapsulé dans une classe ECGmetadata :
signal : vecteur d’échantillons (ex. 256 valeurs),
label : type de battement (N, V, S, etc.),
fs : fréquence d’échantillonnage (souvent 360 Hz),
length : taille de la fenêtre (ex. 256 échantillons),
Méthodes : accesseurs (getSignal(), getLabel(), etc.).
Les signaux sont lus depuis un fichier brut :
fs=360,centered=R,length=256,label=N
0.02,0.05,0.12,0.35, ...
...
fs=360,centered=R,length=256,label=V
...
 Chaque bloc devient un objet ECGmetadata stocké dans :
std::vector<ECGmetadata> allECG;

2 Prétraitement du signal

a) Detrend
Retire la composante lente ou constante (ligne de base) :
Soustraction de la moyenne (centrage),
Optionnellement, suppression d’une pente linéaire si dérive visible.

b) Filtre Savitzky–Golay
Lissage polynomiale local pour réduire le bruit sans déformer le QRS :
Fenêtre = 11 points (≈30 ms à 360 Hz),
Ordre du polynôme = 3,
Application aller-retour (zéro-phase) pour conserver la position du pic R.
Avantage : supprime le bruit haute fréquence tout en préservant la forme physiologique du signal.
 
c) Z-score
Normalisation pour rendre les signaux comparables :

 
Peut être appliqué :
par signal (centrage + écart-type individuel),
par position (même moyenne et écart-type sur tout le dataset).
3 Organisation des données
Les signaux sont ensuite regroupés selon leur label :
std::map<std::string, std::vector<std::vector<double>>> signalsByClass;
Exemple :
signalsByClass["N"] → battements normaux,
signalsByClass["V"] → battements ventriculaires.
4️ Visualisation
Les signaux prétraités peuvent être visualisés :
Axe x : indices d’échantillons (0–255),
Axe y : amplitude centrée et normalisée,
Le pic R doit rester centré et non décalé après filtrage.
 Théorie des filtres utilisés
Étape	Type de filtre	Effet principal	Remarques
Detrend	Passe-haut (0 Hz)	supprime dérive lente	ligne de base stabilisée
SG (11,3)	Passe-bas doux (~15–20 Hz)	lisse bruit HF	préserve les pentes
Aller-retour	compensation de phase	évite le décalage du pic R	indispensable
Z-score	normalisation statistique	comparabilité	sans effet sur la forme

 Compilation et exécution
Compilation (avec g++)
g++ -std=c++17 -O2 src/*.cpp -I includes -o ecg_analyzer
