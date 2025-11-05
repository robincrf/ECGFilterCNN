import matplotlib.pyplot as plt
import os

# Get the directory of the current script and build the path to the data file
script_dir = os.path.dirname(os.path.abspath(__file__))
data_file = os.path.join(script_dir, "..", "data", "only_data.csv")

signals = []
with open(data_file, "r", encoding="utf-8") as f:
    for ligne in f:
        # Skip empty lines and convert values to float
        ligne = ligne.strip()
        if ligne:  # Only process non-empty lines
            signals.append(float(ligne))

# Création de la figure
plt.figure(figsize=(12, 6))  # Taille de la figure en pouces

# Tracé du signal ECG
plt.plot(signals, 'b-', label='Signal ECG')  # 'b-' pour ligne bleue continue

# Personnalisation du graphique
plt.title('Visualisation du signal ECG')
plt.xlabel('Échantillons')
plt.ylabel('Amplitude')
plt.grid(True, linestyle='--', alpha=0.7)  # Grille en pointillés
plt.legend()

# Afficher le graphique
plt.show()