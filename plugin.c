#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>

#include "huion.h"
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
        huion_read(fp, msg, data);
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
            sp_ftbl_create(pd->sp, &hd->data, P_MAX);
            plumber_ftmap_add(pd, str, hd->data);
            huion_start(hd);
            break;
        case PLUMBER_INIT:
            str = sporth_stack_pop_string(stack);
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
