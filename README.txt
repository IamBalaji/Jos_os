1: what is the purpose of macro MPBOOTPHYS? Why is it necessary in kern/mpentry.S but not in boot/boot.S? In other words, what could go wrong if it were omitted in kern/mpentry.S?

A:MPBOOTPHYS is used to calculate absolute addresses.It is necessary because it is loaded by bootstrap cpu.We think mappings od bootstrap CPU's will be over written.

2:It seems that using the big kernel lock guarantees that only one CPU can run the kernel code at a time. Why do we still need separate kernel stacks for each CPU? Describe a scenario in which using a shared kernel stack will go wrong, even with the protection of the big kernel lock.
A:Answer for having different stacks for each cpu lies in basic principle of OS design "ISOLATION".If we don't have separate stacks,another process can read the data of the process which last recently executed some kernel services from stack.
Suppose we have two cpu's sharing same kernel stack.Now interrupt has occured in cpu0.Architecture pushes the details of interrupt into kernel stack.Suppose while cpu0 switching from user to kernel mode,in cpu1 interrupt happened.So new error code pushed into same kernel satack.This leads to the scenario that cpu0 will try service interrupt raised by cpu1.
Basically interrupt handler mechanism will be messed up.

3. In your implementation of env_run() you should have called lcr3(). Before and after the call to lcr3(), your code makes references (at least it should) to the variable e, the argument to env_run. Upon loading the %cr3 register, the addressing context used by the MMU is instantly changed. But a virtual address (namely e) has meaning relative to a given address context--the address context specifies the physical address to which the virtual address maps. Why can the pointer e be dereferenced both before and after the addressing switch? 
A:This is because:Before and after lcr3() it is true that mapping changes.But kernel mapping to each environments virtual space doesnot change beacause kernel is mapped at KERNBASE in all the env's.so address can be accessed as if there was no change of mapping.

4. Whenever the kernel switches from one environment to another, it must ensure the old environment's registers are saved so they can be restored properly later. Why? Where does this happen?
A: It must save them properly because after the context switch happens and then when say the earlier process is supposed to be executed, we want to presume from the last left point and hence it becomes essential for us to store the environment's registers. The instruction
	curenv->env_tf = *tf in trap.c saves the trapframe which has all the information regarding the current environment.
