# eBPF Kernel Lab (Zero to Systems Engineering)

Hands-on journey learning Linux kernel internals, eBPF, and runtime security on **Fedora 43 (Linux Kernel 7.0.8)**.

## Progress Log

### Day 1 & Day 2: Syscall Tracing & Kernel-Space Filtering
- **Tools used:** `bpftrace`, LLVM/Clang bytecode compiler, Linux tracepoints
- **Probes built:**
  - `day-01-and-02/exec_spy.bt` — Hooks `tracepoint:syscalls:sys_enter_execve` to monitor live process spawns (`bwrap`, `localsearch-3`, `sd-worker`).
  - `day-01-and-02/sensitive_file_alert.bt` — Hooks `tracepoint:syscalls:sys_enter_openat` with an in-kernel string filter to trigger alerts when processes read `/etc/passwd` or `/etc/hostname`.
- **Key Takeaway:** User space applications talk to the Linux kernel via system calls (`execve`, `openat`). `bpftrace` compiles probes into safe bytecode via LLVM and attaches them directly to kernel tracepoints without modifying kernel source code.
