#include <inc/mmu.h>
#include <inc/x86.h>
#include <inc/assert.h>

#include <kern/pmap.h>
#include <kern/trap.h>
#include <kern/console.h>
#include <kern/monitor.h>
#include <kern/env.h>
#include <kern/syscall.h>
#include <kern/sched.h>
#include <kern/kclock.h>
#include <kern/picirq.h>
#include <kern/cpu.h>
#include <kern/spinlock.h>

static struct Taskstate ts;

/* For debugging, so print_trapframe can distinguish between printing
 * a saved trapframe and printing the current trapframe and print some
 * additional information in the latter case.
 */
static struct Trapframe *last_tf;

/* Interrupt descriptor table.  (Must be built at run time because
 * shifted function addresses can't be represented in relocation records.)
 */
struct Gatedesc idt[256] = { { 0 } };
struct Pseudodesc idt_pd = {
	sizeof(idt) - 1, (uint32_t) idt
};


static const char *trapname(int trapno)
{
	static const char * const excnames[] = {
		"Divide error",
		"Debug",
		"Non-Maskable Interrupt",
		"Breakpoint",
		"Overflow",
		"BOUND Range Exceeded",
		"Invalid Opcode",
		"Device Not Available",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack Fault",
		"General Protection",
		"Page Fault",
		"(unknown trap)",
		"x87 FPU Floating-Point Error",
		"Alignment Check",
		"Machine-Check",
		"SIMD Floating-Point Exception"
	};

	if (trapno < sizeof(excnames)/sizeof(excnames[0]))
		return excnames[trapno];
	if (trapno == T_SYSCALL)
		return "System call";
	if (trapno >= IRQ_OFFSET && trapno < IRQ_OFFSET + 16)
		return "Hardware Interrupt";
	return "(unknown trap)";
}


