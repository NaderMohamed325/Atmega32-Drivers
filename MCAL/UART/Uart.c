/*
 * uart.c
 *
 * Created: 9/9/2023 7:36:08 PM
 *  Author: Mohamed
 */ 


#include "uart.h"

// Define CPU frequency and baud rate

#define BAUD 9600


/**
* @brief Initialize the UART with the specified baud rate and frame format.
* @param None
* @return None
*/
void UART_Init(void){
	// Set baud rate
	UBRRL=51;
	CLEAR_BIT(UCSRA,U2X);


	
	// Disable double speed mode
	CLEAR_BIT(UCSRA, U2X);
	


	
	// Enable transmitter and receiver
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
}

/**
* @brief Transmit a byte of data through UART.
* @param data The byte to be transmitted
* @return None
*/
void UART_Send(unsigned char data){
	// Wait for the transmit buffer to be empty
	while (!READ_BIT(UCSRA, UDRE));
	// Put data into the buffer, sends the data
	UDR = data;
}

/**
* @brief Receive a byte of data through UART.
* @param None
* @return The received byte
*/
unsigned char UART_Receive(void){
	// Wait for data to be received
	while (!READ_BIT(UCSRA, RXC));
	// Get and return received data from buffer
	return UDR;
}
void UART_Send_Number(unsigned int num){
	unsigned char *p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

unsigned int UART_Receive_Number(void){
	unsigned int num = 0;
	unsigned int *p = (unsigned int*)&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	return *p;
}