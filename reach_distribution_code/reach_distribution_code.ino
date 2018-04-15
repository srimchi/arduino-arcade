#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

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

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void print_ground();

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



class Dinosaur {
  public:
    //Constructors
    Dinosaur() {
      x = 3;
      y = 8;
      jump = false;
      come_down = false;
    }

    int get_x() {
      return x;
    }

    int get_y() {
      return y;
    }

    void set_jump() {
      jump = true;
    }

    bool has_jumped() {
      return jump;
    }

    void set_x(int x_arg) {
      x = x_arg;
    }

    void set_y(int y_arg) {
      y = y_arg;
    }

    void dino_jump() {
      if (!come_down) {
        if (y > 0) {
          y -= 1;
        }
        else {
          come_down = true;
        }
      }
    }

    void dino_come_down() {
      if (come_down) {
        if (y < 8) {
          y += 1;
        }
        else {
          come_down = false;
          jump = false;
        }
      }
    }

    void duck() {
      redraw_with_rgb(AQUA);
    }

    void duck_erase() {
      redraw_with_rgb(BLACK);
    }

    void draw() {
      draw_with_rgb(AQUA);
    }

    void erase() {
      draw_with_rgb(BLACK);
    }

  private:
    int x;
    int y;
    bool jump;
    bool come_down;

    void draw_with_rgb(Color color) {
      matrix.drawPixel(x, y, color.to_333());
      matrix.drawPixel(x + 1, y + 1, color.to_333());
      matrix.drawPixel(x + 1, y + 2, color.to_333());
      matrix.drawPixel(x, y + 3, color.to_333());
      matrix.drawPixel(x + 1, y + 4, color.to_333());
      matrix.drawPixel(x, y + 2, color.to_333());
      matrix.drawPixel(x, y + 3, color.to_333());
      matrix.drawPixel(x, y + 4, color.to_333());
      matrix.drawPixel(x, y + 5, color.to_333());
      matrix.drawPixel(x - 1, y + 1, color.to_333());
      matrix.drawPixel(x - 1, y + 2, color.to_333());
      matrix.drawPixel(x - 1, y + 3, color.to_333());
      matrix.drawPixel(x - 1, y + 4, color.to_333());
      matrix.drawPixel(x - 3, y + 4, color.to_333());
      matrix.drawPixel(x - 1, y + 5, color.to_333());
      matrix.drawPixel(x - 2, y + 5, color.to_333());
      matrix.drawPixel(x - 3, y + 5, color.to_333());
      matrix.drawPixel(x, y + 1, RED.to_333());
    }
    void redraw_with_rgb(Color color) {
      matrix.drawPixel(0, 13, color.to_333());
      matrix.drawPixel(1, 13, color.to_333());
      matrix.drawPixel(2, 13, color.to_333());
      matrix.drawPixel(3, 13, color.to_333());
      matrix.drawPixel(1, 12, color.to_333());
      matrix.drawPixel(2, 12, color.to_333());
      matrix.drawPixel(1, 11, color.to_333());
      matrix.drawPixel(2, 11, color.to_333());
      matrix.drawPixel(3, 11, color.to_333());
      matrix.drawPixel(1, 10, color.to_333());
      matrix.drawPixel(3, 10, color.to_333());
      matrix.drawPixel(2, 9, color.to_333());
      matrix.drawPixel(x, y + 1, RED.to_333());
    }

};

class Bird {
  public:

    Bird() {

      x = 31;

    }

    void draw_bird_1() {
      matrix.drawPixel(x, y, RED.to_333());
      matrix.drawPixel(x + 1, y - 1, RED.to_333());
      matrix.drawPixel(x - 1, y - 1, RED.to_333());
    }

    void draw_bird_2() {
      matrix.drawPixel(x, y, RED.to_333());
      matrix.drawPixel(x - 1, y + 1, RED.to_333());
      matrix.drawPixel(x + 1, y + 1, RED.to_333());
    }

    void erase_1() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x + 1, y - 1, BLACK.to_333());
      matrix.drawPixel(x - 1, y - 1, BLACK.to_333());
    }

    void erase_2() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x - 1, y + 1, BLACK.to_333());
      matrix.drawPixel(x + 1, y + 1, BLACK.to_333());
    }

    void set_y(int y_arg) {
      y = y_arg;
    }

    int get_x() {
      return x;
    }

    int get_y() {
      return y;
    }
    void move() {
      if (x >= 0) {
        x--;
      }
    }

  private:
    int x;
    int y;
};

class Cactus {
  public:
    Cactus() {
      x = 30;
      y = 13;
      cactus_on_screen = false;
    }

