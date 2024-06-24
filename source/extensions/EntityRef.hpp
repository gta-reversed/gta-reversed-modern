#pragma once

namespace notsa {
//! Wrapper for entity references, avoids manual usage of `CleanupOldRef` and `RegisterRef`
template<typename T>
struct EntityRef {
    EntityRef(T* ptr = nullptr) :
        m_Ptr{ ptr }
    {
        if (m_Ptr) {
            m_Ptr->RegisterReference(reinterpret_cast<CEntity**>(&m_Ptr));
        }
    }

    ~EntityRef() {
        if (m_Ptr) {
            m_Ptr->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_Ptr));
        }
    }

    // No need for moving/copying the class itself, but just the pointer directly to it's new address
    // (This way we avoid extra calls to `CleanUpOld/RegisterReference`...)
    EntityRef<T>& operator=(EntityRef&&) = delete;
    EntityRef<T>& operator=(const EntityRef&) = delete;
    EntityRef(EntityRef<T>&&) = delete;
    EntityRef(const EntityRef<T>&) = delete;

    // This is the only magic we need
    EntityRef<T>& operator=(T* ptr) {
        if (m_Ptr) {
            m_Ptr->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_Ptr));
        }
        m_Ptr = ptr;
        if (m_Ptr) {
            m_Ptr->RegisterReference(reinterpret_cast<CEntity**>(&m_Ptr));
        }
        return *this;
    }

    T* Get()              { return m_Ptr; }
    const T* Get()  const { return m_Ptr; }

    operator T*()   const { return m_Ptr;  }
    operator T*()         { return m_Ptr;  }

    T* operator->() const { return m_Ptr;  }
    T* operator->()       { return m_Ptr;  }

    T& operator*()  const { return *m_Ptr; }
    T& operator*()        { return *m_Ptr; }

    T* operator&()  const { return &m_Ptr; }
    T* operator&()        { return &m_Ptr; }

private:
    T* m_Ptr;
};
VALIDATE_SIZE(EntityRef<int>, sizeof(int*));
}; // namespace notsa
