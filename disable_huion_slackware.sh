xinput list | grep "HUION" | cut -f 2 |\
    awk -F '=' '{ system("xinput set-prop " $2 " \"Device Enabled\" 0")}' 
