void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("out of memory, download more RAM\n");
        exit(1);
    }
    return ptr;
}