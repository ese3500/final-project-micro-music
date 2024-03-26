[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: Micro Music
    * Team Members: Nhlanhla Mavuso and Tim Liang
    * Github Repository URL: https://github.com/orgs/ese3500/teams/micro-music
    * Github Pages Website URL: [for final submission]
    * Description of hardware: AtMega328PB, Microphone, Speaker, LED strips

## Final Project Proposal

### 1. Abstract

Micro Music is a music recorder, amplifier, and playback speaker that provides awesome multi-colored music visualization using LED strips. Enhance your music listening experience with Micro Music! We will design a highly-differential music box with state of the art music production capablities.  We will use a microphone to take sound as an input from a user, then uses the most advanced Digital Signal Processing (DSP) to sample the sound into frequency and amplitude. We use the sound to amplify the sound, which will be outputted in a speaker. We are also excited to be able to synthesize a realistic visualization of the sound in an array of LED strips.

### 2. Motivation

Most speakers don't provide audio visualization features, and audio visualization software is oftentimes proprietary and expensive. Our device offers a cheap alternative for people who would like to immerse themselves in their music both audibly and visually, without having to go through the hassle of buying software or expensive products.

### 3. Goals

These are to help guide and direct your progress.

<ol>
   <li>Record music and save it into a playable audio file that can be played on the speaker later</li>
   <li>Amplify music using volume control and a speaker in real time</li>
   <li>Provide music visualization features through LED strips</li>
   <li>Ensure the device is cheap and portable</li>
   <li>Ensure the device is user-friendly by making the buttons, screen UI, and knobs very intuitive to use</li>
</ol>

### 4. Software Requirements Specification (SRS)

#### Overview

The software will process the input audio signals from the microphone and ouput the signals through the LED strips and the speaker. It should also be able to store the audio data in an external memory device and read from the memory device to play the audio data on the speaker. Finally, the software should take user input via buttons and potentiometers so the user can interact with the LCD screen.

#### Users

The users of this technology include music producers who want to enhance their sounds, store files, and have a realistic visual output of the sound they create. Users could also include music enjoyers who want to better immerse themselves in the music they like.

#### Definitions and Abbreviations
     
JTAG - Joint Test Action Group

#### Functionality

The program shall take input audio data from an ADC that is connected to the microphone. 

The program shall take the input only when a pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this).

The program shall call a sampling subroutine to convert the analog sound into an amplitude and a frequency.

If the program is in real-time mode (it outputs the audio signals as they are being inputted), the values of the amplitude and frequency shall be used to control how many LEDs should be set on, and how we simulate the frequency. The program shall output amplitude and frequency in the form of a sine wave to the speaker through the speaker pin so the audio signal can be amplified. The sine wave should be generated using a timer in PWM mode and a low pass filter or a software-generated sine wave using a look-up table.

If the program is in recording mode (it is saving the audio signals into an audio file), the audio data should be sent through using a JTAG port to a memory device.

When the program is playing a saved audio file, the audio data shall be sent from the memory device to the AtMega328PB via a JTAG port, where its amplitude and frequency can be outputted to the speaker pin via a sine wave to play the audio. The audio data read from the memory device should be saved in a buffer on the AtMega328PB, so the audio data can be read efficiently while not using up all of the AtMega's memory.

The program shall display a selection of saved audio files on an LCD screen, and allow the user to interact the LCD screen using buttons and pin change interrupts.

### 5. Hardware Requirements Specification (HRS)

#### Overview

The hardware components should be able to convert audio signals into electrical signals and electrical signals into audio signals. The hardware should also include LED lights so the user can visualize the audio data. Finally, the hardware should include interactive components such as an LCD screen, buttons, and potentiometers so the users can adjust volume, select audio files, and choose when to start and stop recording.

#### Definitions and Abbreviations

ADC - Analog to Digital Converter

LCD - Liquid Crystal Display

#### Functionality

The project shall be based on the AtMega328PB microcontroller.

The microphone shall be used to convert audio signals into electrical signals, which can be inputted into the AtMega328PB's ADC.

The speaker shall be used to convert electrical sine waves generated by the AtMega328PB into audio signals. A potentiometer knob should be used to adjust the speaker's volume.

Multiple LED strips lined up together shall be used to create a 2D screen where the audio signals can be visualized via the LEDs lighting up.

An external memory device shall be used to store audio files that can be read and written by the AtMega328PB. The memory device should be able to store at least 5 minutes of audio data.

An LCD screen shall be used to display audio data information.

Push buttons shall be used to enable the user to interact with the LCD screen.

### 6. MVP Demo

What do you expect to accomplish by the first milestone?

