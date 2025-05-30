#include <avr/io.h>
#include <stdio.h>

#define USE_OWN_EEPROM 1 /* 0 = EEPROM-Funktionen der AVR-LibC nutzen, 1 = eigene Funktionen nutzen */

#if USE_OWN_EEPROM
/* Vordeklarationen für eigene EEPROM-Funktionen */
uint8_t eeprom_read_byte(const uint8_t* p);
uint16_t eeprom_read_word(const uint16_t* p);
uint32_t eeprom_read_dword(const uint32_t* p);

void eeprom_write_byte(uint8_t* p, uint8_t value);
void eeprom_write_word(uint16_t* p, uint16_t value);
void eeprom_write_dword(uint32_t* p, uint32_t value);
#else
/* Nutze AVR-LibC-Implementierung der EEPROM-Funktionen */
#include <avr/eeprom.h>
#endif

#define OFFSET_MARKER 0
#define OFFSET_COUNT 4
#define OFFSET_VERSION 8

#define MARKER 0x0F00B002
#define CURRENT_VERSION 1

void uart_setup() {
    /* TODO UART initialisieren - 9600Baud, 8N1*/
}

void uart_send_char(char ch) {
    /* TODO Zeichen ch über UART senden*/
}

int uart_putc(char ch, FILE *file) {
    if (ch == '\n') {
        uart_send_char('\r');
    }

    uart_send_char(ch);
    return 0;
}

/* Prüfen, ob EEPROM validen Marker mit Version enthält */
int has_valid_header() {
  uint32_t marker;
  uint16_t version;

  /* TODO Marker-Wert von Adresse OFFSET_MARKER nach marker einlesen*/
  if (marker != MARKER) {
    /* Kein valider Marker */
    return 0;
  }

  /* Valider Marker wurde gefunden => Version prüfen */
  /* TODO Version von Adresse OFFSET_VERSION nach version einlesen*/
  if (version != CURRENT_VERSION) {
    /* Nicht die aktuelle Version */
    return 0;
  }

  /* Marker und Version stimmen */
  return 1;
}

/* Schreibe initialen Header mit count=1 */
void initialize_header() {
  /* TODO MARKER an Adresse OFFSET_MARKER schreiben*/
  /* TODO Zählerwert 1 an Adresse OFFSET_COUNT schreiben*/
  /* TODO CURRENT_VERSION an Adresse OFFSET_VERSION schreiben*/
}

/* Zählerwert aktualisieren und zurückgeben */
uint16_t read_and_update_count() {
  if (has_valid_header()) {
    /* Es gibt schon einen validen Header => Zähler erhöhen */
    uint16_t version;
    /* TODO Aktuellen Zählerwert von Adresse OFFSET_COUNT in version einlesen*/
    /* Version um 1 erhöhen */
    version++;
    /* TODO Neuen Zählerwert an Adresse OFFSET_COUNT schreiben*/
    return version;
  } else {
    /* Es gibt noch keinen validen Header => wir schreiben einen */
    initialize_header();
    return 1;
  }
}

int main() {
  /* UART-Initialisierung */
  uart_setup();

  /* Initialisierung für stdout */
  stdout = fdevopen(uart_putc, 0);
  stderr = 0;

  /* Zähler aktualisieren */
  uint16_t count = read_and_update_count();

  /* Zählerwert ausgeben */
  printf("Zaehlerwert %u\n", count);

  /* Endlos warten */
  while (1);
}

#if USE_OWN_EEPROM
/* Eigene Implementierungen der EEPROM-Funktionen */
uint8_t eeprom_read_byte(const uint8_t* p) {
  /* TODO Einzelnes Byte von Adresse p aus dem EEPROM lesen und zurückgeben*/
}

uint16_t eeprom_read_word(const uint16_t* p) {
  /* TODO Zwei Bytes von Adresse p aus dem EEPROM lesen und als uint16_t zurückgeben*/
}

uint32_t eeprom_read_dword(const uint32_t* p) {
  /* TODO Zwei Words von Adresse p aus dem EEPROM lesen und als uint32_t zurückgeben*/
}

void eeprom_write_byte(uint8_t* p, uint8_t value) {
  /* TODO Byte value an Adresse p im EEPROM schreiben*/
}

void eeprom_write_word(uint16_t* p, uint16_t value) {
  /* TODO value als Word an Adresse p im EEPROM schreiben*/
}

void eeprom_write_dword(uint32_t* p, uint32_t value) {
  /* TODO value als Double-Word an Adresse p im EEPROM schreiben*/
}
#endif