# Memory Management Rituals in C

Memory management in C is a discipline that separates novice coders from system architects. In long-running daemons and server applications, a single missed `free()` can slowly consume all available RAM, eventually bringing the entire system to its knees.

## The Basics: malloc and free

At its core, dynamic memory in C revolves around two functions: `malloc()` to allocate and `free()` to release. But the simplicity is deceptive. Every allocation creates an obligation — a contract that the programmer must honor.

```c
void *ptr = malloc(6000);
if (!ptr) {
    // Handle allocation failure
    return -1;
}
// ... use the memory ...
free(ptr);
ptr = NULL; // Prevent dangling pointer
```

## Arena Allocators: The Superior Pattern

For high-performance applications, arena (or region-based) allocators offer a paradigm shift. Instead of tracking individual allocations, you allocate from a large pre-reserved block and free everything at once.

```c
typedef struct {
    char *base;
    size_t offset;
    size_t capacity;
} Arena;

void *arena_alloc(Arena *a, size_t size) {
    if (a->offset + size > a->capacity) return NULL;
    void *ptr = a->base + a->offset;
    a->offset += size;
    return ptr;
}

void arena_reset(Arena *a) {
    a->offset = 0;
}
```

## Common Pitfalls

- **Double free**: Freeing the same pointer twice leads to undefined behavior and potential security vulnerabilities.
- **Use after free**: Accessing memory after it has been freed. The data may still be there, or it may be overwritten — a Heisenbug.
- **Memory fragmentation**: Repeated small allocations and frees can fragment the heap, making large allocations fail even with sufficient total memory.

## Tools of the Trade

Use `valgrind` to detect leaks, `AddressSanitizer` for buffer overflows, and custom logging wrappers around `malloc`/`free` to track allocation patterns in production systems.

Memory management is not a chore — it is a ritual. Respect it, and your daemons will run forever.