void
trap_init(void)
{
	extern struct Segdesc gdt[];

	// LAB 3: Your code here.

	void thdlr0();
	void thdlr1();
	void thdlr2();
	void thdlr3();
	void thdlr4();
	void thdlr5();
	void thdlr6();
	void thdlr7();
	void thdlr8();
	void thdlr9();
	void thdlr10();
	void thdlr11();
	void thdlr12();
	void thdlr13();
	void thdlr14();
	void thdlr15();
	void thdlr16();
	void thdlr17();
	void thdlr18();
	void thdlr19();
	void thdlr20();
	void thdlr21();
	void thdlr22();
	void thdlr23();
	void thdlr24();
	void thdlr25();
	void thdlr26();
	void thdlr27();
	void thdlr28();
	void thdlr29();
	void thdlr30();
	void thdlr31();
	void thdlr32();
	void thdlr33();
	void thdlr34();
	void thdlr35();
	void thdlr36();
	void thdlr37();
	void thdlr38();
	void thdlr39();
	void thdlr40();
	void thdlr41();
	void thdlr42();
	void thdlr43();
	void thdlr44();
	void thdlr45();
	void thdlr46();
	void thdlr47();
	void thdlr48();
	void thdlr49();
	void thdlr50();
	void thdlr51();
	void thdlr52();
	void thdlr53();
	void thdlr54();
	void thdlr55();
	void thdlr56();
	void thdlr57();
	void thdlr58();
	void thdlr59();
	void thdlr60();
	void thdlr61();
	void thdlr62();
	void thdlr63();
	void thdlr64();
	void thdlr65();
	void thdlr66();
	void thdlr67();
	void thdlr68();
	void thdlr69();
	void thdlr70();
	void thdlr71();
	void thdlr72();
	void thdlr73();
	void thdlr74();
	void thdlr75();
	void thdlr76();
	void thdlr77();
	void thdlr78();
	void thdlr79();
	void thdlr80();
	void thdlr81();
	void thdlr82();
	void thdlr83();
	void thdlr84();
	void thdlr85();
	void thdlr86();
	void thdlr87();
	void thdlr88();
	void thdlr89();
	void thdlr90();
	void thdlr91();
	void thdlr92();
	void thdlr93();
	void thdlr94();
	void thdlr95();
	void thdlr96();
	void thdlr97();
	void thdlr98();
	void thdlr99();
	void thdlr100();
	void thdlr101();
	void thdlr102();
	void thdlr103();
	void thdlr104();
	void thdlr105();
	void thdlr106();
	void thdlr107();
	void thdlr108();
	void thdlr109();
	void thdlr110();
	void thdlr111();
	void thdlr112();
	void thdlr113();
	void thdlr114();
	void thdlr115();
	void thdlr116();
	void thdlr117();
	void thdlr118();
	void thdlr119();
	void thdlr120();
	void thdlr121();
	void thdlr122();
	void thdlr123();
	void thdlr124();
	void thdlr125();
	void thdlr126();
	void thdlr127();
	void thdlr128();
	void thdlr129();
	void thdlr130();
	void thdlr131();
	void thdlr132();
	void thdlr133();
	void thdlr134();
	void thdlr135();
	void thdlr136();
	void thdlr137();
	void thdlr138();
	void thdlr139();
	void thdlr140();
	void thdlr141();
	void thdlr142();
	void thdlr143();
	void thdlr144();
	void thdlr145();
	void thdlr146();
	void thdlr147();
	void thdlr148();
	void thdlr149();
	void thdlr150();
	void thdlr151();
	void thdlr152();
	void thdlr153();
	void thdlr154();
	void thdlr155();
	void thdlr156();
	void thdlr157();
	void thdlr158();
	void thdlr159();
	void thdlr160();
	void thdlr161();
	void thdlr162();
	void thdlr163();
	void thdlr164();
	void thdlr165();
	void thdlr166();
	void thdlr167();
	void thdlr168();
	void thdlr169();
	void thdlr170();
	void thdlr171();
	void thdlr172();
	void thdlr173();
	void thdlr174();
	void thdlr175();
	void thdlr176();
	void thdlr177();
	void thdlr178();
	void thdlr179();
	void thdlr180();
	void thdlr181();
	void thdlr182();
	void thdlr183();
	void thdlr184();
	void thdlr185();
	void thdlr186();
	void thdlr187();
	void thdlr188();
	void thdlr189();
	void thdlr190();
	void thdlr191();
	void thdlr192();
	void thdlr193();
	void thdlr194();
	void thdlr195();
	void thdlr196();
	void thdlr197();
	void thdlr198();
	void thdlr199();
	void thdlr200();
	void thdlr201();
	void thdlr202();
	void thdlr203();
	void thdlr204();
	void thdlr205();
	void thdlr206();
	void thdlr207();
	void thdlr208();
	void thdlr209();
	void thdlr210();
	void thdlr211();
	void thdlr212();
	void thdlr213();
	void thdlr214();
	void thdlr215();
	void thdlr216();
	void thdlr217();
	void thdlr218();
	void thdlr219();
	void thdlr220();
	void thdlr221();
	void thdlr222();
	void thdlr223();
	void thdlr224();
	void thdlr225();
	void thdlr226();
	void thdlr227();
	void thdlr228();
	void thdlr229();
	void thdlr230();
	void thdlr231();
	void thdlr232();
	void thdlr233();
	void thdlr234();
	void thdlr235();
	void thdlr236();
	void thdlr237();
	void thdlr238();
	void thdlr239();
	void thdlr240();
	void thdlr241();
	void thdlr242();
	void thdlr243();
	void thdlr244();
	void thdlr245();
	void thdlr246();
	void thdlr247();
	void thdlr248();
	void thdlr249();
	void thdlr250();
	void thdlr251();
	void thdlr252();
	void thdlr253();
	void thdlr254();
	void thdlr255();
	SETGATE(idt[0],0,GD_KT,thdlr0,0);
	SETGATE(idt[1],0,GD_KT,thdlr1,0);
	SETGATE(idt[2],0,GD_KT,thdlr2,0);
	SETGATE(idt[3],0,GD_KT,thdlr3,3);
	SETGATE(idt[4],0,GD_KT,thdlr4,0);
	SETGATE(idt[5],0,GD_KT,thdlr5,0);
	SETGATE(idt[6],0,GD_KT,thdlr6,0);
	SETGATE(idt[7],0,GD_KT,thdlr7,0);
	SETGATE(idt[8],0,GD_KT,thdlr8,0);
	SETGATE(idt[9],0,GD_KT,thdlr9,0);
	SETGATE(idt[10],0,GD_KT,thdlr10,0);
	SETGATE(idt[11],0,GD_KT,thdlr11,0);
	SETGATE(idt[12],0,GD_KT,thdlr12,0);
	SETGATE(idt[13],0,GD_KT,thdlr13,0);
	SETGATE(idt[14],0,GD_KT,thdlr14,0);
	SETGATE(idt[15],0,GD_KT,thdlr15,0);
	SETGATE(idt[16],0,GD_KT,thdlr16,0);
	SETGATE(idt[17],0,GD_KT,thdlr17,0);
	SETGATE(idt[18],0,GD_KT,thdlr18,0);
	SETGATE(idt[19],0,GD_KT,thdlr19,0);
	SETGATE(idt[20],0,GD_KT,thdlr20,0);
	SETGATE(idt[21],0,GD_KT,thdlr21,0);
	SETGATE(idt[22],0,GD_KT,thdlr22,0);
	SETGATE(idt[23],0,GD_KT,thdlr23,0);
	SETGATE(idt[24],0,GD_KT,thdlr24,0);
	SETGATE(idt[25],0,GD_KT,thdlr25,0);
	SETGATE(idt[26],0,GD_KT,thdlr26,0);
	SETGATE(idt[27],0,GD_KT,thdlr27,0);
	SETGATE(idt[28],0,GD_KT,thdlr28,0);
	SETGATE(idt[29],0,GD_KT,thdlr29,0);
	SETGATE(idt[30],0,GD_KT,thdlr30,0);
	SETGATE(idt[31],0,GD_KT,thdlr31,0);
	SETGATE(idt[32],0,GD_KT,thdlr32,0);
	SETGATE(idt[33],0,GD_KT,thdlr33,0);
	SETGATE(idt[34],0,GD_KT,thdlr34,0);
	SETGATE(idt[35],0,GD_KT,thdlr35,0);
	SETGATE(idt[36],0,GD_KT,thdlr36,0);
	SETGATE(idt[37],0,GD_KT,thdlr37,0);
	SETGATE(idt[38],0,GD_KT,thdlr38,0);
	SETGATE(idt[39],0,GD_KT,thdlr39,0);
	SETGATE(idt[40],0,GD_KT,thdlr40,0);
	SETGATE(idt[41],0,GD_KT,thdlr41,0);
	SETGATE(idt[42],0,GD_KT,thdlr42,0);
	SETGATE(idt[43],0,GD_KT,thdlr43,0);
	SETGATE(idt[44],0,GD_KT,thdlr44,0);
	SETGATE(idt[45],0,GD_KT,thdlr45,0);
	SETGATE(idt[46],0,GD_KT,thdlr46,0);
	SETGATE(idt[47],0,GD_KT,thdlr47,0);
	SETGATE(idt[48],0,GD_KT,thdlr48,3);
	SETGATE(idt[49],0,GD_KT,thdlr49,0);
	SETGATE(idt[50],0,GD_KT,thdlr50,0);
	SETGATE(idt[51],0,GD_KT,thdlr51,0);
	SETGATE(idt[52],0,GD_KT,thdlr52,0);
	SETGATE(idt[53],0,GD_KT,thdlr53,0);
	SETGATE(idt[54],0,GD_KT,thdlr54,0);
	SETGATE(idt[55],0,GD_KT,thdlr55,0);
	SETGATE(idt[56],0,GD_KT,thdlr56,0);
	SETGATE(idt[57],0,GD_KT,thdlr57,0);
	SETGATE(idt[58],0,GD_KT,thdlr58,0);
	SETGATE(idt[59],0,GD_KT,thdlr59,0);
	SETGATE(idt[60],0,GD_KT,thdlr60,0);
	SETGATE(idt[61],0,GD_KT,thdlr61,0);
	SETGATE(idt[62],0,GD_KT,thdlr62,0);
	SETGATE(idt[63],0,GD_KT,thdlr63,0);
	SETGATE(idt[64],0,GD_KT,thdlr64,0);
	SETGATE(idt[65],0,GD_KT,thdlr65,0);
	SETGATE(idt[66],0,GD_KT,thdlr66,0);
	SETGATE(idt[67],0,GD_KT,thdlr67,0);
	SETGATE(idt[68],0,GD_KT,thdlr68,0);
	SETGATE(idt[69],0,GD_KT,thdlr69,0);
	SETGATE(idt[70],0,GD_KT,thdlr70,0);
	SETGATE(idt[71],0,GD_KT,thdlr71,0);
	SETGATE(idt[72],0,GD_KT,thdlr72,0);
	SETGATE(idt[73],0,GD_KT,thdlr73,0);
	SETGATE(idt[74],0,GD_KT,thdlr74,0);
	SETGATE(idt[75],0,GD_KT,thdlr75,0);
	SETGATE(idt[76],0,GD_KT,thdlr76,0);
	SETGATE(idt[77],0,GD_KT,thdlr77,0);
	SETGATE(idt[78],0,GD_KT,thdlr78,0);
	SETGATE(idt[79],0,GD_KT,thdlr79,0);
	SETGATE(idt[80],0,GD_KT,thdlr80,0);
	SETGATE(idt[81],0,GD_KT,thdlr81,0);
	SETGATE(idt[82],0,GD_KT,thdlr82,0);
	SETGATE(idt[83],0,GD_KT,thdlr83,0);
	SETGATE(idt[84],0,GD_KT,thdlr84,0);
	SETGATE(idt[85],0,GD_KT,thdlr85,0);
	SETGATE(idt[86],0,GD_KT,thdlr86,0);
	SETGATE(idt[87],0,GD_KT,thdlr87,0);
	SETGATE(idt[88],0,GD_KT,thdlr88,0);
	SETGATE(idt[89],0,GD_KT,thdlr89,0);
	SETGATE(idt[90],0,GD_KT,thdlr90,0);
	SETGATE(idt[91],0,GD_KT,thdlr91,0);
	SETGATE(idt[92],0,GD_KT,thdlr92,0);
	SETGATE(idt[93],0,GD_KT,thdlr93,0);
	SETGATE(idt[94],0,GD_KT,thdlr94,0);
	SETGATE(idt[95],0,GD_KT,thdlr95,0);
	SETGATE(idt[96],0,GD_KT,thdlr96,0);
	SETGATE(idt[97],0,GD_KT,thdlr97,0);
	SETGATE(idt[98],0,GD_KT,thdlr98,0);
	SETGATE(idt[99],0,GD_KT,thdlr99,0);
	SETGATE(idt[100],0,GD_KT,thdlr100,0);
	SETGATE(idt[101],0,GD_KT,thdlr101,0);
	SETGATE(idt[102],0,GD_KT,thdlr102,0);
	SETGATE(idt[103],0,GD_KT,thdlr103,0);
	SETGATE(idt[104],0,GD_KT,thdlr104,0);
	SETGATE(idt[105],0,GD_KT,thdlr105,0);
	SETGATE(idt[106],0,GD_KT,thdlr106,0);
	SETGATE(idt[107],0,GD_KT,thdlr107,0);
	SETGATE(idt[108],0,GD_KT,thdlr108,0);
	SETGATE(idt[109],0,GD_KT,thdlr109,0);
	SETGATE(idt[110],0,GD_KT,thdlr110,0);
	SETGATE(idt[111],0,GD_KT,thdlr111,0);
	SETGATE(idt[112],0,GD_KT,thdlr112,0);
	SETGATE(idt[113],0,GD_KT,thdlr113,0);
	SETGATE(idt[114],0,GD_KT,thdlr114,0);
	SETGATE(idt[115],0,GD_KT,thdlr115,0);
	SETGATE(idt[116],0,GD_KT,thdlr116,0);
	SETGATE(idt[117],0,GD_KT,thdlr117,0);
	SETGATE(idt[118],0,GD_KT,thdlr118,0);
	SETGATE(idt[119],0,GD_KT,thdlr119,0);
	SETGATE(idt[120],0,GD_KT,thdlr120,0);
	SETGATE(idt[121],0,GD_KT,thdlr121,0);
	SETGATE(idt[122],0,GD_KT,thdlr122,0);
	SETGATE(idt[123],0,GD_KT,thdlr123,0);
	SETGATE(idt[124],0,GD_KT,thdlr124,0);
	SETGATE(idt[125],0,GD_KT,thdlr125,0);
	SETGATE(idt[126],0,GD_KT,thdlr126,0);
	SETGATE(idt[127],0,GD_KT,thdlr127,0);
	SETGATE(idt[128],0,GD_KT,thdlr128,0);
	SETGATE(idt[129],0,GD_KT,thdlr129,0);
	SETGATE(idt[130],0,GD_KT,thdlr130,0);
	SETGATE(idt[131],0,GD_KT,thdlr131,0);
	SETGATE(idt[132],0,GD_KT,thdlr132,0);
	SETGATE(idt[133],0,GD_KT,thdlr133,0);
	SETGATE(idt[134],0,GD_KT,thdlr134,0);
	SETGATE(idt[135],0,GD_KT,thdlr135,0);
	SETGATE(idt[136],0,GD_KT,thdlr136,0);
	SETGATE(idt[137],0,GD_KT,thdlr137,0);
	SETGATE(idt[138],0,GD_KT,thdlr138,0);
	SETGATE(idt[139],0,GD_KT,thdlr139,0);
	SETGATE(idt[140],0,GD_KT,thdlr140,0);
	SETGATE(idt[141],0,GD_KT,thdlr141,0);
	SETGATE(idt[142],0,GD_KT,thdlr142,0);
	SETGATE(idt[143],0,GD_KT,thdlr143,0);
	SETGATE(idt[144],0,GD_KT,thdlr144,0);
	SETGATE(idt[145],0,GD_KT,thdlr145,0);
	SETGATE(idt[146],0,GD_KT,thdlr146,0);
	SETGATE(idt[147],0,GD_KT,thdlr147,0);
	SETGATE(idt[148],0,GD_KT,thdlr148,0);
	SETGATE(idt[149],0,GD_KT,thdlr149,0);
	SETGATE(idt[150],0,GD_KT,thdlr150,0);
	SETGATE(idt[151],0,GD_KT,thdlr151,0);
	SETGATE(idt[152],0,GD_KT,thdlr152,0);
	SETGATE(idt[153],0,GD_KT,thdlr153,0);
	SETGATE(idt[154],0,GD_KT,thdlr154,0);
	SETGATE(idt[155],0,GD_KT,thdlr155,0);
	SETGATE(idt[156],0,GD_KT,thdlr156,0);
	SETGATE(idt[157],0,GD_KT,thdlr157,0);
	SETGATE(idt[158],0,GD_KT,thdlr158,0);
	SETGATE(idt[159],0,GD_KT,thdlr159,0);
	SETGATE(idt[160],0,GD_KT,thdlr160,0);
	SETGATE(idt[161],0,GD_KT,thdlr161,0);
	SETGATE(idt[162],0,GD_KT,thdlr162,0);
	SETGATE(idt[163],0,GD_KT,thdlr163,0);
	SETGATE(idt[164],0,GD_KT,thdlr164,0);
	SETGATE(idt[165],0,GD_KT,thdlr165,0);
	SETGATE(idt[166],0,GD_KT,thdlr166,0);
	SETGATE(idt[167],0,GD_KT,thdlr167,0);
	SETGATE(idt[168],0,GD_KT,thdlr168,0);
	SETGATE(idt[169],0,GD_KT,thdlr169,0);
	SETGATE(idt[170],0,GD_KT,thdlr170,0);
	SETGATE(idt[171],0,GD_KT,thdlr171,0);
	SETGATE(idt[172],0,GD_KT,thdlr172,0);
	SETGATE(idt[173],0,GD_KT,thdlr173,0);
	SETGATE(idt[174],0,GD_KT,thdlr174,0);
	SETGATE(idt[175],0,GD_KT,thdlr175,0);
	SETGATE(idt[176],0,GD_KT,thdlr176,0);
	SETGATE(idt[177],0,GD_KT,thdlr177,0);
	SETGATE(idt[178],0,GD_KT,thdlr178,0);
	SETGATE(idt[179],0,GD_KT,thdlr179,0);
	SETGATE(idt[180],0,GD_KT,thdlr180,0);
	SETGATE(idt[181],0,GD_KT,thdlr181,0);
	SETGATE(idt[182],0,GD_KT,thdlr182,0);
	SETGATE(idt[183],0,GD_KT,thdlr183,0);
	SETGATE(idt[184],0,GD_KT,thdlr184,0);
	SETGATE(idt[185],0,GD_KT,thdlr185,0);
	SETGATE(idt[186],0,GD_KT,thdlr186,0);
	SETGATE(idt[187],0,GD_KT,thdlr187,0);
	SETGATE(idt[188],0,GD_KT,thdlr188,0);
	SETGATE(idt[189],0,GD_KT,thdlr189,0);
	SETGATE(idt[190],0,GD_KT,thdlr190,0);
	SETGATE(idt[191],0,GD_KT,thdlr191,0);
	SETGATE(idt[192],0,GD_KT,thdlr192,0);
	SETGATE(idt[193],0,GD_KT,thdlr193,0);
	SETGATE(idt[194],0,GD_KT,thdlr194,0);
	SETGATE(idt[195],0,GD_KT,thdlr195,0);
	SETGATE(idt[196],0,GD_KT,thdlr196,0);
	SETGATE(idt[197],0,GD_KT,thdlr197,0);
	SETGATE(idt[198],0,GD_KT,thdlr198,0);
	SETGATE(idt[199],0,GD_KT,thdlr199,0);
	SETGATE(idt[200],0,GD_KT,thdlr200,0);
	SETGATE(idt[201],0,GD_KT,thdlr201,0);
	SETGATE(idt[202],0,GD_KT,thdlr202,0);
	SETGATE(idt[203],0,GD_KT,thdlr203,0);
	SETGATE(idt[204],0,GD_KT,thdlr204,0);
	SETGATE(idt[205],0,GD_KT,thdlr205,0);
	SETGATE(idt[206],0,GD_KT,thdlr206,0);
	SETGATE(idt[207],0,GD_KT,thdlr207,0);
	SETGATE(idt[208],0,GD_KT,thdlr208,0);
	SETGATE(idt[209],0,GD_KT,thdlr209,0);
	SETGATE(idt[210],0,GD_KT,thdlr210,0);
	SETGATE(idt[211],0,GD_KT,thdlr211,0);
	SETGATE(idt[212],0,GD_KT,thdlr212,0);
	SETGATE(idt[213],0,GD_KT,thdlr213,0);
	SETGATE(idt[214],0,GD_KT,thdlr214,0);
	SETGATE(idt[215],0,GD_KT,thdlr215,0);
	SETGATE(idt[216],0,GD_KT,thdlr216,0);
	SETGATE(idt[217],0,GD_KT,thdlr217,0);
	SETGATE(idt[218],0,GD_KT,thdlr218,0);
	SETGATE(idt[219],0,GD_KT,thdlr219,0);
	SETGATE(idt[220],0,GD_KT,thdlr220,0);
	SETGATE(idt[221],0,GD_KT,thdlr221,0);
	SETGATE(idt[222],0,GD_KT,thdlr222,0);
	SETGATE(idt[223],0,GD_KT,thdlr223,0);
	SETGATE(idt[224],0,GD_KT,thdlr224,0);
	SETGATE(idt[225],0,GD_KT,thdlr225,0);
	SETGATE(idt[226],0,GD_KT,thdlr226,0);
	SETGATE(idt[227],0,GD_KT,thdlr227,0);
	SETGATE(idt[228],0,GD_KT,thdlr228,0);
	SETGATE(idt[229],0,GD_KT,thdlr229,0);
	SETGATE(idt[230],0,GD_KT,thdlr230,0);
	SETGATE(idt[231],0,GD_KT,thdlr231,0);
	SETGATE(idt[232],0,GD_KT,thdlr232,0);
	SETGATE(idt[233],0,GD_KT,thdlr233,0);
	SETGATE(idt[234],0,GD_KT,thdlr234,0);
	SETGATE(idt[235],0,GD_KT,thdlr235,0);
	SETGATE(idt[236],0,GD_KT,thdlr236,0);
	SETGATE(idt[237],0,GD_KT,thdlr237,0);
	SETGATE(idt[238],0,GD_KT,thdlr238,0);
	SETGATE(idt[239],0,GD_KT,thdlr239,0);
	SETGATE(idt[240],0,GD_KT,thdlr240,0);
	SETGATE(idt[241],0,GD_KT,thdlr241,0);
	SETGATE(idt[242],0,GD_KT,thdlr242,0);
	SETGATE(idt[243],0,GD_KT,thdlr243,0);
	SETGATE(idt[244],0,GD_KT,thdlr244,0);
	SETGATE(idt[245],0,GD_KT,thdlr245,0);
	SETGATE(idt[246],0,GD_KT,thdlr246,0);
	SETGATE(idt[247],0,GD_KT,thdlr247,0);
	SETGATE(idt[248],0,GD_KT,thdlr248,0);
	SETGATE(idt[249],0,GD_KT,thdlr249,0);
	SETGATE(idt[250],0,GD_KT,thdlr250,0);
	SETGATE(idt[251],0,GD_KT,thdlr251,0);
	SETGATE(idt[252],0,GD_KT,thdlr252,0);
	SETGATE(idt[253],0,GD_KT,thdlr253,0);
	SETGATE(idt[254],0,GD_KT,thdlr254,0);
	SETGATE(idt[255],0,GD_KT,thdlr255,0);

	// Per-CPU setup 
	trap_init_percpu();
}

