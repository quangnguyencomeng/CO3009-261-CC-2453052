param([string]$Toolchain = 'C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\14.2 rel1\bin')
$ErrorActionPreference = 'Stop'
$project = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$out = Join-Path $project 'Build'
New-Item -ItemType Directory -Force -Path $out | Out-Null
$gcc = Join-Path $Toolchain 'arm-none-eabi-gcc.exe'
$copy = Join-Path $Toolchain 'arm-none-eabi-objcopy.exe'
$size = Join-Path $Toolchain 'arm-none-eabi-size.exe'
$includes = @('Core/Inc','Drivers/STM32F1xx_HAL_Driver/Inc','Drivers/STM32F1xx_HAL_Driver/Inc/Legacy','Drivers/CMSIS/Device/ST/STM32F1xx/Include','Drivers/CMSIS/Include') | ForEach-Object { '-I' + (Join-Path $project $_) }
$flags = @('-mcpu=cortex-m3','-mthumb','-std=gnu11','-Os','-ffunction-sections','-fdata-sections','-DUSE_HAL_DRIVER','-DSTM32F103x6') + $includes
$sources = @(Get-ChildItem (Join-Path $project 'Core/Src') -Filter '*.c') + @(Get-ChildItem (Join-Path $project 'Drivers/STM32F1xx_HAL_Driver/Src') -Filter '*.c') + @(Get-Item (Join-Path $project 'Core/Startup/startup_stm32f103c6tx.s'))
$objects = @()
foreach ($source in $sources) {
  $obj = Join-Path $out ($source.BaseName + '.o')
  & $gcc @flags -c $source.FullName -o $obj
  if ($LASTEXITCODE -ne 0) { throw "Compile failed: $($source.Name)" }
  $objects += $obj
}
$elf = Join-Path $out 'Lab03_TrafficLight_Fitted.elf'
$hex = Join-Path $out 'Lab03_TrafficLight_Fitted.hex'
$maparg = '-Wl,-Map=' + (Join-Path $out 'Lab03_TrafficLight_Fitted.map')
& $gcc '-mcpu=cortex-m3' '-mthumb' '-Wl,--gc-sections' $maparg '-T' (Join-Path $project 'STM32F103C6TX_FLASH.ld') @objects '-specs=nano.specs' '-specs=nosys.specs' -o $elf
if ($LASTEXITCODE -ne 0) { throw 'Link failed' }
& $copy -O ihex $elf $hex
if ($LASTEXITCODE -ne 0) { throw 'HEX conversion failed' }
& $size $elf
Write-Output $hex
