# Jamsil Character Placement

## Summary

- Source character FBX: `F:\workspace_f\KR_trunk\Assets\03_Arts\FBX\Character\player_low.FBX`
- Unreal character destination: `/Game/Characters/Prototype`
- Target map: `/Game/Maps/Stadiums/L_Jamsil_Prototype`

## Placement Set

- `Pitcher`
- `Catcher`
- `Batter`
- `FirstBase`
- `SecondBase`
- `ThirdBase`
- `ShortStop`
- `LeftField`
- `CenterField`
- `RightField`

## Execution

- PowerShell entry point: `F:\workspace_f\KR_unreal\Scripts\Setup-JamsilCharacters.ps1`
- Python setup script: `F:\workspace_f\KR_unreal\Scripts\setup_jamsil_characters.py`

Run:

```powershell
& 'F:\workspace_f\KR_unreal\Scripts\Setup-JamsilCharacters.ps1'
```

## Notes

- This pass uses a single generic player skeletal mesh to make the baseball formation visible in the editor.
- Labels are spawned above every actor so position names are easy to spot in the viewport.
- The current coordinates assume the stadium origin is near home plate. If the lineup is offset, the next pass should derive exact transforms from the Unity stadium scene.
- Resulting assets:
  - `/Game/Characters/Prototype/player_low`
  - `/Game/Maps/Stadiums/L_Jamsil_Prototype`
