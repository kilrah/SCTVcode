# SCTVcode
SCTV scope clock code

The SCTV Scope Clock from Cathode Corner displays time, words and games on a 3 inch oscilloscope tube, using a Teensy 3.6 computer to generate X-Y-Z signals. 

This code makes it run. 

---

The original code from Cathode Corner has been hacked up to add some new things:

- Adjustmnets to make it easier to add new clock faces/screen modes
- Multi-font support - four additional fonts - and a font demo screen to show them
- Adjustable brightness / greyscale support
- Two calibration creens to help with focusing and centering of the display
- Three new analog clock faces
  - A basic clock with second tick marks and a smoothly moving second hand.
  - The above base clock with a 3d rotating cube in the background
  - The above base clock with a starfield flying by in the background
- Several new digital clock faces
- a 3d spinning cube screen effect
- a starfield screen effect
- two 'memory display' screen effects that plot the content of memory onto the screen

Compiling and installation are the same as for the original code.  However, I suggest adjusting the optimization settings to get slightly better performance (which means less flicker):

Tools -> Optimize -> "Fastest + pure-code with LTO"

The greyscale code requires the brightness knob to be turned up a bit more than before, to allow a somewhat higher dynamic range.  Just play around to find the brightest setting with decent focus.
