// This #include statement was automatically added by the Particle IDE.
#include "Thread.h"
#include "ThreadController.h"

// This #include statement was automatically added by the Particle IDE.
#include "ringbuffer.h"

// Include Particle Device OS APIs
#include "Particle.h"
#include "MPU6050.h"



// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

int ledPin = D7;

// MPU variables:
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Ring Buffer:
IntRingBuffer buffer = create_int_ring(50);



//My simple Thread
MyThread thread1 = MyThread();
MyThread thread2 = MyThread();


int i = 0;
// callback for myThread
void callback1(){
	i ++;
	Serial.print("T1: running on ");
	Serial.print(millis());
	Serial.print("\t incrementing i \t");
	Serial.println(i);
}

void callback2(){
    i = i * 2;
	Serial.print("T2: running on ");
	Serial.print(millis());
	Serial.print("\t doubling i \t\t");
	Serial.println(i);
}


void setup() {
    int baud_rate = 9600;

    Wire.begin();
    
    // Initialize Serial for debugging
    Serial.begin(baud_rate);
    
    // Initialize Serial1 to communicate with an external device
    Serial1.begin(baud_rate);  // Baud rate for UART1
    
    Serial.println("Initializing I2C devices...");
    // accelgyro.initialize();

    // Cerify the connection:
    Serial.println("Testing device connections...");
    // Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed")
    
	thread1.onRun(callback1);
	thread1.setInterval(2000);
	
	thread2.onRun(callback2);
	thread2.setInterval(5000);
}



void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // Serial.print("a/g:\t");
    
    // test_ringbuffer();
    
    // Serial.print("ax:\t");
    // Serial.println(ax);
    
    // Put IMU data in ring buffer
    int16_t num_ax = ax;
    // ring_buffer_put(&buffer, ax);
    
    
    // int random_time = random(50,100);
    
    // for (int i = 0; i < random_time; i++){
    //     delay(500);
    // }
    

	if(thread1.shouldRun()) {
	    Serial.println();
	    thread1.run();
	    Serial.println();
	}
	
	if(thread2.shouldRun()) {
	    Serial.println();
	    thread2.run();
	    Serial.println();
	}


    // Serial.print("ay:\t");
    // Serial.println(ay);
    // Serial.print("az:\t");
    // Serial.println(az);
    // Serial.println();


    // Serial.print("Added: ");
    // for (int16_t i = 0; i < 50; i ++) {
    //     ring_buffer_put(&buffer, i);
    //     Serial.print(i);
    //     Serial.print(" ");
    // }
    
    // Serial.println();
    
    // Serial.println("____________DUMPING RING BUFFER________________________________");
    // dumpRingBuffer(&buffer);
    

}

int16_t receiveInt16() {
    while (!Serial1.available()); // Wait
    uint8_t low_byte = Serial1.read();
    while (!Serial1.available()); // Wait
    uint8_t high_byte = Serial1.read();
    int16_t recieved_byte = ((int16_t)high_byte << 8) | low_byte;
    Serial.print("High byte: ");
    Serial.println(high_byte, HEX);
    Serial.print("Low byte: ");
    Serial.println(low_byte, HEX);

    //return low_byte;
    return recieved_byte;

}

void UART_sendInt(int16_t n){
    uint8_t high_byte = (n >> 8) & 0xFF;
    uint8_t low_byte = n & 0xFF;
    Serial1.println(high_byte);
    Serial1.println(low_byte);
}

void test_ringbuffer() {
    Serial.println("Test 1: Initialization");
    IntRingBuffer buffer = create_int_ring(3);
    Serial.print("Buffer capacity: ");
    Serial.println(buffer.capacity);
    Serial.println();

    Serial.println("Test 2: Adding Elements");
    ring_buffer_put(&buffer, 10);
    ring_buffer_put(&buffer, 20);
    ring_buffer_put(&buffer, 30);
    Serial.println();
    
    Serial.println("Test 3: Retrieving Elements");
    Serial.print("Expected: 10, Got: ");
    Serial.println(ring_buffer_get(&buffer));
    Serial.print("Expected: 20, Got: ");
    Serial.println(ring_buffer_get(&buffer));
    Serial.println();

    Serial.println("Test 4: Buffer Wraparound");
    ring_buffer_put(&buffer, 40);
    ring_buffer_put(&buffer, 50);
    

    Serial.print("Expected: 30, Got: ");
    Serial.println(ring_buffer_get(&buffer));

    Serial.print("Expected: 40, Got: ");
    Serial.println(ring_buffer_get(&buffer));
    Serial.println();


    Serial.println("Test 5: Overwrite Old Data");
    ring_buffer_put(&buffer, 60);
    ring_buffer_put(&buffer, 70);
    ring_buffer_put(&buffer, 80); // Should overwrite 50

    Serial.print("Expected: 60, Got: ");
    Serial.println(ring_buffer_get(&buffer));

    Serial.print("Expected: 70, Got: ");
    Serial.println(ring_buffer_get(&buffer));

    Serial.print("Expected: 80, Got: ");
    Serial.println(ring_buffer_get(&buffer));
    Serial.println();

    Serial.println("Tests Completed.");
    free_ring_buffer(&buffer); // Cleanup allocated memory
    
    delay(10);
}


//prints + dumps the buffer
void dumpRingBuffer(IntRingBuffer *buffer) {
    int size = buffer->size;
    for (int i = 0; i < size; i ++) {
        Serial.print(ring_buffer_get(buffer));
        Serial.print(" ");
    }
    Serial.println();
}
