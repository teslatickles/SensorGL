#include <iostream>
#include <thread>

#include "graphics.h"
#include "utils.h"

class AnalogToDigital {
public:
	AnalogToDigital();

	void adc_th_routine(SensorGL_GUI gui) {
		const double M_PI = 3.145654;
		while (1) {
			pot_position = read_pot_position();

			// start fresh
			gui.m_circle_positions.clear();

			for (int i = 0; i < 360; i += 15) {
				// convert angle -- degrees to radians
				double angle = i * M_PI / 180;

				gui.m_circle_positions.push_back(pot_position * cos(angle));
				gui.m_circle_positions.push_back(pot_position * sin(angle));
			}
		}
		print_ok(SystemType::ADC, "adc thread exited successfully");
	}

	std::thread adc_main_th(SensorGL_GUI gui) {
		std::thread adc_thread(&adc_th_routine, gui);
		return adc_thread;
	};

private:
	double pot_position = 0;
	const adc1_channel_t pot_channel = ADC1_CHANNEL_6;

	void adc_init() {
		// Initialize the ADC
		adc1_config_width(ADC_WIDTH_BIT_12);
		adc1_config_channel_atten(pot_channel);

		// Init is okay
		print_ok(SystemType::ADC);
	}

	double read_pot_position() {
		print_ok(SystemType::ADC);

		int pot_value = adc1_get_raw(adc_channel);

		double pot_position_percent = pot_value / 4095.0;

		printf("Potentiometer position: %f\n", pot_position_percent);

		vTaskDelay(100 / portTICK_PERIOD_MS);

		return pot_position_percent;
	}
};
