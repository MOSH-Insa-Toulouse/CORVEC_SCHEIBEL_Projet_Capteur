# CORVEC_SCHEIBEL_Projet_Capteur

[Lien GitHub du projet ](https://github.com/MOSH-Insa-Toulouse/CORVEC_SCHEIBEL_Projet_Capteur)

Étudiantes en 4ème année Génie Physique à l’INSA (Institut National des Sciences Appliquées) de Toulouse ce ReadMe présente le projet réalisé dans le cadre de l’UF « Du capteur au banc de test ». L’objectif de ce projet est de designer et construire un PCB Shield incluant un capteur de déformation en graphite couplé à un circuit analogique. Un code Arduino permet de contrôler le tout et de communiquer les mesures du capteur vers une application Android.

## Sommaire 

- [1. Contexte du projet](#1-contexte-du-projet)  

- [2. Fabrication du capteur](#2-fabrication-du-capteur)  
    - [a. Kicad](#a-kicad)
    - [b. Réalisation du PCB](#b-réalisation-du-pcb)
- [3. Contrôle et interface du capteur](#3-contrôle-et-interface-du-capteur)
- [a. Code Arduino](#a-code-arduino)
- [b. Application Android](#b-application-android)
- [4. Banc de test](#4-banc-de-test)
- [5. Pistes d'amélioration](#5-pistes-damélioration)
- [6. Commentaires et conclusion](#6-commentaires-et-conclusion)

## 1. Contexte du projet

Le crayon papier est un objet du quotidien et fait partie intégrante de nos vies depuis bien longtemps. La mine d’un crayon est composée d'une fine poudre de graphite liées par des argiles. Lorsque l’on effectue des traces de crayons sur une feuille de papier (surface naturellement poreuse), des particules ultrafines de graphite se déplosent en surface. Ces traces sont des films minces conducteurs constituées de réseaux percolés. Elles peuvent ainsi jouer le rôle de conducteur passif dans divers dispositifs et peuvent être également utilisées en tant que conducteur actif dans des capteurs piézorésistifs. En 2014, les chercheurs Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang ont publié l’article « Pencil Drawn Strain Gauges and Chemiresistors on Paper » dans lequel ils démontrent que « les traces de crayon peuvent fonctionner non seulement comme des jauges de contrainte pour détecter les déflexions de compression et de traction, mais également comme des résistances chimiques sensibles aux vapeurs chimiques volatiles »[1]. 

Pour rappels : Les crayons en graphite sont désignés comme ceci :

- 9H à H (avec H9 le plus dur et léger)
- HB
- 9B à B (avec 9B le plus doux et sombre)

![type_craton](/Photos/type_crayon.png)

Les résultats présentés par l’équipe de chercheurs sont les suivants : les résistances mesurées sans contrainte pour des mines 9B, 6B, 2B, and HB sont respectivement de 200 kΩ, 500 kΩ, 2MΩ, 20 MΩ. Plus les mines sont douces et sombres (donc contenant plus de graphite) plus la résistance est faible.  
L’étude des chercheurs a révélé que les traces laissées par des crayons de duretés supérieures et égales à 2H ne pouvaient être mesurées, elles étaient donc non conductrices. Cependant les traces de crayons HB ont montré la plus grande réponse, elles se situeraient à priori juste au-dessus du seuil de percolation. Les mesures ont été réalisés via un programme Labview avec un compteur source Keithley 2400 d’une valeur de 5760€.  

À travers ce projet nous avons cherché à mesurer la valeur de résistance 2H et ce, avec un dispositif bas coût et facilement transportable.

## 2. Fabrication du capteur

Le capteur de déformation en graphite est une jauge de contrainte. Le principe consiste ici appliquer des forces de compression ou de traction sur une feuille de papier où a été déposé du graphite via un crayon papier (Figure 1).  Comme énoncé précédemment, les traces laissées par le crayon vont, sous compression ou traction, présenter une variation de résistance. Suite à cette faible variation, on mesure une tension, grâce à un circuit d'amplification transimpédance.

![capteur](/Photos/capteur.png)

Figure 1

### a. Kicad

La schématique du circuit a été créé via le logiciel LTSpice IV (Figures 2). La schématique présente une partie lecture analogique, nous utilisons un amplificateur trans-impédance. Il s’agit d’un convertisseur courant-tension permettant d’amplifier la sortie de courant du capteur.  Ce circuit trans-impédance à filtre passe-bas nous permet de récupérer les données du capteur de traction (pour plus de détails : voir notre datasheet, partie « Exemple d’intégration »). Une autre partie expose les modules pouvant être ajoutés sur la carte : un écran OLED, un Bluetooth et un encodeur rotatoire.  Après avoir généré la liste des empreintes des composants, nous avons pu concevoir notre PCB Shield grâce au logiciel KICAD (Figures 3).

![schématique](/Photos/schématique.png)

![schématique_modules](/Photos/schématique_modules.png)
![schématique_pins](/Photos/schématique_pins.png)

Figures 2

![shield](/Photos/shield.png)
![shield_3d](/Photos/shield_3d.png)
![shield_pdf](/Photos/shield_pdf.png)

Figures 3

### b. Réalisation du PCB

Le masque de notre PCB a ensuite été imprimé et placé sur une plaque recouverte d’une résine. La résine non protégée par le masque est exposée aux UV. Une solution basique attaque les dépôts de résine insolée pour révéler certaines zones du PCB. La plaque est ensuite chauffée dans une solution afin d'attaquer les zones de cuivre non désirées. Le PCB est ensuite percé et les différents composants y sont soudés (Figures 4).

![pcb_photo](/Photos/pcb_photo.png)
![pcb_final](/Photos/pcb_final.png)

Figures 4

## 3. Contrôle et interface du capteur

### a. Code Arduino

Le PCB se plug sur une carte Arduino (Figure 5). Le branchement est détaillé dans la datasheet. Le code Arduino ([lien code](/Arduino_code/Arduino_capteur_graphite.ino)) permet de :

- Lire la tension (ADC) délivrée par le capteur (capteur graphite + circuit amplificateur)
- D'envoyer la donnée vers l'application Android via la connection Blueotooth établie
- De calculer la resistance du capteur graphite équivalente à cette tension pour l'afficher sur l'écran OLED

![arduino](/Photos/arduino.png)

Figure 5

### b. Application Android

L'application Android affiche la valeur de la tension lue par l'ensemble du capteur. Elle calcule la valeur de la résistance en (Ohm) et l'affiche au dessus de la tension. Parallèlement un graphique montre la valeur de la résistance en fonction du temps.
L'îcone "Bluetooth" permet d'ouvrir la liste des appareils associés au smartphone pour établir la connexion Bluetooth avec le capteur.

![apk_interface](/Photos/apk_interface.jpg)

Cette application a été créée sur le site [MIT app inventor](https://appinventor.mit.edu/). Pour télécharger notre application, il faut ouvrir cette [apk](/Application_Android/Capteur.apk) depuis un smartphone.

## 4. Banc de test

Une fois le branchement du capteur effectué nous réalisons les mesures de caractérisation. Nous utilisons une pièce imprimée en 3D(Figure 6). Elle comporte 7 rayons différents, cela permet d’appliquer plusieurs contraintes connues à notre capteur. Pour nos mesures les diamètres notés R1 à R6 sont utilisés.

- ETAPE 1 : Dépôt du graphite à tester sur la feuille de papier, en coloriant.
- ETAPE 2 : Lecture de la valeur de l’offset, notée R0 grâce à l’écran OLED ou via l’application.
- ETAPE 3 : Application de la première contrainte au rayon R1 et lecture de la résistance R du capteur.
- ETAPE 4 : Calcul de ∆R.
- ETAPE 5 : Répétition des étapes 2, 3 et 4 jusqu’au rayon R6.
- ETAPE 6 : Calcul de la déformation appliquée pour chaque rayon.
- ETAPE 7 : Affichage de (∆R )/R en fonction de la déformation.

![Banc_test](/Photos/Banc_test.PNG)

Figure 6

![Schema_Banc](/Photos/Schema_Banc.PNG)

## 5. Pistes d'améliorations

Les différentes mesures effectuées ne sont pas répétables. Dès la première mesure du protocole de test, le capteur entre dans le domaine de non-détérioration, c’est-à-dire que ses caractéristiques métrologiques sont modifiées. En effet la résistance d'offset varie après chaque nouvelle contrainte appliquée, ce qui influe sur le résultat, d’où l’importance de relever avant chaque mesure la nouvelle valeur de R0. À partir des rayons R3 ou R4 nous entrons dans le domaine de non-destruction du capteur, les caractéristiques métrologiques sont modifiées de façon irréversible. L’offset devient de plus en plus important et il n’est plus possible de répéter les précédentes mesures sans entacher les résultats d’erreurs. Il est plutôt conseillé de changer de capteur, en effet lorsqu’une contrainte trop élevée est appliquée, les réseaux percolés sur graphite ne peuvent revenir à leur état d’origine.

Plusieurs pistes d’améliorations sont envisageables, sur différents éléments du capteur :

**Concernant la précision des mesures** du banc de test : les mesures effectuées sont peu répétables. En effet, entre chaque série de mesures les déformations appliquées peuvent varier (le banc de test ne permettant pas d’appliquer une déformation identique) tout comme la  concentration de graphite déposée sur le papier (manque de précision du coloriage).

Pour diminuer l’erreur sur les mesures, nous pourrions répéter les tests sur un grand nombre de capteurs équivalents et pour chaque contrainte, nous aurions ainsi une moyenne arithmétique de la valeur de résistance.

Un autre moyen d’améliorer la répétabilité des mesures, serait de fabriquer un banc de test plus précis et fiable, par exemple l’utilisation d’un banc de test contrôlé par un cervo moteur permettrait d’appliquer une contrainte beaucoup plus précise et répétable que la contrainte appliquée à la main sur la pièce 3D.

Concernant le **PCB** : Pour adapter les mesures des résistances en fonction des types de capteur (donc en fonction des différents types de graphite), il serait très utile de pouvoir modifier le gain de l’amplificateur transimpédance. Le gain est influencé par le rapport R2/R3, R3 est important pour le filtrage, c’est donc la résistance R2 qui permet de jouer sur le gain. Plutôt que de souder une résistance d’une valeur fixe, il serait alors judicieux de souder des plots. Ainsi le changement de R2 serait plus facile.

Enfin le **code Arduino** pourrait également être développé. Si des plots sont soudés sur le PCB pour pouvoir changer la résistance R2, alors l’Arduino pourrait gérer un encodeur rotatoire. Celui-ci permettrait de modifier la valeur de R2 dans le code, et ainsi faire le lien entre la résistance physique et la valeur de R2 dans les formules du code. Le code Arduino peut toujours être amélioré, d’autres fonctionnalités sont possibles, comme par exemple l’affichage d’un menu sur l’écran OLED. Ce menu permettrait d’entrer une nouvelle valeur de R2, de modifier la valeur de l’offset du capteur ou encore de changer la vitesse de transfert des données entre le capteur et l’application, etc…

## 6. Commentaires et conclusion

Les résultats des mesures effectuées sont disponibles dans notre datasheet. Nous pouvons apporter les commentaires suivants : plus une mine est douce, plus elle est concentrée en carbone et moins la variation de résistance est importante. En effet les réseaux percolés sont beaucoup plus denses et on a une meilleure conduction. Lorsqu’on applique une contrainte sur ce type de mine, les réseaux percolés, du fait de leur nombre, sont peu impactés. Ce qui pourrait expliquer pourquoi la mine la plus concentrée 6B a montré une variation de résistance quasiment constante. Les graphites 3B et B varient le plus linéairement. L'application d'une traction vient déconnecter les réseaux, on a une diminution de la conductivité. Les mines plus dures comme HB ou 2H creusent davantage le papier mais sont moins concentrées en carbone. Les mesures effectuées présentaient de très fortes variations de résistances et ces dernières étaient très instables, donc plus difficile à mesurer notamment le 2H. Cependant, malgré les grandes incertitudes sur ces mesures nous avons tout de même observé des variations de résistance sur le 2H contrairement aux chercheurs cités précédemment. Donc, la concentration en graphite du type 2H se situe probablement au-dessus du seuil de percolation.

Il est surprenant de réaliser un capteur de déformation avec si peu de matériel, une simple feuille de papier coloriée au crayon permet de mettre en évidence de faibles déformations. Cependant on notera que le capteur en graphite est très peu précis et relativement fragile, sans oublier qu’il manque fortement de répétabilité. Cet inconvénient est problématique pour un capteur, car il ne permet pas d'accéder de manière fiable à des valeurs de contraintes inconnues.
L’élaboration de ce capteur en graphite a permis de nous rendre compte de l’importance de certaines caractéristiques des capteurs. Ce projet nous a aussi fait découvrir l’Arduino, qui est très pratique par sa polyvalence et ses multiples applications.

Références :

[1] Lin, C.-W., Zhao, Z., Kim, J. & Huang, J. Pencil Drawn Strain
Gauges and Chemiresistors on Paper. Sci. Rep. 4, 3812; DOI:10.1038/srep03812 (2014)