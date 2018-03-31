/**
 * File:
 *     pid.c
 *
 * Description:
 *     Implementation for pid.h.
 * 
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */


#include "micromouse/core/pid.h"


long double p_term(
    const long double err, 
    const long double kp
) {
    return err * kp;
}

long double i_term(
    const long double err, 
    const long double integral, 
    const long double dt, 
    const long double ki
) {
    return (integral + err * dt) * ki;
}

long double d_term(
    const long double err, 
    const long double prev_err, 
    const long double dt, 
    const long double kd
) {
    return ((err - prev_err) / dt) * kd;
}