// Initialize and load the per-CPU TSS and IDT
void
trap_init_percpu(void)
{
	// The example code here sets up the Task State Segment (TSS) and
	// the TSS descriptor for CPU 0. But it is incorrect if we are
	// running on other CPUs because each CPU has its own kernel stack.
	// Fix the code so that it works for all CPUs.
	//
	// Hints:
	//   - The macro "thiscpu" always refers to the current CPU's
	//     struct CpuInfo;
	//   - The ID of the current CPU is given by cpunum() or
	//     thiscpu->cpu_id;
	//   - Use "thiscpu->cpu_ts" as the TSS for the current CPU,
	//     rather than the global "ts" variable;
	//   - Use gdt[(GD_TSS0 >> 3) + i] for CPU i's TSS descriptor;
	//   - You mapped the per-CPU kernel stacks in mem_init_mp()
	//
	// ltr sets a 'busy' flag in the TSS selector, so if you
	// accidentally load the same TSS on more than one CPU, you'll
	// get a triple fault.  If you set up an individual CPU's TSS
	// wrong, you may not get a fault until you try to return from
	// user space on that CPU.
	//
	// LAB 4: Your code here:

	struct Taskstate* xyz = &thiscpu->cpu_ts;
	uint32_t cid = cpunum();

	// Setup a TSS so that we get the right stack
	// when we trap to the kernel.
	xyz->ts_esp0 = KSTACKTOP - cid*(KSTKSIZE+KSTKGAP);
	xyz->ts_ss0 = GD_KD;

	// Initialize the TSS slot of the gdt.
	gdt[(GD_TSS0 >> 3)+cid] = SEG16(STS_T32A, (uint32_t) (xyz),
					sizeof(struct Taskstate) - 1, 0);
	gdt[(GD_TSS0 >> 3)+cid].sd_s = 0;

	// Load the TSS selector (like other segment selectors, the
	// bottom three bits are special; we leave them 0)
	ltr(GD_TSS0+cid*8);

	// Load the IDT
	lidt(&idt_pd);
}

