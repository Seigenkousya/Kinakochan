# kinako-chan 
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 
 [![Build Status](https://travis-ci.com/Seigenkousya/kinako-chan.svg?branch=master)](https://travis-ci.com/Seigenkousya/kinako-chan)
 ![Version](https://img.shields.io/badge/version-1.0.2-orange)
 ![S.I.N](https://img.shields.io/badge/S.I.N-%23003-00aaaa)  

kinako-chan is a programming language that can be programmed like momone-chan.
![](https://pbs.twimg.com/media/DOw0HQDVwAE92LD?format=jpg&name=medium)  

# Install
kinako-chan needs a g++ or clang.  
See [Travis ci](https://travis-ci.com/github/Seigenkousya/kinako-chan) for details.

```terminal
$ git clone https://github.com/Seigenkousya/kinako-chan.git
$ cd kinako-chan
$ make install
```

# Usage
```terminal
$ ./kinako-chan -(h|n|c|s=) terget_file  
	--help(-h) :show help  
	--no-visualize(-n) :only print result  
	--convert(-c) (knk2bf|bf2knk):convert kinako-chan to brainfuck or brainfuck to kinako-chan    
	--speed=(-s=) :demo speed[ms]  
```

## example
```terminal
$ ./kinako-chan -n terget_file
```
kinako-chan defaults to Visualize mode.  
Visualize mode show memory, datapointer, source, brainfuck code, and output.  

![kinako-chan](https://user-images.githubusercontent.com/57716584/81172231-d3f55500-8fd8-11ea-8edc-8fa1ace18cc8.png)

```terminal
$ ./kinako-chan -n terget_file
```
kinako-chan show only result.

```terminal
$ ./kinako-chan -s=100 terget_file
```
kinako-chan stepping every 100ms.

```terminal
$ ./kinako-chan -c knk2bf terget_file.knk
```
convert kinako-chan to brainfuck.

```terminal
$ ./kinako-chan -c bf2knk terget_file.bf
```
convert brainfuck to kinako-chan.


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

## hello world
```
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈孑ちゃん
黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黃奈子ちゃん黃奈子ちゃん黃奈子ちゃん黃奈子ちゃん黃奈子ちゃん
黃奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん
黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黄奈孑ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黃奈子ちゃん
黃奈子ちゃん黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黄奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん
黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黃奈子ちゃん黄奈孑ちゃん
黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん
黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈子ちゃん黃奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黄奈子ちゃん
黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん黃奈子ちゃん黄奈子ちゃん黄奈子ちゃん黄奈子ちゃん黃奈子ちゃん黄奈孑ちゃん
```

# License
The code is released under the MIT License.  
See LICENSE.  

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
