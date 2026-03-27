# Valgrind Analysis

## 1. heap_example.c

### Error 1
- **Type:** Memory Leak (definitely lost)
- **Object:** alice->name
- **Line:** 21 (malloc in person_new)
- **Cause:** person_free_partial only frees the Person struct, not the name field which is a separate heap allocation
- **Valgrind output:**
```
==11599== 6 bytes in 1 blocks are definitely lost in loss record 1 of 1
==11599==    at 0x4846828: malloc (vg_replace_malloc.c)
==11599==    by 0x109211: person_new (heap_example.c:21)
==11599==    by 0x1092FA: main (heap_example.c:51)
```

---

## 2. aliasing_example.c

### Error 1
- **Type:** use-after-free (invalid read)
- **Object:** b[2] — dangling pointer to freed block
- **Line:** 42
- **Cause:** b and a alias the same heap block. free(a) frees the block,
but b still holds the address. Reading b[2] accesses freed memory.
- **Valgrind output:**
```
  ==19433== Invalid read of size 4
  ==19433==    at 0x1092F5: main (aliasing_example.c:42)
  ==19433==  Address 0x4a76488 is 8 bytes inside a block of size 20 free'd
```

### Error 2
- **Type:** use-after-free (invalid write)
- **Object:** b[3] — dangling pointer to freed block
- **Line:** 44
- **Cause:** same aliasing issue — writing to a freed block via b.
- **Valgrind output:**
```
  ==19433== Invalid write of size 4
  ==19433==    at 0x109315: main (aliasing_example.c:44)
  ==19433==  Address 0x4a7648c is 12 bytes inside a block of size 20 free'd
```

### Error 3
- **Type:** use-after-free (invalid read)
- **Object:** b[3] — reading back the value just written
- **Line:** 45
- **Cause:** same aliasing issue — printf reads b[3] after free.
- **Valgrind output:**
```
  ==19433== Invalid read of size 4
  ==19433==    at 0x109323: main (aliasing_example.c:45)
  ==19433==  Address 0x4a7648c is 12 bytes inside a block of size 20 free'd
```

---

## 3. crash_example.c

### Error 1
- **Type:** Invalid write of size 4 (NULL dereference)
- **Object:** nums
- **Line:** 32
- **Cause:** allocate_numbers(0) returns NULL because n <= 0. nums is never checked before use, dereferencing NULL at line 32 causes a segfault
- **Valgrind output:**
```
==21677== Invalid write of size 4
==21677==    at 0x10928A: main (crash_example.c:32)
==21677==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

---

## AI correction

**What AI said:** "The segfault occurs because malloc failed to allocate memory and returned NULL. This is a memory allocation error caused by insufficient system memory."
**Why it was wrong:** malloc is never called. When n = 0, allocate_numbers() hits the if (n <= 0) return NULL check and returns immediately. The crash is not an allocation failure
**Correction:** The crash is caused by passing n = 0 without checking the return value of allocate_numbers(). nums is NULL before line 32, dereferencing it causes the segfault