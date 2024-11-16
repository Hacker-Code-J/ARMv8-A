The error `undefined reference to 'printf'` occurs because the linker cannot find the `printf` function. In assembly, when calling standard library functions like `printf`, you need to link your code with the C standard library.

Here’s how to resolve this:

1. **Link with the C Standard Library**: Use the `-lc` flag when linking to include the C library, which contains `printf`.

2. **Specify the Entry Point (if required)**: If the linker is still giving issues about `_start`, you might need to add the `-nostartfiles` option or specify `_start` manually.

Here’s an example `Makefile` entry that should work for your assembly file, `arith1.s`:

```makefile
arith1: arith1.s
    aarch64-linux-gnu-gcc -o arith1 arith1.s -lc
```

### Explanation of the Flags:
- **`-o arith1`**: Sets the output file name to `arith1`.
- **`-lc`**: Links the C standard library, which includes `printf`.

### Notes:
Ensure you have the `aarch64-linux-gnu-gcc` toolchain if you’re assembling for ARM64. This command should handle both assembling and linking, so you don’t need a separate `ld` step.