#include "main.h"

//CPU_Parallel�� ARIA_CTR�� ��ȣȭ�� ��ȣ�� ����Լ�
void STRING_CTR_CT_printstate(uint8_t* ct, uint32_t size) {
	uint32_t cnt_i;
	printf("STRING_CTR_CT: ");
	printf("\n");
	for (cnt_i = 0; cnt_i < size; cnt_i++) {
		if (cnt_i != 0 && cnt_i % 16 == 0) {
			printf("\n");
		}
		printf("%02X ", ct[cnt_i]);
	}
	printf("\n");
	printf("\n");
}


int main() {
	pthread_t thread[4];
	uint8_t* msg_data = "���δ��б� ���ѹα� ����Ư���� ���ϱ� ������ 77 ���б���� �������Ⱦ�ȣ���а�";
	uint32_t msg_size = strlen(msg_data);
	uint32_t cnt_i;
	pthread_mutex_init(&mutx, NULL);
	uint32_t index[4] = { 0,1,2,3 };
	//create DATA ARRAY & create thread
	for (cnt_i = 0; cnt_i < 4; cnt_i++) {
		if (cnt_i == 3) {
			memcpy(enc_data[cnt_i].text_msg, msg_data + ((msg_size >> 2) * cnt_i), msg_size - ((msg_size >> 2) * 3));
			enc_data[cnt_i].msg_size = msg_size - ((msg_size >> 2) * 3);
		}
		else {
			memcpy(enc_data[cnt_i].text_msg, msg_data + ((msg_size >> 2) * cnt_i), msg_size >> 2);
			enc_data[cnt_i].msg_size = msg_size >> 2;
		}
		enc_data[cnt_i].sum_size = msg_size;
		pthread_create(&thread[cnt_i], NULL, ARIA_CTR, (void*)&index[cnt_i]);
	}
	//join thread
	for (cnt_i = 0; cnt_i < 4; cnt_i++) {
		pthread_join(thread[cnt_i], NULL);
	}

	STRING_CTR_CT_printstate(msg.payload, msg_size);
	pthread_mutex_destroy(&mutx);
	return 0;
}

