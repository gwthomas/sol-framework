Welcome to Sol-Framework!
=========================

<h4>Sol is a C++ framework that eases the creation of high-performance 2D games for iOS.</h4>

<b>PLEASE NOTE<b>: This project is still under development and may change significantly between releases.

It is a hobby project for my own pleasure and learning experience, so unless some kind soul volunteers to help out, updates will be made on my own schedule. I wrote this framework from scratch and by myself (except for the 3rd party libraries of course), so there are probably a number of bugs and issues. Suggestions and contributions are welcome! There are comments in the source to explain some things, but I am currently in the process of adding actual documentation and example code.

Efficiency, ease of use, and flexibility are the primary design goals of Sol. If you think there is a way to better accomplish these goals, let me know so I can make any necessary changes.

It should be simple enough to port, since it's written in C++11 using just a bit of Objective-C for the iOS-specific code. The only things that would need to be rewritten are the application lifecycle (setup/teardown/main loop/pause), touch and accelerometer input, and filepath adjustment.

Uses the MIT license (see LICENSE for details)

Features:<br/>
Supports iPhone and iPad, including retina display<br/>
Uses OpenGL ES 2.0<br/>
Scenegraph to allow heirarchy of objects<br/>
Batch rendering of sprites<br/>
TTF font rendering<br/>
Physics with chipmunk<br/>
Smart resource manager avoids loading duplicates of resources<br/>
Audio using ogg vorbis. Stream or load the whole file into memory<br/>
TexturePacker integration for simple sprite sheet creation<br/>

Plans for the future:<br/>
Android<br/>
Networking

Questions? Comments? Suggestions? Email me at gwthomas@berkeley.edu or join the Facebook page for discussion and announcements at http://www.facebook.com/solframework

I hope you enjoy using Sol as much as I enjoy writing it! :) Garrett Thomas
