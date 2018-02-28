/**
 * File:
 *     encoder.h
 *
 * Description:
 *     Hardware level functions for interacting with the encoder.
 *
 * Notes:
 *     Before any functions are used, the init function must be called.
 *
 * Author:
 *     Paulo Lemus
 */

#ifndef MICROMOUSE_PIC_COMPONENTS_ENCODER_H_
#define MICROMOUSE_PIC_COMPONENTS_ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the encoder in hardware. Must be called before use.
 */
void init_encoder();


#ifdef __cplusplus
}
#endif

#endif // MICROMOUSE_PIC_COMPONENTS_ENCODER_H_
