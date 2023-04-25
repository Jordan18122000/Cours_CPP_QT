# Cours_CPP_QT

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table des matières</summary>
  <ol>
    <li><a href="#prérequis">Prérequis</a></li>
    <li><a href="#configuration-projet">Configuration projet</a></li>
    <li><a href="#installation-logiciel">Installation logiciel</a></li>
    <li><a href="#utilisation-du-logiciel">Utilisation du logiciel</a></li>
        <ul>
        <li><a href="#crypter-une-image">Crypter une image</a></li>
            <ul>
            <li><a href="#première-étape">Première étape</a></li>
            </ul>
            <ul>
            <li><a href="#deuxième-étape">Deuxième étape</a></li>
            </ul>
        </ul>
        <ul>
        <li><a href="#décrypter-une-image">Décrypter une image</a></li>
            <ul>
            <li><a href="#première-étape">Première étape</a></li>
            </ul>
            <ul>
            <li><a href="#deuxième-étape">Deuxième étape</a></li>
           </ul>
      </ul>
  </ol>
</details>

## Prérequis
Installer l'outil steghide : 

``` sudo apt-get install steghide ```

ou

``` sudo apt-get install steghide -y ```

## Configuration projet

![readme_config_qt5](https://user-images.githubusercontent.com/79545759/234222067-df52baae-1e34-46ae-b937-f886c66d9a76.png)

## Installation logiciel

Pour installer la supervision QT, suivre le lien ci-dessous :

[installer/EMBEDDED_CPP_QT_v1.0](./installer/EMBEDDED_CPP_QT_v1.0_setup.exe)

## Utilisation du logiciel

Interface graphique :

![image](https://user-images.githubusercontent.com/79545759/234398797-6f01375f-89ab-44e9-a879-6df128fbfb2c.png)

### Crypter une image 

#### Première étape:

Entrer le texte à cacher dans l'image comme ci-dessous dans l'espace dédié:
![image](https://user-images.githubusercontent.com/79545759/234395197-ab24284e-f39e-404e-bb22-2535f74f2d08.png)

Puis cliquer sur le bouton ci-dessous : 
![image](https://user-images.githubusercontent.com/79545759/234395357-0c18c13a-3802-40d2-b73e-b2c6b68e13e6.png)

##### Si vous essayez de crypter une image sans avoir entré un texte au préalable vous aurez le message ci-dessous : 
![image](https://user-images.githubusercontent.com/79545759/234395670-7314ee5f-b1a6-42cb-b748-9d06e8cafd98.png)

##### Si la sauvegarde fonctionne :
![image](https://user-images.githubusercontent.com/79545759/234396018-b78c8303-e1b4-499a-8f0c-ee8adae314b0.png)

#### Deuxième étape:

Pour choisir l'image que vous souhaitez crypter cliquer sur :
![image](https://user-images.githubusercontent.com/79545759/234396337-97aed791-a951-43be-acb1-6a8f597a4ef1.png)

Utiliser l'interface pour trouver votre image :
![image](https://user-images.githubusercontent.com/79545759/234396493-bb9e554b-5ed2-4a6e-8920-1409f36e9b7c.png)

##### Vous avez à votre disposition une image test ici : [documents/image](./documents/image.jpg)

Entrer alors un mot de passe pour protéger le cryptage :

![image](https://user-images.githubusercontent.com/79545759/234396960-5202e578-a43f-4f07-bc3a-29342999d861.png)

##### Pour consulter votre PassPhrase cliquer sur : 
![image](https://user-images.githubusercontent.com/79545759/234397141-2bb59e53-b328-4ba8-8d0b-49d899380f04.png)
##### Pour avoir :
![image](https://user-images.githubusercontent.com/79545759/234397375-9c3430a5-7cf8-4436-9aee-0a1f196aede5.png)

### Décrypter une image 

#### Première étape:
Pour choisir l'image que vous souhaitez décrypter cliquer sur :
![image](https://user-images.githubusercontent.com/79545759/234397676-69f5b18c-dc21-4d6f-9caa-2a7f0f0b22b8.png)

Allez donc dans le répertoire de votre image à décrypter :
![image](https://user-images.githubusercontent.com/79545759/234397785-4bb2ed54-b688-409e-a47b-388123dedc57.png)

Entrer la PassPhrase utilisé lors du cryptage :

![image](https://user-images.githubusercontent.com/79545759/234397996-69923b1e-95dc-4b42-a5d9-d2681f489a07.png)

#### Deuxième étape:

Voir le message trouvé :

![image](https://user-images.githubusercontent.com/79545759/234398321-cf107ae1-4686-4413-9ccb-ac5da44bf46d.png)

Pour nettoyer la zone message cliquer sur :

![image](https://user-images.githubusercontent.com/79545759/234398460-d615305f-4dd7-46b2-91d2-220e21c5218a.png)

