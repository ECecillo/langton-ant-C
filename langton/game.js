let intervalId = null;

async function main() {
  // charge le module WASM
  let result = await WebAssembly.instantiateStreaming(
    fetch('./langton.wasm'),
    {},
  );
  let {
      memory,
      get_image_address,
      get_image_height,
      get_image_size,
      get_image_width,
      get_counter,
      init,
      move,
  } = result.instance.exports;

  // initialise l'image
  init();

  // récupère le buffer image pour Javascript
  let image = new Uint8ClampedArray(
    memory.buffer,
    get_image_address(),
    get_image_size(),
  );

  // adapte la taille du canvas
  let c = document.querySelector("canvas");
  const counterNode = document.getElementById("counter");
  c.width = get_image_width();
  c.height = get_image_height();

  // fonction pour mettre à jour l'image
  function updateImage() {
    imageData = new ImageData(image, c.width, c.height);
    let ctx = c.getContext('2d');
    ctx.putImageData(imageData, 0, 0);
  }

  // fonction pour démarrer la simulation
  function startSimulation() {
    if (intervalId == null) {
      intervalId = setInterval(function() {
        move();
        updateImage();
        counterDiv.textContent = "Changements de case : " + get_counter();
      }, 10);
    }
  }

  // fonction pour arrêter la simulation
  function stopSimulation() {
    if (intervalId != null) {
      clearInterval(intervalId);
      intervalId = null;
    }
  }

  // ajoute des boutons pour démarrer et arrêter la simulation
  let startButton = document.createElement("button");
  startButton.textContent = "Démarrer";
  startButton.addEventListener("click", startSimulation);
  document.body.appendChild(startButton);

  let stopButton = document.createElement("button");
  stopButton.textContent = "Arrêter";
  stopButton.addEventListener("click", stopSimulation);
  document.body.appendChild(stopButton);

  let counterDiv = document.createElement("div");
  counterDiv.textContent = "0"
  document.body.appendChild(counterDiv);

  // affiche le contenu initial du buffer image dans le canvas
  updateImage();
}

main();

