/**
 * Simple accelerometer test which waits for events to happen and displays them on the console
 * as well as sending it to a remote data logger via radio.
 *
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 *
 * Licensed under the Apache Software License 2.0 (ASL 2.0)
 */

#include <MicroBit.h>
#include <BMX055Accelerometer.h>

MicroBit uBit;

void onFreeFall(MicroBitEvent event) {
    (void) event;
    uBit.display.print("F");
}

void on2G(MicroBitEvent event) {
    (void) event;
    uBit.display.print("2");
}

void on3G(MicroBitEvent event) {
    (void) event;
    uBit.display.print("3");
}

void on6G(MicroBitEvent event) {
    (void) event;
    uBit.display.print("6");
}

void on8G(MicroBitEvent event) {
    (void) event;
    uBit.display.print("8");
}

void onShake(MicroBitEvent event) {
    (void) event;
    uBit.display.print("S");
}

void onFaceUp(MicroBitEvent event) {
    (void) event;
    uBit.display.print("+");
}

void onFaceDown(MicroBitEvent event) {
    (void) event;
    uBit.display.print("-");
}

void onTiltUp(MicroBitEvent event) {
    (void) event;
    uBit.display.print("U");
}

void onTiltDown(MicroBitEvent event) {
    (void) event;
    uBit.display.print("D");
}

void onTiltLeft(MicroBitEvent event) {
    (void) event;
    uBit.display.print("L");
}

void onTiltRight(MicroBitEvent event) {
    (void) event;
    uBit.display.print("R");
}

void onUpdate(MicroBitEvent event) {
    (void) event;

    static int cnt = 1;
    static int x = 0;
    static int y = 0;
    static int z = 0;

    x = (x + uBit.accelerometer.getX()) / cnt;
    y = (y + uBit.accelerometer.getY()) / cnt;
    z = (z + uBit.accelerometer.getZ()) / cnt;
    if (++cnt > 100) {
        cnt = 1;
        uBit.serial.send("C = [x=");
        uBit.serial.send(x);
        uBit.serial.send(", y=");
        uBit.serial.send(y);
        uBit.serial.send(", z=");
        uBit.serial.send(z);
        uBit.serial.send("]\r\n");
    }

}

int main(void) {
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Calliope Accelerometer Test v1.0\r\n");

    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FREEFALL, onFreeFall);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_3G, on3G);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_6G, on6G);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_8G, on8G);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_SHAKE, onShake);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FACE_UP, onFaceUp);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FACE_DOWN, onFaceDown);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_UP, onTiltUp);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_DOWN, onTiltDown);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT, onTiltLeft);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT, onTiltRight);
//    uBit.messageBus.listen(MICROBIT_ID_ACCELEROMETER, MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE, onUpdate);


//    new MicroBitAccelerometerService(*uBit.ble, uBit.accelerometer);
    while (1) {
        uBit.sleep(100);
    }
}