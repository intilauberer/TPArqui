#include "include/UserSyscalls.h"
 
 void goal(){
    call_beep(261, 200); 
    call_sleepms(50);
    call_beep(294, 125);
    call_beep(392, 325);
 }
 
 void bounce(){
     call_beep(100, 1); 
 }
 
 void bokee(){
    int n = 200; // Duración de cada nota (ajustable según preferencias)

    // Primer verso
    call_beep(262, n); // C
    call_beep(294, n); // D
    call_beep(330, n); // E
    for (int i = 0; i < 8; i++)
        call_beep(349, n); // F
    call_beep(330, n);     // E
    call_beep(294, n);     // D
    call_beep(349, n);     // F
    call_beep(294, 2 * n); // D

    // Segundo verso
    call_beep(262, n); // C
    call_beep(294, n); // D
    call_beep(330, n); // E
    for (int i = 0; i < 8; i++)
        call_beep(349, n); // F
    call_beep(330, n);     // E
    call_beep(294, n);     // D
    call_beep(349, n);     // F
    call_beep(392, 2 * n); // G

    // Tercer verso
    call_beep(262, n); // C
    call_beep(294, n); // D
    call_beep(330, n); // E
    for (int i = 0; i < 8; i++)
        call_beep(392, n); // G
    call_beep(349, n);     // F
    call_beep(330, n);     // E
    call_beep(392, n);     // G
    call_beep(330, 2 * n); // E

    // Cuarto verso
    call_beep(262, n); // C
    call_beep(294, n); // D
    call_beep(330, n); // E
    for (int i = 0; i < 4; i++)
        call_beep(349, n); // F
    for (int i = 0; i < 3; i++)
        call_beep(330, n); // E
    call_beep(349, n);     // F
    call_beep(330, n);     // E
    for (int i = 0; i < 3; i++)
        call_beep(294,2*n); // D
}