void
print_trapframe(struct Trapframe *tf)
{
	cprintf("TRAP frame at %p from CPU %d\n", tf, cpunum());
	print_regs(&tf->tf_regs);
	cprintf("  es   0x----%04x\n", tf->tf_es);
	cprintf("  ds   0x----%04x\n", tf->tf_ds);
	cprintf("  trap 0x%08x %s\n", tf->tf_trapno, trapname(tf->tf_trapno));
	// If this trap was a page fault that just happened
	// (so %cr2 is meaningful), print the faulting linear address.
	if (tf == last_tf && tf->tf_trapno == T_PGFLT)
		cprintf("  cr2  0x%08x\n", rcr2());
	cprintf("  err  0x%08x", tf->tf_err);
	// For page faults, print decoded fault error code:
	// U/K=fault occurred in user/kernel mode
	// W/R=a write/read caused the fault
	// PR=a protection violation caused the fault (NP=page not present).
	if (tf->tf_trapno == T_PGFLT)
		cprintf(" [%s, %s, %s]\n",
			tf->tf_err & 4 ? "user" : "kernel",
			tf->tf_err & 2 ? "write" : "read",
			tf->tf_err & 1 ? "protection" : "not-present");
	else
		cprintf("\n");
	cprintf("  eip  0x%08x\n", tf->tf_eip);
	cprintf("  cs   0x----%04x\n", tf->tf_cs);
	cprintf("  flag 0x%08x\n", tf->tf_eflags);
	if ((tf->tf_cs & 3) != 0) {
		cprintf("  esp  0x%08x\n", tf->tf_esp);
		cprintf("  ss   0x----%04x\n", tf->tf_ss);
	}
}

