#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biggie.h"

struct biggie {
  bool negative;
  char *digits;
};

static char *remove_0(char *digits) {
  assert(digits);
  int count = 0;
  int d_len = strlen(digits);
  for (int i = d_len - 1; i > 0; --i) {
    if (digits[i] == '0') {
      ++count;
      continue;
    } 
    break;
  }
  int temp = count;
  int my_len = d_len;
  for (int i = my_len - 1; temp > 0; --i) {
    digits[i] = 0;
    --temp;
  }
  digits = realloc(digits, (my_len - count + 1) * sizeof(char));
  return digits;
}


static void substarct(struct biggie *n, const struct biggie *m, int BIGGER) {
  assert(n);
  assert(m);
  int n_len = strlen(n->digits);
  int m_len = strlen(m->digits);
  int len = 0;
  if (n_len < m_len) {
    len = m_len;
  } else {
    len = n_len;
  }
  n->digits = realloc(n->digits, (len + 1) * sizeof(char));
  int digit = 0;
  int extra = 0;
  if (BIGGER == 1) {
    for (int i = 0; i < len; ++i) {
      if (i >= m_len) {
        digit = n->digits[i] - '0';
      } else {
        digit = n->digits[i] - m->digits[i];
      }
      digit += extra;
      if (digit < 0) {
        extra = -1;
        digit += 10;
      } else {
        extra = 0;
      }
      digit += '0';
      n->digits[i] = digit;
    }
  } else if (BIGGER == 0) {
    for (int i = 0; i < len; ++i) {
      if (i >= n_len) {
        digit = m->digits[i] - '0';
      } else {
        digit = m->digits[i] - n->digits[i];
      }
      digit += extra;
      if (digit < 0) {
        extra = -1;
        digit += 10;
      } else {
        extra = 0;
      }
      digit += '0';
      n->digits[i] = digit;
    }
  }
  n->digits[len] = 0;
  n->digits = remove_0(n->digits);
}


struct biggie *biggie_create(const char *s) {
  assert(s);
  struct biggie *my_big = malloc(sizeof(struct biggie));
  if (strlen(s) == 0) {
    free(my_big);
    return NULL;
  } else if (s[0] == '-') {
    if ((s[1] == '0') || (strlen(s) == 1)){
      free(my_big);
      return NULL;
    } else {
      my_big->negative = true;
    }
  } else if ((strlen(s) > 1) && (s[0] == '0')) {
    free(my_big);
    return NULL;
  } else {
    my_big->negative = false;
  }
  int len = strlen(s);
  if (my_big->negative == true) {
    int temp = len - 2;
    my_big->digits = malloc(len * sizeof(char));
    for (int i = 1; i < len; ++i) {
      if ((s[i] >= '0') && (s[i] <= '9')) {
        my_big->digits[temp] = s[i];
        --temp;
        continue;
      } 
      biggie_destroy(my_big);
      return NULL;
    }
    --len;
  } else {
    my_big->digits = malloc((len + 1) * sizeof(char));
    int temp = len - 1;
    for (int i = 0; i < len; ++i) {
      if ((s[i] >= '0') && (s[i] <= '9')) {
        my_big->digits[temp] = s[i];
        --temp;
        continue;
      } 
      biggie_destroy(my_big);
      return NULL;
    }
  }
  my_big->digits[len] = 0;
  return my_big;
}



void biggie_destroy(struct biggie *big) {
  assert(big);
  free(big->digits);
  free(big);
}

void biggie_print(const struct biggie *big, bool newline) {
  assert(big);
  if (big->negative) {
    printf("-");
  }
  for (int i = strlen(big->digits) - 1; i >= 0; --i) {
    printf("%c", big->digits[i]);
  }
  if (newline) {
    printf("\n");
  }      
}

