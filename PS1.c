#define FOSC 1843200  //Clock speed
#define BAUD 115200
#define MYUBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr)
{
  //Set baud rate
  UBRR0H= (unsigned char)(ubrr>8);
  UBRR0L= (unsigned char)ubrr;
  //Enable receiver and transmitter
  UCSR0B=(1<<RXEN0)|(1<<TXEN0);
  //Set frame format:8data,2 stop bit
  UCSR0C= (1<<USBS0)|(3<<UCSZ00);
  }

  void USART_Transmit(unsigned char data)
  {
    //wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)))
       ;
       //put data into buffer,sends the data
       UDR0=data;
  }

  unsigned char USART_Receive()
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) )
  ;
  /* Get and return received data from buffer */
  return UDR0;
}


  
bool comutare=0; //variabila de stocare
int n=0;
int NR_MAX_LED=7;
void setup() {
  // put your setup code here, to run once:
 //DDRB |= (1 << 1) | (1 << 2) |(1<<3) | (1<<4) | (1<<5);
 DDRB |= (1 << 0);
 DDRD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

 //dezactiveaza intreruperile 
 cli(); 

 
  TCCR1A = 0;// resetarea registrului
  
  TCCR1B = 0;
  
  TCNT1  = 0;//initializeaza val 0 lui TCNT1
  
  //setarea pentru a comuta la interval de 2 secunde(16*10^6/1024*(31249+1)
  //OCR1A = 0x7A11;
  //setarea pentru a comuta la interval de 1 secunde(16*10^6/1024*(15624+1)
  OCR1A=0x3D08;
  //setarea pt a comuta la interval de 0,2 secunde(16*10^6/1024*(3124+1)
  //OCR1A=0x0C34;
  
  // activeaza modul CTC
  TCCR1B |= (1 << WGM12);
  
  // setare pentru prescaler de 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  
  // activeaza intreruperea 
  TIMSK1 |= (1 << OCIE1A);

 //valideaza intreruperile
 sei();
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
ISR(TIMER1_COMPA_vect){ //prima etapa

  if (comutare){
    //PORTB=(1 << 1) | (1 << 2) |(1<<3) | (1<<4) | (1<<5);
    PORTB |= 0x01;
    //PORTD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    PORTD |= 0xFC;


    comutare = 0;
  }
  else{
    //PORTB=(0 << 1) | (0 << 2) |(0<<3) | (0<<4) | (0<<5);
    //PORTB |= (0 << 0);
    //PORTD |= (0 << 2) | (0 << 3) | (0 << 4) | (0 << 5) | (0 << 6) | (0 << 7);
    PORTB &= ~0x01;
    PORTD &= ~0xFC;


    comutare = 1;
  }
}

//creare matrici
/*
int A[]={63,80,63};
int B[]={127,73,85,85,119};
int C[]={62,65,65,65,65};
int D[]={127,65,65,34,28};
int E[]={127,73,73,73,73};
int F[]={127,80,80,80,80};
int G[]={62,65,73,73,78};
int H[]={127,8,8,8,127};
int I[]={65,127,65};
int J[]={3,2,92};
int K[]={127,24,36,66,1};
int L[]={127,1,1,1,1};
int M[]={127,32,16,32,127};
int N[]={127,32,16,8,127};
int O[]={62,65,65,65,62};
int P[]={127,80,80,80,32};
int Q[]={112,72,72,72,63};
int R[]={127,80,88,84,35};
int S[]={1,49,63,69,34};
int T[]={64,64,127,64,64};
int U[]={127,1,1,1,127};
int V[];
int W[];
int X[]={68,40,16,40,68};
int Y[]={64,32,31,32,64};
int Z[]={68,76,84,100,68};
int 1[]={16,32,127};
int 2[]={49,67,69,41,17};
int 3[]={65,81,89,86,36};
int 4[]={8,24,40,31,72};
int 5[]={115,81,81,82,84};
int 6[]={15,21,41,69,39};
int 7[]={64,64,64,64,127};
int 8[]={114,85,73,85,114};
int 9[]={120,89,81,81,127};*/
