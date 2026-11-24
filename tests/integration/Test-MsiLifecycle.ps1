param(
    [Parameter(Mandatory = $true)]
    [string]$MsiPath
)

$ErrorActionPreference = 'Stop'
$serviceName = 'PSeriesService'
$resolvedMsi = (Resolve-Path -LiteralPath $MsiPath).Path
$logRoot = Join-Path $env:TEMP ('PSeriesNative-Msi-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $logRoot | Out-Null

function Invoke-Msi {
    param([string]$Arguments)
    $log = Join-Path $logRoot ('msi-' + [guid]::NewGuid() + '.log')
    $result = Start-Process -FilePath "$env:SystemRoot\System32\msiexec.exe" `
        -ArgumentList "/i `"$resolvedMsi`" /qn /norestart $Arguments /l*v `"$log`"" `
        -Wait -PassThru
    if ($result.ExitCode -ne 0) {
        throw "MSI operation failed with exit code $($result.ExitCode). Log: $log"
    }
}

try {
    Write-Host 'Fresh installation'
    Invoke-Msi ''

    $exe = Join-Path ${env:ProgramFiles} 'PSeries Native\PSeriesService.exe'
    if (-not (Test-Path -LiteralPath $exe)) {
        throw "PSeriesService.exe was not installed"
    }

    $service = Get-Service -Name $serviceName -ErrorAction Stop
    if ($service.StartType -ne 'Automatic') {
        throw "Expected Automatic startup; found $($service.StartType)"
    }

    Stop-Service -Name $serviceName -Force -ErrorAction Stop
    Wait-Service -Name $serviceName -Status Stopped -Timeout 30
    Start-Service -Name $serviceName -ErrorAction Stop
    Wait-Service -Name $serviceName -Status Running -Timeout 30

    Write-Host 'Repair'
    $repairLog = Join-Path $logRoot 'repair.log'
    $repair = Start-Process -FilePath "$env:SystemRoot\System32\msiexec.exe" `
        -ArgumentList "/fa `"$resolvedMsi`" /qn /norestart /l*v `"$repairLog`"" `
        -Wait -PassThru
    if ($repair.ExitCode -ne 0) { throw "Repair failed with exit code $($repair.ExitCode)" }
    if (-not (Test-Path -LiteralPath $exe)) { throw "Repair did not restore PSeriesService.exe" }

    Write-Host 'Uninstall'
    $uninstallLog = Join-Path $logRoot 'uninstall.log'
    $uninstall = Start-Process -FilePath "$env:SystemRoot\System32\msiexec.exe" `
        -ArgumentList "/x `"$resolvedMsi`" /qn /norestart /l*v `"$uninstallLog`"" `
        -Wait -PassThru
    if ($uninstall.ExitCode -ne 0) { throw "Uninstall failed with exit code $($uninstall.ExitCode)" }

    if (Get-Service -Name $serviceName -ErrorAction SilentlyContinue) {
        throw 'Service registration remains after uninstall'
    }
    if (Test-Path -LiteralPath $exe) {
        throw 'PSeriesService.exe remains after uninstall'
    }

    Write-Host 'Reinstall'
    Invoke-Msi ''
    if (-not (Get-Service -Name $serviceName -ErrorAction SilentlyContinue)) {
        throw 'Reinstallation did not register PSeriesService'
    }
}
finally {
    try {
        if (Get-Service -Name $serviceName -ErrorAction SilentlyContinue) {
            Stop-Service -Name $serviceName -Force -ErrorAction SilentlyContinue
        }
    } catch {}
}
