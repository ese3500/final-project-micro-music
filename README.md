[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: Micro Music
    * Team Members: Nhlanhla Mavuso and Tim Liang
    * Github Repository URL: https://github.com/orgs/ese3500/teams/micro-music
    * Github Pages Website URL: [for final submission]
    * Description of hardware: AtMega328PB, Microphone, Speaker, LED strips

## Final Project Proposal

### 1. Abstract

Micro Music is a music recorder, amplifier, and playback device that provides awesome multi-colored music visualization using LED strips. Enhance your music listening experience with Micro Music! We want to design a highly-differential music box with state of the art music production capablities.  We will use a microphone to take sound as an input from a user, then uses the most advanced Digital Signal Processing (DSP) to sample the sound into frequency and amplitude. We use the sound to amplify the sound, which will be outputted in a speaker. We are also excited to be able to synthesize a realistic visualization of the sound in an array of LED strips.

### 2. Motivation

Most speakers don't provide audio visualization features, and audio visualization software is oftentimes proprietary and expensive. 
Our device offers a cheap alternative for people who would like to immerse themselves in their music both audibly and visually, 
without having to go through the hassle of buying software or expensive products.

### 3. Goals

These are to help guide and direct your progress.

<ol>
   <li>Record music and save into a playable audio file that can be played later</li>
   <li>Amplify music in real time</li>
   <li>Play music at a variety of volumes through a speaker</li>
   <li>Provide music visualization features through LED strips</li>
   <li>Ensure the device is cheap and portable</li>
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

By the first milestone, we expect to have all necessary components ordered. This includes the microphone, speaker, LED strips, and other components like knobs and buttons for volume control. 
We expect to implement real-time audio visualization and amplification by the first milestone. When music is played into the device's microphone, it should be able to output the audio signals through the LED strips and the speaker. We also hope to have implemented adjustable volume control and some visualization options (colors, patterns, etc.). Also, we expect to have obtained and properly modified a container so it can house all the circuitry and sensors as well as the knobs and buttons for volume control, recording music, selecting music files, etc..

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

By the final demonstration, we expect have implemented the audio recording and file storage features. This should allow the user to press a button to start recording, play audio into the microphone of the device, and then stop recording and save the file. Then, through an LCD screen, the user should be able to select and play their desired music files through the speaker and LED light strips. Because the memory space on the AtMega328PB is limited, we will use some external memory storage that the AtMega328PB can send audio data to and read audio data from. We also expected to have fitted everything into the container with all the knobs, sensors, and LED light strips integrated for the user to use.  

### 8. Methodology

What is your approach to the problem?

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
