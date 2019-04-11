#include <stdio.h>
#include <string.h>
#include "sha256.h"

typedef uint8_t u8;

int main(int argc, char* argv[]) {
	sha256_context ctx;
	sha256_init(&ctx);

	u8 hash[SHA256_BYTES];

	char* filename = argv[1];
	FILE *fp;
	size_t n_read;
	u8 data[32*1024];

	if (argc < 2 || strcmp(filename, "-") == 0) {
		fp = stdin;
	} else {
		fp = fopen(filename, "r");
		if (fp == NULL) {
			printf("uh oh! can't open file.");
			return 2;
		}
	}

	while ((n_read = fread(data, 1, sizeof(data), fp)) != 0) {
		sha256_hash(&ctx, data, n_read);
	}

	sha256_done(&ctx, hash);

	// -- print the hash to stdout
	for (size_t i = 0; i < SHA256_BYTES; i++)
		printf("%02x", hash[i]);
	printf("\n");

	return 0;
}