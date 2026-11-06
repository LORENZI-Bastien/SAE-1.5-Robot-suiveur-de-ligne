# SAÉ 1.5 · Programmer un robot suiveur de ligne

> Programmation d’un robot autonome qui fait trois tours d’un circuit en 8, change la couleur de sa LED à chaque tour et revient à son point de départ.

| | |
|---|---|
| **Formation** | BUT Réseaux et Télécommunications, Montbéliard |
| **Année** | 1<sup>re</sup> année, semestre 1 |
| **Organisation** | En binôme, sur 3 jours (janvier 2025) |
| **Outils et notions** | `Arduino` `C++` `Capteurs infrarouges` `Moteurs` `LED RGB NeoPixel` |

## Le défi

Parmi les challenges proposés, nous avons choisi le **défi n° 1** : faire parcourir au robot trois tours d’un circuit en forme de 8, changer la couleur des LED à chaque tour, puis le ramener sur sa ligne de départ.

## Déroulé

- **Jour 1** : calibration des capteurs et premières stratégies de déplacement (vitesse, angles, distances entre croisements).
- **Jour 2** : code de déplacement finalisé, puis gestion des LED. Le robot détectait de faux croisements dans certains virages, quand ses trois capteurs passaient en même temps sur la bande noire : nous avons revu la logique de détection.
- **Jour 3** : rédaction du rapport et préparation de la soutenance du 16 janvier 2025.

[Vidéo du robot sur YouTube](https://youtu.be/jW6hT_Eip9o)

## Le code

[`code/robot-suiveur/robot-suiveur.ino`](code/robot-suiveur/robot-suiveur.ino) : lecture des capteurs avec un seuil de détection de ligne, commande des deux moteurs, détection des croisements pour compter les tours et changement de couleur de la LED RGB (vert, bleu, orange, rouge).

Pour le téléverser : ouvrir le dossier `code/robot-suiveur` dans l’IDE Arduino et installer la bibliothèque **Adafruit NeoPixel**.

## Contenu du dépôt

| Fichier | Description |
|---|---|
| [`code/robot-suiveur/robot-suiveur.ino`](code/robot-suiveur/robot-suiveur.ino) | Programme Arduino du robot |
| [`rapport/journal-de-bord-sae-1.5.pdf`](rapport/journal-de-bord-sae-1.5.pdf) | Journal de bord des trois jours |
| [`consignes/sujet-sae-1.5.pdf`](consignes/sujet-sae-1.5.pdf) | Sujet de la SAÉ fourni par l’IUT |

---

<sub>Bastien Lorenzi · BUT Réseaux et Télécommunications, parcours cybersécurité · [Portfolio](https://bastien-lorenzi.netlify.app/#projets) · [Profil GitHub](https://github.com/LORENZI-Bastien)</sub>
