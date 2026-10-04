# 🔥 Fire Fighter Robot

An Arduino-based autonomous fire-fighting robot that detects fire using flame sensors, moves toward the detected fire, activates a water pump, aims the water nozzle using a servo motor, and sends an SMS alert through a GSM module.

## Features

- 🔥 Three-direction fire detection
- 🤖 Autonomous robot movement
- 💧 Automatic water pump activation
- 🎯 Servo-controlled water nozzle
- 📱 GSM-based SMS notification
- ⚙️ Adjustable motor speed
- 🖥️ Serial Monitor status messages

## Hardware Requirements

- Arduino Uno
- 3 × Flame/Fire Sensors
- L293D or L298N Motor Driver
- 2 × DC Motors
- Water Pump
- Servo Motor
- GSM Module (SIM800/SIM900 compatible)
- Battery
- Water container
- Robot chassis
- Jumper wires

## Pin Configuration

| Component | Arduino Pin |
|---|---:|
| Left Fire Sensor | D9 |
| Right Fire Sensor | A0 |
| Forward Fire Sensor | D8 |
| Left Motor 1 | D2 |
| Left Motor 2 | D7 |
| Right Motor 1 | D4 |
| Right Motor 2 | D13 |
| Left Motor Speed | D3 |
| Right Motor Speed | D5 |
| Water Pump | A2 |
| Servo Motor | D10 |
| GSM RX | D11 |
| GSM TX | D12 |

## How It Works

The robot continuously reads three fire sensors.

### No Fire

If all sensors report no fire, the robot remains stopped and the water pump stays OFF.

### Fire in Front

If the forward sensor detects fire:

1. The robot moves forward.
2. The water pump turns ON.
3. The servo moves to the center position.
4. An SMS alert is sent.

### Fire on the Left

If the left sensor detects fire:

1. The robot turns left.
2. The water pump turns ON.
3. The servo moves toward the left.
4. An SMS alert is sent.

### Fire on the Right

If the right sensor detects fire:

1. The robot turns right.
2. The water pump turns ON.
3. The servo moves toward the right.
4. An SMS alert is sent.

## GSM Configuration

Before uploading the program, change:

```cpp
String phoneNumber = "+880XXXXXXXXXX";
```

to your own phone number.

**Do not commit your personal phone number to a public GitHub repository.**

## Required Arduino Libraries

- `Servo.h`
- `SoftwareSerial.h`

These libraries are commonly available for Arduino Uno/AVR Arduino boards.

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/fire-fighter-robot.git
cd fire-fighter-robot
```

### 2. Open the project

Open:

```text
FireFighterRobot/FireFighterRobot.ino
```

in the Arduino IDE.

### 3. Select the board

```text
Tools → Board → Arduino Uno
```

### 4. Select the correct port

```text
Tools → Port → Your Arduino Port
```

### 5. Configure the phone number

Update the phone number in the Arduino sketch.

### 6. Upload

Click **Upload** in Arduino IDE.

## Testing

Before testing with real fire:

1. Test each flame sensor individually.
2. Test both motors.
3. Test the water pump separately.
4. Test the servo movement.
5. Test GSM SMS functionality.
6. Test the complete robot with a safe simulated flame source.

## Safety

This project is an educational prototype and is **not a certified fire-safety system**.

Do not test the robot near flammable materials or uncontrolled fire.

Use appropriate electrical protection for the motors, pump, GSM module, and battery.

## Project Structure

```text
fire-fighter-robot/
│
├── FireFighterRobot/
│   └── FireFighterRobot.ino
│
├── .gitignore
├── LICENSE
└── README.md
```

## License

This project is released under the MIT License.

See `LICENSE` for details.

## Author

**Nafis Wadud Ansari**

---

⭐ If you find this project useful, consider giving the repository a star.
