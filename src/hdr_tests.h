#ifndef HDR_TESTS_H
#define HDR_TESTS_H

/* These are functions used in tests and are not intended for normal usage. */

#include "hdr_histogram.h"

__BEGIN_DECLS

void hdr_reset_internal_counters(struct hdr_histogram* h);
int32_t counts_index_for(const struct hdr_histogram* h, int64_t value);
int hdr_encode_compressed(struct hdr_histogram* h, uint8_t** compressed_histogram, size_t* compressed_len);
int hdr_decode_compressed(uint8_t* buffer, size_t length, struct hdr_histogram** histogram);
void hdr_base64_decode_block(const char* input, uint8_t* output);
void hdr_base64_encode_block(const uint8_t* input, char* output);

__END_DECLS

#endif
