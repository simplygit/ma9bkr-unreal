param(
    [ValidateSet('KRUnreal', 'KRUnrealEditor')]
    [string]$Target = 'KRUnreal',

    [ValidateSet('Development', 'DebugGame')]
    [string]$Configuration = 'Development',

    [switch]$AllowEditorProcess
)

$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $PSScriptRoot
$uprojectPath = Join-Path $projectRoot 'KRUnreal.uproject'
$engineRoot = 'D:\EpicLibrary\UE_5.7\Engine'
$buildBatPath = Join-Path $engineRoot 'Build\BatchFiles\Build.bat'

if (-not (Test-Path $uprojectPath)) {
    throw "Missing Unreal project file: $uprojectPath"
}

if (-not (Test-Path $buildBatPath)) {
    throw "Missing Build.bat: $buildBatPath"
}

$isEditorTarget = $Target -eq 'KRUnrealEditor'
$runningEditor = Get-Process UnrealEditor -ErrorAction SilentlyContinue

if ($isEditorTarget -and $runningEditor -and -not $AllowEditorProcess) {
    Write-Error "UnrealEditor is currently running. Close the editor before building KRUnrealEditor, or rerun with -AllowEditorProcess if you intentionally want to test the locked-DLL path."
    exit 2
}

$arguments = @(
    $Target,
    'Win64',
    $Configuration,
    $uprojectPath,
    '-WaitMutex',
    '-NoHotReloadFromIDE',
    '-NoUBA',
    '-NoXGE',
    '-MaxParallelActions=1'
)

Write-Host "Building $Target $Configuration"
Write-Host "Project: $uprojectPath"
Write-Host "Engine:  $engineRoot"

& $buildBatPath @arguments
$exitCode = $LASTEXITCODE

if ($exitCode -ne 0) {
    throw "Build failed with exit code $exitCode"
}

Write-Host "Build succeeded."
