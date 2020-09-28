#include <main.h>
uint8_t spi_send_read_word (uint8_t word);
void SendSetMode (void);
void SendResetPointer (void);
uint8_t SendReadStatus (void);
void SendReadCommand (void);
void ReadSendData (void);
void SPI_Config(void);

int main(void)
{
	unsigned long statusCounter = 0;
	//pocetne inicijalizacije
	USART1_Init();
	SPI_Config();
	timer2_init();
	timer2_wait_microsec(1000);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//timer2_wait_microsec(10);
	
	SendSetMode();
	SendResetPointer();
	do{
		if(SendReadStatus() != 0x20){
		statusCounter++;
		}	
		else{
		continue;
		}
		if(statusCounter == 100){
			break;
		}
	}while(statusCounter < 100);
	SendReadCommand();
	ReadSendData();	
}

uint8_t spi_send_read_word (uint8_t word){ 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData (SPI1, word);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

void SendSetMode (void){
	unsigned long modee = 0xC0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	spi_send_read_word(modee);
	timer2_wait_microsec(1);
	spi_send_read_word(0x00);
	timer2_wait_microsec(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	timer2_wait_microsec(1);
}

void SendResetPointer (void){
	unsigned long modee = 0x80;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	spi_send_read_word(modee);
	timer2_wait_microsec(1);
	spi_send_read_word(0x00);
	timer2_wait_microsec(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	timer2_wait_microsec(1);
}

uint8_t SendReadStatus (void){
	unsigned long status = 0x00;
	unsigned long dataValid = 0x00;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	spi_send_read_word(status); 
	timer2_wait_microsec(1);
	dataValid = spi_send_read_word(0x00);
USART1_SendChar(dataValid);
	timer2_wait_microsec(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	timer2_wait_microsec(1);
//	dataValid &= 0x20;
	return dataValid;
}

void SendReadCommand (void){
	unsigned long read = 0x40;
//	unsigned long x = 0x00;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	spi_send_read_word(read);
	timer2_wait_microsec(1);
	spi_send_read_word(0x00);
//USART1_SendChar(x);
}

void ReadSendData (void){
	unsigned long i, j;
//	unsigned char imageData = 0;
	unsigned char imageData;
	timer2_wait_microsec(1);
	for(i=0;i<288;i++){
		for(j=0;j<224;j++){
		timer2_wait_microsec(1);
		imageData = spi_send_read_word(0x00);
		timer2_wait_microsec(1);
		USART1_SendChar(imageData);
		}
		spi_send_read_word(0x00);
	}
	timer2_wait_microsec(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	timer2_wait_microsec(1);
}
