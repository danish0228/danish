
#include <mbed.h>
#include <TextLCD.h>
#include <vector>


class Digits {
private:
	std::vector<char> chars;
public:
	Digits()
	{
		int i;
		for (i = 0; i < 10; i++) {
			chars.push_back('0' + i);
		}
	}
	char get(int n)
	{
		return chars[n];
	}
};


class Test {
private:
	unsigned int count;
	DigitalOut led;
	TextLCD lcd;
	Digits digits;
public:
	Test()
		: count(0)
		, led(p21)
		, lcd(p4, p7, p8, p16, p18, p19)
	{
	}
	void print(char const *p)
	{
		while (*p) {
			lcd.putc(*p);
			p++;
		}
	}
	void printcount()
	{
		char tmp[20];
		char *p = tmp + sizeof(tmp);
		int i, v;
		*--p = 0;
		v = count;
		do {
			int c = digits.get(v % 10);
			*--p = c;
			v /= 10;
		} while (v != 0);
		lcd.cls();
		print(p);
	}
	void run()
	{
		while (1) {
			printcount();
			wait_us(1000000);
			count++;
			led = count & 1;
		}
	}
};


int main()
{
	Test *test = new Test();
	test->run();
}

