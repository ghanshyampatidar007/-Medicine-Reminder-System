#include "types.h"
void delay_us(u32 us){
for(us*=12;us>0;us--);
}
void delay_ms(u32 ms){
for(ms*=12000;ms>0;ms--);
}
void delay_s(u32 s){
for(s*=12000000;s>0;s--);
}
