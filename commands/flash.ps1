Get-ChildItem -Path .\ -Filter "*.rxe" -File -Name| ForEach-Object {
    flash $_
}