void
print_regs(struct PushRegs *regs)
{
	cprintf("  edi  0x%08x\n", regs->reg_edi);
	cprintf("  esi  0x%08x\n", regs->reg_esi);
	cprintf("  ebp  0x%08x\n", regs->reg_ebp);
	cprintf("  oesp 0x%08x\n", regs->reg_oesp);
	cprintf("  ebx  0x%08x\n", regs->reg_ebx);
	cprintf("  edx  0x%08x\n", regs->reg_edx);
	cprintf("  ecx  0x%08x\n", regs->reg_ecx);
	cprintf("  eax  0x%08x\n", regs->reg_eax);
}

static void
trap_dispatch(struct Trapframe *tf)
{
	// Handle processor exceptions.
	// LAB 3: Your code here.



	if(tf->tf_trapno==T_SYSCALL){
     	tf->tf_regs.reg_eax = syscall(tf->tf_regs.reg_eax,tf->tf_regs.reg_edx,tf->tf_regs.reg_ecx,tf->tf_regs.reg_ebx,tf->tf_regs.reg_edi,tf->tf_regs.reg_esi);
     	return ;
     }
     if(tf->tf_trapno==T_PGFLT){
     	page_fault_handler(tf);
     	return ;
     }
     if(tf->tf_trapno==T_BRKPT){
     	monitor(tf);
     	return ;
     }


	// Handle spurious interrupts
	// The hardware sometimes raises these because of noise on the
	// IRQ line or other reasons. We don't care.
	if (tf->tf_trapno == IRQ_OFFSET + IRQ_SPURIOUS) {
		cprintf("Spurious interrupt on irq 7\n");
		print_trapframe(tf);
		return;
	}

	// Handle clock interrupts. Don't forget to acknowledge the
	// interrupt using lapic_eoi() before calling the scheduler!
	// LAB 4: Your code here.
    if(tf->tf_trapno==IRQ_OFFSET+IRQ_TIMER){
    	lapic_eoi();
    	sched_yield();
    	return;
    }
	
     
	// Unexpected trap: The user process or the kernel has a bug.
	print_trapframe(tf);
	if (tf->tf_cs == GD_KT){
		panic("Balaji");
	}
	else {
		env_destroy(curenv);
		return;
	}
}

