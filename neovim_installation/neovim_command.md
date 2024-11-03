
## commands

 :e path\filename -> create/open path\filename
 :new path\filename  -> open path\filename in split window
 :tabs            -> list of tabs 
 :tabnext(tabprevious) -> next(previous) tab

 :buffers              -> list of buffer
 :bnext (bprevious)    -> next(preious) buffer
  

## build-in autocompletion:
   insert mode + ctlr + n( or p)


## buffers:
  :bnext
  :bprevious
  :enew
  :bd! (close and save buffer)


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
