# Detection-of-synchronization-between-stereo-frames

<h1> Introduction:</h1>
<p>Detecting synchronization between stereo frames is a critical aspect of stereo vision in computer vision. This process ensures that images captured by two cameras are perfectly aligned in time, eliminating jitter or delays. Achieving synchronization is vital for accurate depth estimation, object tracking, and other computer vision tasks that rely on temporal consistency. The detection involves matching features like edges, textures, and colors between stereo frames and applying transformations for precise alignment.</p>

<h1>Need for Frame Synchronization:</h1>
It is an absolute requirement for efficient video effects or glitch-free source switching.
For moving cameras or objects, temporal asynchrony may lead to spatially displaced views, false parallax and ghosting effects that can have a significant impact on the perceived 3D quality.
To eliminate the relative delay between left and right images.
If the stereo frames are not properly synchronized, the correspondence between the left and right images will be disrupted, which will result in inaccurate depth information and potentially cause problems for 3D reconstruction
<img width="805" alt="motivation" src="https://github.com/Ruchithrt/Detection-of-synchronization-between-stereo-frames/assets/83587252/882cc33b-1f66-4b07-9e02-a3e6944986c1">


<h1>Basic framework for implementation:</h1>
<p>The overall flow consists of two subsystems: 

The Timestamp-Based Algorithm computes
the absolute difference between the timestamps of the left and right images. This calcula-
tion allows for the determination of the time disparity or synchronization status between
the two subsystems.


<img width="280" height="500" alt="motivation" src="https://github.com/Ruchithrt/Detection-of-synchronization-between-stereo-frames/assets/83587252/da248886-18cd-494c-8037-b3bf4679f9b9">
  
The Validation Algorithm, the SSIM algorithm utilized in between. Initially, the pro-
cess begins by converting the RAW images to RGB format. Once in RGB format, the
SSIM algorithm is applied to both the left and right RGB images. The SSIM algorithm
quantifies the structural similarity between the two images, providing a measure of how
similar they are in terms of their content and structure.
<img width="400" height="500" alt="motivation" src="https://github.com/Ruchithrt/Detection-of-synchronization-between-stereo-frames/assets/83587252/95c1abee-e37e-455e-8f89-518615f852cf">


Finally, based on the outputs of both subsystems, the sync decision is determined. Pre-
sumably, the decisions made by the Validation Algorithm and the Timestamp-Based Al-
gorithm are combined or considered together to make the final sync decision. The specifics
of how the outputs are merged or weighted to determine the overall sync decision would
depend on the design and implementation of the algorithm.
<img width="600" height="400" src="https://github.com/Ruchithrt/Detection-of-synchronization-between-stereo-frames/assets/83587252/837c6daf-e072-4ee3-8f40-89d7fa615f08">

The proposed method has been implemented on Jetson AGX orin developer kit developed
by Nvidia. By utilizing the Jetson AGX Orin developer kit, the proposed method can
harness the hardware acceleration capabilities of the platform to significantly improve its
performance. The powerful GPUs and CPUs on the Orin SoC enable efficient parallel
processing of complex algorithms, enabling faster execution and enhanced overall system
performance. The proposed method has been tested on multiple datasets that may present
variations in image quality, lighting conditions, object occlusions, and scene complexity.
By testing the proposed method on multiple datasets, it can be assessed whether the
performance gains achieved with the Jetson AGX Orin developer kit are consistent and
applicable in various real-world settings
<img width="400" height="400" src="https://github.com/Ruchithrt/Detection-of-synchronization-between-stereo-frames/assets/83587252/0c77f297-60ae-4237-a023-eb38a3547451">
</p>

<h1>Application:</h1>
<p>
3D Cinemas: Ensures a seamless and comfortable 3D movie experience by perfectly syncing left and right eye pictures, allowing viewers to appreciate visual effects without discomfort.

VR and AR: Essential for creating realistic and engaging environments in virtual and augmented reality applications. Precise alignment of left and right eye pictures enhances depth perception in gaming, training simulations, and architectural visualization.

Autonomous Vehicles: Enables accurate depth perception, object recognition, and obstacle avoidance in autonomous vehicles. Synchronization in stereo camera configurations enhances the reliability of information, contributing to safer and more efficient autonomous driving systems.

Medical Imaging: Beneficial in medical imaging techniques like laparoscopy and stereoscopic endoscopy. Synchronized stereo pictures aid surgeons in performing minimally invasive surgeries, ensuring safer and more accurate procedures.
</p>

