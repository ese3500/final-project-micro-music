[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# Micro-Music - Differentiated Music Box 





    * Team Name: Micro Music
    * Team Members: Nhlanhla Mavuso and Tim Liang
    * Github Repository URL: https://github.com/orgs/ese3500/teams/micro-music
    * Github Pages Website URL: [for final submission]
    * Description of hardware: AtMega328PB, Microphone, Speaker, 64 X 32 LED Matrix, ESP32, Artix-7 Nexys Video FPGA

![image](https://github.com/ese3500/final-project-micro-music/assets/141350627/6d1c46c9-b75c-4a31-94e2-a3871cc74250)

## Final Project Proposal

### 1. Abstract

Micro Music is a group at the University of Pennsylvania that produces the most capable music recorder with an amplifier and playback speaker, that is interfaced with a multicolored LED matrix for sound visualization. Micro-music is committed in providing the best music sampling, amplification, and playback using the cutting edge FPGA and Microcontroller Technology. A user can choose to record any sounds in 16 banks, which they can choose to play at the same time.  Enhance your music listening experience with Micro Music! We have designed a highly-differentiated music box with state of the art music production capablities.  The device uses a microphone to sample sound from a user, and use  Digital Signal Processing (DSP) embedded in an FPGA and Cooley-Tukey Fast Fourier Transform in the Atmega 328PB microcontroller to sample the sound into frequency and amplitude. The music box uses an amplifier to play back the sound through two speakers. In addition to sound playback, we also show a visualization of the sound through an LED matrix. 

### 2. Motivation

Micro-music is deeply invested in improving the recording, playback, and visualization capababilities at a very low cost, to provide music producers the ability to produce any music of their choice without the burden of cost and energy usage. Using a low-powered ATMEGA328PB microcontroller and a 7-series FPGA, we are confident in our ability to improve and shape the recording, playback, and visualization opportunities in the music industry.


### 3. Goals

These are to help guide and direct your progress.

<ol>
   <li>Record music and play it back through headphones or speakers</li>
   <li>Provide music visualization features through LED Matrix</li>
   <li>Ensure the device is cheap and portable</li>
   <li>Ensure the device is user-friendly by making the buttons, and knobs very intuitive to use</li>
</ol>

### 4. Software Requirements Specification (SRS)

#### Overview

The software processes the input audio signals from the microphone and ouput the signals through the LED matrix and speakers. It also allows the music to be stored music in any of the 16 banks of a DRAM. The software allows the user to change the visualization color and mode using interrupt buttons. 
#### Users

Our target users are music producers who want to enhance their music production experiences. Anyone who is interested in listening to music, recording, and audio visualization will find our product a close companion. 

#### Definitions and Abbreviations

ADC - Analog to Digital Converter

#### Functionality

The program takes an input audio data via UART from a device (Field Programmable Gate Array) that can sample audio from a microphone with amplifier at a rate of 44.1 kHz. We test the functionality  using serial print to a computer to make sure the right data is being sent.

The program takes the input only when a pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this). 

The program sends the amplitude and frequency data from the sampling device to an ESP32 via a UART. We test this using serial print to a computer to make sure the right data is being sent. Then, the ESP32 acts a peripheral memory device that drive the 2048 LEDs using an amplitude and frequency it recieved from an ATMEGA328PB. The program have options for visualization, including just lines for signals and a sine wave. This is tested visually (by inspecting the output of the LED Matrix).

The program outputs the amplitude and frequency data to a speaker using a timer in fast PWM mode, where OCR1A register controls the frequency and OCR1B register controls the duty cycle (frequency). This is tested audibly (from the sound of the speakers).

The program has a GPIO pin change interrupt for a switch, which determines the visualization mode being displayed. This is also tested visually output of the LED Matrix).

Switch debouncing is implemented in software and tested using an oscilloscope.

### 5. Hardware Requirements Specification (HRS)

#### Overview

