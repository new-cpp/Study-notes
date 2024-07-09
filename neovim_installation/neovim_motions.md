### 4 modes : 
    - insert
    - visual
    - command (e.g. :w)
    - normal

### anotomie of motion: command count motion

### normal mode :

 ## part one:

    -  hjkl : navigation (left , down, up, right)
    -  w    : jump word by word
    -  b    : jump backwor word by word
    -  d    : delete  
            - dd : delete line
            - 
    - u    :undo action
    - ctrl + r : redo action
    - i    : insert on the left side of the cursor.
    - a    : insert on the right side of the cursor.

    - v   : insert to visual mode (and you can combine with any other motion) 
    - shift + v: visual line mode (add new line to the yanked part)
    - y   : yank
    - p   : paste
 

 ## part two:
    
    - '_' : go to the beginning the sentence.
    - $   : go to the end of the line.
    - 0   : go to the beginning of the line

    - f ( : search onward for the first '('
    - F ( : seach backward for the first '('
    - t ( : jump  to but not on the charchter '('
    - T ( : jump backward but not on the character '('
    - ;   : repeat last command onward
    - ,   : repeat backward

    - I   : insert in the beginning of the line 
    - A   : insert in the end of the line 
    - o   : newline and insert mode.
    - O   : newline above the current line and inset mode


## part three: Vertical movement
   - { : up by paragraph
   - } : down by paragraph
   - ctrl + d: jump half page down
   - ctrl + u : jump half page up
   - G    : jump the end of the buffer 
   - gg   : jump to the beginning of the buffer
   - :line_number    :  jump to line number

   # searching :
     - /string : search for the string 
                 - n        : for next result
                 - shift + n: for prev result
    - ?string  : reverse search ( search upward)

    - * : shortcut for /string (if the string being cut)
    - # : same but for reverse search


   + bonus  zz: center the view
   + bonus  % : jump to the matched ({[ closing character.




### combination command count motion:
 # part one:

    - 8k , 16j , 5w 
    - d3j : delete my current line plus 3 lines below.
    - dw : delete word
    - d2w : delete 2 word
    - db  : delete backward
    - vwy : yank a word
    - y5j : yank 3 line below (without visual mode)
    - yy  : yank a line
 
 # part two:
   
   - d$ : delete till end of the line.
   - df(: delete up to the first '('
   - dt(: delete up to but not include '('
   - yt(: yank up to ...
   - vF= : jump back and hightlight till '='
   - d2f(: delete up to the second (
