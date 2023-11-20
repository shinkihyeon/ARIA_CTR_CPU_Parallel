#include "main.h"
message msg;
DATA enc_data[4];
pthread_mutex_t mutx;

//Counter +1�� ���ִ� �Լ�
void CTR_INC(uint8_t* ICTR) {
	int cnt_i;
	for (cnt_i = 15; cnt_i > 7; cnt_i--) {
		if (ICTR[cnt_i] != 0xff) {
			ICTR[cnt_i] += 1;
			break;
		}
		else {
			ICTR[cnt_i] = 0x00;
		}
	}
}


//ARIA_CTR�� ��Ƽ������� CPU_Parallel ���ִ� �Լ�!
void* ARIA_CTR(void* arg) {
	uint32_t cnt_i;
	//valuable settings
	uint32_t thread_num = *(uint32_t*)arg;

	//ctr_crypto start
	printf("thread_num:%d\n", thread_num);
	uint8_t CTR_KEY[16] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff };
	uint32_t enc_len = (enc_data[thread_num].msg_size % 16 == 0) ? enc_data[thread_num].msg_size : enc_data[thread_num].msg_size + (16 - enc_data[thread_num].msg_size % 16);
	uint8_t temp[1024] = { 0x00, };//ī���Ͱ� ��ȣȭ�� �� ���� ����
	uint8_t result[1024] = { 0x00, };
	uint8_t iv[16] = { 0x00, };
	uint8_t IV[1024] = { 0X00, };//������ CTR���� ���� ����
	uint32_t enc_start = 16 * (((enc_data[thread_num].sum_size >> 2) * thread_num) >> 4);
	uint32_t enc_end = (((enc_data[thread_num].sum_size >> 2) * thread_num) + enc_data[thread_num].msg_size - 1) + (16 - ((((enc_data[thread_num].sum_size >> 2) * thread_num) + enc_data[thread_num].msg_size - 1)) % 16);
	
	//CTR�� ��ȣȭ�ϱ����� �ش�κ��� CTR������ ����� �۾�
	for (cnt_i = 0; cnt_i < (enc_start >> 4); cnt_i++) {
		CTR_INC(iv);
	}

	//�ʿ��� ��ŭ�� CTR+@�� �����ϴ� �۾�
	for (cnt_i = 0; cnt_i < ((enc_end - enc_start) >> 4); cnt_i++) {
		memcpy(IV + (16 * cnt_i), iv, 16);
		CTR_INC(iv);
	}
	for (cnt_i = 0; cnt_i < ((enc_end - enc_start) >> 4); cnt_i++) {
		//CTR��ȣȭ
		ARIA_EnCrypt(IV + (16 * cnt_i), temp + (16 * cnt_i), CTR_KEY);//�ʿ��Ѹ�ŭ �߶󾵰ž�!
	}
	uint32_t temp_start = ((enc_data[thread_num].sum_size >> 2) * thread_num) - enc_start;

	//ct -> pt ^ ENC(CTR)
	for (cnt_i = 0; cnt_i < enc_data[thread_num].msg_size; cnt_i++) {//�ʿ��Ѹ�ŭ �߶� ���!
		result[cnt_i] = enc_data[thread_num].text_msg[cnt_i] ^ temp[cnt_i + temp_start];
	}

	//������ ó��
	memcpy(msg.payload + ((enc_data[thread_num].sum_size >> 2) * thread_num), result, enc_data[thread_num].msg_size);
	return NULL;
}


