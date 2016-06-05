{
# pressure is last two bytes when $20 == 18
# y is last two bytes when $20 == 1
# x is last two bytes when $20 == 0
    # Pressure
    # if ($18 == 3 && $20 == 18) {
    # y axis
    #if ($18 == 3 && $20 == 1) {
    # x axis
    # if ($18 == 3 && $20 == 0) {

    # mouse press on/off tablet hits page
    # if ($18 == 1 && $20 == "4a") {
   
    # buttom button kind of? 
    # if ($18 == 1 && $20 == "4b") {

    # both buttons when the pen is down
    if ($18 == 1 && $20 == "4c") {
    #if ($18 != 3 && $18 != 0) {
        #for(i = 22; i < 24; i++) printf $(i) " "
        print $23 $22
        printf "\n"
    }
}
