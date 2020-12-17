#pragma once
#include <stdint.h>

typedef struct {
	uint32_t startaddr;
	uint32_t size;
	uint32_t loop_start;
	uint32_t loop_end;
	uint16_t freq;
} __attribute__((__packed__)) hdr_pcm_data;

typedef struct {
	char magic[4]; // PZI1
	char pad[0x1C]; // Padding
	hdr_pcm_data pcmdata[128]; // 128 entries
} __attribute__((packed)) pzi_data;



//
// THANKS TO
/*
 * TAN-Y: for PZI Format specification
 * kuma: for (essentially) my emotonal support,. PMD Insights and C# remake PMD remake in .NET 
*/

