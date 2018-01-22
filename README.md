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

Power up the Arduino and upload __MoistureSensorTest.ino__ to it. Open up the Arduino IDE and from the tools menu select __Serial Monitor__. If everything has been set up correctly, the window which opens will display a reading from the sensor which is updated every few seconds. If the monitor displays nonsensical symbols instead of human-readable text, make sure that the baud rate for the monitor matches what is set in the code: using the vanilla code, set to __9600__ Bd.

In order to be sure that the sensor is working proper, after you have begun to see readings from it, slowly add water to the plant. Pour carefully, taking care to not splash the sensor directly. Gradually the reading from the sensor should *decrease* in value.
