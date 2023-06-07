# Web Assembly Langton Ant

Ce dépôt contient un exemple de la fourmis de Langton codé en C et affiché 
en utilisant Javascript et une page HTML.

Vous pouvez build et run l'application en utilisant docker.

build avec : `docker build -t wasm-intro .`
run : `docker run -v "$PWD":/data -it --rm -p 8080:8080 wasm-intro /bin/bash`

Enfin voici les commandes pour compiler le code et lancer un serveur sur lequel
vous pourrez vous connecter.

* `make` va compiler les fichiers C en Web Assembly dans les différents exemples
* `make serve` va lancer un serveur Web local permettant de les tester
  (en ouvrant le fichier HTML dans chacun des répertoires d'exemple)
