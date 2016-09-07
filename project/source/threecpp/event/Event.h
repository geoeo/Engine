// Simple Event System
// @src: http://bastian.rieck.ru/blog/posts/2015/event_system_cxx11/
#pragma once

class Event {

public:
  virtual~ Event();

  typedef const char* DescriptorType;

  virtual DescriptorType type() const = 0;
};