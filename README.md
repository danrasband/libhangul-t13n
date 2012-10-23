libhangeul-romaja
=================
A C library for converting between hangeul and roman characters.

TODO
----
* Write specifications
* Write tests

ROADMAP
-------
For now, I'm just going to write down an approximate plan for how I'm
going to code this all out and what it will include.

Requirements
------------
* Open source: What license?
* Cross-platform: Works on Linux and Mac OS X, and later Windows.
* Library (libhangeul-romaja) can be linked to from other C/C++
  programs. (Static or shared).
* Executable (hangeulconv) has the following options:
  * --help : show help message
  * --yale|-y : to or from yale
  * --yale-original|-l : to or from Yale Original
  * --mccune-reischauer|-m : to or from McCune Reischauer
  * --revised|-r : To or from Revised Romanization
  * --input=|-i : Input filename
  * --output=|-o : Output filename
  * --hangeulize|-h : Hangeulize romaja
