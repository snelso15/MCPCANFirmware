
#ifndef SOURCES_CANCONSTANTS_H_
#define SOURCES_CANCONSTANTS_H_

//misc comments
#define HALF_SEC_WAIT 1000000
#define MODE_SWITCH_WAIT 10000
#define TRANSMIT_BUFFER_WAIT 1000

//spi commands to MCP25625
#define CMD_RESET      0xC0
#define CMD_READ       0x03
#define CMD_WRITE      0x02
#define CMD_LOAD_TX0   0x40
#define CMD_LOAD_TX1   0x42
#define CMD_LOAD_TX2   0x44
#define CMD_RTS_BUF_0  0x81
#define CMD_RTS_BUF_1  0x82
#define CMD_RTS_BUF_2  0x84
#define CMD_READ_STAUS 0xA0
#define CMD_RX_STAUS   0xB0
#define CMD_BIT_MOD    0x05

//register addresses
#define REG_RXF0SIDH    0x00
#define REG_RXF0SIDL    0x01
#define REG_RXF0EID8    0x02
#define REG_RXF0EID0    0x03
#define REG_RXF1SIDH    0x04
#define REG_RXF1SIDL    0x05
#define REG_RXF1EID8    0x06
#define REG_RXF1EID0    0x07
#define REG_RXF2SIDH    0x08
#define REG_RXF2SIDL    0x09
#define REG_RXF2EID8    0x0A
#define REG_RXF2EID0    0x0B
#define REG_CANSTAT     0x0E
#define REG_CANCTRL     0x0F
#define REG_RXF3SIDH    0x10
#define REG_RXF3SIDL    0x11
#define REG_RXF3EID8    0x12
#define REG_RXF3EID0    0x13
#define REG_RXF4SIDH    0x14
#define REG_RXF4SIDL    0x15
#define REG_RXF4EID8    0x16
#define REG_RXF4EID0    0x17
#define REG_RXF5SIDH    0x18
#define REG_RXF5SIDL    0x19
#define REG_RXF5EID8    0x1A
#define REG_RXF5EID0    0x1B
#define REG_TEC         0x1C
#define REG_REC         0x1D
#define REG_RXM0SIDH    0x20
#define REG_RXM0SIDL    0x21
#define REG_RXM0EID8    0x22
#define REG_RXM0EID0    0x23
#define REG_RXM1SIDH    0x24
#define REG_RXM1SIDL    0x25
#define REG_RXM1EID8    0x26
#define REG_RXM1EID0    0x27
#define REG_CNF3        0x28
#define REG_CNF2        0x29
#define REG_CNF1        0x2A
#define REG_CANINTE     0x2B
#define REG_CANINTF     0x2C
#define REG_EFLG        0x2D
#define REG_TXB0CTRL    0x30
#define REG_TXB1CTRL    0x40
#define REG_TXB2CTRL    0x50
#define REG_TXB0DLC     0x35
#define REG_TXB1DLC     0x45
#define REG_TXB2DLC     0x55
#define REG_RXB0CTRL    0x60
#define REG_RXB0SIDH    0x61
#define REG_RXB0SIDL    0x62
#define REG_RXB1CTRL    0x70
#define REG_RXB1SIDH    0x71
#define REG_RXB1SIDL    0x72
#define REG_TXB0SIDH    0x31
#define REG_TXB1SIDH    0x41
#define REG_TXB2SIDH    0x51
#define REG_TXB0SIDL    0x32
#define REG_TXB1SIDL    0x42
#define REG_TXB2SIDL    0x52
#define REG_TXB0D0      0x36
#define REG_TXB1D0      0x46
#define REG_TXB2D0      0x56
#define REG_RXB0D0      0x66
#define REG_RXB1D0      0x76

// cancrtl register values
#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP    0xE0
#define MODE_MASK       0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT    0x08
#define CLKOUT_ENABLE   0x04
#define CLKOUT_DISABLE  0x00
#define CLKOUT_PS1      0x00
#define CLKOUT_PS2      0x01
#define CLKOUT_PS4      0x02
#define CLKOUT_PS8      0x03

// CANINTF register bits
#define RX0IF       0x01
#define RX1IF       0x02
#define TX0IF       0x04
#define TX1IF       0x08
#define TX2IF       0x10
#define ERRIF       0x20
#define WAKIF       0x40
#define MERRF       0x80

//masks
#define SLAVE_MASK_HIGH 0x80
#define SLAVE_MASK_LOW 0x00
#define SLAVE_FILTER 0x80
#define MASTER_MASK_HIGH 0x80
#define MASTER_MASK_LOW 0x00
#define MASTER_FILTER 0x00

//timing values
//10kbps
//TODO- research/update these
#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

//CAN RX values
#define RX_ALL_FILTERS_OFF 0x60
#define RX_ALL_FILTERS_ON 0x00
#define RX_STD 0x20
#define RX_EXT 0x40



#endif /* SOURCES_CANCONSTANTS_H_ */
