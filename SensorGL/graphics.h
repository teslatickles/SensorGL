#include "glfw3.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "utils.h"
#include <thread>


class SensorGL_GUI {
public:
	SensorGL_GUI();
	std::vector<double> m_circle_positions;

	void set_title(const char* new_title) {
		this->m_window_title = new_title;
	}

	void set_window_size(int win_width = 0, int win_height = 0) {
		if (win_width != 0) 
			this->m_window_width = win_width;
		if (win_height != 0)
			this->m_window_height = win_height;
	}

	// main gui routine
	void gui_th_routine() {
		GLFWwindow* window;
		glfwSetErrorCallback(error_callback);
		if (!glfwInit())
			exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(this->m_window_width, this->m_window_height, this->m_window_title, NULL, NULL);
		if (!window) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);
		while (!glfwWindowShouldClose) {
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;
			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

			// example
			/*glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.6f, 0.f);
			glEnd();
			*/

			// draw circles
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.f, 0.f, 0.f);
			glVertex2f(0.f, 0.f);

			for (int i = 0; i < this->m_circle_positions.size(); i++) {
				glVertex2f(this->m_circle_positions[i], this->m_circle_positions[static_cast<std::vector<double, std::allocator<double>>::size_type>(i) + 1]);
			}
			glEnd();

			// Update displayed frame 
			// by swapping buffers
			glfwSwapBuffers(window);

			// poll for events
			glfwPollEvents();
		}
		glfwDestroyWindow(window);
		glfwTerminate();

		print_ok(SystemType::DISPLAY, "glfw successfully terminated");
		exit(EXIT_SUCCESS);
	}

	std::thread gui_main_th() {
		std::thread gui_th(&gui_th_routine, this);
		return gui_th;
	}

private:
	const char* m_window_title = "SensorGL";
	int m_window_width = 750;
	int m_window_height = 750;

	// Callbacks for glfw
	static void error_callback(int error, const char* description) {
		fputs(description, stderr);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

};
