#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#define DEBUG_STATE    false
#define GET_MEM_STATE  false

// Registers

#define  gen  "gen"   // General porpuse register, 4byte
#define  crs  "crs"   // Compare result register => 8 bits each will be a flag
#define  srg  "srg"   // System register, syscalls works based on this
#define  org  "org"   // Output register
#define  irg  "irg"   // Input register -> points to a buffer that the user will write data to has to be initialized
#define  frg  "frg"   // Fetch register, data from array retrieved by idx is stored here (max 8bit)

// Reg modifiers

#define  scl  "scl"   // System call, result is based on srg
#define  ldd  "ldd"   // Loaded memory destination (ldm returns the value here)

// Array

#define  arr  "arr"   // Declare an array, should be pre allocated (before execution starts), cannot grow
#define  dar  "dar"   // Dynamic array, can grow, shrink
#define  par  "par"   // Pop array => deletes dynamic array
#define  idx  "idx"   // Get value at a given index, stores it in a register 
#define  msg  "msg"   // String, dynamic
		 
// Moving data around
		 
#define  mov  "mov"   // Move data to register
#define  set  "set"   // Set variable to value or to a register
#define  ldm  "ldm"   // Load from memory, store it in
#define  stv  "stv"   // Store value
#define  del  "del"   // Delete a variable


// ; at the end, everything after it will be ignored (Can also be used as comments)

#define ADDR_CONSTANT_SYMBOL  '#'
#define ADDR_REGISTER_SYMBOL  '^'
#define ADDR_IP_SYMBOL        '$'
#define ADDR_LBL_JUMP         '@'


#define ADDR_CONSTANT  1  // Constant addressing eg.: mov gen, #12  => # for constants
#define ADDR_VARIABLE  2  // Happens with variables: mov gen, some_variable
#define ADDR_IP		   3  // manipulates instruction ptr, only with jmps. eg.:  jmp $ +/- some_value
#define ADDR_LABEL	   4  // It is label, no need to bother, value_buffer will hold the label's name
#define ADDR_REGISTER  5  // Register addressing -> ^  example: add variable, ^gen;
#define ADDR_JMP       6  // Label jump addresing example: jmp @_Label;

// Different vars
#define DEL_V "del2"
#define PVA_V "pva2"

#define VAR_C "var1"
#define VAR_V "var2"

#define ADD_C "add1"
#define ADD_V "add2"

#define SUB_C "sub1"
#define SUB_V "sub2"

#define MUL_C "mul1"
#define MUL_V "mul2"

#define DIV_C "div1"
#define DIV_V "div2"

#define MOD_C "mod1"
#define MOD_V "mod2"

#define EQU_C "equ1"
#define EQU_V "equ2"

#define CMP_C "cmp1"
#define CMP_V "cmp2"
#define CCF_R "ccf5"

// jumps

#define JMP_L "jmp6"
#define JMP_C "jmp1"

#define JEQ_L "jeq6"
#define JEQ_C "jeq1"

#define JNE_C "jne1"
#define JNE_L "jne6"

#define JGR_C "jgr1"
#define JGR_L "jgr6"

#define JSM_C "jsm1"
#define JSM_L "jsm6"

#define JSE_C "jse1"
#define JSE_L "jse6"

#define JGE_C "jge1"
#define JGE_L "jge6"

#define RET_S "ret5"

// Arrays

#define ARR_C "arr1"
#define ARR_V "arr2"

#define STR_V "str2"
#define PRS_C "prs1"
#define PSN_C "psn1"

#define PSH_R "psh5"  // Push current position to the stack
#define PPS_R "pps5"  // Pop stack


//|---------- Label Rules ----------|
// 
// Must start with '_'
//    -> For example: _myLabel;
// 
// Must have a ret position:
//    -> For example:  jmp _labelEnd
// 
// Jump checking is not implemented
// 
//|---------- Label Rules ----------|
#define ENTR_POINT_NAME "_MAIN"

#endif // ! _INSTRUCTIONS_H