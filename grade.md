# lab 7  networking (CHEATED)

### something we need to know

1. E1000, a network device, handles network communication. To xv6 (and the driver you write), the E1000 looks like a real piece of hardware connected to a real Ethernet local area network (LAN).

2. On this emulated LAN, xv6 (the "guest") has an IP address of 10.0.2.15. Qemu also arranges for the computer running qemu to appear on the LAN with IP address 10.0.2.2. When xv6 uses the E1000 to send a packet to 10.0.2.2, qemu delivers the packet to the appropriate application on the (real) computer on which you're running qemu (the "host").

3. The ***e1000_init()*** function configures the E1000 to read packets to be transmitted from RAM, and to write received packets to RAM. This technique is called DMA, for direct memory access, referring to the fact that the E1000 hardware directly writes and reads packets to/from RAM.

4. To test your driver, run `make server` in one window, and in another window run `make qemu` and then run `nettests` in xv6. The first test in nettests tries to send a UDP packet to the host operating system, addressed to the program that make server runs. If you haven't completed the lab, the E1000 driver won't actually send the packet, and nothing much will happen.

<br>
TODO:

1. transmit
    * [] ***e1000_transmit()*** with an mbuf that holds the packet to be sent. Your transmit code must place a pointer to the packet data in a descriptor in the TX (transmit) ring. struct tx_desc describes the descriptor format. You will need to ensure that each mbuf is eventually freed, but only after the E1000 has finished transmitting the packet (the E1000 sets the E1000_TXD_STAT_DD bit in the descriptor to indicate this).

2. recv
    * []