void biggie_add(struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  if (n->negative == m->negative) {
    int n_len = strlen(n->digits);
    int m_len = strlen(m->digits);
    int len = 0;
    if (n_len < m_len) {
      len = m_len;
    } else {
      len = n_len;
    }
    n->digits = realloc(n->digits, (len + 1) * sizeof(char));
    int my_digit = 0;
    int exceed = 0;
    for (int i = 0; i < len; ++i) {
      my_digit = 0;
      if (i >= n_len) {
        my_digit = m->digits[i] - '0';
      } else if (i >= m_len) {
        my_digit = n->digits[i] - '0';
      } else {
        my_digit = n->digits[i] - '0' + m->digits[i] - '0';
      }
      my_digit += exceed;
      if (my_digit >= 10) {
        exceed = 1;
        my_digit -= 10;
      } else {
        exceed = 0;
      }
      my_digit += '0';
      n->digits[i] = my_digit;
    }
    if (exceed > 0) {
      n->digits = realloc(n->digits, (len + 2) * sizeof(char));
      n->digits[len] = exceed + '0';
      n->digits[len + 1] = 0;
    } else {
      n->digits[len] = 0;
    }
  } else {
    if (n->negative) {
      n->negative = false;
    } else {
      n->negative = true;
    }
    biggie_sub(n, m);
    if (n->negative) {
      n->negative = false;
    } else {
      n->negative = true;
    }
  }
  if (strcmp(n->digits, "0") == 0) {
    n->negative = false;
  }
}

void biggie_sub(struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  int n_len = strlen(n->digits);
  int m_len = strlen(m->digits);
  int FLAG = 0;
  int BIGGER = 0;
  if (n_len != m_len) {
    if (n_len > m_len) {
      BIGGER = 1;
      FLAG = 1;
    } else {
      BIGGER = 0;
      FLAG = 1;
    }
  } else {
    for (int i = n_len - 1; i >= 0; --i) {
      if (n->digits[i] > m->digits[i]) {
        BIGGER = 1;
        FLAG = 1;
        break;
      } else if (n->digits[i] < m->digits[i]){
        BIGGER = 0;
        FLAG = 1;
        break;
      }
    }
  }
  if (FLAG == 0) {
    BIGGER = 0;
  }
  if (n->negative != m->negative) {
    if (n->negative) {
      n->negative = false;
    } else {
      n->negative = true;
    }
    biggie_add(n, m);
    if (n->negative) {
      n->negative = false;
    } else {
      n->negative = true;
    }
  } else if (n->negative == m->negative) {
    struct biggie *copy = biggie_copy(n);
    substarct(n, m, BIGGER);
    if ((copy->negative == true) && (BIGGER == 0)) {
      n->negative = false;
    } else if ((copy->negative == false) && (BIGGER == 0)){
      n->negative = true;
    }
    biggie_destroy(copy);
  }
  if (strcmp(n->digits, "0") == 0) {
    n->negative = false;
  }
}

void biggie_mult(struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  int m_len = strlen(m->digits);
  int NEG = 0;
  if (n->negative == m->negative) {
    NEG = 0;
  } else {
    NEG = 1;
  }
  struct biggie *copy_n = biggie_copy(n);
  copy_n->negative = false;
  struct biggie *copy_m = biggie_copy(m);
  copy_m->negative = false;
  struct biggie *s = biggie_copy(n);
  s->negative = false;
  s->digits = realloc(s->digits, 2 * sizeof(char));
  s->digits[0] = '0';
  s->digits[1] = 0;
  for (int i = 0; i < m_len; ++i) {
    struct biggie *timed = biggie_copy(copy_n);
    timed->negative = false;
    timed->digits = realloc(timed->digits, 2 * sizeof(char));
    timed->digits[0] = '0';
    timed->digits[1] = 0;
    for (int count = copy_m->digits[i] - '0'; count > 0; --count) {
      biggie_add(timed, copy_n);
    }
    char* copy = malloc((strlen(timed->digits) + 1) 
                        * sizeof(char));
    strcpy(copy, timed->digits);
    timed->digits = realloc(timed->digits, 
                            (strlen(timed->digits) + i + 1) *
                            sizeof(char));
    for (int j = 0; j < i; ++j) {
      timed->digits[j] = '0';
    } 
    strcpy(timed->digits + i, copy);
    biggie_add(s, timed);
    free(copy);
    biggie_destroy(timed);
  }
  biggie_destroy(copy_n);
  biggie_destroy(copy_m);
  n->negative = NEG;
  int sum_len = strlen(s->digits);
  n->digits = realloc(n->digits, (sum_len + 1)
                      * sizeof(char));
  strcpy(n->digits, s->digits);
  biggie_destroy(s);
  n->digits = remove_0(n->digits);
  if (strcmp(n->digits, "0") == 0) {
    n->negative = false;
  }
}



