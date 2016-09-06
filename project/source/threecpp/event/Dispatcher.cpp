#include "Dispatcher.h"

void Dispatcher::subscribe( const Event::DescriptorType& descriptor, SlotType&& slot ) {
  _observers[descriptor].push_back( slot );
}

void Dispatcher::notify( const Event& event ) const {
  auto type = event.type();

  // // Ignore events for which we do not have an observer (yet).
  // if( _observers.find( type ) == _observers.end() ) {
  //   return;
  // }

  // auto&& observers = _observers.at( type );

  // for( auto&& observer : observers ) {
  //   observer( event );
  // }

  for (auto const& x : _observers) {
    std::string key = x.first;
    if (strcmp(key.data(), type) == 0) {
      for( auto&& observer : x.second ) {
        observer( event );
      }
    }
  }
}