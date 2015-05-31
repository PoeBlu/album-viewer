#ifndef JPEG_DEC_H
#define JPEG_DEC_H

#include <stdint.h>
#include <stdbool.h>

#define DQT_MARKER	0xFFDB
#define SOI_MARKER	0XFFD8
#define SOF_MARKER	0xFFC0
#define HUF_MARKER	0xFFC4

typedef struct {
	uint16_t	soi;
	uint16_t	app0;
	uint16_t	app0_len;
	// Null terminated string "JFIF"
	uint8_t		id_str[5];
	uint16_t	version;
	uint8_t		units;
	uint16_t	x_res;
	uint16_t	y_res;
	uint8_t		x_pixel;
	uint8_t		y_pixel;
} __attribute__((__packed__)) jfif_header ;

// Define Quantization table
// TODO(pmalani): Need to account for multiple QT
typedef struct {
	uint16_t	lq;
	uint8_t		pq; // QT precision
	uint8_t		tq; // QT identifier
	uint8_t		el[64]; // QT elements
} jfif_dqt;

typedef struct {
	uint8_t		c; // Component indentifier
	uint8_t		h; // Horizontal sampling factor
	uint8_t		v; // Veritical sampling factor
	uint8_t		qt_sel; // Quantization table selector
} jfif_sof_comp;

typedef struct {
	uint16_t	len;
	uint8_t		prec;
	uint16_t	y;
	uint16_t	x;
	uint8_t		num_f;
	jfif_sof_comp	comp[3]; // For Y U and V
} jfif_sof;


typedef struct {
	jfif_header	hdr;
	jfif_dqt	dqt[2];
	bool		one_dqt;
	jfif_sof	sof;
} jfif_info;

#endif
