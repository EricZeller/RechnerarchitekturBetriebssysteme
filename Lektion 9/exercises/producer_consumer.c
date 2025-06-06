#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> /* für sleep */



/* Vorwärtsdeklarationen von Funktionen */
void *producer_main(void* param);
void *consumer_main(void* param);

/* Maximal zu erzeugende Elemente */
#define PRODUCED_ITEMS 100
/* Anzahl der Producer */
#define PRODUCER_COUNT 4

/* Globale Variablen */
#define BUFFER_SIZE 4               /* Anzahl der Einträge im Buffer */
int buffer[BUFFER_SIZE];            /* Puffer */
int read_index = 0;                 /* Lesezeiger */
int write_index = 0;                /* Schreibzeiger */
volatile int buffer_level = 0;      /* Füllstand */
volatile int total_count = 0;       /* Gesamtzahl erzeugter Elemente */
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; /* Mutex für total_count */

int main(void)
{
    int ret;    /* Variable für Rückgabewerte von pthread_*-Funktionen */
    pthread_t consumer_id;
    pthread_t producer_id[PRODUCER_COUNT];
    int producer_index[PRODUCER_COUNT];

    /* Producer starten */
    ret = pthread_create(&consumer_id, NULL, consumer_main, NULL);
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Erstellung des Consumers fehlgeschlagen %s\n", strerror(ret));
        return 1;
    }

    /* Producer starten */
    for (int i=0;i<PRODUCER_COUNT; i++) {
        producer_index[i] = i;
        ret = pthread_create(&producer_id[i], NULL, producer_main, &producer_index[i]);
        if (ret != 0) {
            /* Bei Fehler Fehlermeldung ausgeben */
            printf("Erstellung des Producers %d fehlgeschlagen %s\n", i, strerror(ret));
            return 1;
        }
    }

    /* Auf Beendigung der Producer warten */
    for (int i=0;i<PRODUCER_COUNT; i++) {
        ret = pthread_join(producer_id[i], NULL);
        if (ret != 0) {
            /* Bei Fehler Fehlermeldung ausgeben */
            printf("Warten auf Producer %d fehlgeschlagen %s\n", i, strerror(ret));
            return 1;
        }
    }

    return 0;
}

void *producer_main(void *param) {
    int producer_id = *(int*)param;
    while (1) {
        /* Nächsten Wert berechnen */
        pthread_mutex_lock(&counter_mutex);
        int current_value = total_count++;
        pthread_mutex_unlock(&counter_mutex);
        if (current_value >= PRODUCED_ITEMS)
            break;
        printf("Producer %d erzeugt Wert %d\n", producer_id, current_value);

        /* Auf freien Platz im Puffer warten */
        while (buffer_level >= BUFFER_SIZE) {
        }
        /* Neuen Wert in den Puffer eintragen */
        buffer[write_index] = current_value;
        /* Puffer-Füllstand aktualisieren */
        buffer_level++;
        /* Schreibzeiger aktualisieren */
        write_index++;
        /* Am Puffer-Ende angekommen? => An den Anfang springen */
        if (write_index == BUFFER_SIZE) {
            write_index = 0;
        }
    }

    return NULL;
}

void *consumer_main(void *param) {
    int current_value;
    while (1) {
        /* Auf Eintrag im Puffer warten */
        while (buffer_level == 0) {
        }
        /* Wert aus Puffer auslesen */
        current_value = buffer[read_index];
        /* Puffer-Füllstand aktualisieren */
        buffer_level--;
        /* Lesezeiger aktualisieren */
        read_index++;
        /* Am Puffer-Ende angekommen? => An den Anfang springen */
        if (read_index == BUFFER_SIZE) {
            read_index = 0;
        }
        /* Ergebnis ausgeben */
        printf("Consumer erhält Wert %d\n", current_value);
    }
}