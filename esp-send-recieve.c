//esp sdk
#include "espressif/esp_common.h"
#include "esp/uart.h"

//rtos
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//rf 433mhz
#include <rf_433mhz.h>

#define TRANSMITTER_PIN 5
#define RECIEVER_PIN 4

reciever_433mhz* reciever;
QueueHandle_t decode_queue;

void rf433mhz_transmit(void *pvParameters) {
	gpio_enable(TRANSMITTER_PIN, GPIO_OUTPUT);
	message_433mhz msg;
	msg.code_lenght=24;
	msg.repeat=2;
	protocol_433mhz proto = protocols_433mhz[PROTO1];
	proto.pulse_length = 312;
	msg.protocol = &proto;

	while(true) {
		msg.data=1364;
		send_message_433mhz(TRANSMITTER_PIN, &msg);
		vTaskDelay(1000);
		msg.data=1361;
		send_message_433mhz(TRANSMITTER_PIN, &msg);
		vTaskDelay(1000);
	}
}

void recieve_interrupt_handler(uint8_t gpio_num) {
	recieve_on_interrupt(reciever);
	if (reciever->repeatCount < 2) {
		return;
	}
	taskENTER_CRITICAL();
	reciever_433mhz* old_reciever = reciever;
	reciever = create_reciever_buffer();
	taskEXIT_CRITICAL();
	xQueueSend(decode_queue, &old_reciever, 0);
}

void rf433mhz_recieve(void *pvParameters) {
	//enable reception on recieve pin
	gpio_enable(RECIEVER_PIN, GPIO_INPUT);
	reciever = create_reciever_buffer();
	gpio_set_interrupt(RECIEVER_PIN, GPIO_INTTYPE_EDGE_ANY, recieve_interrupt_handler);

	reciever_433mhz* recv;
	message_433mhz msg;
	while(1) {
		if(xQueueReceive(decode_queue, &recv, 0) == pdTRUE){
			//try to decode recieved data
			bool recieved = false;
			for(int i=0; i < PROTOCOL_COUNT ; i++) {
				if(decode_recieved(recv, &protocols_433mhz[i], &msg)) {
					recieved = true;
					printf("Recieved message with data: %d\n", msg.data);
					break;
				}
				//no protcol found to decode data
			}
			free(recv);
		}
	}
}

void user_init(void) {
	uart_set_baud(0, 115200);

	decode_queue = xQueueCreate(2, sizeof(reciever_433mhz*));

	//start tasks
	xTaskCreate(rf433mhz_transmit, "transmitter_rf", 256, NULL, 1, NULL);
	xTaskCreate(rf433mhz_recieve, "reciever_rf", 256, NULL, 1, NULL);

}
