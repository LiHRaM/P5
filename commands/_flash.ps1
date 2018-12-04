param($1)
if ($1 -eq $null) {
    echo "Error:    No file set to flash."
    echo "          Example: flash nxt.rxe"
    exit 1;
} else {
    echo "Flashing NXT with: $1..."
}
if ((& "$env:ROOT/NeXTTool.exe" /COM=usb -getname) -eq "YAYER") {
    cmd /C "$env:ROOT/NeXTTool.exe /COM=usb -delete=$1"
    cmd /c "$env:ROOT/NeXTTool.exe /COM=usb -download=$1"
    cmd /c "$env:ROOT/NeXTTool.exe /COM=usb -listfiles=$1"
    echo "Flashing complete.";
} else {
    echo "Flashing failed.";
}