The hardware components converts audio anlog signals into electrical signals and electrical signals into audio signals. The hardware includes an LED Matrix for the user to visualize the audio data. Finally, the hardware includes interactive components such as switches and a potentiometer so the users can adjust volume and change visualization modes.

#### Definitions and Abbreviations

#### Functionality

The project is based on the AtMega328PB microcontroller.

The microphone is used to convert audio signals into electrical signals, which will be sampled by an FPGA and sent via UART to the ATMEGA328PB.

The speaker is used to convert the PWM signal generated by the AtMega328PB into audio signals. A potentiometer knob is used to adjust the speaker's volume.

An LED Matrix is used to create a 2D screen where the audio signals can be visualized via the LEDs lighting up.

The ESP32 chip communicates via UART to the AtMega328PB and drives the 2D screen.

Switches are used to take user input for selecting visualization mode.

### 6. MVP Demo

What do you expect to accomplish by the first milestone?

By the first milestone, had all the necessary components ordered. This includes the microphone, speaker, LED Matrix, and other components like a knob for volume control. We also hoped to have implemented real-time audio visualization by the first milestone. In other words, audio signals were expected to be able to be played through the speaker and visualized through the LED matrix. Additionally, we hoped to have implemented audio sampling. Also, we expected to have obtained a container that can house all the circuitry.

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

By the final demonstration, we expected to have implemented the audio recording and playback features. This allowed the user to press a button to start recording, play audio into the microphone of the device, and then stop recording and playback the audio. The ESP32 received audio data from the AtMega328PB and drove to the LED Matrix. We also expected to have fitted all the components (MCU, speaker, microphone, LED strips, circuit parts) into the container with all the user interaction parts (knobs, sensors, and LED light strips) integrated for the user to easily use. We were able to achieve all this by Final Demo day. 

### 8. Methodology

First, we outline our design in both software and hardware. For software, we discuss how each feature is implemented using software. For example, for recording audio, we establish that we use an interrupt service routine triggered by a button press to start the recording process. We also define how the software in the AtMega328PB interface with peripherals. This required reading the datasheets of the various peripherals we have sourced and discussing how the AtMega can properly interface with them using polling/interrupts or serial communication. For hardware, drew a circuit schematic outlining all the wire connections between the AtMega328PB and peripherals.

Next, after the planning stage, we implemented one feature at a time. The first feature was reading in audio using the microphone. The next feature was providing real-time audio visualization through the LED Matrix (as the audio is being played into the microphone). Next, we implemented the recording and playback music feature. Each feature took a few days to a week to implement. 

Finally, once all the features were implemented, we started to integrate the components into the container that housed everything. This involved a lot of testing and assembling. At the end, we succesfully completed audio recording, amplifying, and playback speaker that provides cool visualization features.

### 9. Components

A microphone that can convert an audio signal into an electrical signal between 0V and 5V was used to enable the AtMega328PB to read audio signals using its ADC. The microphone was small in size (in the order of a few centimeters in size). Also, the microphone was of a good quality, and captured sounds with a very high accuracy.

Additionally, a speaker was used to output amplified music. The speaker was able to output high volume sounds (so the user can really immerse themselves). Also, the speaker was of a decent quality for user enjoyment. The speaker operated between 0 and 5V.

Next, LED matrix was used to provide music visualization. We used an LED Matrix to create a 2D screen of lights, which was programmed to output the corresponding audio signals in a brilliant way. The LED matrix was able to interface with the ESP32, that it can be droved by a microcontroller with a higher RAM Size. 

The ESP32 chip used in Lab 4 is utilized to allow the system to write data to the LED Matrix.

### 10. Evaluation

The metric was the sum of the below three metrics:

The first metric was audio visualization quality on a scale of 1-10. We wanted to make sure the audio visualization experience allows the user immerse themselves in the music in another dimension. While this can't be determined objectively, we rank it on a scale of 1-10 based on the device playing songs that we like. We also asked other people to play songs they like on the device and rank the visualization feature from 1 to 10.

