#include "tommath.h"

struct MVMP6smallbigintBody {
    int pad1, pad2;
#if !defined(_M_X64) && !defined(__amd64__)
    MVMuint32 pad3;
#endif
    MVMint32 storage;
    long flag; // this flag has to be 1, so not a valid pointer!
};

/* Representation used by P6 Ints. */
struct MVMP6bigintBody {
    /* Big integer storage slot. */
    mp_int i;
};
struct MVMP6bigint {
    MVMObject common;
    union {
        MVMP6bigintBody body;
        /* Alternatively, we cheat if 32bit are enough */
        MVMP6smallbigintBody smallbig;
    };
};

/* Function for REPR setup. */
const MVMREPROps * MVMP6bigint_initialize(MVMThreadContext *tc);
