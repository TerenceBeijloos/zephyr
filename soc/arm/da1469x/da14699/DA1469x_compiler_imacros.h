#ifndef DA1469X_HELPER_DEFINES
#define DA1469X_HELPER_DEFINES

#define asm __asm__ //Either use __asm__ instead of asm with -std=c99, or use -std=gnu99

#ifndef RAND_MAX
    #define RAND_MAX 0x7fff //For some reason Zephyr cannot find this define in stdlib.h
#endif //RAND_MAX

#endif //DA1469X_HELPER_DEFINES
