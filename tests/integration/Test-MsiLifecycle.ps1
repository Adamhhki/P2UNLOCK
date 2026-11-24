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

function Wait-ForServiceStatus {
    param(
        [string]$Name,
        [System.ServiceProcess.ServiceControllerStatus]$Status,
        [int]$TimeoutSeconds = 30
    )

    $deadline = [DateTime]::UtcNow.AddSeconds($TimeoutSeconds)
    do {
        $service = Get-Service -Name $Name -ErrorAction Stop
        if ($service.Status -eq $Status) {
            return
        }
        Start-Sleep -Milliseconds 500
    } while ([DateTime]::UtcNow -lt $deadline)

    $service = Get-Service -Name $Name -ErrorAction Stop
    throw "Service '$Name' did not reach '$Status' within $TimeoutSeconds seconds; current status is '$($service.Status)'"
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
    Wait-ForServiceStatus -Name $serviceName -Status Running

    Stop-Service -Name $serviceName -Force -ErrorAction Stop
    Wait-ForServiceStatus -Name $serviceName -Status Stopped
    Start-Service -Name $serviceName -ErrorAction Stop
    Wait-ForServiceStatus -Name $serviceName -Status Running

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
    $service = Get-Service -Name $serviceName -ErrorAction SilentlyContinue
    if ($service -and $service.Status -ne 'Stopped') {
        Stop-Service -Name $serviceName -Force -ErrorAction Stop
        Wait-ForServiceStatus -Name $serviceName -Status Stopped
    }
}