    void set_cactus_on_screen() {
      cactus_on_screen = true;
    }

    void move() {
      if (x >= -1) {
        x--;
      }
      else {
        cactus_on_screen = false;
      }
    }

    bool get_cactus_on_screen() {
      return cactus_on_screen;

    }

    int get_y() {
      return y;
    }

    int get_x() {
      return x;
    }

    void erase_1() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x, y - 1, BLACK.to_333());
      matrix.drawPixel(x - 1, y, BLACK.to_333());
      matrix.drawPixel(x + 1, y, BLACK.to_333());
    }

    void erase_2() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x + 1, y - 1, BLACK.to_333());
      matrix.drawPixel(x - 1, y - 1, BLACK.to_333());
      matrix.drawPixel(x, y - 1, BLACK.to_333());
      matrix.drawPixel(x, y - 2, BLACK.to_333());
    }

    void erase_3() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x, y - 1, BLACK.to_333());
      matrix.drawPixel(x, y - 2, BLACK.to_333());
      matrix.drawPixel(x, y - 3, BLACK.to_333());
      matrix.drawPixel(x + 1, y - 2, BLACK.to_333());
      matrix.drawPixel(x - 1, y - 2, BLACK.to_333());
    }

    void draw_cacti_1() {
      matrix.drawPixel(x, y, GREEN.to_333());
      matrix.drawPixel(x, y - 1, GREEN.to_333());
      matrix.drawPixel(x - 1, y, GREEN.to_333());
      matrix.drawPixel(x + 1, y, GREEN.to_333());
    }
    void draw_cacti_2() {
      matrix.drawPixel(x, y, GREEN.to_333());
      matrix.drawPixel(x + 1, y - 1, GREEN.to_333());
      matrix.drawPixel(x - 1, y - 1, GREEN.to_333());
      matrix.drawPixel(x, y - 1, GREEN.to_333());
      matrix.drawPixel(x, y - 2, GREEN.to_333());
    }
    void draw_cacti_3() {
      matrix.drawPixel(x, y, GREEN.to_333());
      matrix.drawPixel(x, y - 1, GREEN.to_333());
      matrix.drawPixel(x, y - 2, GREEN.to_333());
      matrix.drawPixel(x, y - 3, GREEN.to_333());
      matrix.drawPixel(x + 1, y - 2, GREEN.to_333());
      matrix.drawPixel(x - 1, y - 2, GREEN.to_333());
    }

  private:
    int x;
    int y;
    bool cactus_on_screen;

};

