#include "graphics.h"
#include <thread>
#include "pot.h"

int main() {
	// start main graphics thread
	SensorGL_GUI* gui = &SensorGL_GUI{};
	std::thread gui_th = gui->gui_main_th();

	// start adc thread
	AnalogToDigital* adc = &AnalogToDigital{};
	std::thread adc_th = adc->adc_main_th(*gui);

	// wait on threads
	gui_th.join();
	adc_th.join();

	return 0;
}
