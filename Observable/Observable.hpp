#ifndef __Observable_HPP__
#define __Observable_HPP__

#include <functional>
#include <vector>
#include <unordered_map>
#include <utility> // std::forward

template <typename Event>
class Observable
{
	typedef std::function<void ()> VoidCallback;
	typedef std::vector<VoidCallback> VoidCallbackVec;

	std::unordered_map<Event, VoidCallbackVec> 	_observers;

public:

	template <typename Observer>
	void registerObserver(const Event& event, Observer&& observer) {
		_observers[event].push_back(std::forward<Observer>(observer));
	}

	template <typename Observer>
	void registerObserver(Event&& event, Observer&& observer) {
		_observers[std::move(event)].push_back(std::forward<Observer>(observer));
	}

	void notify(const Event& event) const {
		/*
			const T &std::map::at( const Key& key ) const;
			Available since c++11 allow us to change notify with a const version.
		*/
		for (const auto& obs : _observers.at(event))
			obs();
	}
};

#endif
