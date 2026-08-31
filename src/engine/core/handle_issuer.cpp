#include "engine/core/handle_issuer.hpp"


namespace engine::core {
    HandleIssuer::Handle::Handle(HandleIssuer& parent_alloc, int id) : parent(&parent_alloc), id(id) {}
    HandleIssuer::Handle::~Handle() {parent->free(*this);}

    HandleIssuer::Handle::Handle(Handle&& other) noexcept : parent(other.parent), id(other.id) {
        other.id = -1;
    }

    HandleIssuer::Handle& HandleIssuer::Handle::operator=(Handle&& other) noexcept {
        if (this != &other) {
            std::swap(parent, other.parent);
            std::swap(id, other.id);
        }
        return *this;
    }

    void HandleIssuer::free(const Handle& handle) {
        if (handle.id == -1)
            return;

        oldFreeHandles.push_back(handle.id);
    }

    HandleIssuer::Handle HandleIssuer::getUniqueHandle() {
        if (!oldFreeHandles.empty()) {
            int id = oldFreeHandles.back();
            oldFreeHandles.pop_back();

            return Handle{*this, id};
        }

        nextFreeHandle++;
        return Handle{*this, nextFreeHandle - 1};
    }
}
