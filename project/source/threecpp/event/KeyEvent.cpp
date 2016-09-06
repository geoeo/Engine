#include "KeyEvent.h"

KeyEvent::KeyEvent(int _key, int _scancode, int _action, int _mods) {
  key = _key;
  scancode = _scancode;
  action = _action;
  mods = _mods;
}

KeyEvent::~KeyEvent() {

}