void
trap(struct Trapframe *tf)
{
	// The environment may have set DF and some versions
	// of GCC rely on DF being clear
	asm volatile("cld" ::: "cc");

	// Halt the CPU if some other CPU has called panic()
	extern char *panicstr;
	if (panicstr)
		asm volatile("hlt");

	// Re-acqurie the big kernel lock if we were halted in
	// sched_yield()
	if (xchg(&thiscpu->cpu_status, CPU_STARTED) == CPU_HALTED)
		lock_kernel();
	// Check that interrupts are disabled.  If this assertion
	// fails, DO NOT be tempted to fix it by inserting a "cli" in
	// the interrupt path.
	assert(!(read_eflags() & FL_IF));

	if ((tf->tf_cs & 3) == 3) {
		// Trapped from user mode.
		// Acquire the big kernel lock before doing any
		// serious kernel work.
		// LAB 4: Your code here.
		lock_kernel();
		assert(curenv);

		// Garbage collect if current enviroment is a zombie
		if (curenv->env_status == ENV_DYING) {
			env_free(curenv);
			curenv = NULL;
			sched_yield();
		}

		// Copy trap frame (which is currently on the stack)
		// into 'curenv->env_tf', so that running the environment
		// will restart at the trap point.
		curenv->env_tf = *tf;
		// The trapframe on the stack should be ignored from here on.
		tf = &curenv->env_tf;
	}

	// Record that tf is the last real trapframe so
	// print_trapframe can print some additional information.
	last_tf = tf;

	// Dispatch based on what type of trap occurred
	trap_dispatch(tf);

//<<<<<<< HEAD
	// If we made it to this point, then no other environment was
	// scheduled, so we should return to the current environment
	// if doing so makes sense.
	if (curenv && curenv->env_status == ENV_RUNNING)
		env_run(curenv);
	else
		sched_yield();
//=======


	// Return to the current environment, which should be running.
	assert(curenv && curenv->env_status == ENV_RUNNING);
	env_run(curenv);
//>>>>>>> lab3
}


