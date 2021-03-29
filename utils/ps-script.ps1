$fileNames = Get-ChildItem -Path "your_audio_files location" -Recurse -Include *.wav
foreach($file in $fileNames ){
 Write-Host  $file.FullName
 .\your_ad4_location\AD4CONVERTER.EXE -E4 $file

}