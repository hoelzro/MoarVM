#define MAKE_SBI(a) ((((MVMP6bigintBody *)a)->i.dp) = 1)
#define IS_SBI(a) ((((MVMP6bigintBody *)a)->i.dp) == 1)
#define STORE_SBI(a, value) (((MVMP6bigintBody *)a)->i.sign = value)
#define VALUE_SBI(a) (((MVMP6littlebigintBody *)a)->i.sign)

#define OBTAIN_BIN(a, name) mp_int *name = obtain_bigint(a);
#define OBTAIN_BI(a) OBTAIN_BIN(a, i##a)
#define CLEANUP_BIN(a, name) if (name != &((MVMP6bigint *)a)->body.i) { printf("had to cleanup a bigint\n"); mp_clear(name); }
#define CLEANUP_BI(a) CLEANUP_BIN(a, i##a)

inline mp_int *obtain_bigint(MVMObject *data);
inline mp_int *obtain_bigint_body(MVMP6bigintBody *body);
inline MVMP6bigint *force_littlebigint(MVMObject *data);
inline int check_can_be_little(MVMP6bigint *data);
// inline int make_compatible(void *a, void *b);

void setup_littlebigint();
