/**
 * File:
 *     utils.h
 *
 * Description:
 *     Various utility functions that do not fit anywhere else.
 *     One utility function for example is the wait_ms function.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */    

#ifndef MICROMOUSE_PIC_UTILS_H_
#define MICROMOUSE_PIC_UTILS_H_

#ifdef	__cplusplus
extern "C" {
#endif


/**
 * A blocking wait functions that waits until the given ms time passes.
 * #param ms The time in ms to wait.
 */
void wait_ms(const unsigned int ms);



#ifdef	__cplusplus
}
#endif

#endif	// MICROMOUSE_PIC_UTILS_H_

