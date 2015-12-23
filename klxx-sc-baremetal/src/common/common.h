/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */

#define DEBUG
#define DEBUG_PRINT

#ifndef CMSIS // If using CMSIS, do not include arm_cm0.h
  /* 
   * Include the generic CPU header file 
   */
  #include "arm_cm0.h"
#else
  #define enable_irq NVIC_EnableIRQ
  #define disable_irq NVIC_DisableIRQ
	#define EnableInterrupts __enable_irq()
	#define DisableInterrupts __disable_irq()
#endif


/* 
 * Include the platform specific header file 
 */
#if (defined(FIREBIRD))
  #include "firebird.h"
#elif (defined(TOWER))
  #include "tower.h"
#elif (defined(FREEDOM))
  #include "freedom.h"
#elif (defined(BACES))
  #include "baces.h"
#else
  #error "No valid platform defined"
#endif

/* 
 * Include the cpu specific header file 
*/
#if (defined (CPU_MKL26Z128VLL4))
  #include "MKL26Z4.h"
#elif (defined (CPU_MKL26Z128VLH4))
  #include "MKL26Z4.h"
#else
  #error "No valid CPU defined"
#endif

#ifdef CMSIS // If using CMSIS, use the MemMapPtr_XXxxx file to bridge the gap between coding styles

/* 
 * Include the cpu specific header file 
*/
#if (defined (CPU_MKL26Z128VLL4))
  #include "MemMapPtr_KL26Z4.h"
#elif (defined(CPU_MKL26Z128VLH4))
  #include "MemMapPtr_KL26Z4.h"
#else
  #error "No valid MemMapPtr_XXxxx header file defined"
#endif

#endif

/* 
 * Include any toolchain specfic header files 
 */
#if (defined(__MWERKS__))
  #include "mwerks.h"
#elif (defined(__DCC__))
  #include "build/wrs/diab.h"
#elif (defined(__ghs__))
  #include "build/ghs/ghs.h"
#elif (defined(__GNUC__))

#elif (defined(IAR))
  #include "iar.h"
#elif (defined(KEIL))

#elif (defined(CW))
  #include "cw.h"
  
#else
#warning "No toolchain specific header included"
#endif

/* 
 * Include common utilities
 */
#include "assert.h"
#include "io.h"
#include "startup.h"
#include "stdlib.h"
#ifdef IAR
#include "intrinsics.h"
#endif

#ifdef CMSIS  // If we are conforming to CMSIS, we need to include these definitions

extern void wait(void);
extern void stop(void);

/*
 * Include common definitions
 *
 * !!! Added for CMSIS Project !!!
 */
#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#ifdef	NULL
#undef	NULL
#endif
#define NULL	(0)

#ifdef  ON
#undef  ON
#endif
#define ON      (1)

#ifdef  OFF
#undef  OFF
#endif
#define OFF     (0)

#define SCB_SCR_SLEEPDEEP_MASK  (1<<2)

/***********************************************************************/
/*
 * The basic data types
 */
typedef unsigned char		uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef char			    int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		            int32;  /* 32 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */

#endif
     
     
/* 
 * Global Variable
 */
     
     


/********************************************************************/

#endif /* _COMMON_H_ */
