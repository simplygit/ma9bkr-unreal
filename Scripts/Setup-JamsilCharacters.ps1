param(
    [string]$ProjectPath = "F:\workspace_f\KR_unreal\KRUnreal.uproject",
    [string]$EngineEditorPath = "D:\EpicLibrary\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe",
    [string]$PythonScriptPath = "F:\workspace_f\KR_unreal\Scripts\setup_jamsil_characters.py"
)

$runningEditor = Get-Process UnrealEditor -ErrorAction SilentlyContinue
if ($runningEditor) {
    Write-Error "Unreal Editor is currently running. Close the editor before placing prototype characters."
    exit 1
}

if (!(Test-Path -LiteralPath $ProjectPath)) {
    Write-Error "Project file not found: $ProjectPath"
    exit 1
}

if (!(Test-Path -LiteralPath $EngineEditorPath)) {
    Write-Error "UnrealEditor.exe not found: $EngineEditorPath"
    exit 1
}

if (!(Test-Path -LiteralPath $PythonScriptPath)) {
    Write-Error "Python setup script not found: $PythonScriptPath"
    exit 1
}

$arguments = @(
    $ProjectPath
    "-ExecutePythonScript=$PythonScriptPath"
    "-unattended"
    "-nop4"
    "-nosplash"
    "-nosound"
    "-log"
)

$process = Start-Process -FilePath $EngineEditorPath -ArgumentList $arguments -Wait -PassThru -NoNewWindow
$exitCode = $process.ExitCode

if ($exitCode -ne 0) {
    Write-Error "Prototype character placement failed with exit code $exitCode."
    exit $exitCode
}

Write-Host "Prototype character placement completed successfully."
