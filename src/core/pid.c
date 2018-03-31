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


double p_term(
    const signed int err, 
    const double kp
) {
    return ((double) err) * kp;
}

double i_term(
    const signed int err, 
    const double integral, 
    const unsigned int dt, 
    const double ki
) {
    return (integral + (double) err * (double) dt) * ki;
}

double d_term(
    const signed int err, 
    const signed int prev_err, 
    const unsigned int dt, 
    const double kd
) {
    return (((double) err - (double) prev_err) / (double) dt) * kd;
}