class Game {
  public:
    void setup() {
      d.draw();
      print_ground();

    }
    void dino_dead() {
      if ((d.get_x() + 1 == c[prev_rand_num].get_x() && d.get_y() + 1 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() + 1 == c[prev_rand_num].get_x() && d.get_y() + 2 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() + 1 == c[prev_rand_num].get_x() && d.get_y() + 4 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() == c[prev_rand_num].get_x() && d.get_y() + 5 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() - 1 == c[prev_rand_num].get_x() && d.get_y() + 5 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() - 2 == c[prev_rand_num].get_x() && d.get_y() + 5 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() - 3 == c[prev_rand_num].get_x() && d.get_y() + 5 == c[prev_rand_num].get_y() - 1) ||
          (d.get_x() + 1 == c[prev_rand_num].get_x() - 1 && d.get_y() + 1 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() + 1 == c[prev_rand_num].get_x() - 1 && d.get_y() + 2 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() + 1 == c[prev_rand_num].get_x() - 1 && d.get_y() + 4 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() == c[prev_rand_num].get_x() - 1 && d.get_y() + 5 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() - 1 == c[prev_rand_num].get_x() - 1 && d.get_y() + 5 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() - 2 == c[prev_rand_num].get_x() - 1 && d.get_y() + 5 == c[prev_rand_num].get_y() + 1) ||
          (d.get_x() - 3 == c[prev_rand_num].get_x() - 1 && d.get_y() + 5 == c[prev_rand_num].get_y() + 1)) {
        exit(0);
      }
    }
    //just cactus
    void level_one(int potentiometer_value, bool button_pressed) {
      dino_curr_time = millis();
      cacti_curr_time = millis();

      if (d.get_y() + 5 == 13) {
        if ((potentiometer_value / 32) > d.get_x()) {
          d.erase();
          d.duck();
          d.duck_erase();
        }
        else if ((potentiometer_value / 32) < d.get_x()) {
          d.erase();
          d.duck();
          d.duck_erase();
        }
      }

      if (button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > 100) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          d.draw();
          dino_dead();
          time = millis();
        }
      }

      if (c[prev_rand_num].get_cactus_on_screen() == false) {
        c[prev_rand_num].set_cactus_on_screen();
        int rand_num = random(0, 39);
        prev_rand_num = rand_num;
        cacti_time = millis();
      }
      else {
        if (cacti_curr_time - cacti_time > 50) {
          if (prev_rand_num < 13) {
            c[prev_rand_num].erase_1();
            c[prev_rand_num].move();
            c[prev_rand_num].draw_cacti_1();
            dino_dead();
            cacti_time = millis();

          }
          else if (prev_rand_num < 26) {
            c[prev_rand_num].erase_2();
            c[prev_rand_num].move();
            c[prev_rand_num].draw_cacti_2();
            dino_dead();
            cacti_time = millis();

          }
          else if (prev_rand_num < 39) {
            c[prev_rand_num].erase_3();
            c[prev_rand_num].move();
            c[prev_rand_num].draw_cacti_3();
            dino_dead();
            cacti_time = millis();
          }
        }
      }
    }

    //add in birds
    /*void level_two(bool button_pressed) {
      dino_curr_time = millis();
      if (button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > 100) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          d.draw();
          time = millis();
        }
      }
      int rand_num = random(4);
      if (cacti_curr_time - cacti_time > 50) {
        if (rand_num = 1) {
          c.erase_1();
          c.move();
          c.draw_cacti_1();
          cacti_time = millis();
        }
        if (rand_num = 2) {
          c.erase_2();
          c.move();
          c.draw_cacti_2();
          cacti_time = millis();
        }
        if (rand_num = 3) {
          c.erase_1();
          c.move();
          c.draw_cacti_3();
          cacti_time = millis();
        }
      }
      }

      //first increase in speed for movement of cacti, bird, and dino
      void level_three(bool button_pressed) {
      dino_curr_time = millis();
      if (button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > 75) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          d.draw();
          time = millis();
        }
      }
      int rand_num = random(4);
      if (cacti_curr_time - cacti_time > 50) {
        if (rand_num = 1) {
          c.erase_1();
          c.move();
          c.draw_cacti_1();
          cacti_time = millis();
        }
        if (rand_num = 2) {
          c.erase_2();
          c.move();
          c.draw_cacti_2();
          cacti_time = millis();
        }
        if (rand_num = 3) {
          c.erase_1();
          c.move();
          c.draw_cacti_3();
          cacti_time = millis();
        }
      }
      }

      //second increase in speed for movement of cacti, bird, and dino
      void level_four(bool button_pressed) {
      dino_curr_time = millis();
      if (button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > 50) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          d.draw();
          time = millis();
        }
      }
      int rand_num = random(4);
      if (cacti_curr_time - cacti_time > 50) {
        if (rand_num = 1) {
          c.erase_1();
          c.move();
          c.draw_cacti_1();
          cacti_time = millis();
        }
        if (rand_num = 2) {
          c.erase_2();
          c.move();
          c.draw_cacti_2();
          cacti_time = millis();
        }
        if (rand_num = 3) {
          c.erase_1();
          c.move();
          c.draw_cacti_3();
          cacti_time = millis();
        }
      }
      }

      //third and final increase in speed for movement of cacti, bird, and dino
      void level_five(bool button_pressed) {
      dino_curr_time = millis();
      if (button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > 25) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          d.draw();
          time = millis();
        }
      }
      int rand_num = random(4);
      if (cacti_curr_time - cacti_time > 50) {
        if (rand_num = 1) {
          c.erase_1();
          c.move();
          c.draw_cacti_1();
          cacti_time = millis();
        }
        if (rand_num = 2) {
          c.erase_2();
          c.move();
          c.draw_cacti_2();
          cacti_time = millis();
        }
        if (rand_num = 3) {
          c.erase_1();
          c.move();
          c.draw_cacti_3();
          cacti_time = millis();
        }
      }
      }*/

    void update(int potentiometer_value, bool button_pressed) {
      d.draw();
      print_ground();
      game_time = millis();
      if (game_time <= 20000) {
        level_one(potentiometer_value, button_pressed);
      }
      //    else if(game_time <= 45000){
      //      level_two(button_pressed);
      //    }
      //    else if(game_time <= 75000){
      //      level_three(button_pressed);
      //    }
      //    else if(game_time <= 110000){
      //      level_four(button_pressed);
      //    }
      //    else{
      //      level_five(button_pressed);
      //    }
    }

  private:
    Cactus c[39];
    Bird b;
    Dinosaur d;
    unsigned long time;
    unsigned long dino_curr_time;
    unsigned long game_time;
    unsigned long cacti_time;
    unsigned long cacti_curr_time;
    int prev_rand_num = random(0, 39);
};

