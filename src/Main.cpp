#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Color {
	float r;
	float g;
	float b;
	float alpha;

	bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && alpha == other.alpha;
	}

	static Color random() {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

		return Color{distrib(gen), distrib(gen), distrib(gen), 1.0f};
	}
};

template <typename T>
T lerp(T a, T b, float t) {
	return a + t * (b - a);
}

int main()
{
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	int width = 640;
	int height = 480;

	GLFWwindow* window = glfwCreateWindow(width, height, "Graphics Engine", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, width, height);

	float startTime = glfwGetTime();
	float duration = 2.0f;

	Color fromColor = Color::random();
	Color toColor = Color::random();

	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		float t = (currentTime - startTime) / duration;
		if (t > 1.0f) t = 1.0f;

		float r = lerp(fromColor.r, toColor.r, t);
		float g = lerp(fromColor.g, toColor.g, t);
		float b = lerp(fromColor.b, toColor.b, t);

		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

		if (t >= 1.0f) {
			fromColor = toColor;
			toColor = Color::random();
			startTime = glfwGetTime();
		}

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
