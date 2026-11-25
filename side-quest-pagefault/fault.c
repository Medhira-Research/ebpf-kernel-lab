#include <stdio.h>

void trigger_fault(int *ptr) {
    *ptr = 42;  // Illegal memory write -> CPU MMU traps into kernel
}

int main() {
    int *bad_addr = (int *)0xdeadbeef;
    trigger_fault(bad_addr);
    return 0;
}
