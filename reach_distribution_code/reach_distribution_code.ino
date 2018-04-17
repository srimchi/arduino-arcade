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
const int BUTTON_PIN_NUMBER_1 = 10; //button one
const int BUTTON_PIN_NUMBER_2 = 11; //button two

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void print_ground();
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
      //matrix.drawPixel(x, y + 1, RED.to_333());
    }
    void redraw_with_rgb(Color color) {
      matrix.drawPixel(3, 9, color.to_333());
      matrix.drawPixel(4, 10, color.to_333());
      matrix.drawPixel(4, 11, color.to_333());
      matrix.drawPixel(3, 11, color.to_333());
      matrix.drawPixel(3, 12, color.to_333());
      matrix.drawPixel(3, 13, color.to_333());
      matrix.drawPixel(2 , 13, color.to_333());
      matrix.drawPixel(1, 13, color.to_333());
      matrix.drawPixel(0, 13, color.to_333());
      matrix.drawPixel(2, 12, color.to_333());
      matrix.drawPixel(2, 11, color.to_333());
      matrix.drawPixel(2, 10, color.to_333());
      matrix.drawPixel(0, 12, color.to_333());
      //matrix.drawPixel(x, y + 2, RED.to_333());
    }

};

class Bird {
  public:

    Bird() {

      x = 31;
      bird_on_screen = false;
    }

    void set_bird_on_screen() {
      bird_on_screen = true;
    }

    void draw_bird() {
      matrix.drawPixel(x, y, RED.to_333());
      matrix.drawPixel(x + 1, y - 1, RED.to_333());
      matrix.drawPixel(x - 1, y - 1, RED.to_333());
    }

