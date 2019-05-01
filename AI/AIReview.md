# AI Report

## Game by game analysis
### Teams 13, 24
#### Winner
Team 13 (13v24)
Team 13 (24v13)

#### Overview
Both perform similarly, but Bot 13 is better at optimising for local victory when openings (two in a row) exist.

Given 
: x o o
: x - -
: - - -

if x = 13
: x o o
: x - -
: x - -

if x = 24
: x o o
: x x -
: - - -

**Claim of Similarity:** Have very similar initial game performances, including local boards won.

#### Scope for better performance
1. Improve local performance

2. Block opponent's winning moves (this is already done, but does not seem to work)


### Teams 14, 24
#### Winner
Team 14 (14v24)
Team 14 (24v14)

### Overview





================BigBoard State================

 x o o  x o x  o x o      - - -  x - -  - - -
 o o x  - - -  x - -      - - -  - - -  - - -
 x x -  - - -  - - -      x - -  - x x  - - -

 - - -  - - -  o o -      x - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - x  - - -
 - - -  - - -  - - -      - - -  - - -  - - -

 o o -  o o o  o - -      - - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - -  - - -
 - - -  - x -  - - -      - - -  - - -  - - -

==============SmallBoards States==============
- - -    - - -
- - -    - - -
- o -    - - -
==============================================


('CONTINUE', '-')
================BigBoard State================

 x o o  x o x  o x o      - - -  x - -  - - -
 o o x  - - -  x - -      - - -  - - -  - - -
 x x -  - - -  - - -      x - -  - x x  - - -

 o - -  - - -  o o -      x - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - x  - - -
 - - -  - - -  - - -      - - -  - - -  - - -

 o o -  o o o  o - -      - - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - -  - - -
 - - -  - x -  - - -      - - -  - - -  - - -

==============SmallBoards States==============
- - -    - - -
- - -    - - -
- o -    - - -
==============================================


('CONTINUE', '-')
================BigBoard State================

 x o o  x o x  o x o      - - -  x - -  - - -
 o o x  - - -  x - -      - - -  - - -  - - -
 x x x  - - -  - - -      x - -  - x x  - - -

 o - -  - - -  o o -      x - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - x  - - -
 - - -  - - -  - - -      - - -  - - -  - - -

 o o -  o o o  o - -      - - -  - - -  - - -
 - - -  - - -  - - -      - - -  - - -  - - -
 - - -  - x -  - - -      - - -  - - -  - - -

==============SmallBoards States==============
x - -    - - -
- - -    - - -
- o -    - - -
==============================================


This should not happen