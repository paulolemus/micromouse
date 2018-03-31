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
double p_term(
    const signed int err, 
    const double kp
);

/**
 * The I term in a PID controller.
 */
double i_term(
    const signed int err, 
    const double integral, 
    const unsigned int dt, 
    const double ki
);

/**
 * The D term in a PID controller.
 */
double d_term(
    const signed int err, 
    const signed int prev_err, 
    const unsigned int dt, 
    const double kd
);


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_CORE_PID_H_
