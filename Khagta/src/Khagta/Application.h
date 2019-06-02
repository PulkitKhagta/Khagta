#pragma once

#include "Core.h"

namespace Khagta
{
	class KHAGTA_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
