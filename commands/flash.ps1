Get-ChildItem -Path .\ -Filter "*.rxe" -File -Name| ForEach-Object {
    _flash $_
}