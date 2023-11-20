#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>


#define BLOCKLEN 16
#define MAXTHREAD 256
#define MAX_CLNT 256
#define BUF_SIZE 4096
#define MAC_SIZE 32
#define PAYLOAD_SIZE (BUF_SIZE+MAC_SIZE) 

//for Multithread_CTR struct
typedef struct _DATA_ {
	uint8_t text_msg[1024];
	uint32_t msg_size;
	uint32_t sum_size;
}DATA;

typedef struct _message_ {
	uint8_t payload[PAYLOAD_SIZE];
	uint32_t msg_len;
}message;


//ARIA
void Add_SubstOdd_Layer(uint8_t* input, uint8_t* key);
void Add_SubstEven_Layer(uint8_t* input, uint8_t* key);
void DiffLayer(uint8_t* input);
void Round_odd(uint8_t* input, uint8_t* rk);
void Round_even(uint8_t* input, uint8_t* rk);
void Final_Round(uint8_t* input, uint8_t* key12, uint8_t* key13);
void Rot_L(uint8_t* input, uint8_t* output, int num);
void ROT_XOR(uint8_t* input, uint8_t* op, uint8_t* output, int num);
void Enc_KEY_Expansion(uint8_t* mk, uint8_t rk[13][16]);
void Dec_KEY_Expansion(uint8_t* mk, uint8_t dk[13][16]);
void ARIA_EnCrypt(uint8_t* pt, uint8_t* ct, uint8_t* key);
void ARIA_DeCrypt(uint8_t* ct, uint8_t* pt, uint8_t* key);

//CTR
void CTR_INC(uint8_t* ICTR);
void* ARIA_CTR(void* arg);


