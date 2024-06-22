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
