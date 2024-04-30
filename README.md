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

Micro Music is a group at the University of Pennsylvania that produces the most capable music recorder with an amplifier and playback speaker, that is interfaced with a multicolored LED matrix for sound visualization. Micro-music is committed in providing the best music sampling, amplification, and playback using the cutting edge FPGA and Microcontroller Technology. A user can choose to record any sounds in 16 banks, which they can choose to play at the same time.  Enhance your music listening experience with Micro Music! We have designed a highly-differentiated music box with state of the art music production capablities.  The device uses a microphone to sample sound from a user, and use  Digital Signal Processing (DSP) embedded in an FPGA to sample the sound into frequency and amplitude. The music box uses an amplifier to play back the sound through two speakers. In addition to sound playback, we also show a visualization of the sound through LED matrix. 

### 2. Motivation

Micro-music is deeply invested in improving the recording, playback, and visualization capababilities at a very low cost, to provide music producers the ability to produce any music of their choice without the burden of cost and energy usage. Using a low-powered ATMEGA328PB microcontroller and a 7-series FPGA, we are confident in our ability to improve and shape the recording, playback, and visualization opportunities in the music industry. Micro-music is the change that is needed to accelerate the music industry - and we know it will. 


### 3. Goals

These are to help guide and direct your progress.

<ol>
   <li>Record music and save it into a playable audio file that can be played on the speaker later</li>
   <li>Amplify music using volume control and a speaker in real time</li>
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

The program shall take input audio data via UART from a device that can sample audio from a microphone at a rate of 44.1 kHz. We can test this using serial print to a computer to make sure the right data is being sent.

The program shall take the input only when a pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this).

The program shall send the amplitude and frequency data from the sampling device to an ESP32 via UART. We can test this using serial print to a computer to make sure the right data is being sent. Then, the program in the ESP32 shall control how many LEDs are set on based on the amplitude and frequency. The program shall have options for visualization, including just lines for signals and a sine wave. This can be tested visually.

The program shall output the amplitude and frequency data to a speaker using a timer in fast PWM mode, where OCR1A can control the frequency and OCR1B can control the duty cycle (frequency). This can be tested audibly.

The program shall have a GPIO pin change interrupt for a switch, which will determine the visualization mode being displayed. This can be tested visually.

Switch debouncing shall be implemented in software and tested visually.

### 5. Hardware Requirements Specification (HRS)

#### Overview

The hardware components should be able to convert audio signals into electrical signals and electrical signals into audio signals. The hardware should also include LED lights so the user can visualize the audio data. Finally, the hardware should include interactive components such as switches and a potentiometer so the users can adjust volume and change visualization modes.

#### Definitions and Abbreviations

#### Functionality

The project shall be based on the AtMega328PB microcontroller.

The microphone shall be used to convert audio signals into electrical signals, which will be sampled by an FPGA and sent via UART to the AtMega328PB.

The speaker shall be used to convert the PWM signal generated by the AtMega328PB into audio signals. A potentiometer knob should be used to adjust the speaker's volume.

An LED array shall be used to create a 2D screen where the audio signals can be visualized via the LEDs lighting up.

The ESP32 chip shall be connected to via UART to the AtMega328PB and will be used to write to the 2D screen.

Switches shall be used to take user input for selecting visualization mode.

### 6. MVP Demo

What do you expect to accomplish by the first milestone?

By the first milestone, we expect to have all the necessary components ordered. This includes the microphone, speaker, LED array, and other components like a knob for volume control. We also expect to have implemented real-time audio visualization by the first milestone. In other words, audio signals should be able to be played through the speaker and visualized through the LED matrix. Additionally, we hope to have implemented audio sampling. Also, we expect to have obtained a container that can house all the circuitry.

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

