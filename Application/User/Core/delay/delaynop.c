/*
 * delaynop.c
 *
 *  Created on: Apr 15, 2023
 *      Author: jcaf
 */



#define _NOP() __asm__ __volatile__("nop")

void delay_us(unsigned int val)
{
  unsigned int i;
/*
 * noinline
 * This function attribute prevents a function from being considered for inlining. If the function does not have side effects,
 * there are optimizations other than inlining that cause function calls to be optimized away, although the function call is live.
 * To keep such calls from being optimized away, put:
 */
  asm ("");

//#define CPU_HZ 32000000
#define CPU_HZ 80000000

#if CPU_HZ == 80000000

  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();

    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
  }
#elif CPU_HZ == 32000000
  for(i=0; i<val; i++)
  {
    _NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
    _NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();
  }
#elif CPU_HZ == 16384000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 16000000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 8192000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#elif CPU_HZ == 8000000
  for(i=0; i<val; i++)
  {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
#else
#error "Invalid value for CPU_HZ!"
#endif
}
