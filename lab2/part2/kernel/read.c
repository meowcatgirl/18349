#include "include/bits/errno.h"
#include "include/bits/swi.h"
#include "include/bits/fileno.h"
#include <exports.h>

ssize_t read(int fd, void* buf, size_t count){                                  

	char *buffer = (char*) buf;
  int i = 0;
  char newChar;
                                                                              
  int SDRAM_start = 0xa0000000;                                                 
  int SDRAM_end = 0xa3ffffff;                               
  int SDRAM_size = SDRAM_end - SDRAM_start;                                     
                                                                       
  //Case 1: If fd doesn't match stdin                       
  if(fd != STDIN_FILENO) return EBADF;                                          
                                                            
  //Case 2: mem range & size outside range of SDRAM                             
  //void* bend = bptr + count;                                    

  if((count > SDRAM_size) || (buf < (void*)SDRAM_start) || (buf > (void*)SDRAM_end))
     return EFAULT;                                                             
   
  //Case 3: read into buffer                                    
  for(i = 0; i < count; i++){                                                   
	newChar = getc();                                                           
    //EOT character                                                             
    if(newChar == 4){                                                       
      return i;                                                                 
    }                                                                           
                                                                                
    //Backspace or delete character                                             
    else if((newChar == '\b') || (newChar == 127)){                             
        if(i > 0) {                                                             
          puts("\b \b");                                                        
          i -= 2;                                                               
          buffer[i+1] = 0;                                                      
        }                                                                       
        else {                                                                  
          i -= 1;                                                               
        }                                                                       
    }                                                                           
                                                                                
    //Newline or Carriage return characters                                     
    else if((newChar == '\n') || (newChar =='\r')){                
     buffer[i] = '\n';                                                         
      putc('\n');                                                               
      return i;                                                                 
    }                                                                           
                                                                                
    //Regular characters                                                        
    else{                                                                       
      buffer[i] = newChar;                                                      
      putc(newChar);                                                            
    }                                                                           
  }                         
  return count;                                                                 
}                                                                               
                                                                                
                              