By the final demonstration, we expect have implemented the audio recording and file storage features. This should allow the user to press a button to start recording, play audio into the microphone of the device, and then stop recording and save the file. Then, through a remote control, the user should be able to select and play their desired music files through the speaker and LED light strips. Because the memory space on the AtMega328PB is limited, we will communicate with a web server via the Raspberry PI where the AtMega328PB can send audio data to and read audio data from. The ESP32 will write to the LED array. We also expect to have fitted all the components (MCU, speaker, microphone, LED strips, circuit parts) into the container with all the user interaction parts (knobs, sensors, and LED light strips) integrated for the user to easily use. 

### 8. Methodology

First, we will outline our design in both software and hardware. For software, we will discuss how each feature will be implemented using software. For example, for recording audio, we will establish that we will use an interrupt service routine triggered by a button press to start the recording process. We also will define how the software in the AtMega328PB will interface with peripherals such as the external memory storage device, the microphone, speaker, LED light strips, etc.. This will require reading the datasheets of the various peripherals we have sourced and discussing how the AtMega can properly interface with them using polling/interrupts or serial communication. For hardware, we plan to draw a circuit schematic outlining all the wire connections between the AtMega328PB and peripherals.

Next, after the planning stage, we will implement one feature at a time. The first feature will be reading in audio using the microphone and then amplifying it through the speaker, with adjustable volume control using a potentiometer. The next feature will be providing real-time audio visualization through the LED strips (as the audio is being played into the microphone). Next, we will implement the recording music feature and the process of storing the audio data a web server using the ESP32 chip. Lastly, we will implement the process by which the AtMega320PB reads audio data from the ESP32 chip to play music files through the speaker and the LED light strips. Each feature will hopefully take a few days to a week to implement. 

Finally, once all the features are implemented, we will start to integrate the components into the container that will house everything. This will involve a lot of testing and assembling. By the end, we should have a completed audio recording, amplifying, and playback speaker that provides cool visualization features.

### 9. Components

A microphone that can convert an audio signal into an electrical signal between 0V and 5V is needed to enable the AtMega328PB to read audio signals using its ADC. The microphone is preferably not too big (in the order of a few centimeters in size). Also, the microphone should be good quality, as in it can capture sounds with very high accuracy.

Additionally, a speaker is needed to output amplified music. The speaker should be able to output high volume sounds (so the user can really immerse themselves). Also, the speaker should be of high quality for user enjoyment. The speaker needs to operate between 0 and 5V so it can interface with the AtMega328PB.

Next, LED strips will be used to provide music visualization. We plan to line up multiple LED strips to create a 2D screen of lights, which can then be programmed to output the corresponding audio signals in a cool way. The LED strips should be able to interface with the AtMega328PB, so we can program them to provide audio visualization functionality. Additionally, the strips shouldn't be too long, as we only need a few centimeters of each strip to create a small 2D screen of LEDs. Finally, the LED strips should be using their own power source, which should be battery powered so the entire system is portable.

The ESP32 chip used in Lab 4 will be utilized to allow the system to write data to the LED array.

### 10. Evaluation

The metric will be the sum of the below three metrics:

The first metric is audio visualization quality on a scale of 1-10. We want to make sure the audio visualization experience allows the user immerse themselves in the music in another dimension. While this can't be determined objectively, we can rank it on a scale of 1-10 based on the device playing songs that we like. We could also ask other people to play songs they like on the device and rank the visualization feature from 1 to 10.

The second metric is sound quality on a scale of 1-10. We want to make sure the audio being outputted from the device is similar in quality to the audio being read through the microphone. Additionally, the sound should complement the audio visualization feature really well, which would mean that the audio quality needs to match the visualization quality. We will rank this on a scale of 1-10 based on the device playing songs that we like. Like the previous metric, we can ask other people to rank from sound quality from 1 to 10.

The third and final metric is cost. While the device doesn't need to be extremely cheap, we want to make sure that the device is cheaper than most speakers. Therefore, we want the total price of the device to be less than 40 dollars.

