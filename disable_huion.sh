ID=$(xinput list | grep "HUION PenTablet Pen" | awk '{ print $6 }' | sed "s/id=//g")

echo xinput set-prop $ID "Device Enabled" 0 
xinput set-prop $ID "Device Enabled" 0 
