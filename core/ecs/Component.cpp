#include "Component.hpp"

void Component::setEnabled(bool flag) {
    enabled = flag;

    if (flag)
        onEnable();
    else
        onDisable();
}

bool Component::isEnabled() const {
    return enabled;
}