#include "Tailor.h"
#include <string> 
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// LEARN HOW TO RENDER TEXT https://learnopengl.com/In-Practice/Text-Rendering

#pragma region static definitios
#define LOGGING_ENABLED false
#define ZERO 0.0f
#define COLOR_BLACK 0.0f, 0.0f, 0.0f
#define COLOR_WHITE 1.0f, 1.0f, 1.0f
#define COLOR_RED 1.0f, 0.0f, 0.0f
#define COLOR_GREEN 0.0f, 1.0f, 0.0f
#define COLOR_BLUE 0.0f, 0.0f, 1.0f
#define COLOR_CYAN 0.f, 1.f, 1.f
#define COLOR_MAGENTA 1.f, 0.f, 1.f
#define COLOR_YELLOW 1.f, 1.f, 0.f
#pragma endregion

using namespace std;

float window_ratio;

#pragma region logging
void console_log(string msg)
{
	if (!LOGGING_ENABLED) return;
	msg.append("\n");
	fprintf(stdout, msg.c_str());
}

void console_error(string msg)
{
	if (!LOGGING_ENABLED) return;
	msg.append("\n");
	fprintf(stderr, msg.c_str());
}
#pragma endregion

bool is_right_arrow_pressed{ false };
bool is_left_arrow_pressed{ false };
bool is_top_arrow_pressed{ false };
bool is_bottom_arrow_pressed{ false };

#pragma region event handlers
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	string msg{ "" };

	msg.append("Key Event: ");

	if (action == GLFW_PRESS) {
		msg.append("PRESS ");

		if (key == 265) is_top_arrow_pressed = true;
		if (key == 264) is_bottom_arrow_pressed = true;
		if (key == 263) is_left_arrow_pressed = true;
		if (key == 262) is_right_arrow_pressed = true;
	}

	if (action == GLFW_RELEASE) {
		msg.append("RELEASE ");

		if (key == 265) is_top_arrow_pressed = false;
		if (key == 264) is_bottom_arrow_pressed = false;
		if (key == 263) is_left_arrow_pressed = false;
		if (key == 262) is_right_arrow_pressed = false;
	}

	msg.append(to_string(key));

	console_log(msg);
}

void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	string msg{ "" };

	msg.append("Mouse Button Event: ");

	if (action == GLFW_PRESS) {
		msg.append("PRESS ");
	}

	if (action == GLFW_RELEASE) {
		msg.append("RELEASE ");
	}

	msg.append(to_string(button));

	console_log(msg);
}

void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

#pragma endregion

#pragma region cool ways to draw polygons
void draw_cool_triangle()
{
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glColor3f(COLOR_RED);
	glVertex3f(-0.6f, -0.35f, ZERO);

	glColor3f(COLOR_GREEN);
	glVertex3f(0.6f, -0.35f, ZERO);

	glColor3f(COLOR_BLUE);
	glVertex3f(0.f, 0.65f, ZERO);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(COLOR_MAGENTA);
	glVertex3f(-0.6f, 0.35f, ZERO);

	glColor3f(COLOR_CYAN);
	glVertex3f(0.6f, 0.35f, ZERO);

	glColor3f(COLOR_YELLOW);
	glVertex3f(0.f, -0.65f, ZERO);
	glEnd();
}

void draw_cool_squares() {
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor3f(COLOR_RED);
	glVertex3f(-0.5f, -0.5f, ZERO);

	glColor3f(COLOR_GREEN);
	glVertex3f(-0.5f, 0.5f, ZERO);

	glColor3f(COLOR_BLUE);
	glVertex3f(0.5f, 0.5f, ZERO);

	glColor3f(COLOR_YELLOW);
	glVertex3f(0.5f, -0.5f, ZERO);
	glEnd();

	glRotatef(180.0f + 45, 0.f, 0.f, 1.f);
	glBegin(GL_POLYGON);
	glColor3f(COLOR_RED);
	glVertex3f(-0.5f, -0.5f, ZERO);

	glColor3f(COLOR_GREEN);
	glVertex3f(-0.5f, 0.5f, ZERO);

	glColor3f(COLOR_BLUE);
	glVertex3f(0.5f, 0.5f, ZERO);

	glColor3f(COLOR_YELLOW);
	glVertex3f(0.5f, -0.5f, ZERO);
	glEnd();
}

#pragma endregion

void draw_rect(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	GLfloat scale{ 1000 };

	x /= scale;
	y /= scale;
	width /= scale;
	height /= scale;

	y *= -1;
	x -= window_ratio;
	y += 1;

	GLfloat x1{ x };
	GLfloat y1{ y };

	GLfloat x2{ x + width };
	GLfloat y2{ y - height };

	glBegin(GL_POLYGON);
	
	glVertex3f(x1, y1, ZERO);
	glVertex3f(x2, y1, ZERO);
	glVertex3f(x2, y2, ZERO);
	glVertex3f(x1, y2, ZERO);

	glEnd();
}

GLfloat character_speed{ 20.0f };
GLfloat character_x{ 100.0f };
GLfloat character_y{ 400.0f };

void little_game() {	
	if (is_right_arrow_pressed) character_x += character_speed;
	if (is_left_arrow_pressed) character_x -= character_speed;	
	if (is_bottom_arrow_pressed) character_y += character_speed;
	if (is_top_arrow_pressed) character_y -= character_speed;

	glColor3f(COLOR_CYAN);
	draw_rect(character_x, character_y, 200.0f, 200.0f);
}

void draw()
{
	

	//draw_cool_triangle();
	draw_cool_squares();
	//draw_rect(10.0f, 10.0f, 200.0f, 200.0f);
	
	//little_game();
}

#pragma region startup
int main()
{
	if (!glfwInit())
	{
		console_error("Failed to initialize GLFW3");
		return -1;
	}

	glfwSetErrorCallback(glfw_error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	int window_width{ 720 };
	int window_height{ 720 };

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Tailor", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		console_error("Failed to create Window");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_callback);
	glClearColor(COLOR_BLACK, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwGetFramebufferSize(window, &window_width, &window_height);
		window_ratio = window_width / (float)window_height;
		glViewport(0.0f, 0.0f, window_width, window_height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-window_ratio, window_ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

#pragma endregion