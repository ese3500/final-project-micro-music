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

Micro Music is a group at the University of Pennsylvania that produces the most capable music recorder with an amplifier and playback speaker, that is interfaced with a multicolored LED matrix for sound visualization. Micro-music is committed in providing the best music sampling, amplification, and playback using the cutting edge FPGA and Microcontroller Technology. A user can choose to record any sounds in 16 banks, which they can choos to play at the same time.  Enhance your music listening experience with Micro Music! We have designed a highly-differentiated music box with state of the art music production capablities.  The device uses a microphone to sample sound from a user, and use  Digital Signal Processing (DSP) embedded in an FPGA to sample the sound into frequency and amplitude. The music box uses an amplifier to play back the sound through two speakers. In addition to sound playback, we also show a visualization of the sound through LED matrix. 

### 2. Motivation

Micro-music is deeply invested in improving the recording, playback, and visualization capababilities at a very low cost, to provide music producers the ability to produce any music of their choice without the burden of cost and energy usage. Using a low-powered ATMEGA328PB microcontroller and a 7-series FPGA, we are confident in our ability to improve and shape the recording, playback, and visualization opportunities in the music industry. Micro-music is the change that is needed to accelerate the music industry - and we know it will. 


### 3. Goals

These are to help guide and direct your progress.

<ol>
   <li>Record music and save it into a playable audio file that can be played on the speaker later</li>
   <li>Amplify music using volume control and a speaker in real time</li>
   <li>Provide music visualization features through LED strips</li>
   <li>Ensure the device is cheap and portable</li>
   <li>Ensure the device is user-friendly by making the buttons, and knobs very intuitive to use</li>
</ol>

### 4. Software Requirements Specification (SRS)

#### Overview

The software will process the input audio signals from the microphone and ouput the signals through the LED strips and the speaker. It should also be able to store the audio data using a web server. Finally, the microcontroller should be able to communicate wit ha remote control.

#### Users

Users should include music enjoyers who want to better immerse themselves in the music they like.

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

The ESP32 chip shall be connected to the same pin as the speaker and will be used to write to the 2D screen. 

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

The Raspberry PI will be used to communicate with a web server.

The remote control and volume control knob should be user interaction features.

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
(https://youtu.be/_2FNFVjFbK0)

### 2. Images

[Insert final project images here]
![image](https://github.com/ese3500/final-project-micro-music/assets/141350627/2a752ccd-b297-40b8-8c8a-ba9ee18d7ca4)


### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
