# Bienvenu sur le projet d'affichage NMEA 0183. 
## _On en a assez de Raymargarine!_



[![Build Status](https://github.com/guybel/afficheur?branch=main)](https://github.com/guybel/afficheur)

Frustré par les prix des produits Rayma.., vous penssez entreprendre de fabriquer votre propre afficheur de vitesse pour bateau. Ce projet DIY ingénieux ne vous coûte que 50 $, soit dix fois moins cher que les options commerciales. En utilisant des composants électroniques bon marché et vos compétences techniques, vous avez créé une alternative économique et personnalisée qui répond parfaitement à vos besoins nautiques.

## software:
Ce projet est fait sur Vs Code et Plateform.io. Vous trouverai les settings dans le fichier.ini du 	projet. 

## Matos:
    un m5stack core2 => 50$

## library:
    https://github.com/Glinnes/NMEAParser 

### sommaire de la library. 
On déclare un parser avec un certain nombre de code NMEA 0183 à parser. 
On redirige les flux série dans le parser comme suit:
```sh
            singlechar = client.read();        
            parser << singlechar;
```

## Fonctionnalités: 
- Lire directement des codes NMEA 0183sur le lien série du wifi.
- Lire et afficher la profondeur sur un M5core2.
- Lire et afficher le vitesse sur un M5core2.

## Code:

La première parti sert au branchement wifi. 
```sh
    const char* ssid = "NMEA2000-Gateway";
    const char* password = "password";
    const char * serverAddress = "192.168.4.1";
    const int serverPort = 2222; // Port série 2222
```
Déclaration des handler qui capte
```sh
NMEAParser<2> parser;

void handleDepthSounder(){
  float depth;
  if (parser.getArg(0, depth)){
    depthBelowKeel = depth;
  }
}
```


```sh
void handleSpeed()
{
  float speed;
  if (parser.getArg(4, speed)){
    speedOverWater = speed * 1.1 ;
  }
}
```
Quelque part dans setup()
```sh
 parser.addHandler("IIDBK", handleDepthSounder);
  parser.addHandler("VWVHW", handleSpeed);
```

## Dans loop():
Connect le client wifi et rammasse le flux (character par character ) 

```sh
 if (client.connect(serverAddress, serverPort)) {
 ...
  while (client.connected()) {
        
        if (client.available()) {
            singlechar = client.read();        
            parser << singlechar;
            }
      // a sentence is finish
      ... do something
  }
..
```
Pour plus de renseignements, vous pouvez me contacter at belleygu@hotmail.com
