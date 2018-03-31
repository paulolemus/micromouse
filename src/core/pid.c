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
    return 0.0;
}

double i_term(
    const signed int err, 
    const double integral, 
    const unsigned int dt, 
    const double ki
) {
    return 0.0;
}

double d_term(
    const signed int err, 
    const signed int prev_err, 
    const unsigned int dt, 
    const double kd
) {
    return 0.0;
}
