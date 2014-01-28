#include "moar.h"
#include "smallbigintsupport.h"

/* Magnitude to compare against if we want to turn a bigint into a smallbigint. */
static mp_int mag_32bit_limit;

/* Forces a bigint to actually be a bigint, rather than a smallbigint. */
inline mp_int *obtain_bigint(MVMObject *data) {
    return obtain_bigint_body(&((MVMP6bigint *)data)->body);
}

inline mp_int *obtain_bigint_body(MVMP6bigintBody *body) {
    mp_int *i = &body->i;
    if (IS_SBI(body)) {
        printf("making a big integer in obtain_bigint: %d\n", VALUE_SBI(body));
        MVMint64 value = VALUE_SBI(body);
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
    return i;
}

/* Turns a bigint into a smallbigint (without checking!) */
inline MVMP6bigint *force_smallbigint(MVMObject *data) {
    MVMP6bigintBody *body = &((MVMP6bigint*)data)->body;
    mp_int *i = &body->i;
    MVMint64 value;

    if (!IS_SBI(body)) {
        if (MP_LT == mp_cmp_d(i, 0)) {
            mp_neg(i, i);
        }
        value = mp_get_long(i);
        printf("making a smallbigint in make_smallbigint: %d\n", value);
        mp_clear(i);
        MAKE_SBI(body);
        STORE_SBI(body, value);
    }
}
inline int check_can_be_small(MVMP6bigint *data) {
    MVMP6bigintBody *body = &((MVMP6bigint *)data)->body;
    return mp_cmp_mag(&body->i, &mag_32bit_limit) == MP_LT;
}

/* inline int make_compatible(MVMObject **a, MVMObject **b) {
    if (!!IS_SBI(a) == !!IS_SBI(b)) {
        return IS_SBI(a);
    } else {
        force_bigint(a);
        force_bigint(b);
        return 0;
    }
} */

void setup_smallbigint() {
    mp_init(&mag_32bit_limit);
    mp_set_int(&mag_32bit_limit, 0x7fffffff);
}
