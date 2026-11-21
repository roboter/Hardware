$ErrorActionPreference = "Stop"

$MakeExe   = "C:/Users/robby/.embeetle/beetle_tools/gnu_make_4.2.1_64b/make.exe"
$ToolPfx   = "C:/Users/robby/.embeetle/beetle_tools/gnu_riscv_xpack_toolchain_10.2.0_1.2_64b/bin/riscv-none-embed-"
$FlashTool = "C:/Users/robby/.embeetle/beetle_tools/openocd_wch_0.11.0_dev02415_32b/bin/openocd.exe"
$BuildDir  = Join-Path $PSScriptRoot "build"

& $MakeExe flash -C $BuildDir -f ../config/makefile "TOOLPREFIX=$ToolPfx" "FLASHTOOL=$FlashTool"
exit $LASTEXITCODE
