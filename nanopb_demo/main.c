/*
 * main.c
 *
 *  Created on: 14 Tem 2020
 *      Author: serbay
 */

#include <stdio.h>

// Proto Includes
#include <pb_encode.h>
#include <pb_decode.h>
#include "demo.pb.h"

device client = device_init_zero;
device server = device_init_zero;

uint8_t buffer[128];
size_t message_length;
bool status;

void proto_client(void)
{
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

	client.indoor_sensor.humidity = 100;
	client.indoor_sensor.temperature = 28.75f;

	client.outdoor_sensor.humidity = 101;
	client.outdoor_sensor.temperature = 33.24f;

	strcpy(client.payload, "Here we go. Client Payload is in here...\n");

	status = pb_encode(&stream, device_fields, &client);
	message_length = stream.bytes_written;

	if (!status)
	{
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return;
	}
}

void proto_server(void)
{
	pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

	status = pb_decode(&stream, device_fields, &server);

	if (!status)
	{
		printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
		return;
	}

	printf("Indoor Sensor Humidity: %d\n", server.indoor_sensor.humidity);
	printf("Indoor Sensor Temperature: %f\n", server.indoor_sensor.temperature);
	printf("Outdoor Sensor Humidity: %d\n", server.outdoor_sensor.humidity);
	printf("Outdoor Sensor Temperature: %f\n", server.outdoor_sensor.temperature);

	printf("Payload from Client: %s\n", server.payload);
}

int main(void)
{
	// Create Client Output Stream
	// Fill Client Data Structure
	// Encode it
	proto_client();

	// Create Client Input Stream
	// Decode it
	// Print the decoded data structure
	proto_server();

	return 0;
}
