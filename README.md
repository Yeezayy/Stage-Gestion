# Stage-Gestion

Stage-Gestion est un projet réalisé dans le cadre scolaire dans laquelle nous devions réaliser est une application en ligne de commande.
Cette dernière permettait la gestion des stages au sein d'un département informatique : offres de stages, candidatures et affectation des étudiants puis notation de chaque stage par un jury.

## Fonctionnalités
- **Suivi des stages** : Gère une liste d'offres de stage avec leurs références.
- **Statut des offres** : Indique si une offre est pourvue ou non.
- **Gestion des candidatures** : Suivi du nombre de candidatures reçues pour chaque offre (maximum 3 candidatures).
- **Gestion des étudiants** : Suivi des stages attribués aux étudiants ainsi que leurs notes finales.

## Structure des Fichiers

### `offres_stage.txt`
Ce fichier contient les informations sur les offres de stage et suit le format suivant :
```
<référence offre> <département> 
<statut pourvu (0 ou 1)>
<nombre de candidatures (0 à 3)>
...
```
**Exemple :**
```
5008 63
0
0
1061 15
0
0
2548 63
0
0
4151 43
0
0
```

### `etudiants.txt`
Ce fichier contient les informations sur les étudiants et suit le format suivant :
```
<identifiant étudiant> <référence de stage attribué (-1 si aucun)> <note finale attribuée (-1 si non attribuée)>
...
```
**Exemple :**
```
101 -1 -1
233 -1 -1
272 -1 -1
464 -1 -1
958 -1 -1
```


## Installation
1. Clonez ce dépôt :
   ```bash
   git clone https://github.com/Yeezayy/Stage-Gestion.git
   ```
2. Accédez au répertoire du projet :
   ```bash
   cd Stage-Gestion



## Licence
Ce projet est sous licence [MIT](LICENSE).

## Auteur
- [Yeezayy](https://github.com/Yeezayy)

