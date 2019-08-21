rf433hmz - A Copyright (c) 2018 Felix Richter <judge@felixrichter.tech>

# About

This is a simple c library which implements encoding and decoding of various rf protocols for sending and recieving rf transmissions. It is heavly based on the RC Switch library. It is designed to be used with the esp8266 using open rtos, but it should be very easy to port to other platforms (by changing the api call in util.h to the ones that your environment provides).

# Notes
Although this code works, it should be noted that the ESP8266 is not an extremly powerfull chip and since this code relies on the CPU to do the recording of the signal length via interrupt and then decoding the signals it takes a lot of CPU time, which will lead to watchdog resets if you are tring to do more stuff at once.

# License

rf433hmz is published under the MIT license.

	Copyright © 2018 Felix Richter <judge@felixrichter.tech>
	
	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE. 
