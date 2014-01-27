#include "tommath.h"

struct MVMP6smallbigintBody {
    int pad1, pad2;
#if !defined(_M_X64) && !defined(__amd64__)
    MVMuint32 pad3;
#endif
    MVMint32 storage;
    mp_digit *flag; // this flag has to be 1, so not a valid pointer!
};

#define p6smallbigintflag ((mp_digit*)1)

/* Representation used by P6 Ints. */
struct MVMP6bigintBody {
    union {
        /* Big integer storage slot. */
        mp_int i;
        /* Alternatively, we cheat if 32bit are enough */
        MVMP6smallbigintBody smallbig;
    };
};
struct MVMP6bigint {
    MVMObject common;
    MVMP6bigintBody body;
};

/* Function for REPR setup. */
const MVMREPROps * MVMP6bigint_initialize(MVMThreadContext *tc);
