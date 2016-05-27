#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>

#define TYPE 16
#define SUBTYPE 18
#define MSB 21
#define LSB 20
#define X_AXIS 0
#define Y_AXIS 1
#define PRESSURE 0x18 
#define CONTACT 0x4a

/* 
 * To compile (on linux):
 * gcc -fPIC -shared huion.c -o huion.so -lsporth -lsoundpipe -lpthread
 *
 */

enum {
    P_X,
    P_Y,
    P_Z,
    P_CONTACT
};

typedef struct {
    void (*func)(int type, int ctl, int val, void *);
    int run;
    pthread_t thread;
    void *ud;
    sp_ftbl *data;
} huion_d;



static void *listen(void *ud) 
{
    huion_d *hd = ud;

    float *data = hd->data->tbl;
    FILE *fp = fopen("/dev/input/by-id/usb-HUION_PenTablet-event-mouse", "rb");
    unsigned char msg[24];
    if(fp == NULL) {
        printf("There was a problem reading the F310 controller. Exiting gracefully...\n");
        return NULL;
    }
    while(hd->run) {
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
                case CONTACT:
                    data[P_CONTACT] = (float)msg[LSB];
                    break;
                default:
                    break;
            }

        }
        usleep(100);
    }

    fprintf(stderr, "Stopping Huion tablet...\n");
    fclose(fp);
    pthread_exit(NULL);
}

int huion_start(huion_d *hd)
{
    fprintf(stderr, "Starting Huion tablet...\n");
    hd->run = 1;
    pthread_create(&hd->thread, NULL, listen, hd);
    return 0;
}
int huion_stop(huion_d *hd)
{
    hd->run = 0;
    sleep(1);
    return 0;
}

/*
int main() 
{
    static huion_d hd;
    huion_start(&hd);
    sleep(10);
    huion_stop(&hd);
    return 0;
}
*/

static int sporth_huion(plumber_data *pd, sporth_stack *stack, void **ud)
{
    huion_d *hd;
    char *str;
    switch(pd->mode) {
        case PLUMBER_CREATE:
            fprintf(stderr, "Creating our custom gain plugin!\n");
            if(sporth_check_args(stack, "s") != SPORTH_OK) {
                fprintf(stderr,"Incorrect arguments for huion\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            /* malloc and assign address to user data */
            str = sporth_stack_pop_string(stack);
            hd = malloc(sizeof(huion_d));
            *ud = hd;
            sp_ftbl_create(pd->sp, &hd->data, 4);
            plumber_ftmap_add(pd, str, hd->data);
            free(str);
            huion_start(hd);
            break;
        case PLUMBER_INIT:
            str = sporth_stack_pop_string(stack);
            free(str);
            break;

        case PLUMBER_COMPUTE:
            break;

        case PLUMBER_DESTROY:
            hd = *ud;
            huion_stop(hd);
            free(hd);
            break;
        default:
            fprintf(stderr, "Huion: unknown mode %d\n", pd->mode);
            break;
    }
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_huion;
}
