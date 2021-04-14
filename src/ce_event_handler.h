#pragma once

#include <SDL_events.h>

namespace ce {
	class IEventHandler {
	 public:
		virtual void onEvent(SDL_Event& event) = 0;
	};
}
