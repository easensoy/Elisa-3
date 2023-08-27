
void setup() {
Serial.begin(9600);

//Setting first four bits high on DDRC and last four low
DDRC &= B11110000;

//Setting last bit high on DDRA
DDRA |= 0b00000001;

//Setting bit high on DDRB
DDRB |= (1<<PB6);

}

void loop() {
  Serial.println(SelectorPosition());

  //If Selector switch is at 0 position do task1
  if(SelectorPosition() == 0)
  {TASK_1();}
  //If Selector switch is at 1 position do task2
  else if(SelectorPosition() == 1)
  {TASK_2();}
  //If Selector switch is at 2 position do task3
  else if(SelectorPosition() == 2)
  {TASK_3();}
  //If Selector switch is at 3 position do task4
  else if(SelectorPosition() == 3)
  {TASK_4();}
}

//Reading Selector switch bits
unsigned char SelectorPosition()
{
  return PINC & 0x0F;
}
