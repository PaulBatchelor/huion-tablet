#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "huion.h"


void huion_read(FILE *fp, unsigned char *msg, float *d)
{
        fread(msg, sizeof(char), 24, fp);
        if(msg[TYPE] == 3) {
            switch(msg[SUBTYPE]) {
                case X_AXIS:
                    d[P_X] = (float)((msg[MSB] << 8) + msg[LSB]) / X_MAX;
                    break;
                case Y_AXIS:
                    d[P_Y] = (float)((msg[MSB] << 8) + msg[LSB]) / Y_MAX;
                    break;
                case PRESSURE:
                    d[P_Z] = (float)((msg[MSB] << 8) + msg[LSB]) / 0x7ff;
                    break;
                default:
                    break;
            }
        } else if(msg[TYPE] == 1) {
            switch(msg[SUBTYPE]) {
                case CONTACT:
                    d[P_CONTACT] = (float)msg[LSB];
                    break;
                case TOP_BUTTON:
                    d[P_TOP_BUTTON] = (float)msg[LSB];
                    break;
                default:
                    break;
            }

        }
}
