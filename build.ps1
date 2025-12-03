param (
    [string]$BuildType = "Debug",
    [switch]$Tests
)

# Create build directory if needed
if (-not (Test-Path "build")) {
    New-Item -Path "build" -ItemType Directory | Out-Null
}

Set-Location -Path "build"

# Construct cmake configure command
$cmakeArgs = @(
    ".."
    "-DCMAKE_BUILD_TYPE=$BuildType"
)

# Add tests if requested
if ($Tests) {
    $cmakeArgs += "-DRH_BUILD_TESTS=ON"
} else {
    $cmakeArgs += "-DRH_BUILD_TESTS=OFF"
}

# Configure
cmake @cmakeArgs

# Build
cmake --build .

Set-Location -Path ".."
