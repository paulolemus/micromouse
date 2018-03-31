/**
 * File: 
 *     pid.h
 * 
 * Description:
 *     PID functions interface.
 * 
 * Notes:
 * 
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_CORE_PID_H_
#define MICROMOUSE_CORE_PID_H_ 

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The P term in a PID controller.
 */
long double p_term(
    const long double err, 
    const long double kp
);

/**
 * The I term in a PID controller.
 */
long double i_term(
    const long double err, 
    const long double integral, 
    const long double dt, 
    const long double ki
);

/**
 * The D term in a PID controller.
 */
long double d_term(
    const long double err, 
    const long double prev_err, 
    const long double dt, 
    const long double kd
);


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_CORE_PID_H_
