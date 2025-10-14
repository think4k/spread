<h3 align="center">ReGameDLL_CS Spread Control Plugin</h3>

<p align="center">Control the FireBullets3 function vecSpread parameter</p>

<p align="center">
    <a href="https://github.com/SmileYzn/spread/issues"><img alt="GitHub Issues" src="https://img.shields.io/github/issues-raw/smileyzn/spread?style=flat-square"></a>
    <a href="https://github.com/SmileYzn/spread/actions"><img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/SmileYzn/spread/build.yml?branch=main&label=Build&style=flat-square"></a>
</p>

<hr>

<p align="center">This plugin control the vecSpread variable of FireBullets3 on <a href="https://github.com/rehlds/ReGameDLL_CS/blob/master/regamedll/dlls/cbase.cpp#L1268" target="_blank">cbase.cpp</a></p>
<p align="center">The plugin remove bullet spread on these situations:</p>
<ol>
  <li>Player is on ground.</li>
  <li>Weapon Recoil (Player->pev->punchangle) is zero (The player AIM is centered).</li>
  <li>With the player walking slower than half the maximum speed of the weapon they are carrying</li>
</ol>

<br>

<p align="center">The plugin removed spread from first bullet shots.</p>
<p align="center">It does not affect recoil, nor does it change the default behavior of aim, it just adjusts the insane pattern of shots in the game.</p>
<p align="center">You can use this plugin as replacement for my <a href="https://github.com/smileYzn/accuracyfix" target="_blank">Accuracy Fix Plugin</a>.</p>

<hr>

<details>
  <summary align="center">Spread Control Settings (Click to expand)</summary><br>
    
```
// Activate Plugin
//
// 0 Disabled
// 1 Enabled
//
// Default "1"
sc_active "1"

// Check if the player is on ground to apply fix
//
// 0 Disable Check
// 1 Enable Check
//
// Default "1"
sc_ground_check "1"

// Maximum player speed divisor:
// Checks if the player moves above the speed:
// Formula of this: PLAYER_VELOCITY <= (WEAPON_MAX_SPEED / sc_max_speed)
// Weapons Table: https://wiki.alliedmods.net/CS_Weapons_Information
//
// > 0.0 (Greater than zero activates the check)
//
// Default "2.0"
sc_max_speed "2.0"

// Maximum player punch angle while shotting:
// The first shot always have 0.0 (Zero) of punch angle
// The second shot have other value deppending each weapon
// 
// >= 0.0 (Greater than or equal to zero activates the check)
// <  0.0 (Less than zero disables checking)
//
// Default "2.0"
sc_max_punch_angle "2.0"

// Spread value applied when all checks has passed
//
// >= 0.0 (Greater than or equal to zero enables the adjustment)
// <  0.0 (Less than zero disables adjustment)
//
// Default "0.0"
sc_spread "0.0"

// Weapons blocked from spread control fix
//
// To block weapon: Put 1 on weapon position
// To allow weapon: Put 0 on weapon slot
//
// 0 Not Used
// 1 P228
// 2 GLOCK
// 3 SCOUT
// 4 HEGRENADE
// 5 XM1014
// 6 C4
// 7 MAC10
// 8 AUG
// 9 SMOKEGRENADE
// 10 ELITE
// 11 FIVESEVEN
// 12 UMP45
// 13 SG550
// 14 GALIL
// 15 FAMAS
// 16 USP
// 17 GLOCK18
// 18 AWP
// 19 MP5N
// 20 M249
// 21 M3
// 22 M4A1
// 23 TMP
// 24 G3SG1
// 25 FLASHBANG
// 26 DEAGLE
// 27 SG552
// 28 AK47
// 29 KNIFE
// 30 P90
//
// Default "000000000000000000000000000000"
// sc_weapons_block "000000000000000000000000000000"
```
</details>
