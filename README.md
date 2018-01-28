# AutoWater
AutoWater is a project which automates watering a potted plant by measure soil moisture levels using a capciative moisture sensor. If the water levels are beneath a threshold, AutoWater will trigger a normally-closed solenoid valve, pumping water into the pot.

## Ingredients
In order to begin this project you will need:
- __Arduino Uno__ or compatible board, with a __9v power supply__ (1)
- __TIP 120 transistor__ (1)
- __1N4007 Diode__ (1)
- __1k Ohm Resistor__ (1)
- [__Analog Capacitive Soil Moisture Sensor v1.0__](https://www.dfrobot.com/wiki/index.php/Capacitive_Soil_Moisture_Sensor_SKU:SEN0193) (1)
- __Breadboard__ (1)
- __Jumper wires__ (10+)
- __Alligator clamps__ (2)
- __Solenoid Valve__ (1)
- __Plastic tubing__ (10 feet)
- __Potted plant__ (1)

## Reading the moisture sensor
The first step is to set up the moisture sensor and get a reading off of it. In the tests directory, there is a file which can be used to run the test -- __MoistureSensorTest.ino__

Place the moisture sensor carefully in the potted plant, leaving the wire section exposed. Notice that on the sensor there is a horizontal white line: *do not submerge the sensor beyond this line*, as it is possible to damage the sensor if the top gets wet. Ideally place the sensor such that the dirt level is approximately __1 inch__ below this.

Take three jumper wires (1 red, 1 black, 1 blue). Match them to the same colors coming off of the sensor. Run the red wire into the __5v__ pin on the Arduino: this will provide power to the sensor. Next run the blue wire to the __Analog 0__ pin, and the black wire to the ground pin (labeled __GND__).

### Moisture Sensor diagram
Here is a diagram showing the connections between the Arduino and the moisture sensor:

![Moisture Sensor Diagram](https://github.com/eindiran/AutoWater/blob/master/diagrams/MoistureSensorDiagram.png)

### Testing the moisture sensor
Plug in the Arduino to your computer, then open the __Arduino IDE__ and upload __MoistureSensorTest.ino__ to it. If you get permissions issues and can't upload it, look up the error message it spits out. Likely you will need to run a command like "__sudo chmod a+rw /dev/ttyACM0__", which will allow everyone (including yourself) to write to the device.

Once you have successfully uploaded the file to the board, from the __Tools__ menu of the IDE, select __Serial Monitor__. If everything has been set up correctly, the window which opens will display a reading from the sensor which is updated every few seconds. If the monitor displays nonsensical symbols instead of human-readable text, make sure that the baud rate for the monitor matches what is set in the code: using the vanilla code, set to __9600__ Bd.

In order to be sure that the sensor is working proper, after you have begun to see readings from it, slowly add water to the plant. Pour carefully, taking care to not splash the sensor directly. Gradually the reading from the sensor should *decrease* in value.

### Calibrate moisture sensor (optional)
This step is optional, depending on the accuracy you want the moisture sensor to report human-readable moistures with (e.g. "75% Humidity").

To calibrate your moisture sensor, follow the steps above to set it up for testing. In addition you will need a glass of water. First, dry off the moisture sensor entirely. Then fire up __MoistureSensorTest.ino__, and record the value that the sensor reports while held outside of any soil, in the air. Write down this value, which will be used as the 0% Humidity value.

Next, submerge the sensor up to the horizontal line in the glass of water. After the readings stabilize, write down the number, as this will be used as the 100% Humidity value.

Once we've captured these two values, open up the Arduino IDE, as we are going to make some small changes to the code. First find a global variable named __DEBUG__. It is set to 0. Change the value to __1__. Next, find the variables __AIR_VALUE__ and __WATER_VALUE__. Change the value for the first from 1000 to the number you recorded when calibrating the moisture sensor in the air, then change the second from 200 to the value you recorded in the cup of water. Finally, we need to make the interval correct. Find the variable __INTERVAL__; you need to set this value to (AIR_VALUE - WATER_VALUE)/4. Originally the variable was set like so: (1000 - 200)/4 = 800/4 = 200. Note that you should round the result to an integer.

Save the code and re-upload it to the Arduino. Re-run the test in the air, water and soil, and see what values you get. Now you should see lines like "*Humidity: >50%*" in the output, which indicates that the humidity is >50 % and <75 % of __WATER_VALUE__.
