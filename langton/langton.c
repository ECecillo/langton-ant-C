#define WASM_EXPORT __attribute__((visibility("default")))

#define WIDTH 256
#define HEIGHT WIDTH
unsigned char IMAGE[HEIGHT][WIDTH][4];
const int R = 0;
const int G = 1;
const int B = 2;
const int A = 3;
int counter = 0;

// Orientation de la fourmi: 0 = haut, 1 = droite, 2 = bas, 3 = gauche
int direction = 0;

// Position actuelle de la fourmi
int ant_x = WIDTH / 2;
int ant_y = HEIGHT / 2;

WASM_EXPORT
void* get_image_address(void) {
  return &IMAGE;
}

WASM_EXPORT
int get_image_width(void) {
  return WIDTH;
}

WASM_EXPORT
int get_image_height(void) {
  return HEIGHT;
}

WASM_EXPORT
int get_image_size(void) {
  return sizeof(IMAGE);
}

WASM_EXPORT
// Initialisation de l'image
void init(void) {
  for (int y=0; y<HEIGHT; y++) {
    for (int x=0; x<WIDTH; x++) {
      IMAGE[y][x][R] = 255;
      IMAGE[y][x][G] = 255;
      IMAGE[y][x][B] = 255;
      IMAGE[y][x][A] = 255;
    }
  }
}

WASM_EXPORT
// Simulation d'un mouvement de la fourmi
void move(void) {
  // Si la case est blanche
  if (IMAGE[ant_y][ant_x][R] == 255) {
    IMAGE[ant_y][ant_x][R] = 0;
    IMAGE[ant_y][ant_x][G] = 0;
    IMAGE[ant_y][ant_x][B] = 0;
    direction = (direction + 1) % 4; // Tourne à droite
  }
  // Si la case est noire
  else {
    IMAGE[ant_y][ant_x][R] = 255;
    IMAGE[ant_y][ant_x][G] = 255;
    IMAGE[ant_y][ant_x][B] = 255;
    direction = (direction + 3) % 4; // Tourne à gauche
  }

  // Avance
  switch (direction) {
    case 0: ant_y = (ant_y - 1 + HEIGHT) % HEIGHT; break;
    case 1: ant_x = (ant_x + 1) % WIDTH; break;
    case 2: ant_y = (ant_y + 1) % HEIGHT; break;
    case 3: ant_x = (ant_x - 1 + WIDTH) % WIDTH; break;
  }
  counter++;
}

WASM_EXPORT
int get_counter(void) {
  return counter;
}
