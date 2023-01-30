#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

//#include "glad/glad.h"
#include "glfw3.h"

//#define FREEGLUT_STATIC
//#define _LIB
//#define FREEGLUT_LIB_PRAGMAS 0

//#include "GL/freeglut.h"

// esp32 includes
//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>
//#include <driver/adc.h>

// Window dimensions
//const int kWindowWidth = 500;
//const int kWindowHeight = 500;

// Potentiometer position
//double pot_position = 0;

// Vector to store circle positions
std::vector<double> circle_positions;

//adc1_channel_t adc_channel
double read_pot_position() {
	//// Read the value of the potentiometer
	//int pot_value = adc1_get_raw(adc_channel);

	//// Convert the value to a position between 0 and 1
	//double position_percent = pot_value / 4095.0;

	//// Output the position
	//printf("Potentiometer position: %f\n", position_percent);

	//// Sleep for a short period of time
	//vTaskDelay(100 / portTICK_PERIOD_MS);

	//return position_percent;

	// for testing
	std::cout << "reading potentiometer position" << std::endl;
	return 180.0;
	
}

void potentiometer_th() {
	//adc1_channel_t adc_channel = adc_init();
	//while (1) {
	//	pot_position = read_pot_position(adc_channel);

	//	// clear circle svg positions
	//	circle_positions.clear();

	//	// calculate new circle positions based on pot position
	//	for (int i = 0; i < 360; i += 15) {
	//		// convert angle from degrees to radians
	//		double angle = i * M_PI / 180;

	//		// calculate the x/y coords of circle per pot position and angle
	//		circle_positions.push_back(pot_position * cos(angle));
	//		circle_positions.push_back(pot_position * sin(angle));
	//	}

	//	// brief sleep to allow other threads to run
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//}
}

void perform_other_tasks() {
	while (1) {
		// Perform other tasks here
		std::cout << "Performing other tasks" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Display() {
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the circles
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);

	// draw updates on circles based on circle_positions
	for (int i = 0; i < circle_positions.size(); i += 2) {
		glVertex2f(circle_positions[i], circle_positions[i + 1]);
	}
	glEnd();

	// Swap buffers to display frame
	glutSwapBuffers();
}

enum class SystemType {
	ADC, 
	DISPLAY
};

void print_ok(SystemType system_type) {
	std::string msg_container;
	switch (system_type)
	{
	case SystemType::ADC:
		msg_container = "ADC initialization: OK!";
		break;
	case SystemType::DISPLAY:
		msg_container = "DISPLAY initialization: OK!";
		break;
	default:
		msg_container = "SystemType was not found!";
		break;
	}
	std::cout << msg_container << std::endl;
}

void glut_init(int argc, char** argv) {
	// Init Glut and set up window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutCreateWindow("SensorGL");

	// Register Display callback
	glutDisplayFunc(Display);
	glutIdleFunc(Display);

	// Glut init is okay
	print_ok(SystemType::DISPLAY);
}

//adc1_channel_t 
void adc_init() {
	//// Set ADC channel for potentiometer
	//const adc1_channel_t pot_channel = ADC1_CHANNEL_6;

	//// Initialize the ADC
	//adc1_config_width(ADC_WIDTH_BIT_12);
	//adc1_config_channel_atten(pot_channel);

	// Init is okay
	print_ok(SystemType::ADC);
}

int main(int argc, char** argv) {
	// init glut for display
	glut_init(argc, argv);

	// start the pot thread
	std::thread adc_thread(potentiometer_th);
	
	// start main GUI loop
	glutMainLoop();
	print_ok(SystemType::DISPLAY);

	// wait for adc thread to finish
	adc_thread.join();

	return 0;
}