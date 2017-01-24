
Arduino workshop with game



Workshop (45+45 minutes)

Introduction (45m)

10 minutes - explain what is arduino and other electric components: breadboard, uno, led, buttons, wires, resistors, power

10 minutes - brief walkthrough code: variables, algorithms, functions, arduino specific functions, editor

25 minutes - let students assemble board and try to run code and play game, should have enough time to play at least 3 times

Challenges (45m)

15 minutes - ask students to move leds from 4 and 12 to 6 and 10 pins, and adjust code. That will show them how variables, constants and methods could save time.

30 minutes - give several challenges to students, and let them choose ones that are most interested
 - change code, so only 1 player wins always
 - change code, so one player get 2 sec advantage
 - change code, so winning led in not just on, but blinking
 - change code, so that they could play 3 games in 25 seconds
 - change code, so delay is always 3 seconds, and they should close eyes when blinking stops, and press button with closed eyes



Game description. Game is for 2 players to find who have faster reaction. 

When power is connected, leds flash twice, indicating that game is loaded.

Press both buttons, to start game. When leds start blinking fast, release both buttons,.

Leds will go off.

Now when both leds turn on, game is started, and the fastest person to press his button, will win.

When at least one button is pressed, leds will go off for few seconds, and then winner led will be on.

When winning led goes off, game is reset, and again wait when both buttons are pressed.