    void erase() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x + 1, y - 1, BLACK.to_333());
      matrix.drawPixel(x - 1, y - 1, BLACK.to_333());
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
      if (x >= -1) {
        x--;
      }
      else {
        bird_on_screen = false;
      }
    }

    bool get_bird_on_screen() {
      return bird_on_screen;
    }

  private:
    int x;
    int y;
    bool bird_on_screen;
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
      if (x >= -2) {
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
      for (int i = 0; i < 40; i++) {
        cactus_bird[i] = random(0, 4);
      }

    }

    void dino_dead_bird() {
      if ((d.get_x() + 1 == b[i3].get_x() && d.get_y() + 1 == b[i3].get_y()) ||
          (d.get_x() + 1 == b[i3].get_x() && d.get_y() + 2 == b[i3].get_y()) ||
          (d.get_x() + 1 == b[i3].get_x() && d.get_y() + 4 == b[i3].get_y()) ||
          (d.get_x() == b[i3].get_x() && d.get_y() + 5 == b[i3].get_y()) ||
          (d.get_x() - 1 == b[i3].get_x() && d.get_y() + 5 == b[i3].get_y()) ||
          (d.get_x() - 2 == b[i3].get_x() && d.get_y() + 5 == b[i3].get_y()) ||
          (d.get_x() - 3 == b[i3].get_x() && d.get_y() + 5 == b[i3].get_y()) ||
          (d.get_x() == b[i3].get_x() && d.get_y() == b[i3].get_y()) ||
          (d.get_x() + 1 == b[i3].get_x() + 1 && d.get_y() + 1 == b[i3].get_y() - 1) ||
          (d.get_x() + 1 == b[i3].get_x() + 1 && d.get_y() + 2 == b[i3].get_y() - 1) ||
          (d.get_x() + 1 == b[i3].get_x() + 1 && d.get_y() + 4 == b[i3].get_y() - 1) ||
          (d.get_x() == b[i3].get_x() + 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 1 == b[i3].get_x() + 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 2 == b[i3].get_x() + 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 3 == b[i3].get_x() + 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() == b[i3].get_x() + 1 && d.get_y() == b[i3].get_y() - 1) ||
          (d.get_x() + 1 == b[i3].get_x() - 1 && d.get_y() + 1 == b[i3].get_y() - 1) ||
          (d.get_x() + 1 == b[i3].get_x() - 1 && d.get_y() + 2 == b[i3].get_y() - 1) ||
          (d.get_x() + 1 == b[i3].get_x() - 1 && d.get_y() + 4 == b[i3].get_y() - 1) ||
          (d.get_x() == b[i3].get_x() - 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 1 == b[i3].get_x() - 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 2 == b[i3].get_x() - 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 3 == b[i3].get_x() - 1 && d.get_y() + 5 == b[i3].get_y() - 1) ||
          (d.get_x() - 3 == b[i3].get_x() - 1 && d.get_y() + 5 == b[i3].get_y() - 1)) {
        game_over();
      }
    }
    void dino_dead_cactus() {
      if ((d.get_x() + 1 == c[i2].get_x() && d.get_y() + 1 == c[i2].get_y() - 1) ||
          (d.get_x() + 1 == c[i2].get_x() && d.get_y() + 2 == c[i2].get_y() - 1) ||
          (d.get_x() + 1 == c[i2].get_x() && d.get_y() + 4 == c[i2].get_y() - 1) ||
          (d.get_x() == c[i2].get_x() && d.get_y() + 5 == c[i2].get_y() - 1) ||
          (d.get_x() - 1 == c[i2].get_x() && d.get_y() + 5 == c[i2].get_y() - 1) ||
          (d.get_x() - 2 == c[i2].get_x() && d.get_y() + 5 == c[i2].get_y() - 1) ||
          (d.get_x() - 3 == c[i2].get_x() && d.get_y() + 5 == c[i2].get_y() - 1) ||
          (d.get_x() + 1 == c[i2].get_x() - 1 && d.get_y() + 1 == c[i2].get_y()) ||
          (d.get_x() + 1 == c[i2].get_x() - 1 && d.get_y() + 2 == c[i2].get_y()) ||
          (d.get_x() + 1 == c[i2].get_x() - 1 && d.get_y() + 4 == c[i2].get_y()) ||
          (d.get_x() == c[i2].get_x() - 1 && d.get_y() + 5 == c[i2].get_y()) ||
          (d.get_x() - 1 == c[i2].get_x() - 1 && d.get_y() + 5 == c[i2].get_y()) ||
          (d.get_x() - 2 == c[i2].get_x() - 1 && d.get_y() + 5 == c[i2].get_y()) ||
          (d.get_x() - 3 == c[i2].get_x() - 1 && d.get_y() + 5 == c[i2].get_y())) {
        game_over();
      }
    }

    void dino_dead_bird3() {
      if ((d.get_x() + 1 == bird[i].get_x() && d.get_y() + 1 == bird[i].get_y()) ||
          (d.get_x() + 1 == bird[i].get_x() && d.get_y() + 2 == bird[i].get_y()) ||
          (d.get_x() + 1 == bird[i].get_x() && d.get_y() + 4 == bird[i].get_y()) ||
          (d.get_x() == bird[i].get_x() && d.get_y() + 5 == bird[i].get_y()) ||
          (d.get_x() - 1 == bird[i].get_x() && d.get_y() + 5 == bird[i].get_y()) ||
          (d.get_x() - 2 == bird[i].get_x() && d.get_y() + 5 == bird[i].get_y()) ||
          (d.get_x() - 3 == bird[i].get_x() && d.get_y() + 5 == bird[i].get_y()) ||
          (d.get_x() == bird[i].get_x() && d.get_y() == bird[i].get_y()) ||
          (d.get_x() + 1 == bird[i].get_x() + 1 && d.get_y() + 1 == bird[i].get_y() - 1) ||
          (d.get_x() + 1 == bird[i].get_x() + 1 && d.get_y() + 2 == bird[i].get_y() - 1) ||
          (d.get_x() + 1 == bird[i].get_x() + 1 && d.get_y() + 4 == bird[i].get_y() - 1) ||
          (d.get_x() == bird[i].get_x() + 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 1 == bird[i].get_x() + 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 2 == bird[i].get_x() + 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 3 == bird[i].get_x() + 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() == bird[i].get_x() + 1 && d.get_y() == bird[i].get_y() - 1) ||
          (d.get_x() + 1 == bird[i].get_x() - 1 && d.get_y() + 1 == bird[i].get_y() - 1) ||
          (d.get_x() + 1 == bird[i].get_x() - 1 && d.get_y() + 2 == bird[i].get_y() - 1) ||
          (d.get_x() + 1 == bird[i].get_x() - 1 && d.get_y() + 4 == bird[i].get_y() - 1) ||
          (d.get_x() == bird[i].get_x() - 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 1 == bird[i].get_x() - 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 2 == bird[i].get_x() - 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 3 == bird[i].get_x() - 1 && d.get_y() + 5 == bird[i].get_y() - 1) ||
          (d.get_x() - 3 == bird[i].get_x() - 1 && d.get_y() + 5 == bird[i].get_y() - 1)) {
        game_over();
      }
    }
    void dino_dead_cactus3() {
      if ((d.get_x() + 1 == cac[i].get_x() && d.get_y() + 1 == cac[i].get_y() - 1) ||
          (d.get_x() + 1 == cac[i].get_x() && d.get_y() + 2 == cac[i].get_y() - 1) ||
          (d.get_x() + 1 == cac[i].get_x() && d.get_y() + 4 == cac[i].get_y() - 1) ||
          (d.get_x() == cac[i].get_x() && d.get_y() + 5 == cac[i].get_y() - 1) ||
          (d.get_x() - 1 == cac[i].get_x() && d.get_y() + 5 == cac[i].get_y() - 1) ||
          (d.get_x() - 2 == cac[i].get_x() && d.get_y() + 5 == cac[i].get_y() - 1) ||
          (d.get_x() - 3 == cac[i].get_x() && d.get_y() + 5 == cac[i].get_y() - 1) ||
          (d.get_x() + 1 == cac[i].get_x() - 1 && d.get_y() + 1 == cac[i].get_y()) ||
          (d.get_x() + 1 == cac[i].get_x() - 1 && d.get_y() + 2 == cac[i].get_y()) ||
          (d.get_x() + 1 == cac[i].get_x() - 1 && d.get_y() + 4 == cac[i].get_y()) ||
          (d.get_x() == cac[i].get_x() - 1 && d.get_y() + 5 == cac[i].get_y()) ||
          (d.get_x() - 1 == cac[i].get_x() - 1 && d.get_y() + 5 == cac[i].get_y()) ||
          (d.get_x() - 2 == cac[i].get_x() - 1 && d.get_y() + 5 == cac[i].get_y()) ||
          (d.get_x() - 3 == cac[i].get_x() - 1 && d.get_y() + 5 == cac[i].get_y())) {
        game_over();
      }
    }

    void dinosaur_button_jump(int period, bool button_pressed, bool button_pressed_2) {
      dino_curr_time = millis();

      if (button_pressed_2 == false && button_pressed == true && d.has_jumped() == false) {
        d.set_jump();
        time = millis();
      }
      if (d.has_jumped() == true) {
        if (dino_curr_time - time > period) {
          d.erase();
          d.dino_jump();
          d.dino_come_down();
          dino_dead_cactus();
          dino_dead_bird();
          d.draw();
          time = millis();
        }
      }

    }

    void dinosaur_button_duck(bool button_pressed_2) {
      if (d.has_jumped() == false && button_pressed_2 == true) {
        d.erase();
        d.duck();
        dino_dead_bird();
      }
      else if (d.has_jumped() == false && button_pressed_2 == false) {
        d.duck_erase();
        d.draw();
        dino_dead_bird();
      }

    }
    //just cactus
    void level_one(bool button_pressed, bool button_pressed_2) {

      cacti_curr_time = millis();
      dinosaur_button_jump(100, button_pressed, button_pressed_2);
      dinosaur_button_duck(button_pressed_2);

      if (game_time <= 19000 && c[i2].get_cactus_on_screen() == false) {
        c[i2].set_cactus_on_screen();
        cacti_time = millis();
        prev_random_num = random(0, 3);
      }
      else {
        if (cacti_curr_time - cacti_time > 60) {
          if (prev_random_num == 0) {
            c[i2].erase_1();
            c[i2].move();
            dino_dead_cactus();
            c[i2].draw_cacti_1();
            cacti_time = millis();
            if (c[i2].get_x() <= -3) {
              i2 += 1;
            }

          }
          else if (prev_random_num == 1) {
            c[i2].erase_2();
            c[i2].move();
            dino_dead_cactus();
            c[i2].draw_cacti_2();
            cacti_time = millis();
            if (c[i2].get_x() <= -3) {
              i2 += 1;
            }

          }
          else if (prev_random_num == 2) {
            c[i2].erase_3();
            c[i2].move();
            dino_dead_cactus();
            c[i2].draw_cacti_3();
            cacti_time = millis();
            if (c[i2].get_x() <= -3) {
              i2 += 1;
            }
          }
        }
      }
    }

    //only birds
    void level_two(bool button_pressed, bool button_pressed_2) {

      bird_curr_time = millis();
      dinosaur_button_jump(85, button_pressed, button_pressed_2);
      dinosaur_button_duck(button_pressed_2);

      if (game_time <= 46000 && b[i3].get_bird_on_screen() == false) {
        b[i3].set_bird_on_screen();
        int rand_num_y = random(6, 13);
        b[i3].set_y(rand_num_y);
        bird_time = millis();
      }
      else {
        if (bird_curr_time - bird_time > 55) {
          b[i3].erase();
          b[i3].move();
          b[i3].draw_bird();
          dino_dead_bird();
          bird_time = millis();
          if (b[i3].get_x() <= -2) {
            i3 += 1;
          }
        }
      }

    }

    //first increase in speed for movement of cacti, bird, and dino
    void level_three(bool button_pressed, bool button_pressed_2) {
      cacti_curr_time = millis();
      bird_curr_time = millis();

      dinosaur_button_jump(50, button_pressed, button_pressed_2);
      dinosaur_button_duck(button_pressed_2);

      if (cactus_bird[i] == 0) {
        if (cac[i].get_cactus_on_screen() == false) {
          cac[i].set_cactus_on_screen();
          cacti_time = millis();
        }
        else {
          if (cacti_curr_time - cacti_time > 30) {
            cac[i].erase_1();
            cac[i].move();
            dino_dead_cactus3();
            cac[i].draw_cacti_1();
            cacti_time = millis();
            if (cac[i].get_x() <= -3) {
              i += 1;
            }
          }
        }
      }
      else if (cactus_bird[i] == 1) {

        if (cac[i].get_cactus_on_screen() == false) {
          cac[i].set_cactus_on_screen();
          cacti_time = millis();
        }
        else {
          if (cacti_curr_time - cacti_time > 30) {
            cac[i].erase_2();
            cac[i].move();
            dino_dead_cactus3();
            cac[i].draw_cacti_2();
            cacti_time = millis();
            if (cac[i].get_x() <= -2) {
              i += 1;
            }
          }
        }
      }
      else if (cactus_bird[i] == 2) {
        if (cac[i].get_cactus_on_screen() == false) {
          cac[i].set_cactus_on_screen();
          cacti_time = millis();
        }
        else {
          if (cacti_curr_time - cacti_time > 30) {
            cac[i].erase_3();
            cac[i].move();
            dino_dead_cactus3();
            cac[i].draw_cacti_3();
            cacti_time = millis();
            if (cac[i].get_x() <= -2) {
              i += 1;
            }
          }
        }

      }
      else if (cactus_bird[i] == 3) {
        if (bird[i].get_bird_on_screen() == false) {
          bird[i].set_bird_on_screen();
          int rand_num_y = random(6, 13);
          bird[i].set_y(rand_num_y);
          bird_time = millis();
        }
        else {
          if (bird_curr_time - bird_time > 35) {
            bird[i].erase();
            bird[i].move();
            bird[i].draw_bird();
            dino_dead_bird3();
            bird_time = millis();
            if (bird[i].get_x() <= -2) {
              i += 1;
            }
          }
        }
      }
    }

    //second increase in speed for movement of cacti, bird, and dino
    void level_four(bool button_pressed, bool button_pressed_2) {
      cacti_curr_time = millis();

      dinosaur_button_jump(50, button_pressed, button_pressed_2);
      dinosaur_button_duck(button_pressed_2);


    }

    //third and final increase in speed for movement of cacti, bird, and dino
    void level_five(bool button_pressed, bool button_pressed_2) {
      cacti_curr_time = millis();

      dinosaur_button_jump(25, button_pressed, button_pressed_2);
      dinosaur_button_duck(button_pressed_2);


    }

    long get_game_time() {
      return game_time / 1000;
    }

    void update(bool button_pressed, bool button_pressed_2) {

      //print_ground();
      game_time = millis();
      if (game_time <= 24350) {
        level_one(button_pressed, button_pressed_2);
      }
      else if (game_time <= 48000) {
        level_two(button_pressed, button_pressed_2);
      }
      else if (game_time <= 75000) {
        level_three(button_pressed, button_pressed_2);
      }
      //      else if (game_time <= 110000) {
      //        level_four(button_pressed, button_pressed_2);
      //      }
      //      else {
      //        level_five(button_pressed, button_pressed_2);
      //      }
    }

  private:
    Cactus c[20];
    Bird b[20];
    Dinosaur d;
    unsigned long time;
    unsigned long dino_curr_time;
    unsigned long game_time;
    unsigned long bird_time;
    unsigned long bird_curr_time;
    unsigned long cacti_time;
    unsigned long cacti_curr_time;
    int i2 = 0;
    int prev_random_num = random(0, 3);
    int i3 = 0;
    int i = 0;
    int cactus_bird[40];
    Cactus cac[40];
    Bird bird[40];
};

Game game;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(BUTTON_PIN_NUMBER_1, INPUT);
  pinMode(BUTTON_PIN_NUMBER_2, INPUT); //button two
  matrix.begin();
  game.setup();
}

void loop() {
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER_1) == HIGH);
  bool button_pressed_2 = (digitalRead(BUTTON_PIN_NUMBER_2) == HIGH);
  game.update(button_pressed, button_pressed_2);

}

void game_over() {
  matrix.fillScreen(BLACK.to_333());
  matrix.setCursor(0, 1);
  matrix.setTextColor(WHITE.to_333());
  matrix.print("SCORE");
  matrix.setCursor(11, 9);
  matrix.setTextColor(WHITE.to_333());
  matrix.print(game.get_game_time());
  delay(3000);
  exit(0);
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
