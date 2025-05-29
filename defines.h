#ifndef MN
#define MN
#define SETBIT(word,bitpos) (word|=(1<<bitpos))
#define CLRBIT(word,bitpos) (word&=(~(1<<bitpos)))
#define CPLBIT(word,bitpos) (word^=(1<<bitpos))
#define SSETBIT(word,bitpos) (word=(1<<bitpos))
#define SCLRBIT(word,bitpos) (SSETBIT(word,bitpos))

#define READBIT(word,bitpos) (word>>bitpos &1)
#define READ2BIT(word,bitpos) (word>>bitpos &3)
#define READ3BIT(word,bitpos) (word>>bitpos &7)
#define READNIBBLE(word,bitpos) (word>>bitpos &15)
#define READ6BIT(word,bitpos) (word>>bitpos &63)
#define READBYTE(word,bitpos) (word>>bitpos &255)

#define WRITEBYTE(word,bitpos,data) (word=(word & ~(0xff<<bitpos))|(data<<bitpos))
#define WRITE6BIT(word,bitpos,data) (word=(word & ~(0x3f<<bitpos))|(data<<bitpos))
#define WRITENIBBLE(word,bitpos,data) (word=(word & ~(0xf<<bitpos))|(data<<bitpos))
#define WRITE3BIT(word,bitpos,data) (word=(word & ~(0x7<<bitpos))|(data<<bitpos))
#define WRITE2BIT(word,bitpos,data) (word=(word & ~(0x3<<bitpos))|(data<<bitpos))
#define WRITEBIT(word,bitpos,data) (word=(word & ~(1<<bitpos))|(data<<bitpos))

#endif
