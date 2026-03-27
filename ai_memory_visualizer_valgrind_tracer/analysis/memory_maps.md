# Memory Maps Analysis

## Table of Contents
1. [stack_example.c](#1-stack_examplec)
2. [heap_example.c](#2-heap_examplec)
3. [aliasing_example.c](#3-aliasing_examplec)
4. [crash_example.c](#4-crash_examplec)
5. [AI Error Documentation](#5-ai-error-documentation)

## stack_example.c

### Variables and memory zones

| Variable    | Zone  | Size     | Lifetime                                          |
|-------------|-------|----------|---------------------------------------------------|
| local_int   | stack | 4 bytes  | created on dump_frame entry, destroyed on return  |
| local_buf   | stack | 16 bytes | created on dump_frame entry, destroyed on return  |
| p_local     | stack | 8 bytes  | created on dump_frame entry, destroyed on return  |

### Stack growth observation

The stack grows downward (toward lower addresses).
Proof from output:
- depth=0: &local_int=0x7ffdc1c90184
- depth=1: &local_int=0x7ffdc1c90154
Address decreased by 0x30 between calls.

### Pointer aliasing

p_local and local_int share the same address: 0x7ffdc1c90184
Modifying *p_local modifies local_int directly.

### Step-by-step memory map

#### Step 1 — main() calls walk_stack(0, 3)
Stack:
  [main frame]
  [walk_stack depth=0] marker=0 @ 0x7ffdc1c901d4

#### Step 2 — walk_stack calls dump_frame("enter", 0)
Stack:
  [main frame]
  [walk_stack depth=0] marker=0 @ 0x7ffdc1c901d4
  [dump_frame depth=0] local_int=100 @ 0x7ffdc1c90184
                       local_buf    @ 0x7ffdc1c90190
                       p_local      = 0x7ffdc1c90184 ← alias!

#### Step 3 — dump_frame returns
  dump_frame frame destroyed — local_int, local_buf, p_local invalid.
  walk_stack(0) frame still active — marker still valid.

#### Step 4 — Recursion peaks at depth=3
Stack:
  [main frame]
  [walk_stack depth=0] marker=0  @ 0x7ffdc1c901d4
  [walk_stack depth=1] marker=10 @ 0x7ffdc1c901a4
  [walk_stack depth=2] marker=20 @ 0x7ffdc1c90174
  [walk_stack depth=3] marker=30 @ 0x7ffdc1c90144

#### Step 5 — Unwinding
  depth=3 returns → frame popped, marker @ 0x7ffdc1c90144 invalid
  depth=2 resumes → marker @ 0x7ffdc1c90174 still valid
  depth=1 resumes → marker @ 0x7ffdc1c901a4 still valid
  depth=0 resumes → marker @ 0x7ffdc1c901d4 still valid

### AI correction

**What AI said:** "At depth=0, local_int is allocated on the heap because it is passed as a parameter to dump_frame. Its address 0x7ffdc1c90184 persists after the function returns, meaning it can safely be accessed later."
**Why it was wrong:** **Why it was wrong:** local_int is a local variable — no malloc 
means no heap. Stack variables are destroyed when their function 
returns. Accessing them after is undefined behavior.
**Correction:** It can't be allocated on the heap because there is no malloc, and the adress cannot persists because it's on the stack, you can't re-use it after a return or it's called a use after free.

## 2. heap_example.c

### Heap allocations
|             Allocation       | Size     |        Freed ?    |
|------------------------------|----------|-------------------|
| malloc(sizeof(Person)) alice | 16 bytes | ❌ name not freed |
| malloc(len + 1) alice->name  | 6 bytes  | ❌ never freed    |
| malloc(sizeof(Person)) bob   | 16 bytes | ✅                |
| malloc(len + 1) bob->name    | 4 bytes  | ✅                |

### Real addresses collected at runtime
- alice struct  @ 0x562fa39bd6b0
- alice->name   @ 0x562fa39bd6d0
- bob struct    @ 0x562fa39bd6f0
- bob->name     @ 0x562fa39bd710

### Why free order matters
free(alice) destroys the struct at 0x562fa39bd6b0.
The only pointer to alice->name (0x562fa39bd6d0) was inside that struct.
Once the struct is freed, alice->name is permanently unreachable — leaked.

### Step-by-step memory map

#### Step 1 — After person_new("Alice", 30)
Heap:
  alice struct @ 0x562fa39bd6b0  (age=30, name ptr inside)
  alice->name  @ 0x562fa39bd6d0  ("Alice\0" — 6 bytes)

#### Step 2 — After person_new("Bob", 41)
Heap:
  alice struct @ 0x562fa39bd6b0  LIVE
  alice->name  @ 0x562fa39bd6d0  LIVE
  bob struct   @ 0x562fa39bd6f0  LIVE
  bob->name    @ 0x562fa39bd710  LIVE

#### Step 3 — free(bob->name) then free(bob)
Heap:
  alice struct @ 0x562fa39bd6b0  LIVE
  alice->name  @ 0x562fa39bd6d0  LIVE
  bob->name    @ 0x562fa39bd710  FREED
  bob struct   @ 0x562fa39bd6f0  FREED

#### Step 4 — person_free_partial(alice)
Heap:
  alice struct @ 0x562fa39bd6b0  FREED
  alice->name  @ 0x562fa39bd6d0  LEAKED — unreachable

### Memory leak analysis
person_free_partial() only frees the Person struct.
p->name is a separate heap allocation — it is not freed automatically.
Result: 6 bytes definitely lost (alice->name).

Valgrind proof:
- definitely lost: 6 bytes in 1 blocks
- at heap_example.c:21 (malloc of p->name in person_new)

### AI correction
**What AI said:** "In person_free_partial, freeing p is sufficient because when the Person structure is freed, all its members including p->name are automatically freed as well."
**Why it was wrong:** p->name is an independent heap allocation, free(p) does not know it exists
**Correction:** The good order is free(p->name) before free(p)

---

## 3. aliasing_example.c

### Pointer aliasing observed
a and b point to the same heap block allocated by make_numbers().
Proof from output:
- a=0x4a76480 b=0x4a76480 (identical addresses)

### Real addresses collected at runtime
- a=0x5f97e64046b0 b=0x5f97e64046b0 (identical — alias confirmed)
- After free(a): b[2]=-1242486022 (allocator overwrote the freed block)
- The value -1242486022 is allocator metadata reinterpreted as int

### Why b[2] is not 22 after free
free() does not zero memory. The allocator writes internal bookkeeping
data into freed blocks. b[2] returns garbage because the allocator
has already modified the freed block's contents.

### Step-by-step memory map

#### Step 1 — make_numbers(5) returns
Stack:  a = 0x5f97e64046b0
Heap:   int[5] @ 0x5f97e64046b0 = {0, 11, 22, 33, 44}

#### Step 2 — b = a
Stack:  a = 0x5f97e64046b0
        b = 0x5f97e64046b0  ← same block, two aliases
Heap:   int[5] @ 0x5f97e64046b0  LIVE

#### Step 3 — free(a)
Stack:  a = 0x5f97e64046b0  ← dangling
        b = 0x5f97e64046b0  ← dangling
Heap:   int[5] @ 0x5f97e64046b0  FREED

#### Step 4 — b[2] read (use-after-free)
  b[2] returns -1242486022 — allocator metadata, not 22
  Reading freed memory — undefined behavior

#### Step 5 — b[3] = 1234 (use-after-free write)
  Corrupts allocator metadata — undefined behavior

### Use after free analysis
After free(a), b becomes a dangling pointer.
b still holds the address 0x4a76480 but the block is freed.

Valgrind proof:
- Invalid read of size 4 at aliasing_example.c:42 (reading b[2])
- Invalid write of size 4 at aliasing_example.c:44 (writing b[3])
- Invalid read of size 4 at aliasing_example.c:45 (reading b[3])
- ERROR SUMMARY: 3 errors from 3 contexts
- No leaks: block was freed via free(a)

### Note on compilation
The compiler itself detected the bug with -Werror=use-after-free.
-Werror had to be removed from CFLAGS to compile and run Valgrind.

### AI correction
**What AI said:** "b is a separate pointer, so after free(a) the memory pointed to by b is still valid and can safely be read and written."
**Why it was wrong:** b = a copies the address, not the block. One allocation, two aliases. free(a) frees the only block, making b free'd too
**Correction:** after free(a), any access to b is use after free 

---

## 4. crash_example.c

### Crash analysis
n = 0 is passed to allocate_numbers().
The function returns NULL because n <= 0.
nums[0] = 42 dereferences NULL → segmentation fault (SIGSEGV).

Valgrind proof:
- Invalid write of size 4 at crash_example.c:32
- Address 0x0 is not stack'd, malloc'd or (recently) free'd
- Process terminated by signal 11 (SIGSEGV)

### Note on still reachable
still reachable: 1,024 bytes in 1 blocks
This is not a leak from our code — it comes from the libc
which did not have time to clean up because the program crashed.

### Step-by-step memory map

#### Step 1 — main() calls allocate_numbers(0)
Stack:  n = 0
        nums = NULL (not yet assigned)

#### Step 2 — allocate_numbers returns NULL
  n <= 0 — early return, malloc never called.
Stack:  nums = NULL

#### Step 3 — nums[0] = 42 (NULL dereference)
  nums is NULL — address 0x0 is not mapped.
  OS raises SIGSEGV — program terminated.
  free(nums) is never reached.

### AI correction
**What AI said:** "The segfault happens because nums array is too small. Allocating more memory would fix the problem."
**Why it was wrong:** The problem is not the size of the allocation. allocate_numbers() returns NULL when n <= 0, and nums is never
checked before use. Writing to NULL causes the crash.
**Correction:** You need to check if malloc returned NULL before dereferencing the pointer.