#include "main.h"
#include "pwmInit.h"
#include "gpioInit.h"

int main() {

	gpioInit();
	pwmInit();

	while(1);
}
