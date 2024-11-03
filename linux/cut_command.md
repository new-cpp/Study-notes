# Cut command:
  
  The cut command is used to extract sections from each line of input data.

  ## example: 
   
   - cut -f 2 -d / /etc/shells  : take the second field with '/' as delimeter

   - cut -f 2- -d / /etc/shells  : take from second field till the end with '/' as delimeter

   - cut -f 2,3 -d /etc/shells 
   
   - cut -f 2-3 -d /etc/shells

   - cut -s -f 2-3 -d /etc/shells : -s just the line that has the delimeter in them 

   