Game game;
const int numReadings = 20;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  randomSeed(analogRead(0));
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  game.setup();
}

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(POTENTIOMETER_PIN_NUMBER);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  //int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  game.update(average, button_pressed);

}

void print_ground() {
  matrix.drawPixel(0, 14, YELLOW.to_333());
  matrix.drawPixel(1, 14, YELLOW.to_333());
  matrix.drawPixel(2, 14, YELLOW.to_333());
  matrix.drawPixel(3, 14, YELLOW.to_333());
  matrix.drawPixel(4, 14, YELLOW.to_333());
  matrix.drawPixel(5, 14, YELLOW.to_333());
  matrix.drawPixel(6, 14, YELLOW.to_333());
  matrix.drawPixel(7, 14, YELLOW.to_333());
  matrix.drawPixel(8, 14, YELLOW.to_333());
  matrix.drawPixel(9, 14, YELLOW.to_333());
  matrix.drawPixel(10, 14, YELLOW.to_333());
  matrix.drawPixel(11, 14, YELLOW.to_333());
  matrix.drawPixel(12, 14, YELLOW.to_333());
  matrix.drawPixel(13, 14, YELLOW.to_333());
  matrix.drawPixel(14, 14, YELLOW.to_333());
  matrix.drawPixel(15, 14, YELLOW.to_333());
  matrix.drawPixel(16, 14, YELLOW.to_333());
  matrix.drawPixel(17, 14, YELLOW.to_333());
  matrix.drawPixel(18, 14, YELLOW.to_333());
  matrix.drawPixel(19, 14, YELLOW.to_333());
  matrix.drawPixel(20, 14, YELLOW.to_333());
  matrix.drawPixel(21, 14, YELLOW.to_333());
  matrix.drawPixel(22, 14, YELLOW.to_333());
  matrix.drawPixel(23, 14, YELLOW.to_333());
  matrix.drawPixel(24, 14, YELLOW.to_333());
  matrix.drawPixel(25, 14, YELLOW.to_333());
  matrix.drawPixel(26, 14, YELLOW.to_333());
  matrix.drawPixel(27, 14, YELLOW.to_333());
  matrix.drawPixel(28, 14, YELLOW.to_333());
  matrix.drawPixel(29, 14, YELLOW.to_333());
  matrix.drawPixel(30, 14, YELLOW.to_333());
  matrix.drawPixel(31, 14, YELLOW.to_333());
  matrix.drawPixel(0, 15, YELLOW.to_333());
  matrix.drawPixel(1, 15, YELLOW.to_333());
  matrix.drawPixel(2, 15, YELLOW.to_333());
  matrix.drawPixel(3, 15, YELLOW.to_333());
  matrix.drawPixel(4, 15, YELLOW.to_333());
  matrix.drawPixel(5, 15, YELLOW.to_333());
  matrix.drawPixel(6, 15, YELLOW.to_333());
  matrix.drawPixel(7, 15, YELLOW.to_333());
  matrix.drawPixel(8, 15, YELLOW.to_333());
  matrix.drawPixel(9, 15, YELLOW.to_333());
  matrix.drawPixel(10, 15, YELLOW.to_333());
  matrix.drawPixel(11, 15, YELLOW.to_333());
  matrix.drawPixel(12, 15, YELLOW.to_333());
  matrix.drawPixel(13, 15, YELLOW.to_333());
  matrix.drawPixel(14, 15, YELLOW.to_333());
  matrix.drawPixel(15, 15, YELLOW.to_333());
  matrix.drawPixel(16, 15, YELLOW.to_333());
  matrix.drawPixel(17, 15, YELLOW.to_333());
  matrix.drawPixel(18, 15, YELLOW.to_333());
  matrix.drawPixel(19, 15, YELLOW.to_333());
  matrix.drawPixel(20, 15, YELLOW.to_333());
  matrix.drawPixel(21, 15, YELLOW.to_333());
  matrix.drawPixel(22, 15, YELLOW.to_333());
  matrix.drawPixel(23, 15, YELLOW.to_333());
  matrix.drawPixel(24, 15, YELLOW.to_333());
  matrix.drawPixel(25, 15, YELLOW.to_333());
  matrix.drawPixel(26, 15, YELLOW.to_333());
  matrix.drawPixel(27, 15, YELLOW.to_333());
  matrix.drawPixel(28, 15, YELLOW.to_333());
  matrix.drawPixel(29, 15, YELLOW.to_333());
  matrix.drawPixel(30, 15, YELLOW.to_333());
  matrix.drawPixel(31, 15, YELLOW.to_333());
}
