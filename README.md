# Kinakochan
Kinakochan is a programming language that can be programmed like momone chan.
![](https://pbs.twimg.com/media/DOw0HQDVwAE92LD?format=jpg&name=medium)  

# install
Kinakochan needs a gnu g++.

```terminal
$ git clone https://github.com/Seigenkousya/Kinakochan.git
$ make install
```

# usage
Usage: ./Kinakochan -(h|n|s=) terget_file  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--help(-h) :show help  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--no-visualize(-n) :only print result  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--speed=(-s=) :demo speed[ms]  

## example
```terminal
$ ./Kinakochan -n terget_file
```
Kinakochan show only result.

```terminal
$ ./Kinakochan -s=100 terget_file
```
Kinakochan stepping every 100ms.


# Language specifications
Kinakochan is a multibyte programming language.

|Kinakochan|brainfuck|C language|
|-------|-------|-------|
|黄奈子ちゃん黄奈子ちゃん|+|(\*ptr)++;|
|黄奈子ちゃん黃奈子ちゃん|-|(\*ptr)--;|
|黃奈子ちゃん黄奈子ちゃん|>|ptr++;|
|黃奈子ちゃん黃奈子ちゃん|<|ptr--;|
|黄奈子ちゃん!|.|putchar(\*ptr);|
|黃奈子ちゃん!|,|\*ptr=getchar();|
|黄奈子ちゃん |[|while(\*ptr){|
|黃奈子ちゃん |]|}|


# Author
正弦工社 S.I.N  
Twitter:[@Seigenkousya](https://twitter.com/Seigenkousya)    
homepage:[https://seigenkousya.github.io/](https://seigenkousya.github.io/)  

## maintainer
Takana Norimasa  
Twitter:[@lIlIIllIIIlIlIl](https://twitter.com/lIlIIllIIIlIlIl)  
homepage:[https://takana-norimasa.github.io/blog/](https://takana-norimasa.github.io/blog/)  

