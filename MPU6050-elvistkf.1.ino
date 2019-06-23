#include "I2Cdev.h" //I2C Device Library
#include "MPU6050.h" //use one of the sub-libraries inside the “i2cdevlib”, namely the MPU6050 library
#include "Wire.h" //establish i2c communication with the MPU6050 module

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t roll_a, pitch_a;
int16_t roll = 0, pitch = 0;

void setup() {
    Wire.begin();

    // Initialize serial communication
    // Remember to set your computer's baud rate to 9600 as well
    Serial.begin(9600);

    // Initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // Verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
    // Read raw accel/gyro measurements from device and save them in ax, ay, az, gx, gy, gz
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // These methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    
    Serial.print("ax ay az: ");
    Serial.print(ax);
    Serial.print(" ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.println(az);
    
    Serial.print("gx gy gz: ");
    Serial.print(gx);
    Serial.print(" ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.println(gz);

    // Calculate the Euler's Angle using accelerometer
    roll_a = (atan2(-ay, az)*180.0)/M_PI;
    pitch_a = (atan2(ax, sqrt(ay*ay + az*az))*180.0)/M_PI;

}
