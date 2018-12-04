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
make all;
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
    flash

} else {
    if (Test-Path ./NXT.rxe) {
        rm ./NXT.rxe;
    }
    echo "Compilation failed.";
}