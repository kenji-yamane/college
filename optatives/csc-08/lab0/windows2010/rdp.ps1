Set-ItemProperty -Path
'HKLM:\System\CurrentControlSet\Control\Terminal Server' -name
"fDenyTSConnections" -value 0
Enable-NetFirewallRule -DisplayGroup "Remote Desktop"
Set-TimeZone 'E. South America Standard Time'
