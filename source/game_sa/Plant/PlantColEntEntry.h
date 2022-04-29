#pragma once

class CEntity;
class CPlantLocTri;

class CPlantColEntEntry {
public:
    CEntity*           m_Entity;
    CPlantLocTri**     m_Objects;
    uint16             m_numTriangles;
    CPlantColEntEntry* m_Prev;
    CPlantColEntEntry* m_Next;

public:
    CPlantColEntEntry* AddEntry(CEntity* entity);
    void ReleaseEntry();
};
VALIDATE_SIZE(CPlantColEntEntry, 0x14);
