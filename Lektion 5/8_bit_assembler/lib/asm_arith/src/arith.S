.text

.global add16
/* Eingabe:
 *    a in r25:r24
 *    b in r23:r22
 * Ausgabewert in r25:r24
 */
add16:
    add r24, r22 ; Niederwertige Bytes addieren (r24 + r22)
    adc r25, r23 ; Höherwertige Bytes mit Übertrag addieren (r25 + r23 + Carry)
    ret

.global shl16
/* Eingabe: a in r25:r24
 * Ausgabewert in r25:r24
 */
shl16:
    lsl r24 ; Shift nach links, oberstes Bit wird im Carry gespeichert
    rol r25 ; Carry-Bit wird hinten eingefügt dadurch
    ret

.global mult8_8
/* Eingabe:
 *    a in r24
 *    b in r22
 * Ausgabewert in r25:r24
 */
 mult8_8:
    ; sichern von r0:r1 im Stack
    push r0 
    push r1

    ; Multiplikation von r22 und r24, Ergebnis in r0:r1
    muls r24, r22
    movw r24, r0

    ; Wiederherstellen von r0:r1
    pop r1
    pop r0

    ret

.global multu8_16
/* Eingabe:
 *    a in r24
 *    b in r23:r22
 * Ausgabewert in r25:r22
 */
multu8_16:
    ; Register sichern
    push r16
    push r17
    
    ; Parameter kopieren
    mov r16, r24       ; a (8-Bit) nach r16
    movw r18, r22      ; b (16-Bit) nach r19:r18 (bh:bl)
    
    ; Teil 1: a * bl (niederwertiger Teil)
    mul r16, r18       ; r1:r0 = a * bl
    movw r22, r0       ; untere 16 Bits nach r23:r22
    
    ; Teil 2: a * bh (höherwertiger Teil)
    mul r16, r19       ; r1:r0 = a * bh
    
    ; Mittlere 8 Bits (für 24-Bit Ergebnis)
    add r23, r0        ; Addiere nur das niedrige Byte von a*bh
    eor r24, r24            ; r24 = 0
    adc r24, r1        ; Nur den Carry berücksichtigen
    
    ; Oberes Byte (r25) auf 0 setzen
    eor r25, r25
    
    ; r1 zurücksetzen auf 0 (0er Register)
    eor r1, r1
    
    ; Register wiederherstellen
    pop r17
    pop r16
    ret

.global multu16_16
/* Eingabe:
 *    a in r25:r24
 *    b in r23:r22
 * Ausgabewert in r25:r22
 */
multu16_16:
.global multu16_16
multu_16_16:
    ; Sichere Parameter in Hilfsregister
    movw r20, r24  ; a_l in r20, a_h in r21
    movw r18, r22  ; b_l in r18, b_h in r19
    
    ; 1. Berechne a_l * b_l (r20 * r18)
    mul r20, r18    ; Ergebnis in r1:r0
    movw r22, r0    ; Niedrigstes Wort des Ergebnisses in r23:r22
    
    ; 2. Berechne a_h * b_h (r21 * r19)
    mul r21, r19    ; Ergebnis in r1:r0
    movw r24, r0    ; Höchstes Wort des Ergebnisses in r25:r24
    
    ; 3. Berechne a_l * b_h (r20 * r19)
    mul r20, r19    ; Ergebnis in r1:r0
    ; Addiere zum mittleren Teil (16-Bit Addition zu 24-Bit Wert)
    add r23, r0     ; Addiere Low-Byte zu r23
    adc r24, r1     ; Addiere High-Byte mit Carry zu r24
    eor r0, r0          ; Clear für nächsten Carry
    adc r25, r0     ; Addiere Carry zu r25 (mit 0, da r1 nicht mehr sicher ist)
    
    ; 4. Berechne a_h * b_l (r21 * r18)
    mul r21, r18    ; Ergebnis in r1:r0
    ; Addiere zum mittleren Teil (16-Bit Addition zu 24-Bit Wert)
    add r23, r0     ; Addiere Low-Byte zu r23
    adc r24, r1     ; Addiere High-Byte mit Carry zu r24
    eor r0, r0          ; Clear für nächsten Carry
    adc r25, r0     ; Addiere Carry zu r25 (mit 0, da r1 nicht mehr sicher ist)
    
    ; Aufräumen
    eor r1, r1          ; MUL-Operationen setzen r1, muss zurückgesetzt werden
    ret
