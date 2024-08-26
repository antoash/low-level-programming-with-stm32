#include "delay.h"

void delay(int val) {
    int i;
    for (;val>0;val--) {
        for(i=0;i<10000;i++);
    }
}