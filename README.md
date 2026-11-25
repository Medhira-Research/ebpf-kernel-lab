# eBPF Kernel Lab (Zero to Systems Engineering)

Hands-on journey learning Linux kernel internals, eBPF, and runtime security on **Fedora 43 (Linux Kernel 7.0.8)**.

## Progress Log

### Day 1 & Day 2: Syscall Tracing & Kernel-Space Filtering
- **Tools used:** `bpftrace`, LLVM/Clang bytecode compiler, Linux tracepoints
- **Probes built:**
  - `day-01-and-02/exec_spy.bt` — Hooks `tracepoint:syscalls:sys_enter_execve` to monitor live process spawns (`bwrap`, `localsearch-3`, `sd-worker`).
  - `day-01-and-02/sensitive_file_alert.bt` — Hooks `tracepoint:syscalls:sys_enter_openat` with an in-kernel string filter to trigger alerts when processes read `/etc/passwd` or `/etc/hostname`.
- **Key Takeaway:** User space applications talk to the Linux kernel via system calls (`execve`, `openat`). `bpftrace` compiles probes into safe bytecode via LLVM and attaches them directly to kernel tracepoints without modifying kernel source code.

### Day 3: In-Kernel Hash Maps & Failed Syscall Aggregation
- **Probe built:** `day-03/file_spy.bt` — Uses two in-kernel eBPF hash maps (`@opens[comm]` on `sys_enter_openat` and `@failed[comm]` filtered by `args->ret < 0` on `sys_exit_openat`) to aggregate top file-opening and error-generating processes without user-space print overhead.
- **Key Takeaway:** Aggregating telemetry in kernel maps (`count()`) eliminates per-event user-space context switches and scales cleanly to thousands of syscalls per second.

### Side Quest: Kernel Page-Fault Interception (`SIGSEGV`) & GDB Register Recovery
- **Files built:** `side-quest-pagefault/fault.c` & `side-quest-pagefault/segfault_kstack.bt`
- **What it does:** Triggers an illegal memory write to `0xdeadbeef`, captures the kernel's `SIGSEGV` delivery along with live `ustack` and `kstack` traces via eBPF (`signal_generate`), and recovers the process mid-crash in `gdb` by allocating heap memory (`malloc(4)`) and patching the `$rax` CPU register.
- **Key Takeaway:** Hardware MMU page faults trap directly into kernel fault handlers (`exc_page_fault`), which can be traced with zero overhead via eBPF tracepoints before signals reach user space.
