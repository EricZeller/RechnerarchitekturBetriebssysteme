#include <avr/io.h>
#include <stdio.h>

#define USE_OWN_EEPROM 1 /* 0 = EEPROM-Funktionen der AVR-LibC nutzen, 1 = eigene Funktionen nutzen */

#if USE_OWN_EEPROM
/* Vordeklarationen für eigene EEPROM-Funktionen */
uint8_t eeprom_read_byte(const uint8_t *p);
uint16_t eeprom_read_word(const uint16_t *p);
uint32_t eeprom_read_dword(const uint32_t *p);

void eeprom_write_byte(uint8_t *p, uint8_t value);
void eeprom_write_word(uint16_t *p, uint16_t value);
void eeprom_write_dword(uint32_t *p, uint32_t value);
#else
/* Nutze AVR-LibC-Implementierung der EEPROM-Funktionen */
#include <avr/eeprom.h>
#endif

#define OFFSET_MARKER 0
#define OFFSET_COUNT 4
#define OFFSET_VERSION 8

#define MARKER 0x0F00B002
#define CURRENT_VERSION 4

void uart_setup()
{
  unsigned int ubrr = 16000000 / 16 / 9600 - 1;
  /*Set baud rate */
  UBRR0H = ubrr >> 8; // obere Bits und
  UBRR0L = ubrr;      // untere Bits von Baudrate

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // enabled read and write
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bit, ein Stoppbit
}

void uart_send_char(char ch)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  UDR0 = ch;
}

int uart_putc(char ch, FILE *file)
{
  if (ch == '\n')
  {
    uart_send_char('\r');
  }

  uart_send_char(ch);
  return 0;
}

/* Prüfen, ob EEPROM validen Marker mit Version enthält */
int has_valid_header()
{
  uint32_t marker;
  uint16_t version;

  /* TODO Marker-Wert von Adresse OFFSET_MARKER nach marker einlesen*/
  marker = eeprom_read_dword((const uint32_t *)OFFSET_MARKER);
  if (marker != MARKER)
  {
    /* Kein valider Marker */
    return 0;
  }

  /* Valider Marker wurde gefunden => Version prüfen */
  /* TODO Version von Adresse OFFSET_VERSION nach version einlesen*/
  version = eeprom_read_word((const uint16_t *)OFFSET_VERSION);
  if (version != CURRENT_VERSION)
  {
    /* Nicht die aktuelle Version */
    return 0;
  }

  /* Marker und Version stimmen */
  return 1;
}

/* Schreibe initialen Header mit count=1 */
void initialize_header()
{
  eeprom_write_dword((uint32_t *)OFFSET_MARKER, MARKER);
  eeprom_write_word((uint16_t *)OFFSET_COUNT, 1);
  eeprom_write_word((uint16_t *)OFFSET_VERSION, CURRENT_VERSION);
  /* TODO MARKER an Adresse OFFSET_MARKER schreiben*/
  /* TODO Zählerwert 1 an Adresse OFFSET_COUNT schreiben*/
  /* TODO CURRENT_VERSION an Adresse OFFSET_VERSION schreiben*/
}

/* Zählerwert aktualisieren und zurückgeben */
uint16_t read_and_update_count()
{
  if (has_valid_header())
  {
    /* Es gibt schon einen validen Header => Zähler erhöhen */
    uint16_t version;
    version = eeprom_read_word((const uint16_t *)OFFSET_COUNT);
    /* TODO Aktuellen Zählerwert von Adresse OFFSET_COUNT in version einlesen*/
    /* Version um 1 erhöhen */
    version++;
    eeprom_write_word((uint16_t *)OFFSET_COUNT, version);
    /* TODO Neuen Zählerwert an Adresse OFFSET_COUNT schreiben*/
    return version;
  }
  else
  {
    /* Es gibt noch keinen validen Header => wir schreiben einen */
    initialize_header();
    return 1;
  }
}

int main()
{
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
  while (1)
    ;
}

#if USE_OWN_EEPROM
/* Eigene Implementierungen der EEPROM-Funktionen */
uint8_t eeprom_read_byte(const uint8_t *p)
{
    /* Warten bis vorheriger Schreibvorgang abgeschlossen ist */
    while(EECR & (1<<EEPE));
    
    /* Adresse setzen */
    uint16_t addr = (uint16_t)p;
    EEAR = addr;
    
    /* Lesevorgang starten */
    EECR |= (1<<EERE);
    
    /* Gelesenes Byte zurückgeben */
    return EEDR;
}

uint16_t eeprom_read_word(const uint16_t *p)
{
    uint16_t value;
    uint8_t *ptr = (uint8_t*)&value;
    uint16_t addr = (uint16_t)p;
    
    /* Little Endian lesen (LSB zuerst) */
    *ptr++ = eeprom_read_byte((uint8_t*)addr);
    *ptr = eeprom_read_byte((uint8_t*)(addr+1));
    
    return value;
}

uint32_t eeprom_read_dword(const uint32_t *p)
{
    uint32_t value;
    uint8_t *ptr = (uint8_t*)&value;
    uint16_t addr = (uint16_t)p;
    
    /* Little Endian lesen (LSB zuerst) */
    *ptr++ = eeprom_read_byte((uint8_t*)addr);
    *ptr++ = eeprom_read_byte((uint8_t*)(addr+1));
    *ptr++ = eeprom_read_byte((uint8_t*)(addr+2));
    *ptr = eeprom_read_byte((uint8_t*)(addr+3));
    
    return value;
}

void eeprom_write_byte(uint8_t *p, uint8_t value)
{
    /* Warten bis vorheriger Schreibvorgang abgeschlossen ist */
    while(EECR & (1<<EEPE));
    
    /* Adresse setzen */
    uint16_t addr = (uint16_t)p;
    EEAR = addr;
    
    /* Daten setzen */
    EEDR = value;
    
    /* Schreibvorgang vorbereiten */
    EECR |= (1<<EEMPE);
    /* Schreibvorgang starten (innerhalb von 4 Taktzyklen nach EEMPE) */
    EECR |= (1<<EEPE);
}

void eeprom_write_word(uint16_t *p, uint16_t value)
{
    uint8_t *ptr = (uint8_t*)&value;
    uint16_t addr = (uint16_t)p;
    
    /* Little Endian schreiben (LSB zuerst) */
    eeprom_write_byte((uint8_t*)addr, *ptr++);
    eeprom_write_byte((uint8_t*)(addr+1), *ptr);
}

void eeprom_write_dword(uint32_t *p, uint32_t value)
{
    uint8_t *ptr = (uint8_t*)&value;
    uint16_t addr = (uint16_t)p;
    
    /* Little Endian schreiben (LSB zuerst) */
    eeprom_write_byte((uint8_t*)addr, *ptr++);
    eeprom_write_byte((uint8_t*)(addr+1), *ptr++);
    eeprom_write_byte((uint8_t*)(addr+2), *ptr++);
    eeprom_write_byte((uint8_t*)(addr+3), *ptr);
}
#endif