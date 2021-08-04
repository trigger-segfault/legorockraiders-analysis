|Property                    |Type     |Notes            |
|:---------------------------|:--------|:----------------|
|`Main::DynamiteWakeRadius`  | `float` | default: `0.0`  |
|`Main::Clear`               | `bool`  | default: `true` |
|`Main::Panels`              | `bool`  | default: `true` |
|`Main::MiniFigureRunAway`   | `float` | default: `10.0` |
|`Main::DrainTime`           | `float` | default: `10.0*25.0`<br>mult: `25.0` |
|`Main::ReinforceHits`       | `int`   | default: `4`    |
|`Main::MaxReturnedCrystals` | `int`   | default: `10`   |
| | | |
|`Levels::_::Seed`           | `int`   | non-zero        |
|`Levels::_::AIMap`          | `path`  |                 |
|`Levels::_::EListFile`      |*(unused)*|                |
|`Levels::_::IntroAVI`       | `path`  |                 |
|`Levels::_::StartFP`        | `bool`  | default: `false`|
|`Levels::_::NoDrain`        | `bool`  | default: `false`|
|`Levels::_::UpgradeTime`    | `float` | mult: `25.0`<br>affects all obj types|
|`Levels::_::MinifigureUpgradeTime`|`float`|mult: `25.0`<br>non-zero|
|`Levels::_::VehicleUpgradeTime`|`float`|mult: `25.0`<br>non-zero|
|`Levels::_::BuildingUpgradeTime`|`float`|mult: `25.0`<br>non-zero|
|`Levels::_::TrainTime`      | `float` | mult: `25.0`    |
|`Levels::_::BuildingTolerance`|`float`| default: `6.0`  |
|`Levels::_::BuildingMaxVariation`|`float`|default: `4.0`|
|`Levels::_::DragBoxRGB`     | `Color` |                 |
|`Levels::_::MaxStolen`      | `int`   |                 |
|`Levels::_::Slug`           |**RockMonsterType**|       |
|`Levels::_::SlugTime`       | `float` | default: `60.0*25.0`<br>mult: `25.0`<br>requires: `Slug`|
|`Levels::_::InitialSlugTime`| `float` | default: `60.0*25.0`<br>mult: `25.0`<br>requires: `Slug`|
|`Levels::_::InitialCrystals`| `int`   |                 |
|`Levels::_::InitialOre`     | `int`   |                 |
|`Levels::_::Precreate`      | `bool`  | default: `false`<br>pre-allocates 10 Pilot Mini-Figures, and then destroys them|
| | | |
|`Stats::_::BuildingBase`    | **Name**| unused: would lookup name in table, but table is empty|
|`Stats::_::Flocks_OnGround` | `bool`  | default: `false`|
|`Stats::_::Flocks_QuickDestroy`|`bool`| default: `false`|
|`Stats::_::Flocks_AnimateByPitch`|`bool`|default: `false`|
|`Stats::_::Unselectable`    | `bool`  | default: `false`|
|`Stats::_::NeedsPilot`      | `bool`  | default: `false`<br>Override required training *((only if driver?)*|
|`Stats::_::Flocks_AttackTime`|`float` | default: `300.0`|



<!-- |Property                    |Type     |Notes            |
|:---------------------------|:--------|:----------------|
**Lego\*::Main::**
```
DynamiteWakeRadius   | float | default: 0.0   |
Clear                | bool  | default: true  |
Panels               | bool  | default: true  |
MiniFigureRunAway    | float | default: 10.0  |
DrainTime            | float | default: 10.0*25.0 | mult: 25.0 |
ReinforceHits        | int   | default: 4     |
MaxReturnedCrystals  | int   | default: 10    |
```
**Lego\*::Levels::\_::**
```
Seed                 | int   | non-zero       |
AIMap                | path  |                |
EListFile            |*(unused)*|             |
IntroAVI             | path  |                |
StartFP              | bool  | default: false |
NoDrain              | bool  | default: false |
UpgradeTime          | float | mult: 25.0     | notes: affects all object types|
MinifigureUpgradeTime| float | mult: 25.0 | non-zero|
VehicleUpgradeTime   | float | mult: 25.0 | non-zero|
BuildingUpgradeTime  | float | mult: 25.0 | non-zero|
TrainTime            | float | mult: 25.0     |
BuildingTolerance    | float | default: 6.0   |
BuildingMaxVariation | float | default: 4.0   |
DragBoxRGB           | Color |                |
MaxStolen            | int   |                |
Slug                 |**RockMonsterType**|    |
SlugTime             | float | default: 60.0*25.0 | mult: 25.0 | requires: Slug|
InitialSlugTime      | float | default: 60.0*25.0 | mult: 25.0 | requires: Slug|
InitialCrystals      | int   |                |
InitialOre           | int   |                |
Precreate            | bool  | default: false | notes: pre-allocates 10 Pilot Mini-Figures, and then destroys them |
```
**Lego\*::Stats::\_::**
```
BuildingBase         |**Name**| unused: would lookup name in table, but table is always empty |
Flocks_OnGround      | bool  | default: false |
Flocks_QuickDestroy  | bool  | default: false |
Flocks_AnimateByPitch| bool  | default: false |
Unselectable         | bool  | default: false |
NeedsPilot           | bool  | default: false | notes: override required training *(only if driver?)* |
Flocks_AttackTime    | float | default: 300.0 |
``` -->
