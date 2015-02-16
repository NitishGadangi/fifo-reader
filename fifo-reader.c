/*
 * This test program tests communication channel for SUZI.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MSG_SZ       256
#define FIFO_PATH    "/tmp/fifo"

static void print_buf(char *buf, int size)
{
    int i;

    printf("====Input Data====\n");
    for(i=0; i<size; i++) {
        printf("%02X ", buf[i]);
        if(0 != i && 0 == ((i+1) % 4))
            printf("\n");
    }
    printf("\n");
}

int main( int argc, char *argv[])
{
    int fifo;
    int rd_cnt;
    char buf[MSG_SZ];
    char fifo_path[64];

    /* getting fifo_path */
    memset(fifo_path,0,sizeof(fifo_path));
    if ( 2 == argc ) {
        if (strlen(argv[1]) >= 64)
            return -1;
        memcpy(fifo_path, argv[1], strlen(argv[1]));
    } else {
        if (strlen(FIFO_PATH) >= 64)
            return -1;
        memcpy(fifo_path, FIFO_PATH, strlen(FIFO_PATH));
    }
    printf("fifo path: %s\n", fifo_path);

    if ((fifo = open(fifo_path, O_RDONLY)) < 0) {
        printf("Failed to open FIFO: %s\n", fifo_path);
        return 1;
    }

    while(1) {
        memset((void*)buf, 0, sizeof(buf));
        printf("Reader_thread: Reading FIFO: %s...\n", fifo_path);
        rd_cnt = read(fifo,(void*)buf,MSG_SZ);
        if(rd_cnt>0) {
            printf("Reader_thread: FIFO Contents:\n");
            print_buf(buf, rd_cnt);
        } else {
            printf("FIFO writer is gone, waiting...\n");
            sleep(5);
        }
    }
    return 0;
}
