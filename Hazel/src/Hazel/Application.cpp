#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			// TODO: Can not directly use HZ_TRACE(e) and don't find the reason yet.
			HZ_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			HZ_TRACE(e.ToString());
		}
		while (true);
	}
}