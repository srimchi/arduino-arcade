#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;

// global constant for the number of Invaders in the game
const int NUM_ENEMIES = 16;

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

// the following functions are for printing messages
void print_level(int level);
void print_lives(int lives);
void game_over();

class Color {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    bool black_color(){
      if(red == 0 && green == 0 && blue == 0){
        return true;
      }
      else {
        return false;
      }
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};

const Color BLACK(0, 0, 0);
const Color RED(4, 0, 0);
const Color ORANGE(6, 1, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 4, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(1, 0, 2);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 4, 4);

class Invader {
  public:
    // Constructors
    Invader() {
      x = 0;
      y = 0;
      strength = 0;
    }
    // sets values for private date members x and y
    Invader(int x_arg, int y_arg) {
      x = x_arg; 
      y = y_arg; 
    }
    // sets values for private data members
    Invader(int x_arg, int y_arg, int strength_arg) {
      x = x_arg; 
      y = y_arg; 
      strength = strength_arg; 
    }
    // sets values for private data members
    void initialize(int x_arg, int y_arg, int strength_arg) {
      x = x_arg; 
      y = y_arg; 
      strength = strength_arg; 
    }
    
    // getters
    int get_x() const {
      return x; 
    }
    int get_y() const {
      return y; 
    }
    int get_strength() const {
      return strength; 
    }

    // Moves the Invader down the screen by one row
    // Modifies: y
    void move() {
      if (strength > 0){
        erase();
        y++;
      }
      if(y > 13) {
        game_over();
      }
      draw();
    }
    
    // draws the Invader if its strength is greater than 0
    // calls: draw_with_rgb
    void draw() {
      if (strength > 0){
        if (strength == 7) {
          draw_with_rgb(WHITE,BLUE);
        }
        if (strength == 6) {
          draw_with_rgb(PURPLE,BLUE);
        }
        if (strength == 5) {
          draw_with_rgb(BLUE,BLUE);
        }
        if (strength == 4) {
          draw_with_rgb(GREEN,BLUE);
        }
        if (strength == 3) {
          draw_with_rgb(YELLOW,BLUE);
        }
        if (strength == 2) {
          draw_with_rgb(ORANGE,BLUE);
        }
        if (strength == 1) {
          draw_with_rgb(RED,BLUE);
        }
        if (strength == 0) {
          erase();
        }
        if (y > 13){
          erase();
        }
      }
    }
    
    // draws black where the Invader used to be
    // calls: draw_with_rgb
    void erase() {
      draw_with_rgb(BLACK, BLACK);
    }    
    
    // Invader is hit by a Cannonball.
    // Modifies: strength
    // calls: draw, erase
    void hit() {
      // FIXME if (!matrix[x - 1][y + 4].black_color()) {
          erase();
          strength--;
          draw();
      
    }

  private:
    int x;
    int y;
    int strength;
    
    // draws the Invader
    void draw_with_rgb(Color body_color, Color eye_color) {
      matrix.drawPixel(x, y, body_color.to_333());
      matrix.drawPixel(x + 1, y, body_color.to_333());
      matrix.drawPixel(x - 1, y + 1, body_color.to_333());
      matrix.drawPixel(x, y + 1, eye_color.to_333());
      matrix.drawPixel(x + 1, y + 1, eye_color.to_333());
      matrix.drawPixel(x + 2, y + 1, body_color.to_333());
      matrix.drawPixel(x - 1, y + 2, body_color.to_333());
      matrix.drawPixel(x, y + 2, body_color.to_333());
      matrix.drawPixel(x + 1, y + 2, body_color.to_333());
      matrix.drawPixel(x + 2, y + 2, body_color.to_333());
      matrix.drawPixel(x - 1, y + 3, body_color.to_333());
      matrix.drawPixel(x + 2, y + 3, body_color.to_333());
    }
};

class Cannonball {
  public:
    Cannonball() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // resets private data members to initial values
    void reset() {
      Cannonball(); 
    }
    
    // getters
    int get_x() const {
      return x; 
    }
    int get_y() const {
      return y; 
    }
    bool has_been_fired() const {
      return true; 
    }
    
