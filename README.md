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

The program will take input audio data from a microphone. The program take the input only when a 
pulldown resistor is set on the microphone (it uses a pin change interrupt from a button to accomplish this). 

Once the program successfully inputs data, we call a sampling subroutine to convert the analog sound into 
an amplitude and a frequency. We then use the values of the amplitude and frequency to control how many LEDs should be set on,
and how we simulate the frequency. We have the option of storing the sound through using a JTAG port, to a memory device. 

From the software pesrpective, we also set the pins to a speaker to high to allow it to reproduce the sound.

USERS

The users of this technology are music producers who want to enhance their sounds, store files, and have a realistic
visual output of the sound they create. 

Definition of Terms
     
JTAG 

Joint Test Action Grop

         
### 5. Hardware Requirements Specification (HRS)

Formulate key hardware requirements here.

### 6. MVP Demo

What do you expect to accomplish by the first milestone?

By the first milestone, we expect to have all the necessary components ordered. This includes the microphone, speaker, LED strips, and other components like knobs and buttons for volume control. We also expect to have implemented real-time audio visualization and amplification by the first milestone. In other words, when music is played into the device's microphone, the device should be able to output the audio signals through the LED strips and the speaker. We also hope to have implemented adjustable volume control and some visualization options (colors, patterns, etc.). Also, we expect to have obtained and properly modified a container so it can house all the circuitry and sensors as well as the knobs and buttons for volume control, recording music, selecting music files, etc..

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

By the final demonstration, we expect have implemented the audio recording and file storage features. This should allow the user to press a button to start recording, play audio into the microphone of the device, and then stop recording and save the file. Then, through an LCD screen, the user should be able to select and play their desired music files through the speaker and LED light strips. Because the memory space on the AtMega328PB is limited, we will use some external memory storage that the AtMega328PB can send audio data to and read audio data from. We also expect to have fitted all the components (MCU, speaker, microphone, LED strips, circuit parts) into the container with all the user interaction parts (knobs, sensors, and LED light strips) integrated for the user to easily use.  

### 8. Methodology

First, we will outline our design in both software and hardware. For software, we will discuss how each feature will be implemented using software. For example, for recording audio, we could use an interrupt service routine triggered by a button press to start the recording process. We also will defined how the software in the AtMega328PB will interface with peripherals such as the external memory storage device, the microphone, speaker, LED light strips, etc.. This will require reading the datasheets of the various peripherals we have sourced and discussing how the AtMega can properly interface with them using polling/interrupts or serial communication. For hardware, we plan to draw a circuit schematic outlining all the wire connections between the AtMega328PB and peripherals.

Next, after the planning stage, we will implement one feature at a time. The first feature will be reading in audio using the microphone and then amplifying it through the speaker, with adjustable volume control using a potentiometer. The next feature will be providing real-time audio visualization through the LED strips (as the audio is being played into the microphone). Next, we will implement the feature of recording music and storing the audio data on an external memory storage device. Lastly, we will implement reading from the external memory storage device to play music files through the speaker and the LED light strips. Each feature will hopefully a few days to a week to implement. 

Finally, once all the features are implemented, we will start to integrate the components into the container that will house everything. This will involve a lot of testing and assembling. By the end, we should have a completed audio recording, amplifying, and playback speaker that provides cool visualization features.

### 9. Components

What major components do you need and why?

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