By the first milestone, we expect to have all the necessary components ordered. This includes the microphone, speaker, LED strips, and other components like knobs and buttons for volume control. We also expect to have implemented real-time audio visualization and amplification by the first milestone. In other words, when music is played into the device's microphone, the device should be able to output the audio signals through the LED strips and the speaker. We also hope to have implemented adjustable volume control and some visualization options (colors, patterns, etc.). Also, we expect to have obtained and properly modified a container so it can house all the circuitry and sensors as well as the knobs and buttons for volume control, recording music, selecting music files, etc..

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

By the final demonstration, we expect have implemented the audio recording and file storage features. This should allow the user to press a button to start recording, play audio into the microphone of the device, and then stop recording and save the file. Then, through an LCD screen, the user should be able to select and play their desired music files through the speaker and LED light strips. Because the memory space on the AtMega328PB is limited, we will use some external memory storage that the AtMega328PB can send audio data to and read audio data from. We also expect to have fitted all the components (MCU, speaker, microphone, LED strips, circuit parts) into the container with all the user interaction parts (knobs, sensors, and LED light strips) integrated for the user to easily use.  

### 8. Methodology

First, we will outline our design in both software and hardware. For software, we will discuss how each feature will be implemented using software. For example, for recording audio, we could use an interrupt service routine triggered by a button press to start the recording process. We also will defined how the software in the AtMega328PB will interface with peripherals such as the external memory storage device, the microphone, speaker, LED light strips, etc.. This will require reading the datasheets of the various peripherals we have sourced and discussing how the AtMega can properly interface with them using polling/interrupts or serial communication. For hardware, we plan to draw a circuit schematic outlining all the wire connections between the AtMega328PB and peripherals.

Next, after the planning stage, we will implement one feature at a time. The first feature will be reading in audio using the microphone and then amplifying it through the speaker, with adjustable volume control using a potentiometer. The next feature will be providing real-time audio visualization through the LED strips (as the audio is being played into the microphone). Next, we will implement the recording music feature and process of storing the audio data on an external memory storage device. Lastly, we will implement the process by which the AtMega320PB reads audio data from the external memory storage device to play music files through the speaker and the LED light strips. Each feature will hopefully take a few days to a week to implement. 

Finally, once all the features are implemented, we will start to integrate the components into the container that will house everything. This will involve a lot of testing and assembling. By the end, we should have a completed audio recording, amplifying, and playback speaker that provides cool visualization features.

### 9. Components

A microphone that can convert an audio signal into an electrical signal between 0V and 5V is needed to enable the AtMega328PB to read audio signals using its ADC. The microphone is preferably not too big (in the order of a few centimeters in size). Also, the microphone should be good quality, as in it can capture sounds with very high accuracy.

Additionally, a speaker is needed to output amplified music. The speaker should be able to output high volume sounds (so the user can really immerse themselves). Also, the speaker should be of high quality for user enjoyment. The speaker needs to operate between 0 and 5V so it can interface with the AtMega328PB.

Next, LED strips will be used to provide music visualization. We plan to line up multiple LED strips to create an 2D screen of lights, which can then be programmed to output the corresponding audio signals in a cool way. The LED strips should be able to interface with the AtMega328PB, so we can program them to provide audio visualization functionality. Additionally, the strips shouldn't be too long, as we only need a few centimeters of each strip to create a small 2D screen of LEDs. Finally, the LED strips should be using its own power source, which should be battery powered so the entire system is portable.

An external memory storage device is needed so the AtMega can read and write audio files without filling up its own memory. The external memory storage device should be able to quickly and efficiently interface with the AtMega328PB via some form of serial communication (UART, I2C, etc.). Additionally, the storage device should hold enough memory to store a few audio files (5-10) so the user has plenty of songs to play.

The LCD screen given in Lab 4 will be utilized so the user can see which songs are stored on the device, select songs to play, and do other basic functions with the device. Other components such as push buttons and potentiometer knobs will also be used to allow the user to interact with the LCD screen. Finally, passive components such as resistors, capacitors, and inductors will be used when needed in the circuitry.

### 10. Evaluation

What is your metric for evaluating how well your product/solution solves the problem? Think critically on this section. Having a boolean metric such as “it works” is not very useful. This is akin to making a speaker and if it emits sound, albeit however terrible and ear wrenching, declare this a success.
It is recommended that your project be something that you can take pride in. Oftentimes in interviews, you will be asked to talk about projects you have worked on.

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task** | **Assigned To**    |
|----------           |--------- |------------------- |
| Week 1: 3/24 - 3/31 |          |                    |
| Week 2: 4/1 - 4/7   |          |                    |
| Week 3: 4/8 - 4/14  |          |                    |
| Week 4: 4/15 - 4/21 |          |                    |
| Week 5: 4/22 - 4/26 |          |                    |

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.

https://docs.google.com/presentation/d/1Cn8vNzp07OBihLg25p4tsMr9FRUsMsbQ/edit?usp=sharing&ouid=101561420450155736831&rtpof=true&sd=true

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

[Insert final project video here]

### 2. Images

[Insert final project images here]

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
