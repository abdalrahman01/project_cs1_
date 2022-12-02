big name_ Menu.c


printMenu:
    set home address to menu screen 
    
    plotWord(0,0, "1: login")
    plotWord(0,3, "2: start")



plotWord:
    set address pointer x y 
    printword("2: start")





mian:
    listen to key (like a while loop):
        store value from pressed_key()
            be careful: set a delay!!

    go(pressed_key) 