The one metric for evaluating our solution is the sum of these three metrics, where the cost metric is either 10 or 0 (10 if its under 40 dollars and 0 if its at 40 or over). Hopefully, we can achieve a metric of 30.

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task**                                                                  | **Assigned To**    |
|---------------------|---------------------------------------------------------------------------|--------------------|
| Week 1: 3/24 - 3/31 |                                                                           | Nhlanhla and Tim   |
| Week 2: 4/1 - 4/7   | Order parts                                                               | Tim and Nhlanhla   |
| Week 3: 4/8 - 4/14  | Implement real-time audio visualization using LEDs                        | Nhlanhla           |
| Week 4: 4/15 - 4/21 | Implement reading writing audio data to web server for recording audio    | Nhlanhla and Tim   |
| Week 5: 4/22 - 4/26 | Implement remote control and integrate all components into one device (container) | Nhlanhla and Tim   |

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.

https://docs.google.com/presentation/d/1Cn8vNzp07OBihLg25p4tsMr9FRUsMsbQ/edit?usp=sharing&ouid=101561420450155736831&rtpof=true&sd=true

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

[Link](https://youtu.be/_2FNFVjFbK0) to a youtube video of the demo.

### 2. Images

![image](https://github.com/ese3500/final-project-micro-music/assets/141350627/2a752ccd-b297-40b8-8c8a-ba9ee18d7ca4)


### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

Our final design consisted of a music box that supports real-time audio immersion through a large LED screen for visualization and real-time playback through a pair of headphones. The box is also capable of recording and playing back audio.

Our design has two main parts: visualization and audio playback.

For visualization, the input device is a microphone that the AtMega328PB's ADC reads audio data from. The ADC is configured to sample as fast as possible, which is around 15 kHz. The output device is the large LED matrix. Note that Nick said that it is fine to designate the LED matrix as our output device, as the AtMega328PB can't possibly drive the LED matrix because it doesn't have enough internal RAM, so the AtMega328PB sends display data to the ESP32 which then drives the matrix. The visualization works as follows: the AtMega328PB inputs 32 ADC values into a fast fourier transform to get a spectrum of 16 frequencies. This frequency data is then sent via UART to the ESP32, which then outputts the frequency spectrum onto the LED screen. Also, we made sure to include additional bare metal C features on the AtMega328PB. For example, we configures three GPIO pins with pin change interrupts to allow the user to change the color and height of the visualization spectrum as well as turn the screen on and off. Additionally, we configured serial communication at a baud rate of 1 MHz between the AtMega328PB and the ESP32. As a result, the visualization part of our design satisfies three requirements in bare metal C: ADC (for audio sampling), interrupts (for visualization customization), and UART communication (for interfacing between the ESP32 and AtMega328PB). 

While the AtMega328PB's ADC is suitable for audio visualization (anything above 10 kHz is good enough for creating visualization patterns), its sampling rate is not fast enough for audio playback, which we really wanted to implemented for the music box. As a result, we utilized an FPGA to also take input from the microphone and sample and store the audio data into its internal memory. Then, once a button is pushd, the FPGA can play the audio back on the speakers. The FPGA also has a real-time playback feature where it can output the audio in real-time through headphones. All these playback features can be used in parallel with the AtMega328PB's visualization, as these two parts are handled by separate components.

As a result, our design consists of a real-time audio visualizer which is controlled by the AtMega328PB and satisfies three bare metal C requirements, as well as an FPGA which handles audio storage and playback, which potentially satisfies an advanced topic, as it was programmed in Verilog.

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

Our Software Requirements Specification outlined during the beginning of the project was for a slightly less optimal design. As we implemented the project, we realized there could be significant improvements in the design of the project. Below are the requirements that are no longer relevant because there were more efficient ways to achieve the same outcome.

"The program shall take input audio data via UART from a device that can sample audio from a microphone at a rate of 44.1 kHz. We can test this using serial print to a computer to make sure the right data is being sent." We realized that audio visualization doesn't need to be sampled at 44.1 kHz. As a result, the program simply used the AtMega328PB's onboard ADC to sample at 15 kHz, which is suitable for audio visualization. 

"The program shall output the amplitude and frequency data to a speaker using a timer in fast PWM mode, where OCR1A can control the frequency and OCR1B can control the duty cycle (frequency). This can be tested audibly." This is inefficient because the sound data is going from the time domain to frequency domain and then back to the time domain. Instead, we just stored the time domain data on the FPGA's IRAM and play it back from there.

"The program shall take the input only when a pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this)." The purpose of this requirement was to establish a way to "turn off" the audio visualizer. However, just turning off the microphone would mean the AtMega328PB is still sampling audio data, processing it using FFT, and then sending it to the ESP32 via UART. Additionally, if the FPGA still wants to use the microphone with the audio visualizer being off, this button would prevent the FPGA from sampling audio from the microphone because the microphone would be off. Clearly, this design prevents more use cases and is not energy efficient. So, we configured a pin change interrupt that stopped the AtMega328PB's polling cycle, instead of turning off the microphone. This is a much more energy efficient way of "turning off" the audio visualizer and ensures the FPGA can still use the microphone.

The rest of the software requirements are discsussed below:

"The program shall send the amplitude and frequency data from the sampling device to an ESP32 via UART. We can test this using serial print to a computer to make sure the right data is being sent. Then, the program in the ESP32 shall control how many LEDs are set on based on the amplitude and frequency. The program shall have options for visualization, including just lines for signals and a sine wave. This can be tested visually." This requirement was mostly satisfied. The AtMega328PB sent 16 frequency amplitudes, or in other words, the "prominence" of 16 distinct frequencies, to the ESP32 via UART at a baud rate of 1 MHz. Each frequency "prominence" was normalized to be between 1 through 9, to ensure only one character had to be sent for each frequency, thereby increasing the UART communication speed. However, we did not include a sine wave visualization pattern because it resulted in a lot of delay between the music being played and the visualization pattern being outputted. Specifically, the delay was in the order of a few seconds, which meant that outputting sine waves onto the screen, even using lookup tables, was too inefficient.

"The program shall have a GPIO pin change interrupt for a switch, which will determine the visualization mode being displayed. This can be tested visually." This requirement was completely satisfied. We had two GPIO pin change interrupts connected to buttons for two visualization parameters: color and frequency spectrum height. The color button simply cycled through 4 possible colors: blue, red, green, and white colors for the frequency spectrum. The height button increased the overall height of the frequency spectrum from a baseline height of 3 pixels tall to a baseline height of 15 pixels tall.

"Switch debouncing shall be implemented in software and tested visually." This requirement was completely satisfied. Button debouncing was implemented in software using the _delay_ms(50) function, which delays the interrupt from executing for 50 milliseconds. This was enough time for the button to debounce.

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

Our Hardware Requirements Specification outlined during the beginning of the project was for a slightly less optimal design. As we implemented the project, we realized there could be significant improvements in the design of the project. Below are the requirements that are no longer relevant because there were more efficient ways to achieve the same outcome.

"The microphone shall be used to convert audio signals into electrical signals, which will be sampled by an FPGA and sent via UART to the AtMega328PB." As discussed previously the AtMega328 can also sample audio from the microphone at a frequency of 15 kHz and still achieve satisfactory visualization.

"The speaker shall be used to convert the PWM signal generated by the AtMega328PB into audio signals. A potentiometer knob should be used to adjust the speaker's volume." As discussed before, converting from time domain to frequency domain and then back to tiem domain is inefficient. Instead, the FPGA can stored the audio signals and play the back. As seen in the demo, the FPGA's playback of audio quality is very good. Also, a potentiometer knob was still used to adjust the speaker's volume.

The rest of the requirements are listed below:

"The project shall be based on the AtMega328PB microcontroller." The requirement was completely satisfied. The AtMega328PB microcontroller did 90% of the audio visualization work: it sampled audio data via its ADC, converted it to frequency domain, took button inputs for visualization features, and sent frequency data to the ESP32 via UART to display it on the LED screen. The ESP32 just took in data and dispalyed it with rectangles, which is extremely simple. As a result, the AtMega328PB microcontroller was used heavily and three requirements were satisfied using the AtMega's C code: ADC, interrupts, and UART communication. Thus, the project was based on the AtMega328PB. While the FPGA was used for audio playback, this was just an additional feature that we wanted for the box. The AtMega328PB performed all of the crucial features.

"An LED array shall be used to create a 2D screen where the audio signals can be visualized via the LEDs lighting up." This requirement was completely satisfied." This requirement was completely satisfied. The LED matrix was able to effectively display the audio being played into the microphone using a 16-wide frequency spectrum. There was little to no delay between the audio being played and the LEDs lighting up. Additionally, looking at the visualizaer was a very immersive experience. Personally, I would same the visualization experience is a 7/10.

"The ESP32 chip shall be connected to via UART to the AtMega328PB and will be used to write to the 2D screen." This requirement was completely satisfied. There was a jumper wire connecting the AtMega328PB and the ESP32 so frequency data could be sent via UART at a baud rate of 1 MHz. This rate of data transfer was fast enough to make the visualizer have little to no delay. 

"Switches shall be used to take user input for selecting visualization mode." This requirement was completely satisfied. Two buttons for two different visualization parameters were used to allow the users to select different colors and heights of the visualizer. The buttons work properly and are debounced in software.

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

Overall, we are very proud of the final product of our project. In terms of the evaluation metrics defined in the proposal, the audio visualization is an immersive experience with little to no delay or glitches, so it is a 9/10. The playback sound through the headphones is a 9/10, as the quality is very good. However, the playback sound through the speakers is a 5/10 because the speakers we bought were not great. Thus, the overall audio rating is a 7/10. Finally, for the cost metric, the visualization part alone is much less than 40 dollars ()

The third and final metric is cost. While the device doesn't need to be extremely cheap, we want to make sure that the device is cheaper than most speakers. Therefore, we want the total price of the device to be less than 40 dollars.

Finally, for cost, we clearly went over budget $40 for the visualization part because the LED matrix alone costed $39, and with the AtMega328PB, microphone, and ESP32, it the cost would be over $40, although not by much. The cost of the FPGA was not included because it was implementing a recording and playback feature, which is an additional feature, not what audio visualizers are usually supposed to do. 

So overall, we hit most of our desired metrics and for the cost, we were pretty close to being below $40.

Through this project, we learned a lot about digital signal processing and how real-life audio systems work. For example, we learned that audio can be visualized using a Fast Fourier Transform that converts the time domain audio data into a frequency spectrum. We learned some FFT algorithmic techniques, such as the Cooley-Tukey Algorithm, that made computing this frequency spectrum much quicker. Finally, we learned the importance of sampling frequency when it comes to audio data. Specifically, if audio data needs to be played back, then it needs to sampled at a frequency above 40 kHz.

One aspect of our project we could have done different is instead of using an FPGA to sample and record audio data for playback, we could have used 3 AtMega328PB's working together to sample the audio data at a frequency of 40 kHz. While this approach certainly seems much complicated, it is something that we will consider trying in the future.

One obstacle that we didn't anticipate was driving the LED matrix. While we could use the AtMega328PB to drive a smaller screen, like the LCD screen, the AtMega328PB simply did not have enough internal RAM to drive the large RGB LED matrix we had bought. However, we solved this issue by driving the LED matrix with the ESP32 and sending frequency data from the AtMega328PB to the ESP32 via UART.

Finally, in the future, we hope to get the audio visualizer running completely on the FPGA. The FPGA can sample and perform FFT and a much faster rate than the AtMega328PB, and we are curious as to how different the visualization will look when using the FPGA.

## References

### Appendix

#### Kiss FFT Library

##### Overview 

The [Kiss FFT library](https://github.com/mborgerding/kissfft) was used on the AtMega328PB to convert the time domain audio data obtained from the ADC into a spectrum of frequencies. 

##### Implementation

To implement the ADC library, the kiss_fft_cfg object needed to be declared and initialized in main.c. The first parameter, nfft, is the number of samples to be inputted for each fast fourier transform. The second parameter is a boolean literal representing whether or not the inverse Fast Fourier Transform should be performed (frequency domain to time domain). In our case, we want time domain to frequency domain, so this boolean parameter was set to false. The final two parameters, both of which are set to NULL, are to ensure the FFT object is allocated using the malloc() function. Additionally, two kiss_fft_cpx objects were used as input and output complex number arrays for the FFT function. For inputting into the cx_in array, the ADC values were placed into the real part of the complex number array and 0s were placed into the imaginary part of the array, as there was no phase shift when reading in the ADC values. For the cx_out array, the magnitudes of the prominence of each frequency could be calculated by finding the magnitude of each complex number in the array. In this way, the kiss fft library provided a simple way to implement the fast fourier transform on audio ADC values to find a frequency spectrum.

##### How it works

The way Kiss FFT works is it first takes the input of sound data through cx_in, which represents how loud the sound is at different points in time. Then, it processes this sound data using techniques derived from the Cooley-Tukey algorithm. The basic idea of the algorithm is to turn the difficult problem of performing FFT on 32 data points into two relatively easier problems of performing FFT on 16 data points each. Then, these two easier problems can each be turned into two even easier probelms of 8 data points, and so on. For this reason, the size of the input must be a power of 2. This is called radix-2 decimation. Additionally, Kiss FFT utilizes "butterfly operations" and complex number operations to convert these easier solved problems back into the solution for the original difficult problem. Finally, Kiss FFT is an "out-of-place" FFT because it stores its input and output arrays in different memory locations, which is why there are separate cx_in and cx_out arrays.


#### P3RGB64x32MatrixPanel library for ESP32 Library

##### Overview

[P3RGB64x32MatrixPanel library for ESP32](https://github.com/NeoCat/ESP32-P3RGB64x32MatrixPanel) was used for drawing on the LED matrix through the ESP32.

##### Implementation
The LED driver is initialized by using the matrix.begin() function. Then, in the main function, the matrix.fillRect(x, y, w, h, color) functions were used to draw the frequency spectrum provided by the AtMega328PB through UART onto the LED matrix. The parameters of the fillRect function are the x and y position of the top left of the rectangle, the width and height of the rectangle relative to its x and y top left position, and finally, the color of the draw rectangle. For the color of the rectangles, the matrix.color444() function was used to generate the red, green, blue, and white colors. The arduino code ensures that the rectangles represent the frequency spectrum being sent through UART. Additionally, it doesn't need to clear the screen each time a new spectrum is sent. Instead, it can update the heights of each rectangle by adding/deleting parts of the rectangle.

##### How it works
The LED driver library uses SPI to enable communication between the ESP32 and the LED matrix panel. However, because the datasheet of the LED matrix panel did not provide a detail description of how this SPI protocol works, a library was the best option to drive the panel. In the matrix.begin() initialization function, all the pins that are needed for the SPI protocol are configured as output pins and some are written to their required values. It also intializes a timer semaphore to ensure that the task of refreshing the LED matrix is executed periodically. The stop() functions is never used in our code, but it disables the timer, which means the screen will no longer refresh. The way the library draws pixels is using the drawPixel function, which utilizes a buffer and sets a single element (which represents a single pixel) in the buffer to the provided color. Next, the draw() function is what actually implements the SPI protocol to "draw" the buffer onto the screen. The function iterates through x and y pixels on the screen, and it uses the cmp and cnt variables along with the inputted color variables r1, g1, and b1 to determine whether the GPIO pin is set or not. Then, it toggles the clock pin (pinCLK) to shift the data into the shift register of the LED matrix. Between each y value (after a row has been iterated through), it sets pins related to row switching and latch/output enabling, waits a small amount of time to allow the operations to process, and hen moves on to the next row (y value). In this way, pixel data is shifted into the internal RAM of the LED matrix to draw pixels on its screen. 

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
