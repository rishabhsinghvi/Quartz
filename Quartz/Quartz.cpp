#include "Application.h"

#include<memory>

int main()
{
	auto quartzApp = std::make_unique<Quartz::Application>();
	
	quartzApp->init();

	quartzApp->run();

	return 0;
}