//
//  Font data for Arial 48pt
//
#include <stdint.h>
#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif

// Character bitmaps for Arial 48pt
extern const uint8_t arial_48ptBitmaps[] = 
{
  // @0 '0' (30 pixels wide)
  0x00, 0x1F, 0xE0, 0x00, //            ########           
  0x00, 0xFF, 0xFC, 0x00, //         ##############        
  0x01, 0xFF, 0xFE, 0x00, //        ################       
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x07, 0xFF, 0xFF, 0x80, //      ####################     
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x3F, 0xF8, 0x7F, 0xF0, //   ###########    ###########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x07, 0xF8, //  #########           ######## 
  0x7F, 0x80, 0x07, 0xF8, //  ########            ######## 
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xF8, // #########            ######## 
  0x7F, 0x80, 0x0F, 0xF8, //  ########           ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x3F, 0xF8, 0x7F, 0xF0, //   ###########    ###########  
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x07, 0xFF, 0xFF, 0x80, //      ####################     
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x01, 0xFF, 0xFE, 0x00, //        ################       
  0x00, 0xFF, 0xFC, 0x00, //         ##############        
  0x00, 0x1F, 0xE0, 0x00, //            ########           

  // @188 '1' (20 pixels wide)
  0x00, 0x07, 0xF0, //              #######
  0x00, 0x0F, 0xF0, //             ########
  0x00, 0x0F, 0xF0, //             ########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x3F, 0xF0, //           ##########
  0x00, 0x3F, 0xF0, //           ##########
  0x00, 0x7F, 0xF0, //          ###########
  0x00, 0xFF, 0xF0, //         ############
  0x03, 0xFF, 0xF0, //       ##############
  0x07, 0xFF, 0xF0, //      ###############
  0x1F, 0xFF, 0xF0, //    #################
  0x7F, 0xFF, 0xF0, //  ###################
  0xFF, 0xFF, 0xF0, // ####################
  0xFF, 0xFF, 0xF0, // ####################
  0xFF, 0xDF, 0xF0, // ########## #########
  0xFF, 0x9F, 0xF0, // #########  #########
  0xFF, 0x1F, 0xF0, // ########   #########
  0xFC, 0x1F, 0xF0, // ######     #########
  0xF8, 0x1F, 0xF0, // #####      #########
  0xE0, 0x1F, 0xF0, // ###        #########
  0x80, 0x1F, 0xF0, // #          #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x1F, 0xF0, //            #########
  0x00, 0x00, 0x00, //                     

  // @329 '2' (30 pixels wide)
  0x00, 0x1F, 0xF0, 0x00, //            #########          
  0x00, 0x7F, 0xFE, 0x00, //          ##############       
  0x01, 0xFF, 0xFF, 0x80, //        ##################     
  0x03, 0xFF, 0xFF, 0xC0, //       ####################    
  0x07, 0xFF, 0xFF, 0xE0, //      ######################   
  0x0F, 0xFF, 0xFF, 0xF0, //     ########################  
  0x1F, 0xFF, 0xFF, 0xF8, //    ########################## 
  0x1F, 0xFF, 0xFF, 0xF8, //    ########################## 
  0x3F, 0xF8, 0x3F, 0xF8, //   ###########     ########### 
  0x3F, 0xF0, 0x0F, 0xFC, //   ##########        ##########
  0x3F, 0xE0, 0x0F, 0xFC, //   #########         ##########
  0x7F, 0xE0, 0x07, 0xFC, //  ##########          #########
  0x7F, 0xC0, 0x07, 0xFC, //  #########           #########
  0x7F, 0xC0, 0x07, 0xFC, //  #########           #########
  0x07, 0xC0, 0x07, 0xFC, //      #####           #########
  0x00, 0x00, 0x07, 0xFC, //                      #########
  0x00, 0x00, 0x07, 0xF8, //                      ######## 
  0x00, 0x00, 0x0F, 0xF8, //                     ######### 
  0x00, 0x00, 0x0F, 0xF8, //                     ######### 
  0x00, 0x00, 0x1F, 0xF0, //                    #########  
  0x00, 0x00, 0x3F, 0xF0, //                   ##########  
  0x00, 0x00, 0x7F, 0xE0, //                  ##########   
  0x00, 0x00, 0xFF, 0xE0, //                 ###########   
  0x00, 0x01, 0xFF, 0xC0, //                ###########    
  0x00, 0x03, 0xFF, 0x80, //               ###########     
  0x00, 0x07, 0xFF, 0x00, //              ###########      
  0x00, 0x0F, 0xFE, 0x00, //             ###########       
  0x00, 0x1F, 0xFC, 0x00, //            ###########        
  0x00, 0x3F, 0xF8, 0x00, //           ###########         
  0x00, 0x7F, 0xF0, 0x00, //          ###########          
  0x00, 0xFF, 0xE0, 0x00, //         ###########           
  0x01, 0xFF, 0xC0, 0x00, //        ###########            
  0x01, 0xFF, 0x80, 0x00, //        ##########             
  0x03, 0xFF, 0x00, 0x00, //       ##########              
  0x07, 0xFE, 0x00, 0x00, //      ##########               
  0x0F, 0xFC, 0x00, 0x00, //     ##########                
  0x1F, 0xF8, 0x00, 0x00, //    ##########                 
  0x1F, 0xFF, 0xFF, 0xFC, //    ###########################
  0x3F, 0xFF, 0xFF, 0xFC, //   ############################
  0x3F, 0xFF, 0xFF, 0xFC, //   ############################
  0x7F, 0xFF, 0xFF, 0xFC, //  #############################
  0x7F, 0xFF, 0xFF, 0xFC, //  #############################
  0x7F, 0xFF, 0xFF, 0xFC, //  #############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0x00, 0x00, 0x00, 0x00, //                               

  // @517 '3' (30 pixels wide)
  0x00, 0x1F, 0xE0, 0x00, //            ########           
  0x00, 0xFF, 0xF8, 0x00, //         #############         
  0x03, 0xFF, 0xFE, 0x00, //       #################       
  0x07, 0xFF, 0xFF, 0x00, //      ###################      
  0x0F, 0xFF, 0xFF, 0x80, //     #####################     
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x3F, 0xF8, 0x7F, 0xE0, //   ###########    ##########   
  0x3F, 0xF0, 0x3F, 0xF0, //   ##########      ##########  
  0x7F, 0xE0, 0x1F, 0xF0, //  ##########        #########  
  0x7F, 0xE0, 0x1F, 0xF0, //  ##########        #########  
  0x7F, 0xC0, 0x1F, 0xF0, //  #########         #########  
  0x01, 0xC0, 0x1F, 0xF0, //        ###         #########  
  0x00, 0x00, 0x1F, 0xF0, //                    #########  
  0x00, 0x00, 0x3F, 0xE0, //                   #########   
  0x00, 0x00, 0x3F, 0xE0, //                   #########   
  0x00, 0x00, 0xFF, 0xC0, //                 ##########    
  0x00, 0x07, 0xFF, 0x80, //              ############     
  0x00, 0x07, 0xFF, 0x00, //              ###########      
  0x00, 0x07, 0xFE, 0x00, //              ##########       
  0x00, 0x0F, 0xFC, 0x00, //             ##########        
  0x00, 0x0F, 0xFF, 0x00, //             ############      
  0x00, 0x0F, 0xFF, 0xC0, //             ##############    
  0x00, 0x0F, 0xFF, 0xE0, //             ###############   
  0x00, 0x08, 0x3F, 0xF0, //             #     ##########  
  0x00, 0x00, 0x1F, 0xF0, //                    #########  
  0x00, 0x00, 0x0F, 0xF8, //                     ######### 
  0x00, 0x00, 0x0F, 0xF8, //                     ######### 
  0x00, 0x00, 0x07, 0xFC, //                      #########
  0x00, 0x00, 0x07, 0xFC, //                      #########
  0x00, 0x00, 0x07, 0xFC, //                      #########
  0x07, 0x80, 0x07, 0xFC, //      ####            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0xC0, 0x07, 0xFC, // ##########           #########
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xE0, 0x1F, 0xF8, //  ##########        ########## 
  0x7F, 0xF8, 0x7F, 0xF8, //  ############    ############ 
  0x3F, 0xFF, 0xFF, 0xF0, //   ##########################  
  0x3F, 0xFF, 0xFF, 0xF0, //   ##########################  
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x07, 0xFF, 0xFF, 0x80, //      ####################     
  0x03, 0xFF, 0xFE, 0x00, //       #################       
  0x00, 0xFF, 0xFC, 0x00, //         ##############        
  0x00, 0x1F, 0xE0, 0x00, //            ########           

  // @705 '4' (33 pixels wide)
  0x00, 0x00, 0x00, 0x00, 0x00, //                                  
  0x00, 0x00, 0x1F, 0xE0, 0x00, //                    ########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x7F, 0xE0, 0x00, //                  ##########      
  0x00, 0x00, 0x7F, 0xE0, 0x00, //                  ##########      
  0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########      
  0x00, 0x01, 0xFF, 0xE0, 0x00, //                ############      
  0x00, 0x01, 0xFF, 0xE0, 0x00, //                ############      
  0x00, 0x03, 0xFF, 0xE0, 0x00, //               #############      
  0x00, 0x07, 0xFF, 0xE0, 0x00, //              ##############      
  0x00, 0x07, 0xFF, 0xE0, 0x00, //              ##############      
  0x00, 0x0F, 0xFF, 0xE0, 0x00, //             ###############      
  0x00, 0x1F, 0xFF, 0xE0, 0x00, //            ################      
  0x00, 0x1F, 0xFF, 0xE0, 0x00, //            ################      
  0x00, 0x3F, 0xFF, 0xE0, 0x00, //           #################      
  0x00, 0x7F, 0xFF, 0xE0, 0x00, //          ##################      
  0x00, 0x7F, 0xBF, 0xE0, 0x00, //          ######## #########      
  0x00, 0xFF, 0x3F, 0xE0, 0x00, //         ########  #########      
  0x01, 0xFE, 0x3F, 0xE0, 0x00, //        ########   #########      
  0x01, 0xFE, 0x3F, 0xE0, 0x00, //        ########   #########      
  0x03, 0xFC, 0x3F, 0xE0, 0x00, //       ########    #########      
  0x07, 0xF8, 0x3F, 0xE0, 0x00, //      ########     #########      
  0x0F, 0xF8, 0x3F, 0xE0, 0x00, //     #########     #########      
  0x0F, 0xF0, 0x3F, 0xE0, 0x00, //     ########      #########      
  0x1F, 0xE0, 0x3F, 0xE0, 0x00, //    ########       #########      
  0x3F, 0xE0, 0x3F, 0xE0, 0x00, //   #########       #########      
  0x3F, 0xC0, 0x3F, 0xE0, 0x00, //   ########        #########      
  0x7F, 0x80, 0x3F, 0xE0, 0x00, //  ########         #########      
  0xFF, 0x80, 0x3F, 0xE0, 0x00, // #########         #########      
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x3F, 0xE0, 0x00, //                   #########      
  0x00, 0x00, 0x00, 0x00, 0x00, //                                  

  // @940 '5' (31 pixels wide)
  0x00, 0x00, 0x00, 0x00, //                                
  0x03, 0xFF, 0xFF, 0xF8, //       #######################  
  0x03, 0xFF, 0xFF, 0xF8, //       #######################  
  0x03, 0xFF, 0xFF, 0xF8, //       #######################  
  0x07, 0xFF, 0xFF, 0xF8, //      ########################  
  0x07, 0xFF, 0xFF, 0xF8, //      ########################  
  0x07, 0xFF, 0xFF, 0xF8, //      ########################  
  0x07, 0xFF, 0xFF, 0xF8, //      ########################  
  0x07, 0xFF, 0xFF, 0xF8, //      ########################  
  0x0F, 0xFF, 0xFF, 0xF8, //     #########################  
  0x0F, 0xF8, 0x00, 0x00, //     #########                  
  0x0F, 0xF8, 0x00, 0x00, //     #########                  
  0x0F, 0xF8, 0x00, 0x00, //     #########                  
  0x0F, 0xF8, 0x00, 0x00, //     #########                  
  0x1F, 0xF0, 0x00, 0x00, //    #########                   
  0x1F, 0xF0, 0x00, 0x00, //    #########                   
  0x1F, 0xF3, 0xF8, 0x00, //    #########  #######          
  0x1F, 0xFF, 0xFF, 0x00, //    #####################       
  0x1F, 0xFF, 0xFF, 0x80, //    ######################      
  0x3F, 0xFF, 0xFF, 0xC0, //   ########################     
  0x3F, 0xFF, 0xFF, 0xE0, //   #########################    
  0x3F, 0xFF, 0xFF, 0xF0, //   ##########################   
  0x3F, 0xFF, 0xFF, 0xF8, //   ###########################  
  0x3F, 0xFF, 0xFF, 0xF8, //   ###########################  
  0x7F, 0xF0, 0x3F, 0xFC, //  ###########      ############ 
  0x7F, 0xE0, 0x0F, 0xFC, //  ##########         ########## 
  0x07, 0x80, 0x07, 0xFC, //      ####            ######### 
  0x00, 0x00, 0x07, 0xFE, //                      ##########
  0x00, 0x00, 0x03, 0xFE, //                       #########
  0x00, 0x00, 0x03, 0xFE, //                       #########
  0x00, 0x00, 0x03, 0xFE, //                       #########
  0x00, 0x00, 0x03, 0xFE, //                       #########
  0x0F, 0x00, 0x03, 0xFE, //     ####              #########
  0xFF, 0x00, 0x03, 0xFE, // ########              #########
  0xFF, 0x80, 0x03, 0xFE, // #########             #########
  0xFF, 0x80, 0x07, 0xFC, // #########            ######### 
  0x7F, 0xC0, 0x0F, 0xFC, //  #########          ########## 
  0x7F, 0xE0, 0x1F, 0xFC, //  ##########        ########### 
  0x7F, 0xF0, 0x3F, 0xF8, //  ###########      ###########  
  0x3F, 0xFF, 0xFF, 0xF8, //   ###########################  
  0x1F, 0xFF, 0xFF, 0xF0, //    #########################   
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################    
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################     
  0x07, 0xFF, 0xFF, 0x80, //      ####################      
  0x03, 0xFF, 0xFF, 0x00, //       ##################       
  0x00, 0xFF, 0xFC, 0x00, //         ##############         
  0x00, 0x1F, 0xF0, 0x00, //            #########           

  // @1128 '6' (30 pixels wide)
  0x00, 0x0F, 0xF0, 0x00, //             ########          
  0x00, 0x3F, 0xFE, 0x00, //           #############       
  0x00, 0xFF, 0xFF, 0x00, //         ################      
  0x01, 0xFF, 0xFF, 0x80, //        ##################     
  0x07, 0xFF, 0xFF, 0xC0, //      #####################    
  0x07, 0xFF, 0xFF, 0xE0, //      ######################   
  0x0F, 0xFF, 0xFF, 0xE0, //     #######################   
  0x1F, 0xFF, 0xFF, 0xF0, //    #########################  
  0x1F, 0xF8, 0x7F, 0xF0, //    ##########    ###########  
  0x3F, 0xF0, 0x1F, 0xF0, //   ##########       #########  
  0x3F, 0xE0, 0x1F, 0xF8, //   #########        ########## 
  0x3F, 0xC0, 0x0F, 0xF8, //   ########          ######### 
  0x7F, 0xC0, 0x0F, 0x80, //  #########          #####     
  0x7F, 0x80, 0x00, 0x00, //  ########                     
  0x7F, 0x80, 0x00, 0x00, //  ########                     
  0x7F, 0x80, 0x00, 0x00, //  ########                     
  0xFF, 0x80, 0x00, 0x00, // #########                     
  0xFF, 0x87, 0xF0, 0x00, // #########    #######          
  0xFF, 0x9F, 0xFE, 0x00, // #########  ############       
  0xFF, 0x3F, 0xFF, 0x00, // ########  ##############      
  0xFF, 0x7F, 0xFF, 0x80, // ######## ################     
  0xFF, 0xFF, 0xFF, 0xC0, // ##########################    
  0xFF, 0xFF, 0xFF, 0xE0, // ###########################   
  0xFF, 0xFF, 0xFF, 0xF0, // ############################  
  0xFF, 0xFF, 0xFF, 0xF0, // ############################  
  0xFF, 0xF0, 0x7F, 0xF8, // ############     ############ 
  0xFF, 0xE0, 0x1F, 0xF8, // ###########        ########## 
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0x7F, 0x80, 0x07, 0xFC, //  ########            #########
  0x7F, 0x80, 0x07, 0xFC, //  ########            #########
  0x7F, 0x80, 0x07, 0xFC, //  ########            #########
  0x7F, 0x80, 0x07, 0xFC, //  ########            #########
  0x7F, 0xC0, 0x07, 0xFC, //  #########           #########
  0x3F, 0xC0, 0x0F, 0xF8, //   ########          ######### 
  0x3F, 0xE0, 0x1F, 0xF8, //   #########        ########## 
  0x3F, 0xF8, 0x3F, 0xF8, //   ###########     ########### 
  0x1F, 0xFF, 0xFF, 0xF0, //    #########################  
  0x0F, 0xFF, 0xFF, 0xF0, //     ########################  
  0x0F, 0xFF, 0xFF, 0xE0, //     #######################   
  0x07, 0xFF, 0xFF, 0xC0, //      #####################    
  0x03, 0xFF, 0xFF, 0x80, //       ###################     
  0x01, 0xFF, 0xFF, 0x00, //        #################      
  0x00, 0x7F, 0xFC, 0x00, //          #############        
  0x00, 0x0F, 0xF0, 0x00, //             ########          

  // @1316 '7' (30 pixels wide)
  0x00, 0x00, 0x00, 0x00, //                               
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xFC, // ##############################
  0xFF, 0xFF, 0xFF, 0xF8, // ############################# 
  0x00, 0x00, 0x0F, 0xF0, //                     ########  
  0x00, 0x00, 0x1F, 0xE0, //                    ########   
  0x00, 0x00, 0x3F, 0xC0, //                   ########    
  0x00, 0x00, 0x7F, 0xC0, //                  #########    
  0x00, 0x00, 0x7F, 0x80, //                  ########     
  0x00, 0x00, 0xFF, 0x00, //                 ########      
  0x00, 0x01, 0xFF, 0x00, //                #########      
  0x00, 0x01, 0xFE, 0x00, //                ########       
  0x00, 0x03, 0xFE, 0x00, //               #########       
  0x00, 0x03, 0xFC, 0x00, //               ########        
  0x00, 0x07, 0xF8, 0x00, //              ########         
  0x00, 0x07, 0xF8, 0x00, //              ########         
  0x00, 0x0F, 0xF0, 0x00, //             ########          
  0x00, 0x0F, 0xF0, 0x00, //             ########          
  0x00, 0x1F, 0xF0, 0x00, //            #########          
  0x00, 0x1F, 0xE0, 0x00, //            ########           
  0x00, 0x3F, 0xE0, 0x00, //           #########           
  0x00, 0x3F, 0xC0, 0x00, //           ########            
  0x00, 0x3F, 0xC0, 0x00, //           ########            
  0x00, 0x7F, 0xC0, 0x00, //          #########            
  0x00, 0x7F, 0x80, 0x00, //          ########             
  0x00, 0xFF, 0x80, 0x00, //         #########             
  0x00, 0xFF, 0x80, 0x00, //         #########             
  0x00, 0xFF, 0x80, 0x00, //         #########             
  0x00, 0xFF, 0x00, 0x00, //         ########              
  0x01, 0xFF, 0x00, 0x00, //        #########              
  0x01, 0xFF, 0x00, 0x00, //        #########              
  0x01, 0xFF, 0x00, 0x00, //        #########              
  0x01, 0xFF, 0x00, 0x00, //        #########              
  0x01, 0xFE, 0x00, 0x00, //        ########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x03, 0xFE, 0x00, 0x00, //       #########               
  0x00, 0x00, 0x00, 0x00, //                               

  // @1504 '8' (30 pixels wide)
  0x00, 0x3F, 0xF0, 0x00, //           ##########          
  0x01, 0xFF, 0xFE, 0x00, //        ################       
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x0F, 0xFF, 0xFF, 0x80, //     #####################     
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x3F, 0xFF, 0xFF, 0xF0, //   ##########################  
  0x3F, 0xF8, 0x7F, 0xF0, //   ###########    ###########  
  0x7F, 0xE0, 0x1F, 0xF8, //  ##########        ########## 
  0x7F, 0xE0, 0x1F, 0xF8, //  ##########        ########## 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x1F, 0xF8, 0x7F, 0xE0, //    ##########    ##########   
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x07, 0xFF, 0xFF, 0x80, //      ####################     
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x01, 0xFF, 0xFE, 0x00, //        ################       
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x3F, 0xF0, 0x7F, 0xF0, //   ##########     ###########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0x7F, 0xC0, 0x0F, 0xF8, //  #########          ######### 
  0x7F, 0xE0, 0x1F, 0xF8, //  ##########        ########## 
  0x7F, 0xF8, 0x7F, 0xF8, //  ############    ############ 
  0x3F, 0xFF, 0xFF, 0xF0, //   ##########################  
  0x1F, 0xFF, 0xFF, 0xE0, //    ########################   
  0x0F, 0xFF, 0xFF, 0xC0, //     ######################    
  0x07, 0xFF, 0xFF, 0x80, //      ####################     
  0x03, 0xFF, 0xFF, 0x00, //       ##################      
  0x00, 0xFF, 0xFC, 0x00, //         ##############        
  0x00, 0x1F, 0xF0, 0x00, //            #########          

  // @1692 '9' (30 pixels wide)
  0x00, 0x3F, 0xC0, 0x00, //           ########            
  0x00, 0xFF, 0xF8, 0x00, //         #############         
  0x03, 0xFF, 0xFE, 0x00, //       #################       
  0x07, 0xFF, 0xFF, 0x00, //      ###################      
  0x0F, 0xFF, 0xFF, 0x80, //     #####################     
  0x1F, 0xFF, 0xFF, 0xC0, //    #######################    
  0x3F, 0xFF, 0xFF, 0xC0, //   ########################    
  0x3F, 0xFF, 0xFF, 0xE0, //   #########################   
  0x7F, 0xF0, 0x7F, 0xF0, //  ###########     ###########  
  0x7F, 0xE0, 0x1F, 0xF0, //  ##########        #########  
  0x7F, 0xC0, 0x0F, 0xF0, //  #########          ########  
  0xFF, 0x80, 0x0F, 0xF8, // #########           ######### 
  0xFF, 0x80, 0x07, 0xF8, // #########            ######## 
  0xFF, 0x80, 0x07, 0xF8, // #########            ######## 
  0xFF, 0x80, 0x07, 0xF8, // #########            ######## 
  0xFF, 0x80, 0x07, 0xF8, // #########            ######## 
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0x80, 0x07, 0xFC, // #########            #########
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0xFF, 0xC0, 0x0F, 0xFC, // ##########          ##########
  0x7F, 0xE0, 0x1F, 0xFC, //  ##########        ###########
  0x7F, 0xF8, 0x3F, 0xFC, //  ############     ############
  0x3F, 0xFF, 0xFF, 0xFC, //   ############################
  0x3F, 0xFF, 0xFF, 0xFC, //   ############################
  0x1F, 0xFF, 0xFF, 0xFC, //    ###########################
  0x0F, 0xFF, 0xFF, 0xFC, //     ##########################
  0x07, 0xFF, 0xFB, 0xFC, //      ################ ########
  0x03, 0xFF, 0xF3, 0xFC, //       ##############  ########
  0x01, 0xFF, 0xE3, 0xFC, //        ############   ########
  0x00, 0x3F, 0x87, 0xFC, //           #######    #########
  0x00, 0x00, 0x07, 0xFC, //                      #########
  0x00, 0x00, 0x07, 0xF8, //                      ######## 
  0x00, 0x00, 0x07, 0xF8, //                      ######## 
  0x00, 0x00, 0x07, 0xF8, //                      ######## 
  0x07, 0xC0, 0x0F, 0xF8, //      #####          ######### 
  0x7F, 0xC0, 0x0F, 0xF0, //  #########          ########  
  0x7F, 0xE0, 0x1F, 0xF0, //  ##########        #########  
  0x3F, 0xE0, 0x1F, 0xF0, //   #########        #########  
  0x3F, 0xF8, 0x7F, 0xE0, //   ###########    ##########   
  0x3F, 0xFF, 0xFF, 0xE0, //   #########################   
  0x1F, 0xFF, 0xFF, 0xC0, //    #######################    
  0x1F, 0xFF, 0xFF, 0x80, //    ######################     
  0x0F, 0xFF, 0xFF, 0x00, //     ####################      
  0x07, 0xFF, 0xFE, 0x00, //      ##################       
  0x03, 0xFF, 0xFC, 0x00, //       ################        
  0x01, 0xFF, 0xF0, 0x00, //        #############          
  0x00, 0x3F, 0xC0, 0x00, //           ########            
};

struct FONT_CHAR_INFO
{
  uint8_t w;
  uint8_t h;
  uint8_t offset;

};

// Character descriptors for Arial 48pt
// { [Char width in bits], [Char height in bits], [Offset into arial_48ptCharBitmaps in bytes] }
const FONT_CHAR_INFO arial_48ptDescriptors[] = 
{
  {30, 47, 0},    // 0 
  {20, 47, 188},    // 1 
  {30, 47, 329},    // 2 
  {30, 47, 517},    // 3 
  {33, 47, 705},    // 4 
  {31, 47, 940},    // 5 
  {30, 47, 1128},     // 6 
  {30, 47, 1316},     // 7 
  {30, 47, 1504},     // 8 
  {30, 47, 1692},     // 9 
};

