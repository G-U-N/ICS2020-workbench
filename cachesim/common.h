#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#define MEM_SIZE (1 << 25) // 1MB
#define BLOCK_WIDTH  6  // 64B
#define BLOCK_SIZE exp2(BLOCK_WIDTH) //64B

typedef uint8_t bool;
#define true 1
#define false 0

void cycle_increase(int n);

// typedef struct 
// {
//     uint8_t data[BLOCK_SIZE];
//     uint32_t tag;
//     bool valid;
//     // bool dirty;
// }Cache;

// #define MAX_GROUP_NUM 64
// #define MAX_LINE_NUM 4
#endif

