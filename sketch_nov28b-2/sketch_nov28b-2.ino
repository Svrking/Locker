#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables para el teclado y la contraseña
int n = 0;
int rele = 35;
String pswd = "123456";  // Contraseña correcta
String pswdp = "";       // Contraseña ingresada
const byte x = 4;
const byte y = 4;

// Definir las teclas del teclado
char keys[x][y] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Pines del teclado
byte xv[x] = { 13, 12, 14, 27 };
byte yv[y] = { 26, 25, 33, 32 };

// Crear el objeto del teclado
Keypad t = Keypad(makeKeymap(keys), xv, yv, x, y);

void setup() {
  pinMode(rele, OUTPUT);
  Serial.begin(9600);  // Iniciar la comunicación serial
  lcd.clear();
  lcd.init();       // Inicializar el LCD
  lcd.backlight();  // Encender la luz de fondo del LCD
}

void loop() {
  char w = t.getKey();  // Leer la tecla presionada

  if (w) {            // Si se presiona una tecla
    Serial.print(w);  // Mostrar la tecla en el monitor serial
    lcd.setCursor(n, 0);
    lcd.print("*");  // Mostrar "*" en la pantalla LCD
    n++;

    if (n > 16 || w == '#') {  // Si se alcanza el límite de caracteres o se presiona "#"
      n = 0;                   // Resetear el cursor

      // Comparar la contraseña ingresada con la correcta
      if (pswdp == pswd) {
        digitalWrite(rele, HIGH);
        lcd.clear();
        lcd.home();
        lcd.print("Welcome");
        delay(2000);  // Mostrar el mensaje por 2 segundos
        lcd.clear();
        pswdp = "";  // Limpiar la contraseña ingresada
      } else {
        digitalWrite(rele, LOW);
        lcd.clear();
        lcd.home();
        lcd.print("Wrong pswd");
        delay(2000);  // Mostrar el mensaje por 2 segundos
        lcd.clear();
        pswdp = "";  // Limpiar la contraseña ingresada
      }
    } else {
      pswdp += w;  // Agregar la tecla presionada a la contraseña ingresada
    }
  }
}