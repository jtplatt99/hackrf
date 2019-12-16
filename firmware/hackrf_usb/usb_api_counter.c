/*
 * Copyright 2016 Schuyler St. Leger
 *
 * This file is part of GreatFET.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "usb_api_counter.h"
#include "usb_queue.h"
#include "sct.h"

#include <operacake_rotator.h>
#include <hackrf_core.h>

#include <stddef.h>

#include <libopencm3/lpc43xx/sgpio.h>
#include <libopencm3/lpc43xx/rgu.h>
#include <libopencm3/lpc43xx/scu.h>
#include <libopencm3/lpc43xx/gima.h>


#undef GREATFET_OPERACAKE

usb_request_status_t usb_vendor_request_counter_start(
		usb_endpoint_t* const endpoint, const usb_transfer_stage_t stage) {
	if (stage == USB_TRANSFER_STAGE_SETUP) {
		rotator_init();

		// Value is the delay for each antenna
		if (endpoint->setup.value) {
			operacake_rotator_set_timing(endpoint->setup.value);
		}

		// Index specifies if same side should be enabled
		if(endpoint->setup.index) {
			operacake_rotator_rotate_crossover_enable(true);
		} else {
			operacake_rotator_rotate_crossover_enable(false);
		}

<<<<<<< HEAD
		// Event 0 triggered by MATCH0. Event 1 triggered by MATCH1.
		SCT_EV0_CTRL = SCT_EV0_CTRL_COMBMODE_MATCH | SCT_EV0_CTRL_MATCHSEL(0);
		SCT_EV1_CTRL = SCT_EV1_CTRL_COMBMODE_MATCH | SCT_EV1_CTRL_MATCHSEL(1);
		SCT_EV2_CTRL = SCT_EV2_CTRL_COMBMODE_MATCH | SCT_EV2_CTRL_MATCHSEL(2);
		SCT_EV3_CTRL = SCT_EV3_CTRL_COMBMODE_MATCH | SCT_EV3_CTRL_MATCHSEL(3);

		#ifdef GREATFET_OPERACAKE
		#define U1CTRL_SET SCT_OUT5_SET
		#define U1CTRL_CLR SCT_OUT5_CLR
		#define U2CTRL0_SET SCT_OUT3_SET
		#define U2CTRL0_CLR SCT_OUT3_CLR
		#define U2CTRL1_SET SCT_OUT4_SET
		#define U2CTRL1_CLR SCT_OUT4_CLR
		#define U3CTRL0_SET SCT_OUT2_SET
		#define U3CTRL0_CLR SCT_OUT2_CLR
		#define U3CTRL1_SET SCT_OUT0_SET
		#define U3CTRL1_CLR SCT_OUT0_CLR
		#endif

		#ifndef GREATFET_OPERACAKE
		#define U1CTRL_SET SCT_OUT14_SET
		#define U1CTRL_CLR SCT_OUT14_CLR
		#define U2CTRL0_SET SCT_OUT13_SET
		#define U2CTRL0_CLR SCT_OUT13_CLR
		#define U2CTRL1_SET SCT_OUT12_SET
		#define U2CTRL1_CLR SCT_OUT12_CLR
		#define U3CTRL0_SET SCT_OUT11_SET
		#define U3CTRL0_CLR SCT_OUT11_CLR
		#define U3CTRL1_SET SCT_OUT8_SET
		#define U3CTRL1_CLR SCT_OUT8_CLR
		#endif

		#define INNERSWITCH
#ifdef REGULAR
		// Event 0, 2 sets output 3, 2. Event 1, 3 clears output 3, 2.
		U2CTRL0_SET = SCT_OUT13_SET_SET0(1) | SCT_OUT13_SET_SET2(1);
		U2CTRL0_CLR = SCT_OUT13_CLR_CLR1(1) | SCT_OUT13_CLR_CLR3(1);

		U3CTRL0_SET = SCT_OUT11_SET_SET0(1) | SCT_OUT11_SET_SET2(1);
		U3CTRL0_CLR = SCT_OUT11_CLR_CLR1(1) | SCT_OUT11_CLR_CLR3(1);


		// Event 1, 2 sets output 4, 0. Event 0, 3 clears output 4, 0.
		U2CTRL1_SET = SCT_OUT12_SET_SET1(1) | SCT_OUT12_SET_SET2(1);
		U2CTRL1_CLR = SCT_OUT12_CLR_CLR0(1) | SCT_OUT12_CLR_CLR3(1);

		U3CTRL1_SET = SCT_OUT8_SET_SET1(1) | SCT_OUT8_SET_SET2(1);
		U3CTRL1_CLR = SCT_OUT8_CLR_CLR0(1) | SCT_OUT8_CLR_CLR3(1);
#endif

#ifdef OUTERSWITCH
		// This should allow the Operacake to switch around only the outer antennas for better path matching
		U1CTRL_SET = SCT_OUT14_SET_SET0(1) | SCT_OUT14_SET_SET1(1);
		U1CTRL_CLR = SCT_OUT14_CLR_CLR2(1) | SCT_OUT14_CLR_CLR3(1);

		U2CTRL1_SET = SCT_OUT12_SET_SET1(1) | SCT_OUT12_SET_SET2(1);
		U2CTRL1_CLR = SCT_OUT12_CLR_CLR0(1) | SCT_OUT12_CLR_CLR3(1);

		U2CTRL0_SET = SCT_OUT13_SET_SET1(1) | SCT_OUT13_SET_SET2(1);
		U2CTRL0_CLR = SCT_OUT13_CLR_CLR0(1) | SCT_OUT13_CLR_CLR3(1);

		U3CTRL1_SET = SCT_OUT8_SET_SET1(1) | SCT_OUT8_SET_SET2(1);
		U3CTRL1_CLR = SCT_OUT8_CLR_CLR0(1) | SCT_OUT8_CLR_CLR3(1);

		U3CTRL0_SET = SCT_OUT11_SET_SET1(1) | SCT_OUT11_SET_SET2(1);
		U3CTRL0_CLR = SCT_OUT11_CLR_CLR0(1) | SCT_OUT11_CLR_CLR3(1);
#endif

#ifdef INNERSWITCH
		// This should allow the Operacake to switch around only the inner antennas for better path matching
		U1CTRL_SET = SCT_OUT14_SET_SET0(1) | SCT_OUT14_SET_SET1(1);
		U1CTRL_CLR = SCT_OUT14_CLR_CLR2(1) | SCT_OUT14_CLR_CLR3(1);

		U2CTRL1_SET = SCT_OUT12_SET_SET1(1) | SCT_OUT12_SET_SET2(1);
		U2CTRL1_CLR = SCT_OUT12_CLR_CLR0(1) | SCT_OUT12_CLR_CLR3(1);

		U2CTRL0_SET = SCT_OUT13_SET_SET0(1) | SCT_OUT13_SET_SET3(1);
		U2CTRL0_CLR = SCT_OUT13_CLR_CLR1(1) | SCT_OUT13_CLR_CLR2(1);

		U3CTRL1_SET = SCT_OUT8_SET_SET1(1) | SCT_OUT8_SET_SET2(1);
		U3CTRL1_CLR = SCT_OUT8_CLR_CLR0(1) | SCT_OUT8_CLR_CLR3(1);

		U3CTRL0_SET = SCT_OUT11_SET_SET0(1) | SCT_OUT11_SET_SET3(1);
		U3CTRL0_CLR = SCT_OUT11_CLR_CLR1(1) | SCT_OUT11_CLR_CLR2(1);
#endif

		// Event 3 toggles output 5.
		#define ONESIDE // Use only 4 antennas, and stay on the same side; comment for 8 antennas
#ifndef ONESIDE
		U1CTRL_SET = SCT_OUT14_SET_SET3(1);
		U1CTRL_CLR = SCT_OUT14_CLR_CLR3(1);
		SCT_RES = SCT_RES_O14RES_TOGGLE_OUTPUT;
#else
		SCT_OUTPUT = BIT14; // Set this to 0 to have A and B crossed statically
#endif


		// Events 0:3 can occur in state 0
		SCT_EV0_STATE = SCT_EV0_STATE_STATEMSK0(1);
		SCT_EV1_STATE = SCT_EV1_STATE_STATEMSK0(1);
		SCT_EV2_STATE = SCT_EV2_STATE_STATEMSK0(1);
		SCT_EV3_STATE = SCT_EV3_STATE_STATEMSK0(1);

		// Event 3 resets the counter to 0
		SCT_LIMIT = BIT3;
		
		// Begin starting
		SCT_STATE = 0;
		
		SCT_CTRL &= ~(SCT_CTRL_STOP_L(1) | SCT_CTRL_HALT_L(1));

=======
>>>>>>> c6ddc625e363c7390da6436a93946164c6ff3720
		usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}

usb_request_status_t usb_vendor_request_counter_stop(
		usb_endpoint_t* const endpoint, const usb_transfer_stage_t stage) {
	if (stage == USB_TRANSFER_STAGE_SETUP) {

		// value == 1 to enable sameside, value == 0 to do nothing, and
		// value != 1 && value != 0 to disable sameside
		// Call reset_state after setting side to update output.
		if (endpoint->setup.value == 1) {
			operacake_rotator_set_default_sameside(true);
			operacake_rotator_reset_state();
		} else if (endpoint->setup.value != 0) {
			operacake_rotator_set_default_sameside(false);
			operacake_rotator_reset_state();
		}

		operacake_rotator_stop();
		usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}

usb_request_status_t usb_vendor_request_counter_set(
	usb_endpoint_t* const endpoint, const usb_transfer_stage_t stage) {
	if (stage == USB_TRANSFER_STAGE_SETUP) {
		// Value is the delay for each antenna
		if (endpoint->setup.value) {
			operacake_rotator_set_timing(endpoint->setup.value);
		}

		// Index specifies if same side should be enabled
		if(endpoint->setup.index) {
			operacake_rotator_rotate_crossover_enable(true);
		} else {
			operacake_rotator_rotate_crossover_enable(false);
		}

		usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}
