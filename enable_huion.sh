ID=$(xinput list | grep "HUION PenTablet Pen" | awk '{ print $6 }' | sed "s/id=//g")

xinput set-prop $ID "Device Enabled" 1 
