#include "main.h"

//확산계층
void DiffLayer(uint8_t* input) {
	uint8_t temp[BLOCKLEN] = { 0x00, };//행렬곱셈 결과 담아놓을 변수

	temp[0] = input[3] ^ input[4] ^ input[6] ^ input[8] ^ input[9] ^ input[13] ^ input[14];
	temp[1] = input[2] ^ input[5] ^ input[7] ^ input[8] ^ input[9] ^ input[12] ^ input[15];
	temp[2] = input[1] ^ input[4] ^ input[6] ^ input[10] ^ input[11] ^ input[12] ^ input[15];
	temp[3] = input[0] ^ input[5] ^ input[7] ^ input[10] ^ input[11] ^ input[13] ^ input[14];
	temp[4] = input[0] ^ input[2] ^ input[5] ^ input[8] ^ input[11] ^ input[14] ^ input[15];
	temp[5] = input[1] ^ input[3] ^ input[4] ^ input[9] ^ input[10] ^ input[14] ^ input[15];
	temp[6] = input[0] ^ input[2] ^ input[7] ^ input[9] ^ input[10] ^ input[12] ^ input[13];
	temp[7] = input[1] ^ input[3] ^ input[6] ^ input[8] ^ input[11] ^ input[12] ^ input[13];
	temp[8] = input[0] ^ input[1] ^ input[4] ^ input[7] ^ input[10] ^ input[13] ^ input[15];
	temp[9] = input[0] ^ input[1] ^ input[5] ^ input[6] ^ input[11] ^ input[12] ^ input[14];
	temp[10] = input[2] ^ input[3] ^ input[5] ^ input[6] ^ input[8] ^ input[13] ^ input[15];
	temp[11] = input[2] ^ input[3] ^ input[4] ^ input[7] ^ input[9] ^ input[12] ^ input[14];
	temp[12] = input[1] ^ input[2] ^ input[6] ^ input[7] ^ input[9] ^ input[11] ^ input[12];
	temp[13] = input[0] ^ input[3] ^ input[6] ^ input[7] ^ input[8] ^ input[10] ^ input[13];
	temp[14] = input[0] ^ input[3] ^ input[4] ^ input[5] ^ input[9] ^ input[11] ^ input[14];
	temp[15] = input[1] ^ input[2] ^ input[4] ^ input[5] ^ input[8] ^ input[10] ^ input[15];

	//결과처리
	memcpy(input, temp, BLOCKLEN * sizeof(uint8_t));
}