#include "main.h"
#include "ARIA_TABLE.h"

//홀수 라운드함수
void Round_odd(uint8_t* input, uint8_t* rk) {
	Add_SubstOdd_Layer(input, rk);
	DiffLayer(input);
}

//짝수 라운드함수
void Round_even(uint8_t* input, uint8_t* rk) {
	Add_SubstEven_Layer(input, rk);
	DiffLayer(input);
}

//마지막 라운드 함수
void Final_Round(uint8_t* input, uint8_t* key12, uint8_t* key13) {
	Add_SubstEven_Layer(input, key12);

	//마지막 라운드키와 XOR
	input[0] ^= key13[0];
	input[1] ^= key13[1];
	input[2] ^= key13[2];
	input[3] ^= key13[3];
	input[4] ^= key13[4];
	input[5] ^= key13[5];
	input[6] ^= key13[6];
	input[7] ^= key13[7];
	input[8] ^= key13[8];
	input[9] ^= key13[9];
	input[10] ^= key13[10];
	input[11] ^= key13[11];
	input[12] ^= key13[12];
	input[13] ^= key13[13];
	input[14] ^= key13[14];
	input[15] ^= key13[15];
}


//ARIA128 암호화 함수
void ARIA_EnCrypt(uint8_t* pt, uint8_t* ct, uint8_t* key) {
	uint8_t copy_pt[BLOCKLEN] = { 0x00, }; 
	memcpy(copy_pt, pt, BLOCKLEN * sizeof(uint8_t));
	uint8_t rk[13][16] = { 0x00, };

	//keysetting
	Enc_KEY_Expansion(key, rk);

	//1R~11R
	Round_odd(copy_pt, rk[0]);
	Round_even(copy_pt, rk[1]);
	Round_odd(copy_pt, rk[2]);
	Round_even(copy_pt, rk[3]);
	Round_odd(copy_pt, rk[4]);
	Round_even(copy_pt, rk[5]);
	Round_odd(copy_pt, rk[6]);
	Round_even(copy_pt, rk[7]);
	Round_odd(copy_pt, rk[8]);
	Round_even(copy_pt, rk[9]);
	Round_odd(copy_pt, rk[10]);

	//12R
	Final_Round(copy_pt, rk[11], rk[12]);

	//결과처리
	memcpy(ct, copy_pt, BLOCKLEN * sizeof(uint8_t));
}

//ARIA128 복호화 함수
void ARIA_DeCrypt(uint8_t* ct, uint8_t* pt, uint8_t* key) {
	uint8_t copy_ct[BLOCKLEN] = { 0x00, }; 
	memcpy(copy_ct, ct, BLOCKLEN * sizeof(uint8_t));
	uint8_t dk[13][16] = { 0x00, };

	//keysetting
	Dec_KEY_Expansion(key, dk);

	//1R~11R
	Round_odd(copy_ct, dk[0]);
	Round_even(copy_ct, dk[1]);
	Round_odd(copy_ct, dk[2]);
	Round_even(copy_ct, dk[3]);
	Round_odd(copy_ct, dk[4]);
	Round_even(copy_ct, dk[5]);
	Round_odd(copy_ct, dk[6]);
	Round_even(copy_ct, dk[7]);
	Round_odd(copy_ct, dk[8]);
	Round_even(copy_ct, dk[9]);
	Round_odd(copy_ct, dk[10]);

	//12R
	Final_Round(copy_ct, dk[11], dk[12]);

	//결과처리
	memcpy(pt, copy_ct, BLOCKLEN * sizeof(uint8_t));
}

