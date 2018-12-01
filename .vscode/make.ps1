# NeXTTool.exe
$tool = "c:/cygwin64/nexttool/NeXTTool.exe";

# Delete pre-existing binary
if (Test-Path ./NXT.rxe) {
    rm ./NXT.rxe;
}

# Build
echo "Compiling files..."

$out = make all 2>&1;
if ($out -match "Error") {
   echo "Errors were encountered in the file.";
   echo $out;
   rm NXT.rxe;
   exit 1;
}

# If build was a success, flash firmware.
if (Test-Path ./NXT.rxe) {
    echo "NXT.rxe successfully generated.";
    $size = (Get-Item ./NXT.rxe).length
    echo "NXT.rxe size: $size"

    $name = & $tool /COM=usb -getname;
    if ($name -eq "YAYER") {
        Start-Process -Wait ./rxeflash.sh;
        echo "Flashing complete.";
    } else {
        echo "Flashing failed.";
    }

} else {
    echo "Compilation failed.";
}