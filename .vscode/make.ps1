# NeXTTool.exe
$tool = "../NeXTTool.exe";

# Delete pre-existing binary
if (Test-Path ./NXT.rxe) {
    rm ./NXT.rxe;
}

# Build
echo "Compiling files..."

# Use a docker container to compile the program
# Name: nxtOSEKCompiler
# docker start nxtOSEKCompiler
docker run --rm -v ${pwd}:/home/nxt/code lihram/nxt-cross-compiler make all;
if ($out -match "Error") {
   echo "Errors were encountered in the file.";
   echo $out;
   rm ./NXT.rxe;
   exit 1;
}

# If build was a success, flash firmware.
if (Test-Path ./NXT.rxe) {
    echo "NXT.rxe successfully generated.";
    $size = (Get-Item NXT.rxe).length
    echo "NXT.rxe size: $size"
    if ((& $tool /COM=usb -getname) -eq "YAYER") {
        if (!(Test-Path ./NeXTTool.exe)) {
            Copy-Item -Path $tool -Destination ./NeXTTool.exe
        }
        cmd /c "NeXTTool.exe /COM=usb -download=NXT.rxe"
        cmd /c "NeXTTool.exe /COM=usb -listfiles=NXT.rxe"
        echo "Flashing complete.";
    } else {
        echo "Flashing failed.";
    }

} else {
    if (Test-Path ./NXT.rxe) {
        rm ./NXT.rxe;
    }
    echo "Compilation failed.";
}