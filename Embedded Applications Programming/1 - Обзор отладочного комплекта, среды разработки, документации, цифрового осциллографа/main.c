int main(void) {
	volatile unsigned char a1=0xE9;
	volatile unsigned char b1=0xE9;
	volatile unsigned char c1=0xE9;
	volatile unsigned char d1=0xE9;
	
	volatile unsigned short a2=0xE9E9;
	volatile unsigned short b2=0xE9E9;
	volatile unsigned short c2=0xE9E9;
	volatile unsigned short d2=0xE9E9;
	
	volatile unsigned int a4=0xE9E9E9E9;
	volatile unsigned int b4=0xE9E9E9E9;
	volatile unsigned int c4=0xE9E9E9E9;
	volatile unsigned int d4=0xE9E9E9E9;
	
	volatile unsigned long long a8=0xE9E9E9E9E9E9E9E9;
	volatile unsigned long long b8=0xE9E9E9E9E9E9E9E9;
	volatile unsigned long long c8=0xE9E9E9E9E9E9E9E9;
	volatile unsigned long long d8=0xE9E9E9E9E9E9E9E9;
	
	volatile char name1[]="Daniil";
	volatile char name2[]="Mel'nikov";
	volatile char name3[]="4133k";
	
	for(;;){}
	return 0;
}

