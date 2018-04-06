#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
//STILL NEED TO DO: logic of the game

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
      if (strength > 0) {
        erase();
        y++;
      }
    }

    // draws the Invader if its strength is greater than 0
    // calls: draw_with_rgb
    void draw() {
      if (strength > 0) {
        if (strength == 7) {
          draw_with_rgb(WHITE, BLUE);
        }
        if (strength == 6) {
          draw_with_rgb(PURPLE, BLUE);
        }
        if (strength == 5) {
          draw_with_rgb(BLUE, BLUE);
        }
        if (strength == 4) {
          draw_with_rgb(GREEN, BLUE);
        }
        if (strength == 3) {
          draw_with_rgb(YELLOW, BLUE);
        }
        if (strength == 2) {
          draw_with_rgb(ORANGE, BLUE);
        }
        if (strength == 1) {
          draw_with_rgb(RED, BLUE);
        }
      }
      else {
        erase();
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
      fired = false;
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
      fired = true;
    }

    // moves the Cannonball and detects if it goes off the screen
    // Modifies: y, fired
    //
    void move() {
      int temp = y;
      for (int i = temp ; i < 16; i++) {
        draw();
        erase();
        if (y > -1) {
          y--;
          draw();
        }
      }
    }

    // resets private data members to initial values
    void hit() {
      x = 0;
      y = 0;
      fired = false;
    }

    // draws the Cannonball, if it is fired
    void draw() {
      if (fired) {
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
      x = 15;
      y = 14;
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
      if (lives > 0) {
        lives--;
      }
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
      matrix.drawPixel(x, y, color.to_333());
      matrix.drawPixel(x - 1, y + 1, color.to_333());
      matrix.drawPixel(x, y + 1, color.to_333());
      matrix.drawPixel(x + 1, y + 1, color.to_333());
    }
};

class Game {
  public:
    Game() {
      level = 1;
      time = 0;
      time_ball = 0;
    }

    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    // see http://arduino.cc/en/Reference/Setup

    int random_num() {
      return random(1, 7);
    }
    void setup() {

      print_lives(player.get_lives());
      delay(3000);
      matrix.fillScreen(BLACK.to_333());
      print_level(level);
      delay(3000);
      matrix.fillScreen(BLACK.to_333());

      //level one invader setup
      if (level == 1) {
        int x = 1;
        enemies[0].initialize(x, 0, 1);
        enemies[0].draw();
        for (int i = 1; i < 8; i++) {
          x = x + 4;
          enemies[i].initialize(x, 0, 1);
          enemies[i].draw();
        }
      }

      if (level == 2) {
        int x = 1;
        int count = 1;
        enemies[0].initialize(x, 0, 1);
        enemies[0].draw();
        count++;
        for (int i = 1; i < 8; i++) {
          x = x + 4;
          if (count % 2 != 0) {
            enemies[i].initialize(x, 0, 1);
            enemies[i].draw();
            count++;
          }
          else {
            enemies[i].initialize(x, 0, 2);
            enemies[i].draw();
            count++;
          }
        }
        x = 1;
        enemies[8].initialize(x, 5, 2);
        enemies[8].draw();
        for (int i = 9; i < 16; i++) {
          x = x + 4;
          if (count % 2 != 0) {
            enemies[i].initialize(x, 5, 1);
            enemies[i].draw();
            count++;
          }
          else {
            enemies[i].initialize(x, 5, 2);
            enemies[i].draw();
            count++;
          }
        }
      }

      if (level == 3) {
        int x = 1;
        int count = 1;
        enemies[0].initialize(x, 0, count);
        enemies[0].draw();
        count++;
        for (int i = 1; i < 8; i++) {
          x = x + 4;
          if (count == 6) {
            count = 1;
          }
          enemies[i].initialize(x, 0, count);
          enemies[i].draw();
          count++;
        }
        x = 1;
        enemies[8].initialize(x, 5, count);
        enemies[8].draw();
        count++;
        for (int i = 9; i < 16; i++) {
          x = x + 4;
          if (count == 6) {
            count = 1;
          }
          enemies[i].initialize(x, 5, count);
          enemies[i].draw();
          count++;
        }
      }

      if (level == 4) {
        int x = 1;
        int count = 1;
        enemies[0].initialize(x, 0, 5);
        enemies[0].draw();
        count++;
        for (int i = 1; i < 8; i++) {
          x = x + 4;
          if (count % 2 != 0) {
            enemies[i].initialize(x, 0, 5);
            enemies[i].draw();
            count++;
          }
          else {
            enemies[i].initialize(x, 0, 4);
            enemies[i].draw();
            count++;
          }
        }
        x = 1;
        enemies[8].initialize(x, 5, 2);
        enemies[8].draw();
        for (int i = 9; i < NUM_ENEMIES; i++) {
          x = x + 4;
          if (count % 2 != 0) {
            enemies[i].initialize(x, 5, 3);
            enemies[i].draw();
            count++;
          }
          else {
            enemies[i].initialize(x, 5, 2);
            enemies[i].draw();
            count++;
          }
        }
      }
      //level 5 and beyond
      if (level >= 5) {
        int x = 1;
        enemies[0].initialize(x, 0, random_num());
        enemies[0].draw();
        for (int i = 1; i < 8; i++) {
          x = x + 4;
          enemies[i].initialize(x, 0, random_num());
          enemies[i].draw();
        }
        x = 1;
        enemies[8].initialize(x, 5, random_num());
        enemies[8].draw();
        for (int i = 9; i < NUM_ENEMIES; i++) {
          x = x + 4;
          enemies[i].initialize(x, 5, random_num());
          enemies[i].draw();
        }
      }
      player.draw();
    }

    // advances the game simulation one step and renders the graphics
    // see spec for details of game
    // Modifies: global variable matrix
    void update(int potentiometer_value, bool button_pressed) {
      int time_passed = millis();
      player.erase();
      if ((potentiometer_value / 32) > player.get_x()) {
        player.set_x(player.get_x() + 1);
      }
      else if ((potentiometer_value / 32) < player.get_x()) {
        player.set_x(player.get_x() - 1);
      }
      else {
        player.set_x(player.get_x());
      }
      player.draw();

      int ball_curr_time = millis();
      if (button_pressed == true) {
        ball.fire(player.get_x(), player.get_y() - 2);
        ball.draw();
        if(ball_curr_time - time_ball > 50){
          ball.move();
        }
        time_ball = millis();
      }

      int period = 1000;
      if (time_passed - time > period) {
        if (level > 1) {
          for (int i = 8; i < 16; i++) {
            if (enemies[i].get_y() + 3 == 15) {
              player.die();
              reset_level();
              break;

            }
            else if ((player.get_x() + 1 == enemies[i].get_x() - 1 && player.get_y() + 1 == enemies[i].get_y() + 3) ||
                     (player.get_x() == enemies[i].get_x() - 1 && player.get_y() == enemies[i].get_y() + 3) ||
                     (player.get_x() == enemies[i].get_x() && player.get_y() == enemies[i].get_y() + 2) ||
                     (player.get_x() == enemies[i].get_x() + 1 && player.get_y() == enemies[i].get_y() + 2) ||
                     (player.get_x() == enemies[i].get_x() + 2 && player.get_y() == enemies[i].get_y() + 3) ||
                     (player.get_x() - 1 == enemies[i].get_x() + 2 && player.get_y() - 1 == enemies[i].get_y() + 3)) {
              player.die();
              reset_level();
              break;

            }
            else if ((ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() - 1)) || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x()))
                     || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x() + 1)) || (ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() + 2))) {
              enemies[i].hit();
              ball.hit();
            }
            else {
              enemies[i].move();
            }

          }
          for (int i = 8; i < 16; i++) {
            enemies[i].draw();
          }

          int count_strength = 0;
          for (int i = 8; i < 16; i++) {
            if (enemies[i].get_strength() == 0) {
              count_strength++;
            }
          }

          if (count_strength == 8) {
            for (int i = 0; i < 8; i++) {
              if (enemies[i].get_y() + 3 == 15) {
                player.die();
                reset_level();
                break;

              }
              else if ((player.get_x() + 1 == enemies[i].get_x() - 1 && player.get_y() + 1 == enemies[i].get_y() + 3) ||
                       (player.get_x() == enemies[i].get_x() - 1 && player.get_y() == enemies[i].get_y() + 3) ||
                       (player.get_x() == enemies[i].get_x() && player.get_y() == enemies[i].get_y() + 2) ||
                       (player.get_x() == enemies[i].get_x() + 1 && player.get_y() == enemies[i].get_y() + 2) ||
                       (player.get_x() == enemies[i].get_x() + 2 && player.get_y() == enemies[i].get_y() + 3) ||
                       (player.get_x() - 1 == enemies[i].get_x() + 2 && player.get_y() - 1 == enemies[i].get_y() + 3)) {
                player.die();
                reset_level();
                break;

              }
              else if ((ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() - 1)) || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x()))
                       || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x() + 1)) || (ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() + 2))) {
                enemies[i].hit();
                ball.erase();
              }
              else {
                enemies[i].move();
              }

            }
            for (int i = 0; i < 8; i++) {
              enemies[i].draw();
            }
          }

        }
        else {
          for (int i = 0; i < 8; i++) {
            if (enemies[i].get_y() + 3 == 15) {
              player.die();
              reset_level();
              break;

            }
            else if ((player.get_x() + 1 == enemies[i].get_x() - 1 && player.get_y() + 1 == enemies[i].get_y() + 3) ||
                     (player.get_x() == enemies[i].get_x() - 1 && player.get_y() == enemies[i].get_y() + 3) ||
                     (player.get_x() == enemies[i].get_x() && player.get_y() == enemies[i].get_y() + 2) ||
                     (player.get_x() == enemies[i].get_x() + 1 && player.get_y() == enemies[i].get_y() + 2) ||
                     (player.get_x() == enemies[i].get_x() + 2 && player.get_y() == enemies[i].get_y() + 3) ||
                     (player.get_x() - 1 == enemies[i].get_x() + 2 && player.get_y() - 1 == enemies[i].get_y() + 3)) {
              player.die();
              reset_level();
              break;

            }
            else if ((ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() - 1)) || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x()))
                     || (ball.get_y() == (enemies[i].get_y() + 2) && ball.get_x() == (enemies[i].get_x() + 1)) || (ball.get_y() == (enemies[i].get_y() + 3) && ball.get_x() == (enemies[i].get_x() + 2))) {
              enemies[i].hit();
              //ball.hit();
            }
            else {
              enemies[i].move();
            }

          }
          for (int i = 0; i < 8; i++) {

            enemies[i].draw();
          }
        }
        time = time_passed;
      }
    }


  private:
    int level;
    unsigned long time;
    unsigned long time_ball;
    Player player;
    Cannonball ball;
    Invader enemies[NUM_ENEMIES];

    // check if Player defeated all Invaders in current level
    bool level_cleared() {
      if (level == 1) {
        for (int i = 0; i < 9; i++) {
          if (enemies[i].get_strength() != 0) {
            return false;
          }
        }
      }
      else {
        for (int i = 0; i < NUM_ENEMIES; i++) {
          if (enemies[i].get_strength() != 0)
            return false;
        }
      }
      level++;
      return true;
    }

    // set up a level
    void reset_level() {
      matrix.fillScreen(BLACK.to_333());
      if (player.get_lives() != 0) {
        setup();
      }
      else {
        matrix.fillScreen(BLACK.to_333());
        game_over();
      }
    }
};

// a global variable that represents the game Space Invaders
Game game;

// see https://www.arduino.cc/reference/en/language/structure/sketch/setup/
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  game.setup();
}

// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  game.update(potentiometer_value, button_pressed);
}

// displays Level
void print_level(int level) {
  matrix.setCursor(1, 0);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print("LEVEL");
  matrix.setCursor(13, 9);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print(level);
}

// displays number of lives
void print_lives(int lives) {
  matrix.setCursor(1, 0);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print("LIVES");
  matrix.setCursor(13, 9);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print(lives);
}

// displays "game over"
void game_over() {
  matrix.fillScreen(BLACK.to_333());
  matrix.setCursor(2, 1);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print("GAME");
  matrix.setCursor(2, 8);
  matrix.setTextColor(WHITE.to_333());
  matrix.setTextSize(1);
  matrix.print("OVER");

}


