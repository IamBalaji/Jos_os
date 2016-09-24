Exercise 1 : Familiarize yourself with the assembly language materials available on the 6.828 reference page.
Response :
	Done

Exercise 2 : Use GDB's si (Step Instruction) command to trace into the ROM BIOS for a few more instructions, and try to guess what it might be doing.
Response : 
	

Exercise 3 :Set a breakpoint at address 0x7c00, which is where the boot sector will be loaded. Continue execution until that breakpoint. Trace through the code in boot/boot.S, using the source code and the disassembly file obj/boot/boot.asm to keep track of where you are. Also use the x/i command in GDB to disassemble sequences of instructions in the boot loader, and compare the original boot loader source code with both the disassembly in obj/boot/boot.asm and GDB.
Response : Done

Question 3.1 : At what point does the processor start executing 32-bit code? What exactly causes the switch from 16- to 32-bit mode?
Answer :
	The switch from the 16- to 32- bit mode is caused by the execution of the following instruction from the obj/boot/boot.asm file (line no. ~77)	
	ljmp  $PROT_MODE_CSED, $protcseg

Question 3.2 : What is the last instruction of the boot loader executed, and what is the first instruction of the kernel it just loaded?
Answer :
	The last instruction which was executed of the boot loader is to call the entry point from the ELF header. 
		((void(*)(void)) (ELFHDR->e_entry))():
	The first instruction it just loaded
		7d5e: 	ff 15 18 00 01 00	call	*0x10018

Question 3.3 : Where is the first instruction of the kernel?
Answer : 
	The first instruction of the kernel can be found by using gdb as follows:
  	Command :	x/x *0x10018
       	Output  :	0x10000c:    0x7205c766
    Therefore first instruction is at memory 0x10000c

Question 3.4 : How does the boot loader decide how many sectors it must read in order to fetch the entire kernel from disk? Where does it find this information?
Answer :
	It is determined from ELFHDR structure member “uint16_t e_phnum"

Exercise 4 : Read about programming with pointers in C. 
Response :
	Done

Exercise 5 : Trace through the first few instructions of the boot loader again and identify the first instruction that would "break" or otherwise do the wrong thing if you were to get the boot loader's link address wrong. Then change the link address in boot/Makefrag to something wrong, run make clean, recompile the lab with make, and trace into the boot loader again to see what happens. 
Response :
	Done

Exercise 6 : Reset the machine. Examine the 8 words of memory at 0x00100000 at the point the BIOS enters the boot loader, and then again at the point the boot loader enters the kernel. Why are they different? What is there at the second breakpoint?
Response :
	The 8 words at the memory  0x00100000 are the instructions (initially) from the bootloader and the eight words  at second break point (at which bootloader completes loading segments and enters kernel using kernel entry) are the instruction related to kernel.So,it is obvious that these words will be different. 

Exercise 7 : What is the first instruction after the new mapping is established that would fail to work properly if the mapping weren't in place? Comment out the movl %eax, %cr0 in kern/entry.S, trace into it, and see if you were right.
Response :
	The first instruction which fails after removing movl  %eax, %cr0 will be :
	mov    $relocated, %eax 
	since it is the first instruction which will be executed after paging is enabled.

Exercise 8 : We have omitted a small fragment of code - the code necessary to print octal numbers using patterns of the form "%o". Find and fill in this code fragment.
Response :
	Code is written

Question 8.1 : Explain the interface between printf.c and console.c. Specifically, what function does console.c export? How is this function used by printf.c?
Answer : printf.c uses interface functions provided by console.c to write into standard output devices. console.c makes the function cputchar() available to printf.c . So fprintf uses cputchar function to call vprintfmt which enables printf to write into standard output device.

Question 8.2 : Explain the following from console.c:
Answer : This code handles the case when the data entered into the standard output device exceeds it max viewable limit. In that case it shifts the data up and makes space for a new line.


