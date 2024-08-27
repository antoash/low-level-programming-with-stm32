#include "gpioInit.h"
#include "button.h"
#include "main.h"

int main() {

	gpioInit();

	while(1){

		button();

	}

}



