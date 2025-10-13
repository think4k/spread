#pragma once

class CSpread
{
public:
    void ServerActivate();

    float GetSpread(CBaseEntity *pEntity, Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand);

    cvar_t* m_Active = nullptr;
    cvar_t* m_GroundCheck = nullptr;
    cvar_t* m_MaxSpeed = nullptr;
    cvar_t* m_MaxPunchAngle = nullptr;
    cvar_t* m_Spread = nullptr;
};

extern CSpread gSpread;