void
page_fault_handler(struct Trapframe *tf)
{
	uint32_t fault_va;

	// Read processor's CR2 register to find the faulting address
	fault_va = rcr2();

	// Handle kernel-mode page faults.

	// LAB 3: Your code here.
	if ((tf->tf_cs&3) == 0)
		panic("Kernel page fault!");
	// We've already handled kernel-mode exceptions, so if we get here,
	// the page fault happened in user mode.

	// Call the environment's page fault upcall, if one exists.  Set up a
	// page fault stack frame on the user exception stack (below
	// UXSTACKTOP), then branch to curenv->env_pgfault_upcall.
	//
	// The page fault upcall might cause another page fault, in which case
	// we branch to the page fault upcall recursively, pushing another
	// page fault stack frame on top of the user exception stack.
	//
	// The trap handler needs one word of scratch space at the top of the
	// trap-time stack in order to return.  In the non-recursive case, we
	// don't have to worry about this because the top of the regular user
	// stack is free.  In the recursive case, this means we have to leave
	// an extra word between the current top of the exception stack and
	// the new stack frame because the exception stack _is_ the trap-time
	// stack.
	//
	// If there's no page fault upcall, the environment didn't allocate a
	// page for its exception stack or can't write to it, or the exception
	// stack overflows, then destroy the environment that caused the fault.
	// Note that the grade script assumes you will first check for the page
	// fault upcall and print the "user fault va" message below if there is
	// none.  The remaining three checks can be combined into a single test.
	//
	// Hints:
	//   user_mem_assert() and env_run() are useful here.
	//   To change what the user environment runs, modify 'curenv->env_tf'
	//   (the 'tf' variable points at 'curenv->env_tf').

	// LAB 4: Your code here.
    void*val=curenv->env_pgfault_upcall;
    if(val)
    {
      struct UTrapframe *utf;
		uintptr_t utf_addr;
		if ((UXSTACKTOP-PGSIZE<=tf->tf_esp) && (tf->tf_esp<=UXSTACKTOP-1))
		  {
		  	utf_addr = tf->tf_esp - sizeof(struct UTrapframe) - 4;
		  }
		else 
		   {	utf_addr = UXSTACKTOP - sizeof(struct UTrapframe);

		   }
		user_mem_assert(curenv, (void*)utf_addr, sizeof(struct UTrapframe), PTE_W);
		utf = (struct UTrapframe *) utf_addr;

		utf->utf_fault_va = fault_va;
		utf->utf_err = tf->tf_err;
		utf->utf_regs = tf->tf_regs;
		utf->utf_eip = tf->tf_eip;
		utf->utf_eflags = tf->tf_eflags;
		utf->utf_esp = tf->tf_esp;

		curenv->env_tf.tf_eip = (uintptr_t)curenv->env_pgfault_upcall;
		curenv->env_tf.tf_esp = utf_addr;
		env_run(curenv);
      	
    }
	// Destroy the environment that caused the fault.
	cprintf("[%08x] user fault va %08x ip %08x\n",
		curenv->env_id, fault_va, tf->tf_eip);
	print_trapframe(tf);
	env_destroy(curenv);
}

