/******************************************************************************
* File:    isr.h
* Purpose: Define interrupt service routines referenced by the vector table.
* Note: Only "vectors.c" should include this header file.
******************************************************************************/

#ifndef __ISR_H
#define __ISR_H 1


/* Example */
/*
#undef  VECTOR_101
#define VECTOR_101 lpt_isr


// ISR(s) are defined in your project directory.
extern void lpt_isr(void);
*/


#undef  VECTOR_044
#define VECTOR_044 lptmr_isr
#undef  VECTOR_031
#define VECTOR_031 adc0_isr


// ISR(s) are defined in your project directory.
extern void lptmr_isr(void);
extern void adc0_isr(void);


#endif  //__ISR_H

/* End of "isr.h" */
