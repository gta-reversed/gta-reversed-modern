class CTaskComplexGetOnBoatSeat {

public:
    static void InjectHooks();

    CTaskComplexGetOnBoatSeat(CVehicle* veh);
    ~CTaskComplexGetOnBoatSeat();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GET_ON_BOAT_SEAT;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x649210
    CTaskComplexGetOnBoatSeat* Constructor(CVehicle* veh) {
        this->CTaskComplexGetOnBoatSeat::CTaskComplexGetOnBoatSeat(veh);
        return this;
    }

    // 0x649280
    CTaskComplexGetOnBoatSeat* Destructor() {
        this->CTaskComplexGetOnBoatSeat::~CTaskComplexGetOnBoatSeat();
        return this;
    }
};
