# Simple Chess Search

A simple chess engine, written entirely in C++17. It uses the Negmax algorithm with Alpha-Beta pruning to search for the best moves to make.

https://stackoverflow.com/questions/17003561/using-the-universal-chess-interface
https://www.stmintz.com/ccc/index.php?id=141612

```
./engine 3 10 0 1

           black
8  R  N  B  Q  K  B  N  R 
7  p  p  p  p  p  p  p  p 
6  .  .  .  .  .  .  .  . 
5  .  .  .  .  .  .  .  . 
4  .  .  .  .  .  .  .  . 
3  .  .  .  .  p  .  .  . 
2  p  p  p  p  .  p  p  p 
1  R  N  B  Q  K  B  N  R 
   a  b  c  d  e  f  g  h
           white
           
white e2e3, found after 0.110870 seconds
```
```
./engine -d 3 -thrd 4
e2e3 e7e5 d1h5 d8f6 f1b5 a7a6 b5d3 g7g6
```


## TODO
implement caching strategy
only recaclulate squares on diagonals, file, rank, adjacent and knight positions for to and from square.

reversable moves
	
