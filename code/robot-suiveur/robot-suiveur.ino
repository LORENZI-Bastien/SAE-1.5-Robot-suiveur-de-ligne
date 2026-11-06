#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Définition des broches des moteurs et de la LED
#define PIN_Motor_PWMA 5  // Broche pour la commande de la vitesse du moteur A
#define PIN_Motor_PWMB 6  // Broche pour la commande de la vitesse du moteur B
#define PIN_Motor_BIN_1 8 // Broche pour la commande du moteur B (direction)
#define PIN_Motor_AIN_1 7 // Broche pour la commande du moteur A (direction)
#define PIN_Motor_STBY 3  // Broche pour activer ou désactiver les moteurs
#define PIN_LED 4         // Broche pour contrôler la LED RGB

const int seuilLigne = 640; // Seuil pour la détection de la ligne, valeur à ajuster selon les capteurs

Adafruit_NeoPixel rgbLed(1, PIN_LED, NEO_GRB + NEO_KHZ800); // Définition de la LED RGB connectée à PIN_LED

// Définition des couleurs de la LED RGB
const uint32_t COULEUR_VERT = rgbLed.Color(0, 255, 0);
const uint32_t COULEUR_BLEU = rgbLed.Color(0, 0, 255);
const uint32_t COULEUR_ORANGE = rgbLed.Color(255, 69, 0);
const uint32_t COULEUR_ROUGE = rgbLed.Color(255, 0, 0);
const uint32_t COULEUR_JAUNE = rgbLed.Color(255, 255, 0);

bool precedentCroisement = false; // Permet de savoir si un croisement a été détecté précédemment
int compteurTours = 0; // Compteur des croisements

// Classe CarMotors pour contrôler les moteurs
class CarMotors {
  private:
    uint8_t currentSpeed; // Vitesse actuelle des moteurs
    bool isMoving;        // Indique si le robot est en mouvement ou non

  public:
    // Initialisation des broches pour les moteurs et réglage de la vitesse initiale
    void init(uint8_t p_speed) {
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(8, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(3, OUTPUT);
      setSpeed(p_speed);
      stop();  // Le robot est initialement arrêté
    }

    // Réglage de la vitesse de rotation des moteurs
    void setSpeed(uint8_t p_speed) {
      currentSpeed = p_speed;
    }

    // Fait avancer le robot
    void goForward() {
      digitalWrite(3, 1);   // Active les moteurs
      digitalWrite(7, 1);  // Moteur A en avant
      digitalWrite(8, 1);  // Moteur B en avant
      analogWrite(5, currentSpeed); // Régle la vitesse du moteur A
      analogWrite(6, currentSpeed); // Régle la vitesse du moteur B
      isMoving = true;
    }

    // Fait reculer le robot
    void goBackward() {
      digitalWrite(3, 1);   // Active les moteurs
      digitalWrite(7, 0);   // Moteur A en arrière
      digitalWrite(8, 0);   // Moteur B en arrière
      analogWrite(5, currentSpeed); // Régle la vitesse du moteur A
      analogWrite(6, currentSpeed); // Régle la vitesse du moteur B
      isMoving = true;
    }

    // Fait tourner le robot vers la gauche sur place
    void turnLeft() {
      digitalWrite(3, 1);   // Active les moteurs
      digitalWrite(7, 0);   // Moteur A en arrière
      digitalWrite(8, 1);  // Moteur B en avant
      analogWrite(5, currentSpeed); // Régle la vitesse du moteur A
      analogWrite(6, currentSpeed); // Régle la vitesse du moteur B
      isMoving = true;
    }

    // Fait tourner le robot vers la droite sur place
    void turnRight() {
      digitalWrite(3, 1);   // Active les moteurs
      digitalWrite(7, 1);  // Moteur A en avant
      digitalWrite(8, 0);   // Moteur B en arrière
      analogWrite(5, currentSpeed); // Régle la vitesse du moteur A
      analogWrite(6, currentSpeed); // Régle la vitesse du moteur B
      isMoving = true;
    }

    // Arrête le robot
    void stop() {
      digitalWrite(3, 0);   // Désactive les moteurs
      analogWrite(5, 0);      // Arrête le moteur A
      analogWrite(6, 0);      // Arrête le moteur B
      isMoving = false;
    }

    // Permet de contrôler les vitesses indépendantes des roues gauche et droite
    void drive(float leftCoef, float rightCoef) {
      digitalWrite(3, 1);   // Active les moteurs
      digitalWrite(7, 1);  // Moteur A en avant
      digitalWrite(8, 1);  // Moteur B en avant
      analogWrite(5, currentSpeed * leftCoef); // Vitesse du moteur A
      analogWrite(6, currentSpeed * rightCoef); // Vitesse du moteur B
      isMoving = true;
    }
};

CarMotors car;  // Crée un objet car de la classe CarMotors

void setup() {
  car.init(120); // Initialisation du robot avec une vitesse de 150
  rgbLed.begin(); // Initialisation de la LED RGB
  rgbLed.setPixelColor(0, COULEUR_ROUGE); // Définit la LED en rouge
  rgbLed.show(); // Affiche la couleur
  delay(3000); // Attends 3 secondes
  rgbLed.setPixelColor(0, COULEUR_VERT); // Change la LED en vert
  rgbLed.show(); // Affiche la couleur
  Serial.begin(9600); // Démarre la communication série
}

void loop() {
  // Lecture des capteurs de ligne
  int gauche = analogRead(A0);  // Lecture du capteur gauche
  int centre = analogRead(A1);  // Lecture du capteur central
  int droite = analogRead(A2);  // Lecture du capteur droit

  // Logique de suivi de ligne
  if (centre > seuilLigne) {  // Si le capteur central détecte la ligne
    car.goForward();  // Avance
  } else if (gauche > seuilLigne) {  // Si le capteur gauche détecte la ligne
    car.turnLeft();   // Tourne à gauche
  } else if (droite > seuilLigne) {  // Si le capteur droit détecte la ligne
    car.turnRight();  // Tourne à droite
  } else {
    car.stop();  // Si aucun capteur ne détecte la ligne, arrête le robot
  }

  // Détection des croisements (si tous les capteurs détectent la ligne)
  bool croisement = (gauche > seuilLigne && centre > seuilLigne && droite > seuilLigne);

  if (croisement && !precedentCroisement) {
    compteurTours++; // Incrémente le compteur de tours
    Serial.println("Croisement détecté. Compteur de tours : " + String(compteurTours));

    // Change la couleur de la LED en fonction du nombre de tours
    if (compteurTours == 1) {
      rgbLed.setPixelColor(0, COULEUR_VERT);
    } else if (compteurTours == 3) {
      rgbLed.setPixelColor(0, COULEUR_BLEU);
    } else if (compteurTours == 5) {
      rgbLed.setPixelColor(0, COULEUR_ORANGE);
    } else if (compteurTours >= 7) {
      rgbLed.setPixelColor(0, COULEUR_JAUNE);
      rgbLed.show();
      delay(250); // Petite pause avant la marche arrière
      car.goBackward();
      delay(375); // Recule légèrement pour repasser derrière la ligne
      car.stop();
      while (true);
    }
    
    rgbLed.show();  // Affiche la nouvelle couleur de la LED
    precedentCroisement = true; // Mémorise qu'un croisement a eu lieu
  } else if (!croisement) {
    precedentCroisement = false; // Réinitialise l'état du croisement
  }

  delay(20); // Attente avant de refaire une nouvelle lecture des capteurs
}
