#include <stdbool.h>

struct biggie;

struct biggie *biggie_create(const char *s);

void biggie_destroy(struct biggie *big);

void biggie_print(const struct biggie *big, bool newline);

void biggie_add(struct biggie *n, const struct biggie *m);

void biggie_sub(struct biggie *n, const struct biggie *m);

void biggie_mult(struct biggie *n, const struct biggie *m);

bool biggie_eq(const struct biggie *n, const struct biggie *m);

bool biggie_gt(const struct biggie *n, const struct biggie *m);

struct biggie *biggie_copy(const struct biggie *n);

void biggie_div(struct biggie *n, const struct biggie *m);
