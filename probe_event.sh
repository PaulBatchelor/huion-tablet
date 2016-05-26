#cat /dev/input/by-id/usb-HUION_PenTablet-event-mouse | xxd -c 28 -g 1
# 32000 x 24000 resolution 
cat /dev/input/by-id/usb-HUION_PenTablet-event-mouse | xxd -c 24 -g 1 | awk -d' ' -f parse.awk
