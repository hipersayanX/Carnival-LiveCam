# Carnival LiveCam, augmented reality made easy #

![Example of the snow plugin](https://github.com/hipersayanX/Carnival-LiveCam/raw/master/share/screenshots/mainscreen.png)

## Intro ##

After a long time to be developing in the background, finally present my most ambitious project [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam).
[Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) can capture images from multiple sources (webcams, video files, image files), and apply various effects such as effects of rain, fire, masks, 3D effects and 2D of all kinds. And also can take pictures and record video.
[Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) is still in an early stage of development, but it shows many of the features that are able to offer. Is the ideal time to join the the development.
[Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) is licensed under GPLv3 and hosted on [github](https://github.com/).

## Basics ##

The design of [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) is thought to be completely modular and is very easy to expand the program by using plugins based on QtPlugin system, so far the types of plugins available are:

* __Effect__: This type of plugins are responsible for providing the graphics effects for [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam).
* __Drivers__: These plugins are used to add new capture devices. These are not drivers such as the operating system, these drivers do not work at the hardware level, but rather working on a top layer above the operating system drivers, for example these drivers capture images from webcam using OpenCV, or V4L2, but if you have not installed the drivers for your webcam then you can not capture images from your webcam using this driver.
* __Shells__: A shell is a graphical interface or not with which the user can interact with  [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam), this interface may be based on Qt Widgets, QML, Web, command line, etc.. The concept of "shell" comes from the \*nix-like environments such as GNU/Linux where the user can choose the graphical environment with which interact with the computer. [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) also offers the same freedom.

## A small tour ##

At the bottom center of [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) can see the control bar, from left to right the controls are:

* Select the capture device.
* Take a picture.
* Record video.
* Open the Effect Bar.
* Set the window to full screen.
* Information about the program.

![Controls Bar](https://github.com/hipersayanX/Carnival-LiveCam/raw/master/share/screenshots/controlsbar.png)

On the right side of [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) can see the Effect Bar, here we can turn on the effects we want to apply to the video. The effects are activated or deactivated by simply clicking on the preview, the deactivated effects has a red box around, the activated has a green box. Each effect has 3 controls:

* __Upper right__: This control displays if the effect requires or not 3D acceleration.
* __Bottom left__: Displays information about the effect.
* __Bottom right__: You can configure the effect. Only available in some effects.

We can also filter by the type of effect using the combobox at the top.

![The Effect Bar](https://github.com/hipersayanX/Carnival-LiveCam/raw/master/share/screenshots/cadybar.png)

Inside the effect bar we also have the _Effect Stack_, here we can change the order in which each effect is applied.

![The Effect Stack](https://github.com/hipersayanX/Carnival-LiveCam/raw/master/share/screenshots/stackbar.png)

Here we see one of the configuration dialogs of a driver in this case the driver of images. With a simple design intended for an _point&click_ experience.

![This is the configuration dialog for the image driver](https://github.com/hipersayanX/Carnival-LiveCam/raw/master/share/screenshots/imageselect.png)

## Obtain and test Carnival LiveCam ##

To obtain a copy of [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) and start working on the project, run the following command:

    git clone https://github.com/hipersayanX/Carnival-LiveCam.git

To compile and run [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) run the following command:

    cd Carnival-LiveCam
    ./build_all.sh
    ./Carnival-LiveCam

To compile and run [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) need the following software packages:

* [Qt](http://qt.nokia.com/) >= 4.7.x
* [OpenSceneGraph](http://www.openscenegraph.org/projects/osg) >= 3.0.x
* [OpenCV](http://opencv.willowgarage.com/) >= 2.3.x
* [FFmpeg](http://ffmpeg.org/)
* [ffmpegthumbnailer](http://code.google.com/p/ffmpegthumbnailer/) >= 2.xx
* [Doxygen](http://www.doxygen.org/) >= 1.7.5.x
* [Graphviz](http://www.graphviz.org/) >= 2.28.x
* [Texlive-bin](http://www.tug.org/texlive/) >= 2011.x
* [Git](http://git-scm.com/) >= 1.7.x
* [Mscgen](http://www.mcternan.me.uk/mscgen/) >= 0.22

May be you can compile and use [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) with an older versions of the recommended software, I don't know. The environment in which I am currently developing [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) is [Arch Linux](http://www.archlinux.org/) x86_64. The packages needed by Arch Linux are:

    yaourt -S qt openscenegraph opencv ffmpeg ffmpegthumbnailer doxygen graphviz texlive-bin git mscgen

## What we have and what we need ##

In principle, the base of the program is almost finished, so far there are only 3 effects available for trial, which give a small sample of what can be done with the program, a effect that shows how to integrate OpenSceneGraph with [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) for create 3D effects, one showing how to use OpenCV to create effects based on face detection, and finally one that shows how to perform simple 2D effects.
Then there are available a basic driver to capture images from your webcam, and another 2 to capture images from image files and video.
And finally the shell designed in QML.
From what we have left to do:

* As a high priority is the creation of the webcam drivers for Mac OS X and Windows.
* Design a mechanism to capture and display from multiple devices simultaneously, for example, that can show 3 webcams at the same time.
* Ideally, at the time of release the version for end users, [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) must have at least 20 effects that provide different effects that users can apply to their videos.
It would be ideal to have more shells, such as a web interface, a plasmoid for KDE, etc..
* So far [Carnival LiveCam](https://github.com/hipersayanX/Carnival-LiveCam) has no logo or artwork, or a website that identifies it. If you have ideas to share in these areas would be great if you join the development.
* Any other idea that comes to mind.

## And finally... ##

In general, if you know how to use Git then you know how to collaborate with the project. Just clone the repository and start working on your copy and when you have everything up and running do a push request.
Here I leave some links on how to use Git:

* [Pro Git](http://progit.org/book/)
* [Git Immersion](http://gitimmersion.com/)
* [A Visual Git Reference](http://marklodato.github.com/visual-git-guide/index-en.html)

And if anyone is interested in participating in the project is welcome :D

## License ##

    Carnival LiveCam, Augmented reality made easy.
    Copyright (C) 2011  Gonzalo Exequiel Pedone

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.

## Third party content attribution ##

This files are used for testing purposes and showcase examples. Of course, we give the appropriate attribution to their respective authors.

### Images ###

* [girl guroopu - pt.1](http://www.flickr.com/photos/notsogoodphotography/2541637575/) (CC-BY-2.0)
* [Shayna : Pretty Girl in a Mustard field](http://www.flickr.com/photos/arcticpuppy/4362434969/) (CC-BY-2.0)
* [Young Girl Sitting on a Bench at Pedara (small town on the Etna)](http://www.flickr.com/photos/eudaimos/2600474628/) (CC-BY-2.0)
* [Aline : Beautiful French girl smiles](http://www.flickr.com/photos/arcticpuppy/4577080479/) (CC-BY-2.0)
* [IMG_6929](http://www.flickr.com/photos/alarzy/4241112147/) (CC-BY-2.0)
* [katsmile.jpg](http://www.flickr.com/photos/ericmcgregor/124313181/) (CC-BY-2.0)
* [-16](http://www.flickr.com/photos/emerycophoto/3125029861/) (CC-BY-SA-2.0)
* [nice young man](http://www.flickr.com/photos/damienw/2887069687/) (CC-BY-SA-2.0)
* [Pinky Rosay](http://www.flickr.com/photos/macsurak/776688335/) (CC-BY-2.0)
* [Daily Booth???](http://www.flickr.com/photos/robboudon/3802765556/) (CC-BY-2.0)
* [Me at work](http://www.flickr.com/photos/davef3138/3038581433/) (CC-BY-SA-2.0)
* [After](http://www.flickr.com/photos/fboyd/2490262996/) (CC-BY-SA-2.0)
* [tuesday morning](http://www.flickr.com/photos/89186997@N00/5550155624/) (CC-BY-2.0)