The second metric was sound quality on a scale of 1-10. We wanted to make sure the audio being outputted from the device is similar in quality to the audio being read through the microphone. Additionally, the sound complemented the audio visualization feature really well, which meant that the audio quality matched the visualization quality. We ranked this on a scale of 1-10 based on the device playing songs that we like. Like the previous metric, we also ask other people to rank the sound quality from 1 to 10.

The third and final metric is cost. While the device doesn't need to be extremely cheap, we want to make sure that the device is cheaper than most speakers. Therefore, we want the total price of the device to be less than 100 US dollars.

The one metric for evaluating our solution is the sum of these three metrics, where the cost metric is either 10 or 0 (10 if its under 40 dollars and 0 if its at 40 or over).

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task**                                                                          | **Assigned To**    |
|---------------------|-----------------------------------------------------------------------------------|--------------------|
| Week 1: 3/24 - 3/31 |                                                                                   | Nhlanhla and Tim   |
| Week 2: 4/1 - 4/7   | Order parts                                                                       | Tim and Nhlanhla   |
| Week 3: 4/8 - 4/14  | Implement real-time audio visualization using LEDs                                | Nhlanhla           |
| Week 4: 4/15 - 4/21 | Implement reading recording and playback of audio                                 | Nhlanhla and Tim   |
| Week 5: 4/22 - 4/26 | Implement remote control and integrate all components into one device (container) | Nhlanhla and Tim   |

### 12. Proposal Presentation



