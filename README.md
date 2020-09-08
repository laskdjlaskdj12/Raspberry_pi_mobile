# Raspberry_pi_mobile

## WARNING

This is only confirm in IOS 10 Android will be avail soon when QtCreator is stable

This is control raspberry pi GPIO Sorvo Moter with Wiring Pi

source code of Raspberry_pi_dial_device is here
https://github.com/laskdjlaskdj12/Raspberry_pi_mobile

This source code require library in Qt_Json_socket_lib
https://github.com/laskdjlaskdj12/Qt_Json_socket_lib

## Build

== if you don't have Qt_Json_socket_library This is download and build process for Qt_Json_socket_lib ==

1. first install qMake in brew packgemanager
   brew install qt5
   
2. make git clone directory
   mkdir Raspberry_pi_mobile_lib
   cd Raspberry_pi_mobile_lib
   
3. need dependency by Qt_Json_socket library
   git clone https://github.com/laskdjlaskdj12/Qt_Json_socket_lib
  
4. make build directory
   mkdir Build
   
5. build 
   cd Build
   qmake ../Qt_Json_socket_lib/Qt_Json_socket_lib.pro

== this is main process of Raspberry_pi_mobile ==

6. make Raspberry_pi_mobile build directory
   cd ../..
   mkdir Raspberry_pi_mobile

7. download source code 
   git clone https://github.com/laskdjlaskdj12/Raspberry_pi_mobile
   cd Raspberry_pi_mobile
  
8. move after build Qt_Json_socket_lib to Raspberry_pi_mobile directory
   mv ../Raspberry_pi_mobile_lib/Build/Qt_Json_socket_lib.a .
                                                            ^
                                                            |
                                                     (must be write dot)
  
9. make build directory
   mkdir Build
  
10. build
   qmake ../Raspberry_pi_mobile/Boiler_Controler.pro

Licenced by Qt Componey (C) 
CopyRight 2016- 2017 (C) laskdjlaskdj12 allright reserve.
Licenced by GPLv_2 licecne 
