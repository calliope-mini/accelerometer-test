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

MicroBit uBit;

void onFreeFall(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT F");
    uBit.display.print("F");
}

void on2G(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT 2G");
    uBit.display.print("2");
}

void on3G(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT 3G");
    uBit.display.print("3");
}

void on6G(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT 6G");
    uBit.display.print("6");
}

void on8G(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT 8G");
    uBit.display.print("8");
}

void onShake(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT SHAKE");
    uBit.display.print("S");
}

void onFaceUp(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT +");
    uBit.display.print("+");
}

void onFaceDown(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT -");
    uBit.display.print("-");
}

void onTiltUp(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT UPSIDE");
    uBit.display.print("U");
}

void onTiltDown(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT UPSIDE DOWN");
    uBit.display.print("D");
}

void onTiltLeft(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT TILTED LEFT");
    uBit.display.print("L");
}

void onTiltRight(MicroBitEvent event) {
    (void) event;
    uBit.radio.datagram.send("EVENT TILTED RIGHT");
    uBit.display.print("R");
}


int main(void) {
    uBit.init();
    uBit.serial.baud(115200);
    uBit.serial.send("Calliope Accelerometer Test v1.0\r\n");

    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FREEFALL, onFreeFall);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_2G, on2G);
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

    uBit.radio.enable();
    uBit.radio.setTransmitPower(7);
    uBit.radio.setGroup(0b01100110);
    uBit.radio.datagram.send("ACCEL TEST START");
    uint16_t lastGesture = 0;
    while (1) {
        uint16_t g = uBit.accelerometer.getGesture();
        if (lastGesture != g) {
            switch (g) {
                case MICROBIT_ACCELEROMETER_EVT_NONE:
                    break;
                case MICROBIT_ACCELEROMETER_EVT_FREEFALL:
                    uBit.radio.datagram.send("LAST F");
                    printf("FREEFALL\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_2G:
                    uBit.radio.datagram.send("LAST 2G");
                    printf("2G\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_3G:
                    uBit.radio.datagram.send("LAST 3G");
                    printf("3G\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_6G:
                    uBit.radio.datagram.send("LAST 6G");
                    printf("6G\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_8G:
                    uBit.radio.datagram.send("LAST 8G");
                    printf("8G\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_SHAKE:
                    uBit.radio.datagram.send("LAST S");
                    printf("S\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_FACE_UP:
                    uBit.radio.datagram.send("LAST +");
                    printf("+\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_FACE_DOWN:
                    uBit.radio.datagram.send("LAST -");
                    printf("-\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_TILT_UP:
                    uBit.radio.datagram.send("LAST U");
                    printf("U\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_TILT_DOWN:
                    uBit.radio.datagram.send("LAST D");
                    printf("D\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_TILT_LEFT:
                    uBit.radio.datagram.send("LAST L");
                    printf("L\r\n");
                    break;
                case MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT:
                    uBit.radio.datagram.send("LAST R");
                    printf("R\r\n");
                    break;
            }
            lastGesture = g;
        }
        uBit.sleep(1);
    }
}