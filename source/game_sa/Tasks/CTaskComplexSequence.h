#pragma once
#include "CTaskComplex.h"

class CTask;
    
class CTaskComplexSequence : public CTaskComplex
{
public:
    int m_nCurrentTaskIndex;         // Used in m_aTasks
    CTask* m_aTasks[8];
    int    m_bRepeatSequence;        // it's either 1 or 0. Sequence will loop if set to 1
    int    m_nSequenceRepeatedCount; // m_nSequenceRepeatedCount simply tells us how many times the sequence has been repeated.
                                     // If m_bRepeatSequence is true, this can be greater than 1, 
                                     // otherwise it's set to 1 when the sequence is done executing tasks.
    bool m_bFlushTasks;
    char field_39;
    char field_3A;
    char field_3B;
    unsigned char m_nReferenceCount; // count of how many CTaskComplexUseSequence instances are using this sequence
};

VALIDATE_SIZE(CTaskComplexSequence, 0x40);