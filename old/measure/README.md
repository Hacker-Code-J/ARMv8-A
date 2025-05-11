1. **Functionality Concern**: The function `_rdtscp` is not typically available in ARM architectures. `_rdtscp` is an x86 instruction that reads the current value of the processor's time-stamp counter and an auxiliary control register into the provided variables. ARM architectures use different instructions and mechanisms for accessing cycle counters.

    - **ARM Counterpart**: For ARM, especially ARMv7 and ARMv8, you can use the `PMCCNTR_EL0` register on ARM Cortex processors, which counts the number of cycles. Access to this counter is typically done using assembly instructions like `MRC` (for ARMv7) or reading system registers in ARMv8.

2. **Platform-Specific Instructions**: Ensure that your code is specifically written for the platform you're targeting. For example, replacing `_rdtscp` with ARM-compatible instructions for cycle counting:

    ```c
    static inline uint64_t read_cycle_counter() {
        uint64_t value;
        // For ARMv8, use:
        asm volatile("mrs %0, PMCCNTR_EL0" : "=r" (value));
        return value;
    }
    ```
    - **Alternative Assembly for ARMv8**: If direct access to `PMCCNTR_EL0` fails, you might try accessing via a more generic method, or ensure the counter is accessible:
    ```c
    static inline uint64_t read_cycle_counter() {
        uint64_t value;
        asm volatile("isb");
        asm volatile("mrs %0, CNTVCT_EL0" : "=r" (value));
        return value;
    }
    ```
    This reads from the virtual count register, which is more commonly enabled for non-privileged access.

3. **Optimization and Compiler Effects**: Be aware that compilers might optimize out empty loops or seemingly unused computations unless they are properly constrained. This can affect your timing measurements:

    - Use `volatile` or other methods to prevent the compiler from optimizing out important measurements or the loop.

4. **Consistency and Baseline Measurement**: Your approach of measuring an empty loop to find the baseline overhead of loop execution is smart. However, ensure that this measurement is consistent and reliable across different runs and conditions.

5. **Simplifying and Securing Code**: The code performs the operation inside a loop 10,000 times, which is common for averaging out discrepancies, but ensure your function and the system can handle this without unintended side effects or performance issues.