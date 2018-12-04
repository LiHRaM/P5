param($1)
if ($1 -eq $null) {
    echo "Error:    No file set to flash."
    echo "          Example: flash nxt.rxe"
    exit 1;
} else {
    echo "Making $1..."
}
docker run --rm -v ${pwd}:/home/nxt/code/ lihram/nxt-cross-compiler make $1