/* Simple math macros.*/
#pragma once
#ifndef min
#define min(a,b) (a) < (b) ? (a) : (b) 
#endif

#ifndef max
#define max(a,b) (a) > (b) ? (a) : (b) 
#endif

#define map(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
