#include "moar.h"
#include "smallbigintsupport.h"

/* Magnitude to compare against if we want to turn a bigint into a smallbigint. */
static mp_int mag_32bit_limit;

/* Forces a bigint to actually be a bigint, rather than a smallbigint. */
inline void force_bigint(void *data) {
    mp_int *i = &((MVMP6bigintBody *)data)->i;
    if (IS_SBI(data)) {
        printf("making a big integer in force_bigint: %d\n", VALUE_SBI(data));
        MVMint64 value = VALUE_SBI(data);
        mp_init(i);
        mp_zero(i);
        if (value >= 0) {
            mp_set_long(i, value);
        } else {
            mp_set_long(i, -value);
            mp_neg(i, i);
        }
    } else {
        printf("forcing a bigint into a bigint.\n");
    }
}

/* Turns a bigint into a smallbigint (without checking!) */
inline void force_smallbigint(void *data) {
    mp_int *i = &((MVMP6bigintBody *)data)->i;
    MVMint64 value;

    if (!IS_SBI(data)) {
        if (MP_LT == mp_cmp_d(i, 0)) {
            mp_neg(i, i);
        }
        value = mp_get_long(i);
        printf("making a smallbigint in make_smallbigint: %d\n", value);
        mp_clear(i);
        MAKE_SBI(data);
        STORE_SBI(data, value);
    }
}
inline int check_can_be_small(void *data) {
    MVMP6bigintBody *body = &((MVMP6bigint *)data)->body;
    return mp_cmp_mag(&body->i, &mag_32bit_limit) == MP_LT;
}

inline int make_compatible(void *a, void *b) {
    if (!!IS_SBI(a) == !!IS_SBI(b)) {
        return IS_SBI(a);
    } else {
        force_bigint(a);
        force_bigint(b);
        return 0;
    }
}

void setup_smallbigint() {
    mp_init(&mag_32bit_limit);
    mp_set_int(&mag_32bit_limit, 0x7fffffff);
}
