# Gender-Bias-Negetive-Comment-Detector-and-Intelligent-System-using-8051-microprocessor
Ever felt put down by a gender biased or negetive comment?Let's use our intelligent system as indicator to warn you so that we can win over the trolls from ignorance.

It is build using the following procedure:

1)Data is collected from a twitter API/A static database used to save tweets got from a social media handle

2)The data after using sentiment analysis technique is refined to categorize it as an appropriate comment or not. According to the polarity there is a column in an additional column added to the database which is in binary form(1 indicates appropriate, 0 indicates inappropriate). That data is serailly fetched 

3)Based on the got input the C program in keil is able to send a message to the hardware component whose output is displayed in the simulator in proteus. A red led lights up if there is a warning and details are displayed on the LCD

4)Using the serial input you can control the switching on of the LCD or lights in your room. Which makes it an overall intelligent room for your comfort.

