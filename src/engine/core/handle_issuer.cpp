#include "engine/core/handle_issuer.hpp"


namespace engine::core {
    Handle::Handle(HandleIssuer& parent_alloc, int id) : parent(&parent_alloc), id(id) {}
    Handle::~Handle() {parent->free(*this);}

    Handle::Handle(Handle&& other) noexcept : parent(other.parent), id(other.id) {
        other.id = -1;
    }

    Handle& Handle::operator=(Handle&& other) noexcept {
        if (this != &other) {
            std::swap(parent, other.parent);
            std::swap(id, other.id);
        }
        return *this;
    }

    bool Handle::operator==(const Handle& other) const {
        return parent == other.parent && id == other.id;
    }

    std::size_t hash_value(const Handle& p)  {
        std::size_t seed = 0;
        boost::hash_combine(seed, p.parent);
        boost::hash_combine(seed, p.id);
        return seed;
    }


    void HandleIssuer::free(const Handle& handle) {
        if (handle.id == -1)
            return;

        oldFreeHandles.push_back(handle.id);
    }

    Handle HandleIssuer::getUnique() {
        if (!oldFreeHandles.empty()) {
            int id = oldFreeHandles.back();
            oldFreeHandles.pop_back();

            return Handle{*this, id};
        }

        nextFreeHandle++;
        return Handle{*this, nextFreeHandle - 1};
    }
}
