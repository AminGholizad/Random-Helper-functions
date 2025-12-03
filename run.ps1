param (
    [string]$BuildType = "Debug"
)

.\build.ps1 -BuildType $BuildType -Tests
if ($LASTEXITCODE -eq 0){
    Set-Location -Path "build"
    ctest --output-on-failure
    Set-Location -Path ".."
#.\build\RandomHelperTests.exe
}