bool biggie_eq(const struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  if (n->negative != m->negative) {
    return false;
  }
  struct biggie *my_equal = biggie_copy(n);
  if (my_equal->negative) {
    my_equal->negative = false;
  } else {
    my_equal->negative = true;
  }
  biggie_add(my_equal, m);
  if ((strlen(my_equal->digits) == 1) && (my_equal->digits[0] == '0')) {
    biggie_destroy(my_equal);
    return true;
  } else {
    biggie_destroy(my_equal);
    return false;
  }
  biggie_destroy(my_equal);
  return false;
}

bool biggie_gt(const struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  if (n->negative == m->negative) {
    struct biggie *my_copy = biggie_copy(n);
    biggie_sub(my_copy, m);
    if (my_copy->negative == false) {
      if (strlen(my_copy->digits) > 1) {
        biggie_destroy(my_copy);
        return true;
      } else if (strlen(my_copy->digits) == 1) {
        if (my_copy->digits[0] == '0') {
          biggie_destroy(my_copy);
          return false;
        } else {
          biggie_destroy(my_copy);
          return true;
        }
      }
    } else if (my_copy->negative == true){
      biggie_destroy(my_copy);
      return false;
    }
  } else {
    if (n->negative == true) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

struct biggie *biggie_copy(const struct biggie *n) {
  assert(n);
  struct biggie *new = malloc(sizeof(struct biggie));
  new->digits = malloc((strlen(n->digits) + 1) * sizeof(char));
  strcpy(new->digits, n->digits);
  new->negative = n->negative;
  return new;
}

/////////////////////////////////////////////////////////////////////////////
// BONUS:
/////////////////////////////////////////////////////////////////////////////
void biggie_div(struct biggie *n, const struct biggie *m) {
  assert(n);
  assert(m);
  struct biggie *assert = biggie_copy(n);
  assert->digits = realloc(assert->digits, 2 * sizeof(char));
  assert->digits[0] = '0';
  assert->digits[1] = 0;
  assert->negative = false;
  assert(biggie_eq(assert, m) == false);
  struct biggie *m_copy = biggie_copy(m);
  struct biggie *n_copy = biggie_copy(n);
  m_copy->negative = false;
  n_copy->negative = false;
  struct biggie *div = biggie_copy(n);
  div->digits = realloc(div->digits, 2 * sizeof(char));
  div->digits[0] = '0';
  div->digits[1] = 0;
  div->negative = false;
  char result = '0';
  int len1 = strlen(n_copy->digits);
  for (int i = len1 - 1; i >= 0; --i) {
    result = '0';
    if (strcmp(div->digits, "0") != 0) {
    char *copy = malloc((strlen(div->digits) + 1) 
                              * sizeof(char));
    strcpy(copy, div->digits);
    div->digits = realloc(div->digits, 
                          (strlen(div->digits) + 2) 
                          * sizeof(char));
    strcpy(div->digits + 1, copy);
    free(copy);
    }
    div->digits[0] = n_copy->digits[i];
    while (biggie_gt(div, m_copy) || biggie_eq(div, m_copy)) {
      biggie_sub(div, m_copy);
      ++result;
    }
    n->digits[i] = result;
  }
  biggie_destroy(assert);
  biggie_destroy(div);
  biggie_destroy(n_copy);
  biggie_destroy(m_copy);
  if (n->negative == m->negative) {
    n->negative = false;
  } else {
    n->negative = true;
  }
  n->digits = remove_0(n->digits);
  if (strcmp(n->digits, "0") == 0) {
    n->negative = false;
  }
}
