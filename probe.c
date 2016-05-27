#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TYPE 16
#define SUBTYPE 18
#define MSB 21
#define LSB 20
#define X_AXIS 0
#define Y_AXIS 1
#define PRESSURE 0x18 

#define IS_TOUCHING

enum {
    P_X,
    P_Y,
    P_Z
};

float data[3];


int main() 
{
    memset(data, 0, sizeof(float) * 3);
    FILE *fp = fopen("/dev/input/by-id/usb-HUION_PenTablet-event-mouse", "rb");
    unsigned char msg[24];
    while(1) {
        fread(msg, sizeof(char), 24, fp);
        if(msg[TYPE] == 3) {
            switch(msg[SUBTYPE]) {
                case X_AXIS:
                    data[P_X] = (float)((msg[MSB] << 8) + msg[LSB]) / 0x7d00;
                    break;
                case Y_AXIS:
                    data[P_Y] = (float)((msg[MSB] << 8) + msg[LSB]) / 0x5dc0;
                    break;
                case PRESSURE:
                    data[P_Z] = (float)((msg[MSB] << 8) + msg[LSB]) / 0x7ff;
                    break;
                default:
                    break;
            }
        } else if(msg[TYPE] == 1) {
            switch(msg[SUBTYPE]) {
                case 0x4a
                default:
                    break;
            }
        }
        //printf("%g %g\n", msg[TYPE], (msg[MSB] << 8) +  msg[LSB]);
        printf("x:%g\ty:%g\tz:%g\t\n", data[P_X], data[P_Y], data[P_Z]);
        usleep(100);
    }
}
