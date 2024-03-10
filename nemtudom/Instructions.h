#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#define DEBUG_STATE    false
#define GET_MEM_STATE  false

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

#define CST_R "cst5"

// Arrays

#define ARR_C "arr1"
#define ARR_V "arr2"

#define STR_V "str2"
#define PRS_C "prs1"
#define PSN_C "psn1"

#define PSH_R "psh5"  // Push current position to the stack
#define PPS_R "pps5"  // Pop stack

// Registers

#define MAR_V "mar2"  // Move arr regsiter (move it to the start of the array)
#define URI_V "uri2"  // Update array index
#define PVR_R "pvr5"  // Push value from register to array at index
#define FVR_V "fvi2"  // fetch value to reigster
#define PRV_R "prv5"  // Print value at index
#define EXP_V "exp2"  // Export value at register to a variable (syntax: exp variable_name)
#define SRV_V "srv2"  // Set registers value to a variable


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