    // sets private data members
    void fire(int x_arg, int y_arg) {
      x = x_arg; 
      y = y_arg; 
    }
    
    // moves the Cannonball and detects if it goes off the screen
    // Modifies: y, fired
    //
    void move() {
      fired = true;
      //what if it hits a space invader.....
      for(int i = x ; i < 16; i++) {
        if(y > 0) {
          erase();
          y--;
          draw();
        }
        else {
          erase();
        }
      }
    }
    
    // resets private data members to initial values
    void hit() {
      Cannonball(); 
    }
    
    // draws the Cannonball, if it is fired
    void draw() {
      if(fired){
        matrix.drawPixel(x, y, ORANGE.to_333());
        matrix.drawPixel(x, y + 1, ORANGE.to_333());
      }
    }
    
    // draws black where the Cannonball used to be
    void erase() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x, y + 1, BLACK.to_333());
    }

  private:
    int x;
    int y;
    bool fired;
};

class Player {
  public:
    Player() {
      x = 0;
      y = 0;
      lives = 3;
    }
    
    // getters
    int get_x() const {
      return x; 
    }
    int get_y() const {
      return y; 
    }
    int get_lives() const {
      return lives; 
    }
    
    // setter
    void set_x(int x_arg) {
      x = x_arg; 
    }
    
    // Modifies: lives
    void die() {
      //what if hits space invader
      lives--;
    }
    
    // draws the Player
    // calls: draw_with_rgb
    void draw() {
      draw_with_rgb(AQUA);
    }
    
    // draws black where the Player used to be
    // calls: draw_with_rgb
    void erase() {
      draw_with_rgb(BLACK);
    }

  private:
    int x;
    int y;
    int lives;

    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg) {
      x = x_arg; 
      y = y_arg; 
    }
    
    // draws the player
    void draw_with_rgb(Color color) {
      matrix.drawPixel(x, y, AQUA.to_333());
      matrix.drawPixel(x - 1, y + 1, AQUA.to_333());
      matrix.drawPixel(x, y + 1, AQUA.to_333());
      matrix.drawPixel(x + 1, y + 1, AQUA.to_333());
    }
};

class Game {
  public:
    Game() {
      level = 0;
      time = 0;
    }
    
    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    // see http://arduino.cc/en/Reference/Setup
    void setup() {
    }
    
    // advances the game simulation one step and renders the graphics
    // see spec for details of game
    // Modifies: global variable matrix
    void update(int potentiometer_value, bool button_pressed) {
    }

  private:
    int level;
    unsigned long time;
    Player player;
    Cannonball ball;
    Invader enemies[NUM_ENEMIES];

    // check if Player defeated all Invaders in current level
    bool level_cleared() {
    }

    // set up a level
    void reset_level() {
    }
};

// a global variable that represents the game Space Invaders
Game game;

// see https://www.arduino.cc/reference/en/language/structure/sketch/setup/
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
}

// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);

  game.update(potentiometer_value, button_pressed);
}

// displays Level
void print_level(int level) {
  matrix.setCursor(5, 9);
  //matrix.setTextColor(WHITE(4,4,4));
  matrix.setTextSize(1);
  matrix.print("LEVEL");
  matrix.setCursor(7, 18);
  //matrix.setTextColor(WHITE(4,4,4));
  matrix.setTextSize(1);
  matrix.print(level);
}

// displays number of lives
void print_lives(int lives) {
  matrix.setCursor(5, 9);
  //matrix.setTextColor(WHITE(4,4,4));
  matrix.setTextSize(1);
  matrix.print("LIVES");
  matrix.setCursor(7, 18);
  //matrix.setTextColor(WHITE(4,4,4));
  matrix.setTextSize(1);
  matrix.print(lives);
}

// displays "game over"
void game_over() {
  matrix.setCursor(3, 9);
  //matrix.setTextColor(WHITE(4,4,4));
  matrix.setTextSize(1);
  matrix.print("GAME OVER");
  //matrix.print('G'); 
  //matrix.print('A'); 
  //matrix.print('M'); 
  //matrix.print('E'); 
  //matrix.print(' ');
  //matrix.print('O');
  //matrix.print('V');
  //matrix.print('E');
  //matrix.print('R');
}

