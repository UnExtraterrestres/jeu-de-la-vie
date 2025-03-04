# jeu-de-la-vie
Ce projet est une version console du célèbre automate cellulaire imaginé par le mathématicien John Conway.

## Introduction

Le Jeu de la Vie est un modèle mathématique fascinant qui simule l'évolution des cellules sur une grille en fonction de règles simples. Chaque cellule peut être dans l'un des deux états : vivante ou morte. Les cellules évoluent en fonction de l'état de leurs voisines, créant ainsi des motifs complexes et parfois surprenants.

## Fonctionnalités

  Interface conviviale : Visualisez facilement l'état de la grille dans la console.
  Simulation automatique : Laissez le jeu évoluer automatiquement selon les règles prédéfinies.

## Comment utiliser

  Clonez le repository sur votre machine locale.
  Construisez l'executable :
    `make`
  
  L'expérience est meilleure en nettoyant la console :
  	`clear`
  
  Exécutez l'exécutable généré :
  	`./bin/jeu2lavie [SEED]`

## Règles du Jeu de la Vie

Les règles du jeu sont simples :

  Toute cellule vivante avec deux ou trois voisines vivantes survit à la génération suivante.
  Toute cellule vivante avec moins de deux voisines vivantes meurt de solitude.
  Toute cellule vivante avec plus de trois voisines vivantes meurt de surpopulation.
  Toute cellule morte avec exactement trois voisines vivantes devient une cellule vivante par reproduction.

## Contribution

Si vous avez des idées pour améliorer le jeu ou corriger des bugs, n'hésitez pas à contribuer.

## Licence

Ce projet est sous licence MIT. Consultez le fichier LICENSE pour plus de détails.