[Micro-Sounds Official Slides] (https://docs.google.com/presentation/d/1daS6fSF7b5Ld-mRoK1HXKTDMX_lYcx7b/edit?usp=sharing&ouid=101561420450155736831&rtpof=true&sd=true)

## Final Project Report

### 1. Video

[Link](https://www.youtube.com/watch?v=WL8mVhScz18) to a youtube video of the demo.

### 2. Images

![image](https://github.com/ese3500/final-project-micro-music/assets/141350627/2a752ccd-b297-40b8-8c8a-ba9ee18d7ca4)


### 3. Results

Our final design consisted of a music box that supports real-time audio immersion through a large LED screen for visualization and real-time playback through a pair of headphones. The box is also capable of recording and playing back audio.

Our design has two main parts: visualization and audio playback.

For visualization, the input device is a microphone that the AtMega328PB's ADC reads audio data from. The microphone is connected to both the AtMega328PB microcontroller and the 7-series Field Programmable Gate Array.  The ADC in the microcontroller is configured to sample at around 15 kHz and the FPGA is configured to sample at 80KHz. The output device is the large LED matrix. The LED Matrix needed to be driven by a microcontroller with at least 4 KB of RAM, but the AtMega has a limited RAM of around 2 KB and thus cannot drive the LED matrix. Instead we used an ESP32 chip with an internal RAM of 4MBs to drive the LED matrix using amplitude and frequency data recieved from the AtMega 328PB through UART. The visualization works as follows: the AtMega328PB inputs 32 ADC values into a fast fourier transform to get a spectrum of 16 frequencies. This frequency data is then sent via UART to the ESP32, which then outputs the frequency spectrum onto the LED screen. Also, we made sure to include additional bare metal C features on the AtMega328PB. For example, we configured three GPIO pins with pin change interrupts to allow the user to change the color and height of the visualization spectrum as well as turn the screen on and off. Additionally, we configured serial communication at a baud rate of 1 MHz between the AtMega328PB and the ESP32. As a result, the visualization part of our design satisfies three requirements in bare metal C: ADC (for audio sampling), interrupts (for visualization customization), and UART communication (for interfacing between the ESP32 and AtMega328PB). 

While the AtMega328PB's ADC is suitable for audio visualization (anything above 10 kHz is good enough for creating visualization patterns), its sampling rate is not fast enough for audio playback, which we wanted to implemented for the music box. As a result, we utilized an FPGA to also take input from the microphone and sample and store the audio data into 16 DDR3 Banks. Then, once a button is pushed, the FPGA can play the audio back on the speakers. The FPGA also has a real-time playback feature where it can output the audio in real-time through headphones. All these playback features can be used in parallel with the AtMega328PB's visualization, as these two parts are handled in parallel.

As a result, our design consists of a real-time audio visualizer which is controlled by the AtMega328PB and satisfies three bare metal C requirements, as well as an FPGA which handles audio storage and playback, which is an advanced topic, as it was programmed in Verilog (and uses two IPs that are implemented in VHSIC Hardware Description Language).

#### 3.1 Software Requirements Specification (SRS) Results

Overall, we hit almost all of our software requirements. However, there were some requirements that were modified because there were more efficient ways to achieve the same outcome. Because these modifications changed our overall design, we also added some new requirements. These modified/added requirements are discussed below:

<ul>
<li>"The program shall take input audio data via UART from a device that can sample audio from a microphone at a rate of 44.1 kHz. We can test this using serial print to a computer to make sure the right data is being sent." 

This is inefficient because the audio doesn't need to be sampled at 44.1 kHz for visualization (see this [example](https://vanhunteradams.com/Pico/VGA/FFT.html) which uses an ADC at a 10 kHz sampling rate). Instead, the program simply used the AtMega328PB's onboard ADC to sample at 15 kHz, which is suitable for audio visualization because the most prominent frequency in music is less than 7.5KHz. So, we changed this requirement to "the program shall sample audio data from the microphone using its ADC configured to a sampling rate of 15 kHz." This requirement was tested by serial printing the ADC values to the computer, where the ADC values went up when a loud sound was being played and went down when a low sound was being played.</li>
<li><b>ADDED REQUIREMENT: </b>"The audio data from the ADC shall be converted to a frequency spectrum using the Cooley-Tukey Fast FFT Algorithm"

We didn't anticipate this being a requirement before because we thought the FPGA could do the FFT for us. However, because the AtMega328PB is doing the audio sampling via its ADC, the FFT must be implemented on the AtMega328PB using bare metal C. This requirement was partially satisfied. Originally, we wanted to implement the FFT on our own without using an external library. However, it soon became clear that implementing the Cooley-Tukey algorithm involved complicated techniques that would take a while to understand, such as fixed-point arithmetic and bit reversals. Since most of our implementation would have ended up using a lot of another library's ideas, we opted to just use another library, namely Kiss FFT (See Appendix for details).
</li>
<li>"The program shall output the amplitude and frequency data to a speaker using a timer in fast PWM mode, where OCR1A can control the frequency and OCR1B can control the duty cycle (frequency). This can be tested audibly." 

This is inefficient because the sound data is going from time domain to frequency domain and then back to the time domain. So, we changed this requirement to "the FPGA shall sample and store the time domain sound data from the microphone into its internal RAM, from which the audio can be played back." This was tested aurally, where the sound being outputted from the speakers or headphones could be clearly heard and understood.</li>
<li>"The program shall take the input only when a pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this)." 

This is inefficient because just turning off the microphone would mean the AtMega328PB is still sampling audio data from the "off" microphone (essentially ground), processing it using FFT, and then sending it to the ESP32 via UART. Additionally, if the FPGA wants to use the microphone with the audio visualizer being off, this button would prevent the FPGA from sampling audio because the microphone would be off. So, we changed this requirement to "the program shall configure a pin change interrupt for an "off" button that will stop the AtMega328PB's audio sampling polling cycle." This is a much more energy efficient way of "turning off" the audio visualizer and ensures the FPGA can still use the microphone. This requirement was tested visually, where pressing the push button caused the screen to turn off, which means visualization stopped. Pressing the button again caused the visualization to start on the screen again.</li>
</ul>

The rest of the software requirements are discussed below:

<ul>
<li>"The program shall send the amplitude and frequency data from the sampling device to an ESP32 via UART. We can test this using serial print to a computer to make sure the right data is being sent." 

This requirement was completely satisfied. The AtMega328PB sent 16 frequency amplitudes, or in other words, the "prominence" of 16 distinct frequencies, to the ESP32 via UART at a baud rate of 1 MHz. Each frequency "prominence" was normalized to be between 1 through 9, to ensure only one character had to be sent for each frequency, thereby increasing the UART communication speed. This requirement was tested by serial printing UART readings for the ESP32 onto a computer screen. The values followed the frequencies of the music being played into the microphone.
</li>
<li>"The program in the ESP32 shall control how many LEDs are set on based on the amplitude and frequency. The program shall have options for visualization, including just lines for signals and a sine wave. This can be tested visually."

This requirement was satisfied. The outputted frequency spectrum on the LED matrix using 1-width rectangles (lines) was tested visually, where the rectangle heights followed the frequencies of the music being played into the microphone with little to no delay. However, we did not include a sine wave visualization pattern because it resulted in a lot of delay between the music being played and the visualization pattern being outputted. Specifically, the delay was in the order of a few seconds, which is too much for an audio visualizer.
</li>
<li>"The program shall have a GPIO pin change interrupt for a switch, which will determine the visualization mode being displayed. This can be tested visually." 

This requirement was completely satisfied. We had two GPIO pin change interrupts connected to buttons for two visualization parameters: color and frequency spectrum height. The color button simply cycled through 4 possible colors: blue, red, green, and white. The height button increased the overall height of the frequency spectrum from a baseline height of 3 pixels tall to a baseline height of 15 pixels tall. This requirement was tested visually by pressing the buttons and enusring the LED matrix followed the expected behavior.</li>
<li>"Switch debouncing shall be implemented in software and tested visually." 

This requirement was completely satisfied. Button debouncing was implemented in software using the _delay_ms(50) function, which delays the interrupt from executing for 50 milliseconds. This requirement was tested visually, where pressing the buttons did not cause any strange behavior.</li>
</ul>

#### 3.2 Hardware Requirements Specification (HRS) Results

Overall, we hit all of our hardware requirements. However, there were some requirements that were modified because there were more efficient ways to achieve the same outcome. These requirements are discussed below:

<ul>
<li>"The microphone shall be used to convert audio signals into electrical signals, which will be sampled by an FPGA and sent via UART to the AtMega328PB." 

This is inefficient because the AtMega328PB can directly sample the microphone using its ADC at a rate of 15 kHz and still achieve satisfactory visualization. The FPGA still needs to sample the microphone so it can record and store the audio for playback. So, we changed this requirement to "The microphone shall be used to convert audio signals to electrical signals, which will be sampled by the AtMega328PB's ADC and the FPGA." This requirement was tested by serial printing the ADC values to a computer screen and ensuring the ADC values follow noise levels.</li>
<li>"The speaker shall be used to convert the PWM signal generated by the AtMega328PB into audio signals. A potentiometer knob should be used to adjust the speaker's volume." 

As discussed before, the speaker should not take input from a PWM siganl, but rather the time domain audio signals generated from the microphone because converting from time domain to frequency domain and then back to time domain is redundant. Instead, we changed this requirement to "the speaker shall take input from the FPGA's time domain audio electrical signals to playback audio. A potentiometer knob should be used to adjsut the speaker's volume." This requirement was tested aurally, where the playback through both the speaker could be clearly heard and understood.</li>
</ul>

The rest of the requirements are discussed below:

<ul>
<li>"The project shall be based on the AtMega328PB microcontroller." 

This requirement was completely satisfied. The AtMega328PB microcontroller did 90% of the audio visualization work: it sampled audio data via its ADC, converted it to the frequency domain, took button inputs for visualization parameters, and sent frequency data to the ESP32 via UART to display it on the LED screen. The LED Matrix displayed the frequency and amplitude using bars. As a result, the AtMega328PB microcontroller was used heavily and three requirements were satisfied using the AtMega's C code: ADC, interrupts, and UART communication. While the FPGA was used for audio playback, this was just an additional feature that we wanted for the box. The AtMega328PB performed all of the crucial features.</li>
<li>"An LED array shall be used to create a 2D screen where the audio signals can be visualized via the LEDs lighting up." We stress tested the LED Matrix visualization using a frequency generator, and it did well in displaying frequencies that are below 7.5KHz as expected. 

The LED matrix was able to effectively display the audio being played into the microphone using a frequency spectrum consisting of 16 1-pixel wide rectangles of various heights representing the 16 distinct frequencies. There was little to no delay between the audio being played and the LEDs lighting up. This requirement was tested visually, where the visualizer followed the frequencies of the music being played into the microphone.</li>
<li>"The ESP32 chip shall be connected to via UART to the AtMega328PB and will be used to write to the 2D screen." 

This requirement was completely satisfied. There was a jumper wire connecting the AtMega328PB and the ESP32 so frequency data could be sent via UART at a baud rate of 1 MHz. This rate of data transfer was fast enough to make the visualizer have little to no delay. This requirement was tested by serial printing the UART readings for ESP32 onto a computer screen. The values followed the frequencies of the music being played into the microphone.</li>
<li>"Switches shall be used to take user input for selecting visualization modes." 

This requirement was completely satisfied. Two buttons for two different visualization parameters were used to allow the users to select different colors and heights of the visualizer. Through visual testing, the buttons worked properly and were properly debounced in software.</li>
</ul>

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

Overall, we are very proud of the final product of our project. In terms of the evaluation metrics defined in the proposal, the audio visualization is an immersive experience with little to no delay or glitches, so it is a 9/10. The playback sound through the headphones is a 9/10, as the quality is very good. However, the playback sound through the speakers is a 8/10 because the speakers we bought were not great (we ordered 4A, 8Ohms) speakers to prove functionality. For a full scale product, we could use better speakers.  Thus, the overall audio rating is a 7/10. Finally, for cost, we were below $100 (we initially had $40 target, but it wasn't realistic) for the visualization part because the LED matrix alone costed $39, and with the AtMega328PB, microphone, and ESP32, the cost would be over $40, although not by much. So overall, we hit most of our desired metrics and for the cost, we were pretty close to being below $40.

Through this project, we learned a lot about digital signal processing and how real-life audio systems work. For example, we learned that audio can be visualized using a Fast Fourier Transform that converts the time domain audio data into a frequency spectrum. We learned some FFT algorithmic techniques, such as the Cooley-Tukey Algorithm, that made computing this frequency spectrum much quicker. Finally, we learned the importance of sampling frequency when it comes to audio data. Specifically, if audio data needs to be played back, then it needs to sampled at a frequency above 40 kHz. We also learnt an advanced topic, high frequency sampling using an FPGA to solve the sampling frequencies of the microcontroller. 

One aspect of our project we could have done differently is instead of using an FPGA to sample and record audio data for playback, we could have used 3 AtMega328PB's working together to sample the audio data at a frequency of 40 kHz. While this approach certainly seems much complicated due to synchronization and concurrency issues, we still believe there is value in learning how to synchronize three microcontrollers.

One obstacle that we didn't anticipate was driving the LED matrix. While we could use the AtMega328PB to drive a smaller screen, like the LCD screen from Lab 4, the AtMega328PB simply does not have enough internal RAM to drive the large LED matrix we had bought. However, we solved this issue by assisting the AtMega328PB using an ESP32 chip RAM through sending frequency data from the AtMega328PB to the ESP32 via UART.

Finally, in the future, we hope to get the audio visualizer running completely on the FPGA or using 3 AtMega328PBs. The FPGA can sample and perform FFT and a much faster rate than the AtMega328PB, so we are curious as to how different the visualization will look when using the FPGA. We are also curious how to synchronize 3 AtMega328PB's ADCs to sample at above 40 kHz.

## References

   [AtMega 328PB datasheet] (https://ww1.microchip.com/downloads/en/DeviceDoc/40001906A.pdf)
### Appendix

#### Kiss FFT Library

##### Overview 

The [Kiss FFT library](https://github.com/mborgerding/kissfft) was used on the AtMega328PB to convert the time domain audio data obtained from the ADC into a spectrum of frequencies. 

##### Implementation

To implement the ADC library, the kiss_fft_cfg object needed to be declared and initialized in main.c. The first parameter, nfft, is the number of samples to be inputted for each fast fourier transform. The second parameter is a boolean literal representing whether or not the inverse Fast Fourier Transform should be performed (frequency domain to time domain). In our case, we wanted time domain to frequency domain, so this boolean parameter was set to false. The final two parameters, both of which were set to NULL, were to ensure that the FFT object is allocated using the malloc() function. Additionally, two kiss_fft_cpx objects were used as input and output complex number arrays for the FFT function. For inputting into the cx_in array, the ADC values were placed into the real part of the complex number array and 0s were placed into the imaginary part of the array, as there was no phase shift when reading in the ADC values. For the cx_out array, the magnitudes of the prominence of each frequency was calculated by finding the magnitude of each complex number in the array. In this way, the kiss fft library provided a simple way to implement the fast fourier transform on audio ADC values to find a frequency spectrum.

##### How it works

The way Kiss FFT works is it first takes the sound data through cx_in, which represents how loud the sound is at different points in time. Then, it processes this sound data using techniques derived from the Cooley-Tukey algorithm. The basic idea of the algorithm is to turn the difficult problem of performing FFT on 32 data points into two relatively easier problems of performing FFT on 16 data points each. Then, these two easier problems can each be turned into two even easier probelms of 8 data points each, and so on. For this reason, the size of the input must be a power of 2. This is called radix-2 decimation. Additionally, Kiss FFT utilizes "butterfly operations" and complex number operations to convert these easier solved problems back into the solution for the original difficult problem. Finally, Kiss FFT is an "out-of-place" FFT because it stores its input and output arrays in different memory locations, which is why there are separate cx_in and cx_out arrays.


#### P3RGB64x32MatrixPanel library for ESP32 Library

##### Overview

[P3RGB64x32MatrixPanel library for ESP32](https://github.com/NeoCat/ESP32-P3RGB64x32MatrixPanel) was used for drawing on the LED matrix through the ESP32.

##### Implementation
The LED driver was initialized by using the matrix.begin() function. Then, in the main function, the matrix.fillRect(x, y, w, h, color) functions were used to draw the frequency spectrum provided by the AtMega328PB through UART onto the LED matrix. The parameters of the fillRect function are the x and y position of the top left of the rectangle, the width and height of the rectangle relative to its x and y top left position, and finally, the color of the drawn rectangle. For the color of the rectangles, the matrix.color444() function was used to generate the red, green, blue, and white colors. The arduino code ensured that the rectangles represented the frequency spectrum being sent through UART. Additionally, the code didn't need to clear the screen each time a new spectrum was sent. Instead, it updated the heights of each rectangle by adding/deleting parts of the rectangle.

##### How it works
The LED driver library uses SPI to enable communication between the ESP32 and the LED matrix panel. However, because the datasheet of the LED matrix panel does not provide a detail description of how this SPI protocol works, a library was the best option to drive the panel. In the matrix.begin() initialization function, all the pins that are needed for the SPI protocol are configured as output pins and some are written to their required values. For example, the clock and latch pins are pulled down to ensure that no data is being shifted into the LED matrix. It also intializes a timer semaphore to ensure that the task of refreshing the LED matrix is executed periodically. The stop() function is never used in our code, but it disables the timer, which means the screen will no longer refresh. The way the library draws pixels is using the drawPixel function, which utilizes a buffer and sets a single element (which represents a single pixel) in the buffer to the provided color. Next, the draw() function is what actually implements the SPI protocol to "draw" the buffer onto the screen. The function iterates through x and y pixels on the screen, and it uses the cmp and cnt variables along with the inputted color variables r1, g1, and b1 to determine whether the GPIO pin is set or not. Then, it toggles the clock pin (pinCLK) to shift the data into the shift register of the LED matrix. Between each y value (after a row has been iterated through), it sets the pins related to row switching and latch/output enabling, waits a small amount of time to allow the operations to process, and then moves onto the next row (y value). In this way, pixel data is shifted into the internal RAM of the LED matrix to draw pixels on its screen. 

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
