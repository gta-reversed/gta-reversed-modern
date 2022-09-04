#pragma once

/*!
* Various utility commands
*/

auto IsCharInArea2D(CRunningScript& S, CPed& ped, CVector2D a, CVector2D b, bool drawSphere) -> notsa::script::CompareFlagUpdate {
    const auto Check = [&](const auto& e) { return e.IsWithinArea(a.x, a.y, b.x, b.y); };

    if (drawSphere) {
        CTheScripts::HighlightImportantArea(reinterpret_cast<int32>(&S) + reinterpret_cast<int32>(S.m_pCurrentIP), a.x, a.y, b.x, b.y, -100.f);
    }

    return { ped.IsInVehicle() ? Check(*ped.m_pVehicle) : Check(ped) };
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CHAR_IN_AREA_2D, IsCharInArea2D);

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CHAR_PROOFS>() { // 0x2AB
    CollectParameters(6);
    auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam >> 8);
    assert(ped);
    ped->physicalFlags.bBulletProof = ScriptParams[1].uParam;
    ped->physicalFlags.bFireProof = ScriptParams[2].uParam;
    ped->physicalFlags.bExplosionProof = ScriptParams[3].uParam;
    ped->physicalFlags.bCollisionProof = ScriptParams[4].uParam;
    ped->physicalFlags.bMeleeProof = ScriptParams[5].uParam;
    return OR_CONTINUE;
}
