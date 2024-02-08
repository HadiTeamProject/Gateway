# Gateway
This repository contains Arduino code that connect LoRa message with the Firebase database 

## Main objective
Gateway is supposed to connect the LoRa network with the internet network. It is supposed to be deploy in road safety place or anywhere we internet connection is available.

## Components
<li>LoRa REYAX RYLR896</li>
<li>ESP 32</li>

## Circuit Diagram
<img width="394" alt="image" src="https://github.com/HadiTeamProject/Gateway/assets/155265586/e04e5ef5-d64c-47ed-8568-41c0c40f71a5">


<li>ESP32 3.3V = LoRa VDD</li>
<li>ESP32 GND = LoRa GND </li>
<li> ESP32 GPIO 26 = LoRa Rx </li>
<li>ESP32 GPIO 27 = LoRa Tx</li>


### Notes:
<li>use arduino IDE </li> 
<li>LoRa address is 1</li>
<li>LoRa network is 4</li>
<li>LoRa band is 915 MHz</li>
<li>LoRa braud rate is 9600 </li>
