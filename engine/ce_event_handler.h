
#ifndef _CE_EVENT_HANDLER_H_
#define _CE_EVENT_HANDLER_H_

#include <SDL_events.h>

namespace ce {
	class IEventHandler {
	private:
	public:
		virtual void onEvent(SDL_Event& event)=0;
	};
}

#endif // _CE_EVENT_HANDLER_H_
