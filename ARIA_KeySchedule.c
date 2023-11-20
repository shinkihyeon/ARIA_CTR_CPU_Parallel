#include "main.h"

//128-bit Left ROTATE 함수
//ROT_R은 ROT_L(N)=ROT_R(128-N)성질 이용할것!
void Rot_L(uint8_t* input, uint8_t* output, int num) {
	uint8_t copy_input[BLOCKLEN] = { 0x00, };
	memcpy(copy_input, input, BLOCKLEN * sizeof(uint8_t));
	int r = num % 8;
	int q = num >> 3;
	uint8_t temp[BLOCKLEN] = { 0x00, };
	memcpy(temp, input, BLOCKLEN * sizeof(uint8_t));
	if (r == 0) {
		copy_input[0] = temp[(0 + q) % BLOCKLEN];
		copy_input[1] = temp[(1 + q) % BLOCKLEN];
		copy_input[2] = temp[(2 + q) % BLOCKLEN];
		copy_input[3] = temp[(3 + q) % BLOCKLEN];
		copy_input[4] = temp[(4 + q) % BLOCKLEN];
		copy_input[5] = temp[(5 + q) % BLOCKLEN];
		copy_input[6] = temp[(6 + q) % BLOCKLEN];
		copy_input[7] = temp[(7 + q) % BLOCKLEN];
		copy_input[8] = temp[(8 + q) % BLOCKLEN];
		copy_input[9] = temp[(9 + q) % BLOCKLEN];
		copy_input[10] = temp[(10 + q) % BLOCKLEN];
		copy_input[11] = temp[(11 + q) % BLOCKLEN];
		copy_input[12] = temp[(12 + q) % BLOCKLEN];
		copy_input[13] = temp[(13 + q) % BLOCKLEN];
		copy_input[14] = temp[(14 + q) % BLOCKLEN];
		copy_input[15] = temp[(15 + q) % BLOCKLEN];
	}
	else {
		copy_input[0] = (temp[(0 + q) % BLOCKLEN] << r) | (temp[(0 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[1] = (temp[(1 + q) % BLOCKLEN] << r) | (temp[(1 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[2] = (temp[(2 + q) % BLOCKLEN] << r) | (temp[(2 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[3] = (temp[(3 + q) % BLOCKLEN] << r) | (temp[(3 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[4] = (temp[(4 + q) % BLOCKLEN] << r) | (temp[(4 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[5] = (temp[(5 + q) % BLOCKLEN] << r) | (temp[(5 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[6] = (temp[(6 + q) % BLOCKLEN] << r) | (temp[(6 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[7] = (temp[(7 + q) % BLOCKLEN] << r) | (temp[(7 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[8] = (temp[(8 + q) % BLOCKLEN] << r) | (temp[(8 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[9] = (temp[(9 + q) % BLOCKLEN] << r) | (temp[(9 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[10] = (temp[(10 + q) % BLOCKLEN] << r) | (temp[(10 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[11] = (temp[(11 + q) % BLOCKLEN] << r) | (temp[(11 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[12] = (temp[(12 + q) % BLOCKLEN] << r) | (temp[(12 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[13] = (temp[(13 + q) % BLOCKLEN] << r) | (temp[(13 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[14] = (temp[(14 + q) % BLOCKLEN] << r) | (temp[(14 + q + 1) % BLOCKLEN] >> (8 - r));
		copy_input[15] = (temp[(15 + q) % BLOCKLEN] << r) | (temp[(15 + q + 1) % BLOCKLEN] >> (8 - r));
	}
	memcpy(output, copy_input, BLOCKLEN * sizeof(uint8_t));
}

//rotate시키고 xor까지 실행
//parameter 정보(parameter 순서대로)
//rotate시킬값, 앞의값에 xor해줄값, 결과값, rotate횟수(R_ROTATE라면 128-num)
void ROT_XOR(uint8_t* input, uint8_t* op, uint8_t* output, int num) {
	uint8_t temp[16] = { 0x00, };
	Rot_L(input, temp, num);
	output[0] = temp[0] ^ op[0];
	output[1] = temp[1] ^ op[1];
	output[2] = temp[2] ^ op[2];
	output[3] = temp[3] ^ op[3];
	output[4] = temp[4] ^ op[4];
	output[5] = temp[5] ^ op[5];
	output[6] = temp[6] ^ op[6];
	output[7] = temp[7] ^ op[7];
	output[8] = temp[8] ^ op[8];
	output[9] = temp[9] ^ op[9];
	output[10] = temp[10] ^ op[10];
	output[11] = temp[11] ^ op[11];
	output[12] = temp[12] ^ op[12];
	output[13] = temp[13] ^ op[13];
	output[14] = temp[14] ^ op[14];
	output[15] = temp[15] ^ op[15];
}

//암호화 과정 키스케줄
//mk는 마스터키 -> 마스터키로부터 12R rk생성
void Enc_KEY_Expansion(uint8_t* mk, uint8_t rk[13][16]) { 
	//initial part 
	uint8_t KL[16] = { 0x00, };
	memcpy(KL, mk, 16 * sizeof(uint8_t));
	uint8_t KR[16] = { 0X00, };

	uint8_t CK1[16] = { 0x51,0x7c,0xc1,0xb7,0x27,0x22,0x0a,0x94,0xfe,0x13,0xab,0xe8,0xfa,0x9a,0x6e,0xe0 };
	uint8_t CK2[16] = { 0x6d,0xb1,0x4a,0xcc,0x9e,0x21,0xc8,0x20,0xff,0x28,0xb1,0xd5,0xef,0x5d,0xe2,0xb0 };
	uint8_t CK3[16] = { 0xdb,0x92,0x37,0x1d,0x21,0x26,0xe9,0x70,0x03,0x24,0x97,0x75,0x04,0xe8,0xc9,0x0e };

	//W0
	uint8_t W0[16] = { 0x00, };
	memcpy(W0, KL, 16 * sizeof(uint8_t));

	//W1
	uint8_t copy_W0[16] = { 0x00, };
	memcpy(copy_W0, W0, 16 * sizeof(uint8_t));
	uint8_t W1[16] = { 0x00, };
	Round_odd(copy_W0, CK1);
	memcpy(W1, copy_W0, 16 * sizeof(uint8_t));

	//W2
	uint8_t W2[16] = { 0x00, };
	uint8_t copy_W1[16] = { 0x00, };
	memcpy(copy_W1, W1, 16 * sizeof(uint8_t));
	Round_even(copy_W1, CK2);
	W2[0] = copy_W1[0] ^ W0[0];
	W2[1] = copy_W1[1] ^ W0[1];
	W2[2] = copy_W1[2] ^ W0[2];
	W2[3] = copy_W1[3] ^ W0[3];
	W2[4] = copy_W1[4] ^ W0[4];
	W2[5] = copy_W1[5] ^ W0[5];
	W2[6] = copy_W1[6] ^ W0[6];
	W2[7] = copy_W1[7] ^ W0[7];
	W2[8] = copy_W1[8] ^ W0[8];
	W2[9] = copy_W1[9] ^ W0[9];
	W2[10] = copy_W1[10] ^ W0[10];
	W2[11] = copy_W1[11] ^ W0[11];
	W2[12] = copy_W1[12] ^ W0[12];
	W2[13] = copy_W1[13] ^ W0[13];
	W2[14] = copy_W1[14] ^ W0[14];
	W2[15] = copy_W1[15] ^ W0[15];

	//W3
	uint8_t W3[16] = { 0x00, };
	uint8_t copy_W2[16] = { 0x00, };
	memcpy(copy_W2, W2, 16 * sizeof(uint8_t));
	Round_odd(copy_W2, CK3);
	W3[0] = copy_W2[0] ^ W1[0];
	W3[1] = copy_W2[1] ^ W1[1];
	W3[2] = copy_W2[2] ^ W1[2];
	W3[3] = copy_W2[3] ^ W1[3];
	W3[4] = copy_W2[4] ^ W1[4];
	W3[5] = copy_W2[5] ^ W1[5];
	W3[6] = copy_W2[6] ^ W1[6];
	W3[7] = copy_W2[7] ^ W1[7];
	W3[8] = copy_W2[8] ^ W1[8];
	W3[9] = copy_W2[9] ^ W1[9];
	W3[10] = copy_W2[10] ^ W1[10];
	W3[11] = copy_W2[11] ^ W1[11];
	W3[12] = copy_W2[12] ^ W1[12];
	W3[13] = copy_W2[13] ^ W1[13];
	W3[14] = copy_W2[14] ^ W1[14];
	W3[15] = copy_W2[15] ^ W1[15];

	//Round key generation part(rk 형태는 uint8_t rk[13][16])
	ROT_XOR(W1, W0, rk[0], 128 - 19);
	ROT_XOR(W2, W1, rk[1], 128 - 19);
	ROT_XOR(W3, W2, rk[2], 128 - 19);
	ROT_XOR(W0, W3, rk[3], 128 - 19);
	ROT_XOR(W1, W0, rk[4], 128 - 31);
	ROT_XOR(W2, W1, rk[5], 128 - 31);
	ROT_XOR(W3, W2, rk[6], 128 - 31);
	ROT_XOR(W0, W3, rk[7], 128 - 31);
	ROT_XOR(W1, W0, rk[8], 61);
	ROT_XOR(W2, W1, rk[9], 61);
	ROT_XOR(W3, W2, rk[10], 61);
	ROT_XOR(W0, W3, rk[11], 61);
	ROT_XOR(W1, W0, rk[12], 31);
}

//복호화 과정 키스케줄
void Dec_KEY_Expansion(uint8_t* mk, uint8_t dk[13][16]) {
	//전략: 암호화키 생성 먼저 하고 나서
	//자리만 바꿔서 복호화키 생성할것!
	uint8_t ek[13][16] = { 0x00, };
	Enc_KEY_Expansion(mk, ek);

	//복호화키 설정 파트
	//DK[0]
	memcpy(dk[0], ek[12], 16 * sizeof(uint8_t));

	//DK[1]~DK[11]
	DiffLayer(ek[11]);
	memcpy(dk[1], ek[11], 16 * sizeof(uint8_t));
	DiffLayer(ek[10]);
	memcpy(dk[2], ek[10], 16 * sizeof(uint8_t));
	DiffLayer(ek[9]);
	memcpy(dk[3], ek[9], 16 * sizeof(uint8_t));
	DiffLayer(ek[8]);
	memcpy(dk[4], ek[8], 16 * sizeof(uint8_t));
	DiffLayer(ek[7]);
	memcpy(dk[5], ek[7], 16 * sizeof(uint8_t));
	DiffLayer(ek[6]);
	memcpy(dk[6], ek[6], 16 * sizeof(uint8_t));
	DiffLayer(ek[5]);
	memcpy(dk[7], ek[5], 16 * sizeof(uint8_t));
	DiffLayer(ek[4]);
	memcpy(dk[8], ek[4], 16 * sizeof(uint8_t));
	DiffLayer(ek[3]);
	memcpy(dk[9], ek[3], 16 * sizeof(uint8_t));
	DiffLayer(ek[2]);
	memcpy(dk[10], ek[2], 16 * sizeof(uint8_t));
	DiffLayer(ek[1]);
	memcpy(dk[11], ek[1], 16 * sizeof(uint8_t));

	//DK[12]
	memcpy(dk[12], ek[0], 16 * sizeof(uint8_t));
}