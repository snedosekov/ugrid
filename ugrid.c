
#include <stdio.h>

#ifndef uint8_t
#define uint8_t unsigned char
#endif

#ifndef uint16_t
#define uint16_t unsigned short int
#endif

#define g_lim 441
#define ug_lim 256

static uint16_t ug_idx_tab[] = {
0 , 26, 51, 77, 102, 128, 154, 179, 205, 230, 256, 282, 307, 333, 358, 379
};

static uint16_t g_idx_tab[] = {
    0, 2, 5, 10, 20, 51, 102, 146, 205, 256, 341, 441, 515, 635, 795, 992
};

static uint8_t g_idx_tab_size = 16;
static uint8_t ug_idx_tab_size = 16;

static uint16_t ucp_tab[16][16] = {
    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256},
    {256, 280, 283,	285, 287, 291, 293, 294, 295, 296, 297, 298, 298, 299, 300, 301},
    {256, 304, 315,	324, 332, 340, 342, 343, 344, 345, 346, 347, 348, 348, 349, 350},
    {256, 329, 344,	358, 371, 380, 383, 384, 386, 386, 389, 390, 390, 391, 392, 394},
    {256, 353, 373,	393, 404, 417, 419, 420, 422, 423, 425, 426, 426, 427, 429, 432},
    {256, 376, 401,	422, 439, 448, 450, 452, 453, 455, 456, 457, 458, 460, 463, 467},
    {256, 402, 434,	452, 467, 475, 477, 478, 480, 482, 484, 485, 487, 490, 493, 498},
    {256, 430, 461,	478, 492, 499, 502, 504, 505, 506, 508, 510, 512, 516, 521, 527},
    {256, 455, 485,	503, 513, 519, 523, 525, 526, 527, 530, 532, 535, 539, 545, 553},
    {256, 477, 506,	522, 532, 537, 541, 543, 544, 546, 548, 551, 553, 559, 566, 576},
    {256, 498, 526,	539, 549, 555, 558, 560, 561, 563, 566, 570, 573, 580, 587, 600},
    {256, 517, 542,	555, 563, 568, 572, 574, 576, 578, 581, 586, 589, 595, 607, 624},
    {256, 534, 557,	569, 577, 582, 586, 587, 589, 592, 595, 601, 605, 614, 626, 636},
    {256, 548, 570,	583, 589, 593, 596, 598, 600, 603, 608, 613, 623, 633, 640, 648},
    {256, 563, 584,	593, 599, 603, 606, 607, 610, 613, 618, 624, 640, 654, 656, 660},
    {256, 572, 591,	600, 606, 612, 615, 616, 620, 623, 628, 637, 670, 670, 670, 670}
};

static uint16_t ucpm_tab[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 600, 607, 614, 623, 631, 637
};

static inline uint8_t get_tab_idx(uint16_t tab[], uint16_t tab_size, uint16_t val){
    uint8_t idx = 0;
    for(; idx < tab_size; idx++)
        if(val < tab[idx])
            break;
    return idx;
}

uint16_t calc_ucp(uint16_t ug, uint16_t g){
    uint8_t g_idx, ug_idx;
    uint16_t kn, ucp, ucpm, ucp1, ucp2;
    
    g_idx = get_tab_idx(g_idx_tab, g_idx_tab_size, g);
    ug_idx = get_tab_idx(ug_idx_tab, ug_idx_tab_size, ug);
    
    //g_idx = (g_idx == 0) ? 1 : g_idx;
    //ug_idx = (ug_idx == 0) ? 1 : ug_idx;
    
    kn = (ug - ug_idx_tab[ug_idx - 1]) / (ug_idx_tab[ug_idx] - ug_idx_tab[ug_idx -1]);
    ucp1 = ucp_tab[g_idx - 1, ug_idx -1] + 
          (ucp_tab[g_idx - 1, ug_idx] - ucp_tab[g_idx - 1, ug_idx -1]) * kn;
    
    ucp2 = ucp_tab[g_idx, ug_idx -1] + 
          (ucp_tab[g_idx, ug_idx] - ucp_tab[g_idx, ug_idx -1]) * kn;
 
    ucp = ucp1 + (ucp2 - ucp1) * (g - g_idx_tab[g_idx - 1]) / (g_idx_tab[g_idx] - g_idx_tab[g_idx - 1]);

    if(g <= g_lim || ug <= ug_lim)
        return ucp;
    
    ucpm = ucpm_tab[g_idx - 1] + (ucpm_tab[g_idx ] - ucpm_tab[g_idx - 1]) * 
            (ug - ug_idx_tab[ug_idx - 1]) / (ug_idx_tab[ug_idx] - ug_idx_tab[ug_idx - 1]);
    if(ucp <= ucpm)
        ucp = ucpm;
    
    return ucp;
}