#pragma once

#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <functional>

#include "Event.h"

class Dispatcher {

public:

  typedef std::function< void( const Event& ) > SlotType;

  void subscribe( const Event::DescriptorType& descriptor, SlotType&& slot );

  void notify( const Event& event ) const;

private:

  std::map< Event::DescriptorType, std::vector<SlotType> > _observers;
};