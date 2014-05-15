#ifndef _SYSTEM_EVENT_H_
#define _SYSTEM_EVENT_H_

#include <Config.h>

namespace System {

namespace priv
{
    class EventImpl;
}

class Event
	/// An Event is a synchronization object that
	/// allows one thread to signal one or more
	/// other threads that a certain event
	/// has happened.
	/// Usually, one thread signals an event,
	/// while one or more other threads wait
	/// for an event to become signalled.
{
public:
	Event(bool autoReset = true);
		/// Creates the event. If autoReset is true,
		/// the event is automatically reset after
		/// a wait() successfully returns.
		
	~Event();
		/// Destroys the event.

	void set();
		/// Signals the event. If autoReset is true,
		/// only one thread waiting for the event 
		/// can resume execution.
		/// If autoReset is false, all waiting threads
		/// can resume execution.

	void wait();
		/// Waits for the event to become signalled.

	void wait(long milliseconds);
		/// Waits for the event to become signalled.
		/// Throws a TimeoutException if the event
		/// does not become signalled within the specified
		/// time interval.

	bool tryWait(long milliseconds);
		/// Waits for the event to become signalled.
		/// Returns true if the event
		/// became signalled within the specified
		/// time interval, false otherwise.

	void reset();
		/// Resets the event to unsignalled state.
	
private:
	Event(const Event&);
	Event& operator = (const Event&);

private:
	priv::EventImpl * myEventImpl;
};


} // namespace System


#endif // _SYSTEM_EVENT_H_
