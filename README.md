# EdisonGrove
DCOM4 Networking for Internet of Things
Intel Edison + SeeedStudio Grove shield.

To install git on Edison:
https://github.com/w4ilun/edison-guides/wiki/Installing-Git-on-Intel-Edison

To enable bluetooth (needs to be run every time board is restarted):

rfkill unblock bluetooth
killall bluetoothd (or, more permanently) systemctl disable bluetooth 
hciconfig hci0 up
