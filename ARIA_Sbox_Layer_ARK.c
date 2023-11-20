#include "main.h"
#include "ARIA_TABLE.h"

//AddRoundKey + SubstOdd_Layer(È¦¼ö ¶ó¿îµå Ä¡È¯°èÃş)
void Add_SubstOdd_Layer(uint8_t* input, uint8_t* key) {
	input[0] = ARIA_S1[input[0] ^ key[0]];
	input[1] = ARIA_S2[input[1] ^ key[1]];
	input[2] = ARIA_RS1[input[2] ^ key[2]];
	input[3] = ARIA_RS2[input[3] ^ key[3]];
	input[4] = ARIA_S1[input[4] ^ key[4]];
	input[5] = ARIA_S2[input[5] ^ key[5]];
	input[6] = ARIA_RS1[input[6] ^ key[6]];
	input[7] = ARIA_RS2[input[7] ^ key[7]];
	input[8] = ARIA_S1[input[8] ^ key[8]];
	input[9] = ARIA_S2[input[9] ^ key[9]];
	input[10] = ARIA_RS1[input[10] ^ key[10]];
	input[11] = ARIA_RS2[input[11] ^ key[11]];
	input[12] = ARIA_S1[input[12] ^ key[12]];
	input[13] = ARIA_S2[input[13] ^ key[13]];
	input[14] = ARIA_RS1[input[14] ^ key[14]];
	input[15] = ARIA_RS2[input[15] ^ key[15]];
}

//AddRoundKey + SubstEven_Layer(Â¦¼ö ¶ó¿îµå Ä¡È¯°èÃş)
void Add_SubstEven_Layer(uint8_t* input, uint8_t* key) {
	input[0] = ARIA_RS1[input[0] ^ key[0]];
	input[1] = ARIA_RS2[input[1] ^ key[1]];
	input[2] = ARIA_S1[input[2] ^ key[2]];
	input[3] = ARIA_S2[input[3] ^ key[3]];
	input[4] = ARIA_RS1[input[4] ^ key[4]];
	input[5] = ARIA_RS2[input[5] ^ key[5]];
	input[6] = ARIA_S1[input[6] ^ key[6]];
	input[7] = ARIA_S2[input[7] ^ key[7]];
	input[8] = ARIA_RS1[input[8] ^ key[8]];
	input[9] = ARIA_RS2[input[9] ^ key[9]];
	input[10] = ARIA_S1[input[10] ^ key[10]];
	input[11] = ARIA_S2[input[11] ^ key[11]];
	input[12] = ARIA_RS1[input[12] ^ key[12]];
	input[13] = ARIA_RS2[input[13] ^ key[13]];
	input[14] = ARIA_S1[input[14] ^ key[14]];
	input[15] = ARIA_S2[input[15] ^ key[15]];
}