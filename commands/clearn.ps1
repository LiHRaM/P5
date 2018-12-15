if ((& "$env:ROOT/NeXTTool.exe" /COM=usb -getname) -eq "YAYER") {
    cmd /c "$env:ROOT/NeXTTool.exe /COM=usb -clear"
    echo "Clearing complete.";
} else {
    echo "Clearing failed.";
}