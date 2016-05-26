# huion-tablet
Making sounds / things with my new Huion 680s tablet

Current files:
- disable_huion.sh: disable the huion tablet as a pointer devcie
- enable_huion.sh: enable the huion tablet as a pointer device
- parse.awk: used to experiment and parse binary data with probe_event.sh. Somewhat useful information in the comments
- probe_event.sh: parses the the 24-byte input events of tablet. gets many parameters liklike absolute position, buttons, and pressure. "Advanced" mode.
- probe_mouse.sh: version of the tablet in "mouse" mode... a 3-byte protocol. "Friendly" mode.
