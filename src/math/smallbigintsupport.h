#define MAKE_SBI(a) ((((MVMP6smallbigintBody *)a)->flag) = 1)
#define IS_SBI(a) ((long)(((MVMP6smallbigintBody *)a)->flag) == 1)
#define STORE_SBI(a, value) (((MVMP6smallbigintBody *)a)->storage = value)
#define VALUE_SBI(a) (((MVMP6smallbigintBody *)a)->storage)

inline MVMP6bigint *obtain_bigint(MVMObject *data);
inline MVMP6bigint *force_smallbigint(MVMObject *data);
inline int check_can_be_small(MVMP6bigint *data);
inline int make_compatible(void *a, void *b);

void setup_smallbigint();
