# kinako-chan 
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 
 [![Build Status](https://travis-ci.com/Seigenkousya/kinako-chan.svg?branch=master)](https://travis-ci.com/Seigenkousya/kinako-chan)    

kinako-chan is a programming language that can be programmed like momone-chan.
![](https://pbs.twimg.com/media/DOw0HQDVwAE92LD?format=jpg&name=medium)  

# install
kinako-chan needs a g++ or clang.
See [Travis ci](https://travis-ci.com/github/Seigenkousya/kinako-chan) for details

```terminal
$ git clone https://github.com/Seigenkousya/kinako-chan.git
$ cd kinako-chan
$ make install
```

# usage
```terminal
$ ./kinako-chan -(h|n|s=) terget_file  
	--help(-h) :show help  
	--no-visualize(-n) :only print result  
	--convert(-c) :convert kinako-chan file to brainfuck file.    
	--rev-convert(-r) :convert brainfuck to kinako-chan file.    
	--speed=(-s=) :demo speed[ms]  
```

## example
```terminal
$ ./kinako-chan -n terget_file
```
kinako-chan show only result.

```terminal
$ ./kinako-chan -s=100 terget_file
```
kinako-chan stepping every 100ms.


# Language specifications
kinako-chan is a multibyte programming language.    
It consists of only eight simple token like brainfuck and an instruction pointer.  
  
_kinako-chan is fully Turing complete._  

|kinako-chan|Meaning|brainfuck|C language|
|------------|-------|------|-------|
|黄奈子ちゃん黄奈子ちゃん|increment the data pointer|+|(\*ptr)++;|
|黄奈子ちゃん黃奈子ちゃん|decrement the data pointer|-|(\*ptr)--;|
|黃奈子ちゃん黄奈子ちゃん|increment the byte at the data pointer|>|ptr++;|
|黃奈子ちゃん黃奈子ちゃん|decrement the byte at the data pointer|<|ptr--;|
|黃奈子ちゃん黄奈孑ちゃん|output the byte at the data pointer|.|putchar(\*ptr);|
|黃奈子ちゃん黃奈孑ちゃん|accept one byte of input|,|\*ptr=getchar();|
|黄奈子ちゃん黄奈孑ちゃん|jump to '黄奈子ちゃん黄奈孑ちゃん' <br>if the byte at data pointer is zero|[|while(\*ptr){|
|黄奈孑ちゃん黄奈子ちゃん|jump to '黄奈孑ちゃん黄奈子ちゃん' <br>if the byte at data pointer is zero|]|}|

kinako-chan is a sequence of these commands, possibly interspersed with other characters (which are ignored).  
The commands are executed sequentially, with some exceptions: an instruction pointer begins at the first command, and each command it points to is executed, after which it normally moves forward to the next command. The program terminates when the instruction pointer moves past the last command.   

# Author
正弦工社 S.I.N  
Twitter:[@Seigenkousya](https://twitter.com/Seigenkousya)    
homepage:[https://seigenkousya.github.io/](https://seigenkousya.github.io/)  

## maintainer
Takana Norimasa  
Twitter:[@lIlIIllIIIlIlIl](https://twitter.com/lIlIIllIIIlIlIl)  
homepage:[https://takana-norimasa.github.io/blog/](https://takana-norimasa.github.io/blog/)  

# Thanks
Utau Aizaki (HOUBUNSHA CO.LTD), どうして私が美術科に!?(Why did I enter the Art Course!?)
