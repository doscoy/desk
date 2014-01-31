#include <cstdio>

#include <glfw3.h>
#pragma comment(lib, "glfw3.lib")

namespace platform {
class Window {
public:
    Window() {
        glfwInit();
        window_ = glfwCreateWindow(960, 640, "my wind", nullptr, nullptr);
        if (!window_) {
            return;
        }

        glfwSetWindowUserPointer(window_, this);
        glfwSetMouseButtonCallback(window_, mouseButtonCallbackImpl);

        glfwSwapInterval(1);
        glfwMakeContextCurrent(window_);

        // GLFWÇÃÉnÉìÉhÉãÇ…é©ï™é©êgÇìoò^
        glfwSetWindowUserPointer(window_, this);
    }

    ~Window() {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

public:
    void update() {
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    bool isActive() const {
        if (!window_) {
            return false;
        }

        return !glfwWindowShouldClose(window_);
    }

private:
    static void mouseButtonCallbackImpl(GLFWwindow* window, const int button, const int action, const int mods) {
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        win->mouseButtonCallback();
    }

    void mouseButtonCallback() {
        printf("click.");
    }


private:
    GLFWwindow* window_;
};

}   // namespace platform


int main(int argc, char* argv[]) {
    platform::Window win;

    while (win.isActive()) {
        win.update();
    }
	return 0;
}


