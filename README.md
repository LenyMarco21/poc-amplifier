| Cibles supportées | ESP32-DevKitC |
| ----------------- | ----- |

Amplificateur Audio Bluetooth 
======================

Ce projet repose sur l'utilisation de la librairie Bluetooth A2DP/AVRCP d'Espressif afin de recevoir de la musique en bluetooth depuis un smartphone ou ordinateur et la diffuser ensuite sur des haut-parleurs.

Il s'agit d'un système audio 2.1 (2 enceintes satellites gauche/droite + 1 caisson de basse).

Le seul protocole de compression supporté à ce jour est SBC (44.1kHz / 16 bits), largement suffisant pour un projet audio amateur.

## Fonctionnement général

### I/O Hardware

| Broche    |I/O    | Signal       | Description                               |
| :-------- | :---- | :----------- | :---------------------------------------- |
| GPIO21    | I/O   | I2C SDA      | Data I2C                                  |
| GPIO22    | O     | I2C SCL      | Clock I2C                                 |
| GPIO25    | O     | I2S DATA     | Data I2S                                  |
| GPIO26    | O     | I2S LRCK     | Clock Synchro L/R I2S                     |
| GPIO27    | O     | I2S BCK      | Clock Principale I2S                      |
| GPIO33    | O     | /RESET       | Reset de l'amplificateur                  |
| GPIO34    | I     | /FAULT       | Faute de l'amplificateur                  |
| GPIO35    | I     | /CLIP        | Ecretage ou surchauffe de l'amplificateur |

### Codec Audio

#### Caractéristiques
Le codec audio utilisé pour convertir le flux PCM stéréo I2S en signal analogique est le TAD5212 de Texas Instruments.

Ce codec intègre :
* Résolution 32 bits
* Sampling rate jusqu'à 768 kHz
* 2 entrées microphone différentielles
* 2 sorties casque différentielles
* Rapport signal/bruit sur les sorties DAC de 120dB
* 1 Melangeur par voie
* 3 Filtres biquadratiques (IIR 2ème ordre) configurables par voie
* 1 Filtre passe haut IIR 1er ordre configurable par voie
* 1 Filtre d'interpolation configurable par voie 

En somme, il s'agit d'un IC audio pro dont les capacités sont assez impressionanntes.

Celui-ci est piloté en I2C pour attaquer ses registres internes (16 pages de 128 octets de registre chacune)

#### Fonctionnement logiciel

Le driver logiciel propose 2 modes de configuration :
* `COMMON` : configuration stéréo 2 voies (gauche et droite) biquad HPF 150Hz
* `SUBWOOFER` : configuration mono 1 voie (moyenne de gauche et droite) biquad LPF 150Hz

Le volume est piloté de -60dB à 0dB par step de 0.6dB (100 valeurs).

### Amplificateur Audio

L'amplificateur audio utilisé est le TPA3255 de Texas Instruments.

Celui-ci intègre 2 entrées différentielles pour 2 sorties différentielles de 315W chacune. 

En configuration l'IC en mono voie, la puissance de sortie atteint 600W.

Sa tension d'entrée admissible est comprise entre 18V et 51V.

Il présente 3 signaux utiles pour le logiciel :
* /RESET : désactive les sorties de l'amplificateur
* /FAULT : indique un défaut
* /CLIP_OTW : indique un écrêtage de la sortie ou un problème de température




 
