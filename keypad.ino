#define LAYOUT_US_ENGLISH
#include <HID-Project.h>
#include <HID-Settings.h>

/*******************************************************************
 *  A simple Macro keyboard built with Arduino Pro Micro and a        
 *  4*4 Button Matrix.
 *  
 *  Parts:
 *  Arduino Pro Micro* - http://s.click.aliexpress.com/e/FQmMd5uc 
 *  4*4 Keypad Button Matrix* - http://s.click.aliexpress.com/e/CqnjTgGg 
 *  
 *  * = Affilate
 *                                                                 
 *  Written by Brian Lough
 *  YouTube: https://www.youtube.com/brianlough
 *  Tindie: https://www.tindie.com/stores/brianlough/
 *  Twitter: https://twitter.com/witnessmenow                                 
 *******************************************************************/

// ----------------------------
// Standard Libraries
// ----------------------------

//#include "Keyboard.h"
// Library with a lot of the HID definitions and methods
// Can be useful to take a look at it see whats available
// https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <Keypad.h>
// This library is for interfacing with the 4x4 Matrix
// 
// Can be installed from the library manager, search for "keypad"
// and install the one by Mark Stanley and Alexander Brevig
// https://playground.arduino.cc/Code/Keypad/

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

// the library will return the character inside this array
// when the appropriate button is pressed.
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  BootKeyboard.begin();     // Para teclas extendidas
  Consumer.begin();  //Para multimedia
}

// Mantiene apretado todos los botones. 
void commandoDiscord(uint8_t key) { //comandos dedicados para discord
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
}
int layer_actual = 0;
void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    Serial.println(layer_actual);
    
    switch (key) {
      case 'A'://posibles layers por ahora nada
        layer_actual = (layer_actual + 1) % 2;
        break;
      case '1': //volumen hacia abajo
        Consumer.write(MEDIA_VOLUME_DOWN);
        break;
      case '2': //volumen hacia arriba
        Consumer.write(HID_CONSUMER_MUTE);
        break;
      case '3': //multimedia mutear/desmutear
        Consumer.write(MEDIA_VOLUME_UP);
        break;
      case '4': //
        if (layer_actual == 0) { //cambiar a la pestaña inmediatamente anterior
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(KEY_TAB);
        } else if (layer_actual == 1) { //Abrir nueva pestaña (chrome)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('t');
        }
        break;
      case '5': 
        if (layer_actual == 0) { //abrir menu de apps
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(KEY_TAB);
        } else if (layer_actual == 1) { //abrir ultima pestaña cerrada
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('t');
        }  
        break;
      case '6':
        if (layer_actual == 0) { //cambiar pestañas una vez abierto el menu de apps
          Keyboard.press(KEY_TAB);
        } else if (layer_actual == 1) { //mover entre pestañas (hacia derecha)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_TAB);
        }  
        break;
      case 'B': 
        if (layer_actual == 0) { //enter
          Keyboard.press(KEY_RETURN);
        } else if (layer_actual == 1) { //Abrir nueva pestaña de incognito (chrome)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('n');
        }
        break;
      case '7':
        if (layer_actual == 0) { //anterior (spotify)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ARROW);
        } else if (layer_actual == 1) { //cerrar pestaña de chrome
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('w');
        }
        break;
      case '8': 
        if (layer_actual == 0) {//pausar/reanudar (pensado para usar con spotify abierto)
          Keyboard.press(KEY_SPACE);
        } else if (layer_actual == 1) { //cerrar todas las pestañas de chrome
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('w');
        }
        break;
      case '9': 
        if (layer_actual == 0) { //siguiente (pensado para usar con spotify abierto)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_RIGHT_ARROW);
        } else if (layer_actual == 1) { //recargar página chrome (F5)
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('r');
        }
        break;
      case 'C':
        if (layer_actual == 0) { //abrir spotify  
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('s');
        }else if (layer_actual == 1) { //abrir chrome
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('g');
        }
        break;
      case '*':
        if (layer_actual == 0) { //mute/unmute discord
          commandoDiscord('m');
        }else if (layer_actual == 1) { //snap izq app
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_LEFT_ARROW);
        }
        break;
      case '0': 
        if (layer_actual == 0) {//ensordecer/volver a poner sonido
          commandoDiscord('d');
        }else if (layer_actual == 1) { //snap der app
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_RIGHT_ARROW);
        }
        break;
      case '#':
        if (layer_actual == 0) {//ir a un canal
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('k');
        } else if (layer_actual == 1) {//mostrar escritorio
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press('d');
        }
        break;
      case 'D': //abrir discord
        if (layer_actual == 0){ //abrir discord
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('d');
        } else if (layer_actual == 1) { //administrador de tareas
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_ESC);
        }
        break;
    }

    delay(100);
    Keyboard.releaseAll(); //suelta los botones
  }
}