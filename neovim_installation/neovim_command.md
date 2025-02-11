
## commands

 :e path\filename -> create/open path\filename
 :new path\filename  -> open path\filename in split window
 :tabs            -> list of tabs 
 :tabnext(tabprevious) -> next(previous) tab

 :buffers              -> list of buffer
 :bnext (bprevious)    -> next(preious) buffer
  
 :tabe : open file in tab

 :pwd -> current working dir
 :cd  -> change working dir

## build-in autocompletion:
   insert mode + ctlr + n( or p)


## buffers:
  :bnext
  :bprevious
  :enew
  :bd! (close and save buffer)


## tabs:
 gt : switch forward (next tab)
 gT : switch backward

## modes motion as commands:
 :normal I hello world  ====> insert mode hello world into line.

 better usage :
   - select multiple lines (or all files) (vgg)
   - :normal A !!     ===> append !! to all lines
   - :normal I call(" 
   - :normal $x   -> delete the last character
   

## run exteranl commands :! command
   -vgg (select all lines)
   -:!sort |uniq (sort all lines)

## vimgrep
  :vimgrep main **/*.java
  :vimgrep /long string regex/ **/*.c
  :clist  -> all the search result of vimgrep
  :cn     -> next search result 
  :cp     -> previous search result
  :cfirst -> jump to the first search result
  :clast  -> jump to the last search result


## text-objects: 
   - :help text-objects (TODO)


## search and replace :
 - :%s/word1/word2/g  --> repalce all word1 occurences with word2 
 - :s/word1/word2/g   --> replace all word1 occurences with word2 in the current line
 - :%s/word1/word2    --> repalce all first occurences of word1 in each line with word2
 - :%s#/#+#g          --> repalce all occurences of '/' with '+' using '#' as delmiter of search and replace command.
