# Prototyping Methodology for Engineering Design

### Final Report: Immersive Skateboard

The **Immersive Skateboard** prototype was developed to provide an immersive skateboarding experience without the need for a real skateboard or specific location. The goal was to make skateboarding more accessible by simulating it in a controlled environment, combining user physical movements with technology to deliver an engaging experience. This prototype allows users to control a small skateboard through their movements, using sensors and motors for realistic feedback and movement.

Initially, user acceleration was detected using an accelerometer connected to an Arduino Uno, focusing on capturing movement in the Z-axis. Based on this data, the direction of movement—forward or backward—was determined by analyzing acceleration trends over short time intervals. To enhance the interaction, an LED matrix was added to provide visual feedback, indicating the direction of movement and whether the user was stationary.

A servo motor was then employed to drive a small skateboard in response to user input. The motor's rotation direction depended on whether the user moved forward or backward, and it was adjusted to ensure a natural response. The prototype was completed with a custom-made box to house the Arduino and related components, making the system portable and easy to attach to the user's body.

Moving forward, the prototype will be improved to incorporate both Y and Z-axis movements, which will enable it to replicate more advanced skateboard tricks. Additionally, future versions will account for acceleration intensity, providing even more responsive and realistic skateboarding control.

#### Equipment and Tools Used
- **Arduino Uno**
- **Accelerometer**
- **LED 8×8 Matrix**
- **Servo Motor**
- **MakerBot Replicator 2X**
