# EdisonGrove
DCOM4 Networking for Internet of Things
Intel Edison + SeeedStudio Grove shield.

To install git on Edison:
https://github.com/w4ilun/edison-guides/wiki/Installing-Git-on-Intel-Edison

To enable bluetooth (needs to be run every time board is restarted):

1. rfkill unblock bluetooth
2. killall bluetoothd (or, more permanently) systemctl disable bluetooth 
3. hciconfig hci0 up
