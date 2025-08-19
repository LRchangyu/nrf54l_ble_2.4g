/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <soc.h>
#include <assert.h>
#include <dk_buttons_and_leds.h>
#include "main.h"
typedef enum{
	MODE_BLE,
	MODE_2_4G,
	MODE_END,
} mode_e;

static mode_e current_mode = MODE_BLE;
static uint8_t ble_id = 0;
void button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if(buttons & DK_BTN1_MSK){
		printk("Button 1 pressed\n");
		if(current_mode == MODE_BLE) {
			NRF_POWER->GPREGRET[1] = 0xffffffff;
			NRF_POWER->GPREGRET[1] = 0XAA;
			NVIC_SystemReset();
		}
		return;
	}

	if(buttons & DK_BTN2_MSK){
		printk("Button 2 pressed\n");
		if(current_mode == MODE_2_4G) {
			NRF_POWER->GPREGRET[1] = 0xffffffff;
			NVIC_SystemReset();
		}else{
			ble_id++;
			if(ble_id >= CONFIG_BT_ID_MAX) {
				ble_id = 0;
			}
			usr_ble_id_set(ble_id);
		}
		return;
	}

	if (current_mode == MODE_BLE) {
		button_handler_ble(button_state, has_changed);
	} else {
		button_handler_2_4g(button_state, has_changed);
	}
}

void configure_buttons(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
	}
}

static void mode_init(void){
	if(NRF_POWER->GPREGRET[1] == 0XAA){
		printk("2.4G mode\n");
		current_mode = MODE_2_4G;
	}else{
		printk("BLE mode\n");
		current_mode = MODE_BLE;
	}

	configure_buttons();
}

static mode_e get_current_mode(void){
	return current_mode;
}

int main(void)
{
	int err;

	mode_init();

	
	
	if (get_current_mode() == MODE_BLE) {
		printk("Starting BLE mode\n");
		err = main_ble();
		if (err) {
			printk("BLE initialization failed (err: %d)\n", err);
		}
		return err;
	} else {
		printk("Starting 2.4G mode\n");
		err = main_2_4g();
		if (err) {
			printk("2.4G initialization failed (err: %d)\n", err);
		}
		return err;
	}
}
