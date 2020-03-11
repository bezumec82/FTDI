Set-Variable -Name FTDI_LIB -Value "d:\Libraries\FTDI\lib\Static\amd64"
Set-Variable -Name FTDI_INC -Value "d:\Libraries\FTDI\include"

Set-Item -Path Env:Path -Value ($FTDI_LIB + ";" + $Env:Path)
Set-Item -Path Env:Path -Value ($FTDI_INC + ";" + $Env:Path)