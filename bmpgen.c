/*******************************************************************************
Travis Grice
08/30/2020
bmpgen.c

This program is designed to take a given width and height and produce a blank
.bmp file (a blank image with the specified dimensions)

To run the program use the command bmpgen.exe [path][width][height] where path
contains the folder of the new .bmp file, and both width and height in pixels.

General form of execution:
    bmpgen.exe [path][width][height]

If no arguments are passed, then the defaults is equivalent to the following:
    bmpgen.exe ./ 640 480
    
In other words, it will create a .bmp file in the current directory relative to
the location where this program is run with a resolution of 640x480.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;

#define TYPE_BM      0x4D42
#define OFFSET       0x36
#define NUL          0x0
#define HEADSIZE     0x28
#define COLORPANES   0x1
#define BPP_24       0x18
#define PATH         argv[1]
#define WIDTH        atoi(argv[2])
#define HEIGHT       atoi(argv[3])
#define BYTESPP      0x3
#define NUL          0x0
#define WRITE_BIN    "wb+"
#define RSVD_0       NUL
#define RSVD_1       NUL
#define COMP_METH    NUL
#define HORIZ_RES    NUL
#define VERT_RES     NUL
#define PSIZE        NUL
#define IMP_COL      NUL
#define RESOLUTION   WIDTH * HEIGHT
#define IMG_SIZE     RESOLUTION * BYTESPP
#define FILE_SIZE    IMG_SIZE + OFFSET
   

/******************************************************************************* 
arg[1] = path to .bmp file
arg[2] = width in pixels
arg[3] = height in pixels
*******************************************************************************/
int main(int argc, char *argv[]) {
    byte buff3, buff4, buff5;
    word buff1;
    dword buff2;
    int i;
    
    // declare fields (See notes above for more detail)
    // FILE * fopen(const char *filename, const char *mode)
    FILE * file = fopen(PATH, WRITE_BIN);
    if (!file) return -2;

    
    // size_t fwrite (const void *ptr, size_t sie, size_t nmemb, FILE *stream)
    buff1 = TYPE_BM;              fwrite(&buff1, sizeof(word) , 1, file);
    buff2 = FILE_SIZE;            fwrite(&buff2, sizeof(dword), 1, file);
    buff1 = RSVD_0;               fwrite(&buff1, sizeof(word) , 1, file);
    buff1 = RSVD_1;               fwrite(&buff1, sizeof(word) , 1, file);
    buff2 = OFFSET;               fwrite(&buff2, sizeof(dword), 1, file); 
    buff2 = HEADSIZE;             fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = WIDTH;                fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = HEIGHT;               fwrite(&buff2, sizeof(dword), 1, file);
    buff1 = COLORPANES;           fwrite(&buff1, sizeof(word) , 1, file);
    buff1 = BPP_24;               fwrite(&buff1, sizeof(word) , 1, file);
    buff2 = COMP_METH;            fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = IMG_SIZE;             fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = HORIZ_RES;            fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = VERT_RES;             fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = PSIZE;                fwrite(&buff2, sizeof(dword), 1, file);
    buff2 = IMP_COL;              fwrite(&buff2, sizeof(dword), 1, file);
    
    buff5 = 0xFF;
    buff3 = buff4 = 0;
    for(i = 0; i < RESOLUTION; i++) {
        fwrite(&buff3, sizeof(byte), 1, file);
        fwrite(&buff4, sizeof(byte), 1, file);
        fwrite(&buff5, sizeof(byte), 1, file);
    }
    
    
    fclose(file);
    
    return 0;
}