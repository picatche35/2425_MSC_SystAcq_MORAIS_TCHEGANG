# Readme
# TP SysAcq MORAIS TCHEGANG
Ce dossier contient notre travail sur l'asservissement d'un moteur avec STM32
Pour cette première séance nous avons procédé à la création de notre git ensuite nous avons téléchargé le projet

 #   TP1 Console UART
L'objectif principal est de fournir une vue d'ensemble des fonctionnalités de la liaison UART ainsi que des étapes nécessaires à sa configuration. Cette partie servira de base pour des applications plus avancées, telles que le contrôle du moteur et la communication avec d'autres périphériques. Nous allons maintenant passer à la configuration des différents éléments nécessaires pour la mise en œuvre de cette fonctionnalité UART.
A partir du Shell nous avons procédé au traitement des Commandes suivantes: 
  - help : Affiche toutes les commandes disponibles;
  - powerOn: qui allume le moteur;
  - powerOff: qui arrête le moteur.

 #   TP2 Commande MCC basique
L'objectif dans ce second TP est de:
  - Générer 4 PWM en complémentaire décalée pour contrôler en boucle ouverte le moteur en respectant le cahier des charges,
  - Inclure le temps mort,
  - Vérifier les signaux de commande à l'oscilloscope,
  - Prendre en main le hacheur,
  - Faire un premier essai de commande moteur
Nous avons généré les PWM à partir du TIM1 et nous avons inclu le deadTime à 160
![image](https://github.com/user-attachments/assets/dbc310a5-9e89-455d-9348-2ff85f9bf0ce)
![image](https://github.com/user-attachments/assets/32708df7-134d-43fe-9078-3b5f885a2dd2)
Nous avons obtenus les PWM suivantes en fonction du rapport cyclique de 50 et 70 et nous avons pris le soin d'inclure une fonction speed pour faire les variations de vitesse:
![image](https://github.com/user-attachments/assets/62f1f6c5-3448-4135-8614-a4d480e3b288)
![image](https://github.com/user-attachments/assets/c04a910b-f0d7-45d4-b593-6b0777caf9bf)




#   TP3 Commande en boucle ouverte, mesure de Vitesse et de courant





