#include "precompiled.h"

CSpread gSpread;

void CSpread::ServerActivate()
{
    // Activate Plugin
    //
    // 0 Disabled
    // 1 Enabled
    //
    // Default "1"
    // sc_active "1"
    static cvar_t tActive = {"sc_active", "1", FCVAR_SERVER, 1.0f, NULL};

    // Check if the player is on ground to apply fix
    //
    // 0 Disable Check
    // 1 Enable Check
    //
    // Default "1"
    // sc_ground_check "1"
    static cvar_t tGroundCheck = {"sc_ground_check", "1", FCVAR_SERVER, 1.0f, NULL};

    // Maximum player speed divisor:
    // Checks if the player moves above the speed:
    // Formula of this: PLAYER_VELOCITY <= (WEAPON_MAX_SPEED / sc_max_speed)
    // Weapons Table: https://wiki.alliedmods.net/CS_Weapons_Information
    //
    // > 0.0 (Greater than zero activates the check)
    //
    // Default "2.0"
    // sc_max_speed "2.0"
    static cvar_t tMaxSpeed = {"sc_max_speed", "2.0", FCVAR_SERVER, 2.0f, NULL};

    // Maximum player punch angle while shotting:
    // The first shot always have 0.0 (Zero) of punch angle
    // The second shot have other value deppending each weapon
    // 
    // >= 0.0 (Greater than or equal to zero activates the check)
    // <  0.0 (Less than zero disables checking)
    //
    // Default "2.0"
    // sc_max_punch_angle "2.0"
    static cvar_t tMaxPunchAngle = {"sc_max_punch_angle", "0.0", FCVAR_SERVER, 0.0f, NULL};

    // Spread value applied when all checks has passed
    //
    // >= 0.0 (Greater than or equal to zero enables the adjustment)
    // <  0.0 (Less than zero disables adjustment)
    //
    // Default "0.0"
    // sc_spread "0.0"
    static cvar_t tSpread = {"sc_spread", "0.0", FCVAR_SERVER, 0.0f, NULL};

    g_engfuncs.pfnCVarRegister(&tActive);
    this->m_Active = g_engfuncs.pfnCVarGetPointer(tActive.name);

    g_engfuncs.pfnCVarRegister(&tGroundCheck);
    this->m_GroundCheck = g_engfuncs.pfnCVarGetPointer(tGroundCheck.name);

    g_engfuncs.pfnCVarRegister(&tMaxSpeed);
    this->m_MaxSpeed = g_engfuncs.pfnCVarGetPointer(tMaxSpeed.name);

    g_engfuncs.pfnCVarRegister(&tMaxPunchAngle);
    this->m_MaxPunchAngle = g_engfuncs.pfnCVarGetPointer(tMaxPunchAngle.name);

    g_engfuncs.pfnCVarRegister(&tSpread);
    this->m_Spread = g_engfuncs.pfnCVarGetPointer(tSpread.name);
}

float CSpread::GetSpread(CBaseEntity *pEntity, Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand)
{
    if (this->m_Active)
    {
        if (this->m_Active->value > 0.0f)
        {
            auto Player = static_cast<CBasePlayer*>(pEntity);

            if (Player)
            {
                // If player is not on ground, block spread fix
                if (this->m_GroundCheck)
                {
                    if (this->m_GroundCheck->value > 0.0f)
                    {
                        if (!(Player->pev->flags & FL_ONGROUND))
                        {
                            return vecSpread;
                        }
                    }
                }

                // If player is moving: Block if player speed is greater than: (weapon-max-speed / max-speed-cvar-value)
                if (this->m_MaxSpeed)
                {
                    if (this->m_MaxSpeed->value > 0.0f)
                    {
                        if (Player->pev->maxspeed > 0.0f)
                        {
                            if (Player->pev->velocity.Length2D() > (Player->pev->maxspeed / this->m_MaxSpeed->value))
                            {
                                return vecSpread;
                            }
                        }
                    }
                }

                // If player has fired: Do not remove spread if player is shoting a lot
                if (this->m_MaxPunchAngle)
                {
                    if (this->m_MaxPunchAngle->value >= 0.0f)
                    {
                        if (Player->pev->punchangle.Length2D() > this->m_MaxPunchAngle->value)
                        {
                            return vecSpread;
                        }
                    }
                }

                // Do not remove spred if player is not aimming his weapons like AWP, SCOUT or other
                if (!Player->m_bResumeZoom)
                {
                    if (Player->m_pActiveItem->m_iId == WEAPON_SCOUT || Player->m_pActiveItem->m_iId == WEAPON_SG550 || Player->m_pActiveItem->m_iId == WEAPON_AWP || Player->m_pActiveItem->m_iId == WEAPON_G3SG1)
                    {
                        return vecSpread;
                    }
                }

                // Spread value to return
                if (this->m_Spread)
                {
                    if (this->m_Spread->value >= 0.0f)
                    {
                        return this->m_Spread->value;
                    }
                }
            }
        }
    }

    return vecSpread;
}
