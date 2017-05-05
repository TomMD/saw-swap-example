#include <stdint.h>

typedef uint8_t u8;
typedef int32_t s32;
typedef int64_t limb;

static void swap_conditional(limb a[19], limb b[19], limb iswap) {
  unsigned i;
  const s32 swap = -iswap;

  for (i = 0; i < 10; ++i) {
    const s32 x = swap & ( ((s32)a[i]) ^ ((s32)b[i]) );
    a[i] = ((s32)a[i]) ^ x;
    b[i] = ((s32)b[i]) ^ x;
  }
}

static void old_swap_conditional(limb a[19], limb b[19], limb iswap) {
  unsigned i;
  const limb swap = -iswap;

  for (i = 0; i < 10; ++i) {
    const limb x = swap & ( (a[i]) ^ (b[i]) );
    a[i] = (a[i]) ^ x;
    b[i] = (b[i]) ^ x;
  }
}


#define NR_A 5
limb test(limb a0[NR_A], limb b0[NR_A], limb iswap)
{
    limb a1[19]={0},b1[19]={0};
    limb a2[19]={0},b2[19]={0};
    limb bad=0;
    int i;
    iswap = iswap ? 1 : 0;
    for (i=0; i<NR_A; i++) {
        if(((limb)a0[i]) >= ((limb)INT32_MAX) || a0[i] < (limb)0) {
            a0[i] = 0;
        }
        if(((limb)b0[i]) >= ((limb)INT32_MAX) || b0[i] < (limb)0) {
            b0[i] = 0;
        }
    }

    for(i=0;i<19;i++) {
        a2[i] = a1[i] = i < NR_A ? a0[i] : 0;
        b1[i] = b2[i] = i < NR_A ? b0[i] : 0;
    }
    swap_conditional(a1,b1,iswap);
    old_swap_conditional(a2,b2,iswap);
    for(i=0; i<19; i++) {
        bad |= a1[i] != a2[i];
        bad |= b1[i] != b2[i];
    }
    return !bad;
}
