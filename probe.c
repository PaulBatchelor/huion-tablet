#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "huion.h"

int main() 
{
    float data[P_MAX];
    memset(data, 0, sizeof(float) * P_MAX);
    FILE *fp = fopen("/dev/input/by-id/usb-HUION_PenTablet-event-mouse", "rb");
    unsigned char msg[24];
    while(1) {
        huion_read(fp, msg, data);
        printf("x:%g\ty:%g\tz:%g\t\n", data[P_X], data[P_Y], data[P_Z]);
        usleep(100);
    }
}
